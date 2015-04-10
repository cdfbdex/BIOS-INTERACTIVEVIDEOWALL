/**
* Interactive Wall Application
*
* Author:	Center of Bioinformatics and Computational Biology
* Version:	1.0
*/

/*TODO: ALGUNAS LIBRERIAS NO AFECTAN LA COMPILACIÓN DEL PROGRAMA (stdio.h) (opencv/cv) */
// Definition of necessary libraries
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


// Namespaces definition
using namespace cv;
using namespace cvb;
using namespace std;
using namespace openni;


// Function definition
void TrackObjects(int, void*);


// Global variables definition
int morph_elem = 0;					// Type (or shape) of structuring element
int morph_size = 0;					// Same as kernel_size. Size of structuring element
int morph_operator = 0;				// Define morphological operation between structuring element and image
int threshold_value = 5;			// Lower threshold limit for binarization
int threshold_value2 = 16;			// Upper threshold limit for binarization

int MinSize = 2;					// Lower limit to filter blob by area
int MaxSize = 30;					// Upper limit to filter blob by area

Mat depthImage;						// 3-Channel gotten image from depth sensor
Mat depthImage_gray;				// 1-Channel gotten image from depth sensor
Mat dst;							// InRange() result from depthImage_gray

IplImage* bwImage;					// Black-White 3-channel image 
IplImage* bwImage1C;				// Black-White 1-channel image for blob labeling
IplImage* labelImg;					// Image with labeled blobs

CvBlobs blobs;						// Structure to identify blobs in binary image
CvTracks tracks;					// Structure to extract characteristics of the blobs

// Define resolution of displayed windows
float const WINDOW_WIDTH = 640.0;
float const WINDOW_HEIGHT = 480.0;

//int const NumChannels = 2;
float P0 = 0.0;

char* main_window_name = "Kinect Depth Filtering and Blob Tracking";
char* video_window_name = "Video";


/// <summary>
/// Get color image from sensor, and generate a matrix with its data.</summary>
/// <param name="color_frame"> Encapsulates all data related to a single frame read from a VideoStream</param>
/// <returns>Matrix with color image data</returns>
Mat getColorImage(VideoFrameRef& color_frame)
{
	// Determine wheter a VideoFrameRef contains actual valid data
	if (!color_frame.isValid())
	{
		return Mat();
	}

	//VideoMode: Stores resolution, framerate and pixel format of a frame
	VideoMode video_mode = color_frame.getVideoMode();

	//Create a matrix to save the image of size ResolutionY,ResolutionX
	Mat color_img = Mat(video_mode.getResolutionY(),
		video_mode.getResolutionX(),
		CV_8UC3,						// Type of matrix: 8bit-3Channel unsigned integers (0..255)
		(char*)color_frame.getData());	// Returns a void pointer to the data to be stored

	Mat ret_img;
	cvtColor(color_img, ret_img, CV_RGB2BGR);				//Converts color_img from RGB2BGR and save it in ret_img
	/*TODO: VERIFICAR SI LA CONVERSIÓN ES CORRECTA DE RGB2GBR 	http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html */

	return ret_img;
}


/// <summary>
/// Converts VideoFrameRef depth image from sensor, and converts it to a matrix for processing.</summary>
/// <param name="depth_image"> Data related to a single frame read from a VideoStream</param>
/// <returns>Matrix with depth image data </returns>
Mat getDepthImage(VideoFrameRef& depth_frame)
{
	// Determine wheter a VideoFrameRef contains actual valid data
	if (!depth_frame.isValid())
	{
		return Mat();
	}

	//VideoMode: Stores resolution, framerate and pixel format of a frame
	VideoMode video_mode = depth_frame.getVideoMode();

	//Create a matrix to save the image of size ResolutionY,ResolutionX
	Mat depth_img = Mat(video_mode.getResolutionY(),
		video_mode.getResolutionX(),
		CV_16U,							// Type of matrix: 16bit-1Channel unsigned integers ( 0..65535 )
		(char*)depth_frame.getData());	// Returns a void pointer to the data to be stored

	return depth_img.clone();									// clone() method creates a full copy of the array
}


/// <summary>
/// Convert image to lower resolution and scale it.</summary>
/// <param name="depth_image"> Matrix that contains the initial depth image from sensor</param>
/// <returns>Scaled and modified image </returns>
Mat getDepthDrawableImage(Mat depth_image)
{
	Mat drawable;
	depth_image.convertTo(drawable, CV_8UC1, 255.0 / 10000);		// Converts depth_image to Unsigned8bit-1Channel (UCHAR) with scale factor
	return drawable;
}


