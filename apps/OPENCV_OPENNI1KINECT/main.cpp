//#include <iostream>
//#include <OpenNI.h>
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//serratomau@yahoo.com

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cvblob.h>
#include <opencv2/opencv.hpp>
#include <OpenNI.h>

#include <tchar.h>
#include <math.h>
#include "vrpn_Text.h"
#include "vrpn_Tracker.h"
#include "vrpn_Analog.h"
#include "vrpn_Button.h"
#include "vrpn_Connection.h"

#include <iostream>
#include <vector>


using namespace cv;
using namespace cvb;
using namespace std;








/////////////////////// ANALOG /////////////////////////////

// your analog class must inherin from the vrpn_Analog class
class myAnalog : public vrpn_Analog
{
public:
	myAnalog( vrpn_Connection *c = 0 );
	virtual ~myAnalog() {};
	virtual void mainloop();
	void setPositionXY(vector <float>);

protected:
	vector<float> PosicionXY;
	struct timeval _timestamp;
};


myAnalog::myAnalog( vrpn_Connection *c /*= 0 */ ) :
	vrpn_Analog( "Analog0", c )
{
	vrpn_Analog::num_channel = 2;

	vrpn_uint32    i;

	for (i = 0; i < (vrpn_uint32)vrpn_Analog::num_channel; i++) {
		vrpn_Analog::channel[i] = vrpn_Analog::last[i] = 0.0;
		PosicionXY.push_back(0.0);
	}
}

void myAnalog::mainloop()
{
	vrpn_gettimeofday(&_timestamp, NULL);
	vrpn_Analog::timestamp = _timestamp;

	// forcing values to change otherwise vrpn doesn't report the changes
	static float f = 0; f+=0.001;

	for( unsigned int i=0; i<vrpn_Analog::num_channel;i++)
	{
		// XXX Set your values here !
		channel[i] = PosicionXY[i];
	}

	// Send any changes out over the connection.
	vrpn_Analog::report_changes();

	server_mainloop();
}

void myAnalog::setPositionXY(vector <float> Positions)
{
	if (Positions.size() < (vrpn_uint32)vrpn_Analog::num_channel)
		return;

	PosicionXY.clear();
	vrpn_uint32    i;
	for (i = 0; i < (vrpn_uint32)vrpn_Analog::num_channel; i++) {
		PosicionXY.push_back(Positions[i]);
	}
}











int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

int threshold_value = 5;
int threshold_value2 = 16;
int MinSize = 2;
int MaxSize = 30;
int threshold_type = 3;;
int const max_value = 255;
int const max_value_size = 100;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
IplImage* image2;
IplImage *chB;
IplImage *labelImg;
CvTracks tracks;
vector <float> P;
int const NumChannels = 2;

float P0=0.0;

char* window_name = "Kinect Depth Filtering and Blob Tracking";

//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";

char* trackbar_MinDistValue = "Min. Dist:";
char* trackbar_MaxDistValue = "Max. Dist:";

char* trackbar_MinDistSize = "Min. (%) Image Size";
char* trackbar_MaxDistSize = "Max. (%) Image Size";



void TrackObjects( int, void* );


cv::Mat getColorImage(openni::VideoFrameRef& color_frame)
{
	if(!color_frame.isValid())
	{
		return cv::Mat();
	}
	openni::VideoMode video_mode = color_frame.getVideoMode();
	cv::Mat color_img = cv::Mat(video_mode.getResolutionY(),
		video_mode.getResolutionX(),
		CV_8UC3, (char*)color_frame.getData());
	cv::Mat ret_img;
	cv::cvtColor(color_img, ret_img, CV_RGB2BGR);
	return ret_img;
}


// CV_16U
cv::Mat getDepthImage(openni::VideoFrameRef& depth_frame)
{
	if(!depth_frame.isValid())
	{
		return cv::Mat();
	}

	openni::VideoMode video_mode = depth_frame.getVideoMode();
	cv::Mat depth_img = cv::Mat(video_mode.getResolutionY(),
		video_mode.getResolutionX(),
		CV_16U, (char*)depth_frame.getData());
	return depth_img.clone();
}


cv::Mat getDepthDrawableImage(cv::Mat depth_image)
{
	cv::Mat drawable;
	depth_image.convertTo(drawable, CV_8UC1, 255.0/10000);
	drawable = drawable; 
	return drawable;
}

