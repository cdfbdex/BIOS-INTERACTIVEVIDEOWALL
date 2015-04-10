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


#include <iostream>
#include <vector>


using namespace cv;
using namespace cvb;
using namespace std;





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

Mat src, src_gray, dst, src1, src_gray1, src2, src_gray2;
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


int width, height;
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
	rectangle(src_gray3channel, Point(0,0), Point(image2->width - 4, image2->height - 2), Scalar(0,0,255), 4);

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

	cvFilterByArea(blobs, int((float(MinSize)/100.0)*((image2->width)*(image2->height))), int((float(MaxSize)/100.0)*((image2->width)*(image2->height))));

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
	

	rectangle(dst, Point(0,0), Point(image2->width, image2->height), Scalar(0,255,0), 5);
	Size sz1 = src_gray3channel.size();
	Size sz2 = dst.size();
	Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
	Mat left(im3, Rect(0, 0, sz1.width, sz1.height));
	Mat right(im3, Rect(sz1.width, 0, sz2.width, sz2.height));
	src_gray3channel.copyTo(left);	
	dst.copyTo(right);
	//imshow("im3", im3);

	imshow( window_name, im3 );


}

int main(int argc, char** argv)
{
	openni::Status rc = openni::STATUS_OK;

	openni::Device device1, device2;
	openni::VideoStream depth1, depth2;


	rc = openni::OpenNI::initialize();
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Initialize failed\n%s\n", argv[0], openni::OpenNI::getExtendedError());
		return 1;
	}

	openni::Array<openni::DeviceInfo> deviceList;
	openni::OpenNI::enumerateDevices(&deviceList);

	const char* device1Uri;
	const char* device2Uri;

	switch (1)
	{
	case 1:
		if (deviceList.getSize() < 2)
		{
			printf("Missing devices\n");
			openni::OpenNI::shutdown();
			return 1;
		}
		device1Uri = deviceList[0].getUri();
		device2Uri = deviceList[1].getUri();
		break;
	case 2:
		if (deviceList.getSize() < 1)
		{
			printf("Missing devices\n");
			openni::OpenNI::shutdown();
			return 1;
		}
		device1Uri = argv[1];
		if (strcmp(deviceList[0].getUri(), device1Uri) != 0)
			device2Uri = deviceList[0].getUri();
		else
			device2Uri = deviceList[1].getUri();
		break;
	default:
		device1Uri = argv[1];
		device2Uri = argv[2];
	}

	rc = device1.open(device1Uri);
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Couldn't open device %s\n%s\n", argv[0], device1Uri, openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 3;
	}

	rc = device2.open(device2Uri);
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Couldn't open device %s\n%s\n", argv[0], device2Uri, openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 3;
	}

	rc = depth1.create(device1, openni::SENSOR_DEPTH);
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Couldn't create stream %d on device %s\n%s\n", argv[0], openni::SENSOR_DEPTH, device1Uri, openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 4;
	}
	rc = depth2.create(device2, openni::SENSOR_DEPTH);
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Couldn't create stream %d on device %s\n%s\n", argv[0], openni::SENSOR_DEPTH, device2Uri, openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 4;
	}

	rc = depth1.start();
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Couldn't start stream %d on device %s\n%s\n", argv[0], openni::SENSOR_DEPTH, device1Uri, openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 5;
	}
	rc = depth2.start();
	if (rc != openni::STATUS_OK)
	{
		printf("%s: Couldn't start stream %d on device %s\n%s\n", argv[0], openni::SENSOR_DEPTH, device2Uri, openni::OpenNI::getExtendedError());
		openni::OpenNI::shutdown();
		return 5;
	}

	if (!depth1.isValid() && !depth2.isValid())
	{
		printf("SimpleViewer: No valid streams. Exiting\n");
		openni::OpenNI::shutdown();
		return 6;
	}


	//std::vector<openni::VideoStream*> streams;
	//streams.push_back(&depth1);
	//streams.push_back(&depth2);


	openni::VideoStream**	streams = new openni::VideoStream*[2];
	streams[0] = &depth1;
	streams[1] = &depth2;

	openni::VideoFrameRef depth_frame1;
	openni::VideoFrameRef depth_frame2;


	openni::VideoMode videoMode1 = depth1.getVideoMode();
	openni::VideoMode videoMode2 = depth2.getVideoMode();

	if (videoMode1.getResolutionX() != videoMode2.getResolutionX() ||
		videoMode1.getResolutionY() != videoMode2.getResolutionY())
	{
		printf("Streams need to match resolution.\n");
		return openni::STATUS_ERROR;
	}

	width = videoMode1.getResolutionX();
	height = videoMode1.getResolutionY();
	//device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);


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

	image2 = cvCreateImage(cvSize(640,height/2),8,3);
	labelImg = cvCreateImage(cvSize(640,height/2), IPL_DEPTH_LABEL, 1);
	chB=cvCreateImage(cvSize(640,height/2),8,1);
	//cv::namedWindow("Depth Image", CV_WINDOW_NORMAL);

	


	//// Creating the network server
	//vrpn_Connection_IP* m_Connection = new vrpn_Connection_IP(3883);
	//// Creating the Analog
	//myAnalog*  serverAnalog  = new myAnalog(m_Connection );
	//cout << "Created VRPN server." << endl;


	while(true)
	{



		bool capture_allkinects = false;
		bool kinect1 = false, kinect2 = false;


		while(capture_allkinects == false){
		int changedIndex;
		openni::Status rc = openni::OpenNI::waitForAnyStream(streams, 2, &changedIndex);
		if (rc != openni::STATUS_OK)
		{
			cerr << ("Wait failed\n");
			return -1;
		}

		switch(changedIndex)
		{
		case 0:
			depth1.readFrame(&depth_frame1);
			kinect1 = true;
			break;

		case 1:
			depth2.readFrame(&depth_frame2);
			kinect2 = true;
			break;

		default:
			cout << "Error in wait" << endl;
		}
		capture_allkinects = kinect1 & kinect2;

		}


		cv::Mat depth_img1;
		if(depth_frame1.isValid())
		{
			depth_img1 = getDepthImage(depth_frame1);
			cv::Mat depth_img_debug = getDepthDrawableImage(depth_img1);
			//cv::imshow("Depth Image", depth_img_debug);
			cvtColor( depth_img_debug, src1, CV_GRAY2BGR );
			cvtColor( src1, src_gray1, CV_RGB2GRAY );
			double minVal; double maxVal;
			minMaxLoc(depth_img_debug, &minVal, &maxVal);
			//cout <<"Min = " << minVal << " - Max = " << maxVal << endl;
		}

		cv::Mat depth_img2;
		if(depth_frame1.isValid())
		{
			depth_img2 = getDepthImage(depth_frame2);
			cv::Mat depth_img_debug = getDepthDrawableImage(depth_img2);
			//cv::imshow("Depth Image", depth_img_debug);
			cvtColor( depth_img_debug, src2, CV_GRAY2BGR );
			cvtColor( src2, src_gray2, CV_RGB2GRAY );
			double minVal; double maxVal;
			minMaxLoc(depth_img_debug, &minVal, &maxVal);
			//cout <<"Min = " << minVal << " - Max = " << maxVal << endl;
		}


		cv::Mat depthresize1, depthresize2;

		resize(src_gray1, depthresize1, Size(width/2, height/2.0));
		resize(src_gray2, depthresize2, Size(width/2, height/2.0));

		Mat ImTotal(depthresize1.rows, depthresize1.cols+depthresize2.cols, CV_8UC1);
		Mat Im1(ImTotal, Rect(0, 0, depthresize1.cols, depthresize1.rows));
		Mat Im2(ImTotal, Rect(depthresize1.cols, 0, depthresize2.cols, depthresize2.rows));
		depthresize1.copyTo(Im1);	
		depthresize2.copyTo(Im2);
		/// Call the function to initialize
		

		
		cvtColor(ImTotal, src, CV_GRAY2BGR);
		cvtColor( src, src_gray, CV_RGB2GRAY );
		TrackObjects( 0, 0 );
		//imshow("Depth Total", src);
		//imshow("Depth 2", depthresize2);

		cout<<"P0 = "<<P0<<endl;
		int CalcularFrame = int((P0/image2->width)*(float(NumberOfFrames)));
		cout<<"Frame = "<<CalcularFrame<<endl;
		if (CalcularFrame < NumberOfFrames)	imshow("Video", Video[CalcularFrame]);
		
		int key = cv::waitKey(1);
		if( key == 'q' )
		{
			break;
		}
	}

	depth1.stop();
	depth1.destroy();
	depth2.stop();
	depth2.destroy();
	if (streams != NULL)
	{
		delete []streams;
	}

	cvReleaseImage(&image2);
	cvReleaseImage(&chB);
	cvReleaseImage(&labelImg);
	return 0;
}