/// <summary>
/// Process the image obtained from depth sensor and prepare the window to show the tracked blobs.</summary>
void TrackObjects(int, void*)
{
	// Threshold depthImage_gray with threshold values and save it in dst.
	// If is in range dst is set to 255, 0 otherwise
	inRange(depthImage_gray, Scalar(threshold_value), Scalar(threshold_value2), dst);

	// Create and structuring element for morphological operations
	// morph_elem: 0=MORPH_RECT; 1=MORPH_CROSS; 2=MORPH_ELLIPSE
	// Size(cols,rows): Size of structuring element - Point(x,y): Anchor position within the element /*TODO: VERIFICAR UTILIDAD DE ANCHOR http://docs.opencv.org/modules/imgproc/doc/filtering.html */
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 3, 2 * morph_size + 3), Point(morph_size, morph_size));

	// Apply the specified morphological operation to dst matrix, and replace it
	// operation: 0=MORPH_ERODE; 1=MORPH_DILATE; 2=MORPH_OPEN; 3=MORPH_CLOSE; 4=MORPH_GRADIENT; 5=MORPH_TOPHAT; 6=MORPH_BLACKHAT;
	int operation = morph_operator + 2;
	morphologyEx(dst, dst, operation, element);

	//Converts dst to 3-Channel image
	cvtColor(dst, dst, CV_GRAY2BGR);

	// Convert matrix data in dst into an IplImage using temporal variables
	IplImage ipltemp = dst;
	cvCopy(&ipltemp, bwImage);

	// Apply fixed-level threshold to each array element in source image of type IplImage
	// Constructor: cvThreshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)
	// type: 0: Binary - 1: Binary Inverted - 2: Threshold Truncated - 3: Threshold to Zero - 4: Threshold to Zero Inverted
	cvThreshold(bwImage, bwImage, 100, 255, 0);


	// Divide multichannel array into several single-channel arrays in IplImages [replaces cvtColor()]
	cvSplit(bwImage, bwImage1C, NULL, NULL, NULL);

	// Get the blobs from binarized image bwImage1C, and save it in labelImg
	unsigned int result = cvLabel(bwImage1C, labelImg, blobs);

	// Filter blobs whose area is not in the range defined in the trackbar. The area computed as the percentage of the container window
	cvFilterByArea(blobs, int((float(MinSize)/100.0)*(WINDOW_WIDTH * WINDOW_HEIGHT)), int((float(MaxSize)/100.0)*(WINDOW_WIDTH * WINDOW_HEIGHT)));

	// Updates list of tracks based on current blobs, converting the detected blobs into structures with
	// info related to lifetime and position. Tracks assure that one blob has the same label while it is
	// existing in different frames
	// Constructor: cvUpdateTracks(CvBlobs const &b, CvTracks &t, const double thDistance, const unsigned int thInactive, const unsigned int thActive=0)
	/*TODO: VERIFICAR PARAMETRO thDistance Y thInactive */
	cvUpdateTracks(blobs, tracks, 5., 10);


	// Draws or prints information about blobs contained in third parameter, with the next properties:
	/* Render mode:
		CV_BLOB_RENDER_COLOR            ///< Render each blob with a different color.
		CV_BLOB_RENDER_CENTROID         ///< Render centroid.
		CV_BLOB_RENDER_BOUNDING_BOX     ///< Render bounding box.
		CV_BLOB_RENDER_ANGLE            ///< Render angle.
	*/
	cvRenderBlobs(labelImg, blobs, bwImage, bwImage, CV_BLOB_RENDER_CENTROID | CV_BLOB_RENDER_BOUNDING_BOX);


	// Prints track information of each blob in third argument, with the next properties:
	/* Render mode:
		CV_TRACK_RENDER_ID					///< Print the ID of each track in the image.
		CV_TRACK_RENDER_BOUNDING_BOX		///< Draw bounding box of each track in the image.
		CV_TRACK_RENDER_TO_LOG				///< Print track info to log out.
		CV_TRACK_RENDER_TO_STD				///< Print track info to log out.
		*/
	cvRenderTracks(tracks, bwImage, bwImage, CV_TRACK_RENDER_ID | CV_TRACK_RENDER_BOUNDING_BOX);


	// Find the blob whose area is the biggest and get its centroid's position
	if (blobs.size() > 0)
	{
		CvLabel largestBlobLabel = cvLargestBlob(blobs);
		// Look in the blob's list
		for (CvBlobs::const_iterator it = blobs.begin(); it != blobs.end(); ++it)
		{
			CvLabel comparingBlobLabel = (*it).second->label;
			if (largestBlobLabel == comparingBlobLabel)
			{
				// Get centroid coordinates of the blob and use it to select the frame of the showing video
				CvPoint2D64f XY = (*it).second->centroid;
				P0 = XY.x;
				cout << "Largest Blob " << largestBlobLabel << " = ( " << XY.x << " , " << XY.y << " )" << endl;
			}
		}
	}
	else
	{
		cout << "No Blob found" << endl;
	}


	// Clear all blob structures of the frame
	cvReleaseBlobs(blobs);

	// Copy matrix of first argument to dst
	dst = Mat(bwImage, true);

	// Draw a rectangle with the next constructor: rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	// img: Image to draw the rectangle - pt1: Origin vertex - pt2: Vertex opposite to pt1
	int const rectangleThickness = 4;
	rectangle(depthImage, Point(0, 0), Point(WINDOW_WIDTH - rectangleThickness, WINDOW_HEIGHT - rectangleThickness), Scalar(0, 0, 255)/*BRG*/, rectangleThickness);
	rectangle(dst, Point(0, 0), Point(WINDOW_WIDTH-rectangleThickness, WINDOW_HEIGHT-rectangleThickness), Scalar(0, 255, 0), rectangleThickness);

	// Design of video containers
	Size sizeLeft = depthImage.size();													// Size of acquired gray-color image
	Size sizeRight = dst.size();														// Size of processed binary-color image

	Mat imageContainer(sizeLeft.height, sizeLeft.width + sizeRight.width, CV_8UC3);		// Create a matrix that contains both videos

	Mat leftImage(imageContainer, Rect(0, 0, sizeLeft.width, sizeLeft.height));			// Size of left container
	depthImage.copyTo(leftImage);														// Assign image to left container

	Mat rightImage(imageContainer, Rect(sizeLeft.width, 0, sizeRight.width, sizeRight.height));	// Size of right container
	dst.copyTo(rightImage);																// Assing image to right container

	imshow(main_window_name, imageContainer);
}