void TrackObjects( int, void* )
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/

	inRange(src_gray, cv::Scalar(threshold_value), cv::Scalar(threshold_value2), dst);
	//cout << threshold_value <<" "<< threshold_value2 << endl;
	//threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

	Mat src_gray3channel;
	cvtColor(src_gray, src_gray3channel, CV_GRAY2BGR);
	rectangle(src_gray3channel, Point(0,0), Point(640 - 4, 480 - 2), Scalar(0,0,255), 4);

	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator + 2;

	Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

	/// Apply the specified morphology operation
	morphologyEx( dst, dst, operation, element );



	Mat dst2;
	cvtColor(dst, dst2, CV_GRAY2BGR);


	IplImage ipltemp=dst2;
	cvCopy(&ipltemp,image2);
	//cvShowImage("Hola", image2);

	cvThreshold(image2, image2, 100, 255, CV_THRESH_BINARY);
	//IplImage *chB=cvCreateImage(cvGetSize(image2),8,1);
	cvSplit(image2,chB,NULL,NULL,NULL);

	//IplImage *labelImg = cvCreateImage(cvGetSize(image2), IPL_DEPTH_LABEL, 1);

	CvBlobs blobs;
	unsigned int result = cvLabel(chB, labelImg, blobs);

	cvFilterByArea(blobs, int((float(MinSize)/100.0)*(640*480)), int((float(MaxSize)/100.0)*(640*480)));

	cvUpdateTracks(blobs, tracks, 5., 10);
	//cvUpdateTracks(blobs, tracks, 10., 5);
	//cout <<"Num Blobs = " << blobs.size() << endl;
	cvRenderBlobs(labelImg, blobs, image2, image2, CV_BLOB_RENDER_CENTROID|CV_BLOB_RENDER_BOUNDING_BOX);
	cvRenderTracks(tracks, image2, image2, CV_TRACK_RENDER_ID|CV_TRACK_RENDER_BOUNDING_BOX);

	if(blobs.size() < 1)
	{
		P.clear();
		for (int i=0; i<NumChannels; i++) P.push_back(0.0);
		
	}else{
		P.clear();
		for (int i=0; i<NumChannels; i++) P.push_back(0.0);

		CvLabel Label = cvLargestBlob(blobs);
		//cout <<"Largest Blob = " << Label << endl;
	    for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
	    {
	        CvLabel label = (*it).second->label;
			if(Label == label)
			{
				CvPoint2D64f XY = (*it).second->centroid;
				P0 = XY.x;
				P.push_back(XY.x); P.push_back(XY.y);
				cout <<"Largest Blob "<< Label <<" = ( " << XY.x << " , " << XY.y <<" )" << endl;
			}
	    }
	}

	//cvShowImage("test_tracking", image2);

	cvReleaseBlobs(blobs);

	//cvReleaseImage(&chB);
	//cvReleaseImage(&labelImg);

	dst = Mat(image2, true);
	rectangle(dst, Point(0,0), Point(640, 480), Scalar(0,255,0), 5);
	Size sz1 = src_gray3channel.size();
	Size sz2 = dst.size();
	Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
	Mat left(im3, Rect(0, 0, sz1.width, sz1.height));
	src_gray3channel.copyTo(left);
	Mat right(im3, Rect(sz1.width, 0, sz2.width, sz2.height));
	dst.copyTo(right);
	//imshow("im3", im3);

	imshow( window_name, im3 );


}