// Main procedure
int main(int argc, char** argv)
{
	Device device;											// Interface to a single sensor device connected
	VideoStream color_stream, depth_stream;					// Create single video stream obtained from a device

	// Open device URI
	/*TODO: If multiple sensors are attached to the system, then you should first call
			OpenNI::enumerateDevices() to obtain a list of all active devices. Then, find the desired device
			in the list, and obtain its URI by calling DeviceInfo:getUri(). Use the output from this function as
			.the calling parameter for Device:open() in order to open that specific device
			If opening a file rather than a physical device, then the argument should be the path to the .ONI
			.file*/

	const char* deviceURI = ANY_DEVICE;						// Specify Uniform Resource Identifier
	Status rc = STATUS_OK;									// Variable to get status messages

	// Check initialization of drivers
	rc = OpenNI::initialize();								// Initialize drivers and make API aware of connected devices
	if (rc != STATUS_OK)
	{
		cout << "Driver initialization failed:" << OpenNI::getExtendedError() << endl;
		return EXIT_FAILURE;
	}

	// Check device openning
	rc = device.open(deviceURI);							// Connect to physical hardware device
	if (rc != STATUS_OK)
	{
		cout << "SimpleViewer: Device open failed:" << OpenNI::getExtendedError() << endl;
		OpenNI::shutdown();									// Shutdown drivers and clean up properly
		return EXIT_FAILURE;
	}

	// Create VideoStream with depth sensor
	rc = depth_stream.create(device, SENSOR_DEPTH);			// Specify device and sensor type: (SENSOR_IR, SENSOR_COLOR, SENSOR_DEPTH)
	if (rc == STATUS_OK)
	{
		rc = depth_stream.start();
		// Check depth sensor video stream started properly
		if (rc != STATUS_OK)
		{
			cout << "SimpleViewer: Couldn't start depth stream:" << OpenNI::getExtendedError() << endl;
			depth_stream.destroy();							// Free memory used by the VideoStream
		}
	}
	else
	{
		cout << "SimpleViewer: Couldn't find depth stream:" << OpenNI::getExtendedError() << endl;
	}

	// Create VideoStream with color sensor
	rc = color_stream.create(device, SENSOR_COLOR);			// Specify device and sensor type: (SENSOR_IR, SENSOR_COLOR, SENSOR_DEPTH)
	if (rc == STATUS_OK)
	{
		rc = color_stream.start();
		// Check color sensor video stream started properly
		if (rc != STATUS_OK)
		{
			cout << "SimpleViewer: Couldn't start color stream:" << OpenNI::getExtendedError() << endl;
			color_stream.destroy();							// Free memory used by the VideoStream
		}
	}
	else
	{
		cout << "SimpleViewer: Couldn't find color stream.\n" << OpenNI::getExtendedError() << endl;
	}

	// Check if any of the streams is invalid
	if (!depth_stream.isValid() || !color_stream.isValid())
	{
		cout << "SimpleViewer: No valid streams. Exiting" << endl;
		OpenNI::shutdown();									// Shutdown drivers and clean up properly
		return EXIT_FAILURE;
	}
	else
	{
		cout << "Device and streams configuration was OK." << endl << endl;
	}


	// Variable to allocate video streams
	vector<VideoStream*> streams;
	streams.push_back(&color_stream);
	streams.push_back(&depth_stream);

	// Variables to allocate frames of video streams
	VideoFrameRef color_frame;
	VideoFrameRef depth_frame;

	// Registration process consists in superimpose depth and RGB images, originally taken from different angles
	// If this feature is enabled, it will be an "shadows" and "holes" in the depthmap, and an to one side of Depthmap will not be shown
	// ImageRegistrationMode: IMAGE_REGISTRATION_OFF = 0 - IMAGE_REGISTRATION_DEPTH_TO_COLOR = 1)
	/*TODO: Check device.isImageRegistrationSupported()*/
	device.setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);


	// Load selected video
	char* loadVideoPath = argv[1];
	VideoCapture cap(loadVideoPath);					// Create a video capturing from the file specified in argument 1
	vector <Mat> Video;									// Matrix to save the specified range of video frames

	// Range and quantity of frames to show in the video
	int initialFrame = atoi(argv[2]);
	int finalFrame = atoi(argv[3]);
	int numberOfFrames;

	if (!cap.isOpened())								// Checks if video capturing has been initialized already
	{
		cout << "Could Not Load Video: " << argv[1] << endl;
		return EXIT_FAILURE;
	}
	else
	{
		cout << "Loading Video..." << endl;
				
		// Set the VideoCapture object in the specified initialFrame of the video
		cap.set(CV_CAP_PROP_POS_FRAMES, initialFrame);


		Mat frame_video;
		int framesCounter;
		// Save the frames that are in the specified range
		for (framesCounter = initialFrame; framesCounter <= finalFrame; framesCounter++)
		{
			cap >> frame_video;							// Read the next video frame
			if (frame_video.empty())	break;
			Video.push_back(frame_video.clone());		// Add the frame to the vector named Video
		}
		numberOfFrames = framesCounter - initialFrame;	// Compute the total frames in the video
		cout << "Video Succesfully Loaded" << endl;
		cout << "Number of frames = " << Video.size() << endl;
	}

#ifdef WIN32
	system("pause");
#endif


	/////////////////////// WINDOW CONFIGURATION

	// Constants defined for trackbar creation
	int const max_pixel_value = 255;	// Max value in a pixel
	int const max_operator = 4;			// Max value for operation between SE and image
	int const max_elem = 2;				// Max value for shape of SE
	int const max_kernel_size = 21;		// Max value for size of SE
	int const max_value_size = 100;		// Max value for filtering size of blobs in the image

	// Definition of trackbar labels
	char* trackbar_MinDistValue = "Min. Dist";			// Labels for depth image binarization thresholds
	char* trackbar_MaxDistValue = "Max. Dist";
	char* trackbar_MinBlobSize = "Min %. Blob Size";		// Labels for filtering blobs by area
	char* trackbar_MaxBlobSize = "Max %. Blob Size";
	char* trackbar_Operator = "Operator";				// Label for morphological operation
	char* trackbar_ShapeSE = "SE Shape";				// Label for SE shape -- 0:Rect - 1:Cross - 2:Ellipse
	char* trackbar_SizeSE = "SE Size (2n+1)";			// Label for SE size
	
	// Windows Creation
	namedWindow(main_window_name, CV_WINDOW_NORMAL);
	namedWindow(video_window_name, CV_WINDOW_NORMAL);

	// Trackbar Creation
	// Trackbar to modify Binarization Thresholds
	createTrackbar(trackbar_MinDistValue, main_window_name, &threshold_value, max_pixel_value, TrackObjects); 
	createTrackbar(trackbar_MaxDistValue, main_window_name, &threshold_value2, max_pixel_value, TrackObjects);
	// Trackbar to choose size limits in the cvFilterbyArea function
	createTrackbar(trackbar_MinBlobSize, main_window_name, &MinSize, max_value_size, TrackObjects);
	createTrackbar(trackbar_MaxBlobSize, main_window_name, &MaxSize, max_value_size, TrackObjects);
	// Trackbar to select Morphology operation
	createTrackbar(trackbar_Operator, main_window_name, &morph_operator, max_operator, TrackObjects);
	// Trackbar to select kernel type
	createTrackbar(trackbar_ShapeSE, main_window_name, &morph_elem, max_elem, TrackObjects);
	// Trackbar to choose kernel size
	createTrackbar(trackbar_SizeSE, main_window_name, &morph_size, max_kernel_size, TrackObjects);
	
	

	// Images used in the TrackObjects function
	bwImage = cvCreateImage(cvSize(WINDOW_WIDTH, WINDOW_HEIGHT), IPL_DEPTH_8U, 3);
	labelImg = cvCreateImage(cvSize(WINDOW_WIDTH, WINDOW_HEIGHT), IPL_DEPTH_LABEL, 1);
	bwImage1C = cvCreateImage(cvSize(WINDOW_WIDTH, WINDOW_HEIGHT), IPL_DEPTH_8U, 1);

	// Infinite loop for window updating and image processing
	bool exit = false;
	while (1)
	{
		int changedIndex = -1;

		// Wait for a new frame from any of the streams provided. And save the status message in rc
		// Reads all the streams in VideoStream variable and assign to changedIndex the index of the first stream that has a new frame available
		rc = OpenNI::waitForAnyStream(&streams[0], streams.size(), &changedIndex);

		// Check if has obtained the frame properly
		if (rc != STATUS_OK)
		{
			cerr << ("Wait failed\n");
			return EXIT_FAILURE;
		}

		// Depending on the index, read the frame from different sensor
		switch (changedIndex)
		{
		case 0:
			color_stream.readFrame(&color_frame);				// In this case, we do not use color image for posterior processing
			break;

		case 1:
			depth_stream.readFrame(&depth_frame);
			break;

		default:
			cout << "Error in wait" << endl;
			return EXIT_FAILURE;
		}


		// Get depth image from sensor and save RGB and GRAY versions of it
		if (depth_frame.isValid())
		{
			// Get and process depth image
			depthImage_gray = getDepthImage(depth_frame);						//Get gray image from depth sensor: Resolution 16 bits
			depthImage_gray = getDepthDrawableImage(depthImage_gray);					//Get gray image from depth sensor: Resolution 8 bits
			cvtColor(depthImage_gray, depthImage, CV_GRAY2BGR);						//Create 3-Channel image from gray image
			//imshow("Depth Image", depthImage_gray);
		}


		// Call the function to initialize
		TrackObjects(0,0);


		// Show the respective frame of the video, based on the centroid of the biggest founded blob 
		cout << "P0 = " << P0 << endl;
		//int CalcularFrame = int((P0 / WINDOW_WIDTH)*(numberOfFrames));
		int CalcularFrame = int((P0 / WINDOW_WIDTH)*(cap.get(CV_CAP_PROP_FRAME_COUNT)));
		cout << "Frame = " << CalcularFrame << endl;

		//if (CalcularFrame < numberOfFrames)	imshow(video_window_name, Video[CalcularFrame]);
		//if (CalcularFrame < numberOfFrames)	{
			cap.set(CV_CAP_PROP_POS_FRAMES, CalcularFrame);
			Mat ii;
			cap >> ii;
			imshow(video_window_name, ii);
		//}

		// Exit of the program
		int key = waitKey(1);
		if (key == 'q')
		{
			exit = true;						// Enable exit flag to close application
			//destroyWindow(main_window_name);
			//destroyWindow(video_window_name);
			
			break;
		}
	}
	destroyAllWindows();				// Close cvWindows
	// Free memory of saved images
	cvReleaseImage(&bwImage);
	cvReleaseImage(&labelImg);
	cvReleaseImage(&bwImage1C);
	
	return EXIT_SUCCESS;
}