int main(int argc, char** argv)
{
	openni::Device device;
	openni::VideoStream color_stream, depth_stream;
	const char* deviceURI = openni::ANY_DEVICE;

	openni::Status rc = openni::STATUS_OK;

	rc = openni::OpenNI::initialize();

	cout << "After initialization:" << openni::OpenNI::getExtendedError();

	rc = device.open(deviceURI);
	if (rc != openni::STATUS_OK)
	{
		cout << "SimpleViewer: Device open failed:" << openni::OpenNI::getExtendedError();
		openni::OpenNI::shutdown();
		return 1;
	}

	rc = depth_stream.create(device, openni::SENSOR_DEPTH);
	if (rc == openni::STATUS_OK)
	{
		rc = depth_stream.start();
		if (rc != openni::STATUS_OK)
		{
			cerr << "SimpleViewer: Couldn't start depth stream:" << openni::OpenNI::getExtendedError();
			depth_stream.destroy();
		}
	}
	else
	{
		cerr << "SimpleViewer: Couldn't find depth stream:" << openni::OpenNI::getExtendedError();
	}

	rc = color_stream.create(device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK)
	{
		rc = color_stream.start();
		if (rc != openni::STATUS_OK)
		{
			cerr << "SimpleViewer: Couldn't find color stream:" << openni::OpenNI::getExtendedError();
			color_stream.destroy();
		}
	}
	else
	{
		cerr << "SimpleViewer: Couldn't find color stream:" << openni::OpenNI::getExtendedError();
	}

	if (!depth_stream.isValid() || !color_stream.isValid())
	{
		cerr << "SimpleViewer: No valid streams. Exiting" << std::endl;
		openni::OpenNI::shutdown();
		return 2;
	}


	std::vector<openni::VideoStream*> streams;
	streams.push_back(&color_stream);
	streams.push_back(&depth_stream);

	openni::VideoFrameRef color_frame;
	openni::VideoFrameRef depth_frame;

	device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);


	VideoCapture cap(argv[1]); // open the default camera
	vector <Mat> Video;
	int NumberOfFrames=0;
	cout<<endl;
	cout<<endl;
	int frameInicial = atoi(argv[2]);
	int frameFinal = atoi(argv[3]);
	NumberOfFrames = frameInicial;

	
    if(!cap.isOpened())  // check if we succeeded
	{
		cout<<"Could Not Load Video: " << argv[1] << endl;
	}else{
		cout<<"Loading Video..."<<endl;
		Mat frame_video;
		int Nframes = 0;
		while(Nframes < frameInicial){
			cap >> frame_video;	
			if (frame_video.empty()) 
				break; 
			Nframes++;
		}

		for(;;){
			cap >> frame_video;
			if (frame_video.empty()) break;
			Video.push_back(frame_video.clone());
			//imshow("Video", frame_video);
			//waitKey(1);
			NumberOfFrames++;
			if (NumberOfFrames>frameFinal) break;
		}
		NumberOfFrames = frameFinal - frameInicial;
		cout<<"Video Succesfully Loaded"<<endl;
		cout<<"Number of frames = "<< Video.size() <<endl;
	}

	

	system("pause");

	/// Load an image
	//src = imread( "lena.bmp", 1 );

	/// Convert the image to Gray
	//cvtColor( src, src_gray, CV_RGB2GRAY );

	/// Create a window to display results
	namedWindow( window_name, CV_WINDOW_NORMAL );
	namedWindow( "Video", CV_WINDOW_NORMAL );

	///// Create Trackbar to choose type of Threshold
	//createTrackbar( trackbar_type,
	//                window_name, &threshold_type,
	//                max_type, TrackObjects );

	createTrackbar( trackbar_MinDistValue,
		window_name, &threshold_value,
		max_value, TrackObjects );

	createTrackbar( trackbar_MaxDistValue,
		window_name, &threshold_value2,
		max_value, TrackObjects );

	/// Create Trackbar to select Morphology operation
	createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, TrackObjects );

	/// Create Trackbar to select kernel type
	createTrackbar( "Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
		&morph_elem, max_elem,
		TrackObjects );

	/// Create Trackbar to choose kernel size
	createTrackbar( "Kernel size:\n 2n +1", window_name,
		&morph_size, max_kernel_size,
		TrackObjects );


	createTrackbar( trackbar_MinDistSize,
		window_name, &MinSize,
		max_value_size, TrackObjects );

	createTrackbar( trackbar_MaxDistSize,
		window_name, &MaxSize,
		max_value_size, TrackObjects );

	image2 = cvCreateImage(cvSize(640,480),8,3);
	labelImg = cvCreateImage(cvSize(640,480), IPL_DEPTH_LABEL, 1);
	chB=cvCreateImage(cvSize(640,480),8,1);
	//cv::namedWindow("Depth Image", CV_WINDOW_NORMAL);




	// Creating the network server
	vrpn_Connection_IP* m_Connection = new vrpn_Connection_IP(3883);
	// Creating the Analog
	myAnalog*  serverAnalog  = new myAnalog(m_Connection );


	cout << "Created VRPN server." << endl;
	while(true)
	{



		int changedIndex;
		openni::Status rc = openni::OpenNI::waitForAnyStream(&streams[0], streams.size(), &changedIndex);
		if (rc != openni::STATUS_OK)
		{
			cerr << ("Wait failed\n");
			return -1;
		}

		switch(changedIndex)
		{
		case 0:
			color_stream.readFrame(&color_frame);
			break;

		case 1:
			depth_stream.readFrame(&depth_frame);
			break;

		default:
			cout << "Error in wait" << endl;
		}

		//cv::Mat color_img;
		//if(color_frame.isValid())
		//{
		//  color_img = getColorImage(color_frame);
		//  cv::imshow("color", color_img);
		//}

		cv::Mat depth_img;
		if(depth_frame.isValid())
		{
			depth_img = getDepthImage(depth_frame);
			cv::Mat depth_img_debug = getDepthDrawableImage(depth_img);
			//cv::imshow("Depth Image", depth_img_debug);
			cvtColor( depth_img_debug, src, CV_GRAY2BGR );
			cvtColor( src, src_gray, CV_RGB2GRAY );
			double minVal; double maxVal;
			minMaxLoc(depth_img_debug, &minVal, &maxVal);
			//cout <<"Min = " << minVal << " - Max = " << maxVal << endl;
		}

		//if(!depth_img.empty() && !color_img.empty())
		//{
		//  cv::Mat depth_img_debug = getDepthDrawableImage(depth_img);
		//  cv::cvtColor(depth_img_debug, depth_img_debug, cv::COLOR_GRAY2BGR);
		//  cv::Mat debug_img = color_img * 0.5 + depth_img_debug * 0.5;
		//  cv::imshow("blend", debug_img);
		//}


		/// Call the function to initialize
		TrackObjects( 0, 0 );

		serverAnalog->setPositionXY(P);
		serverAnalog->mainloop();
		m_Connection->mainloop();

		cout<<"P0 = "<<P0<<endl;
		int CalcularFrame = int((P0/640.0)*(float(NumberOfFrames)));
		cout<<"Frame = "<<CalcularFrame<<endl;
		if (CalcularFrame < NumberOfFrames)	imshow("Video", Video[CalcularFrame]);
		
		int key = cv::waitKey(1);
		if( key == 'q' )
		{
			break;
		}
	}

	cvReleaseImage(&image2);
	cvReleaseImage(&chB);
	cvReleaseImage(&labelImg);
	return 0;
}
