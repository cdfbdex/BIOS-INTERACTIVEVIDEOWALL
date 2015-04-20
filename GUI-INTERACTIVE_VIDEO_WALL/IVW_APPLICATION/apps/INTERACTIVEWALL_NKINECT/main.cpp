/**
* Interactive Wall Application
*
* Author:	Center of Bioinformatics and Computational Biology
* Version:	1.0
*/

// Constants definition
#define	MAX_POSSIBLE_SENSORS	10


// Definition of necessary libraries
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <cvblob.h>
#include <OpenNI.h>

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
int morph_operator = 2;				// Define morphological operation between structuring element and image

int threshold_value = 55;			// Lower threshold limit for binarization
int threshold_value2 = 110;			// Upper threshold limit for binarization

int MinSize = 1;					// Lower limit to filter blob by area
int MaxSize = 30;					// Upper limit to filter blob by area

int DistanceCroppingUnderneath = 0;

Mat finalDepthImage, finalDepthImage_gray;			// Final joined depth images
Mat depthImage[MAX_POSSIBLE_SENSORS];				// 3-Channel gotten image from depth sensor
Mat depthImage_gray[MAX_POSSIBLE_SENSORS];			// 1-Channel gotten image from depth sensor
Mat finalBinaryImage;								// Final processed image



IplImage* bwImage;					// Black-White 3-channel image 
IplImage* bwImage1C;				// Black-White 1-channel image for blob labeling
IplImage* labelImg;					// Image with labeled blobs

CvBlobs blobs;						// Structure to identify blobs in binary image
CvTracks tracks;					// Structure to extract characteristics of the blobs

// Define resolution of displayed windows
float const WINDOW_WIDTH = 640.0;
float const WINDOW_HEIGHT = 480.0;

int ScaleHeight = 2;				// Resize images decreasing height of the image in ScaleHeight factor
int detectedDevices;				// Number of devices that are connected

float P0 = 0.0;						// Centroid of biggest found Blob

char* main_window_name = "Control Panel (Press 'q' to exit)";
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
	// Threshold finalDepthImage_gray with threshold values and save it in finalBinaryImage.
	// If is in range finalBinaryImage is set to 255, 0 otherwise
	inRange(finalDepthImage_gray, Scalar(threshold_value), Scalar(threshold_value2), finalBinaryImage);

	// Create and structuring element for morphological operations
	// morph_elem: 0=MORPH_RECT; 1=MORPH_CROSS; 2=MORPH_ELLIPSE
	// Size(cols,rows): Size of structuring element - Point(x,y): Anchor position within the element /*TODO: VERIFICAR UTILIDAD DE ANCHOR http://docs.opencv.org/modules/imgproc/doc/filtering.html */
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 3, 2 * morph_size + 3), Point(morph_size, morph_size));

	// Apply the specified morphological operation to finalBinaryImage matrix, and replace it
	// operation: 0=MORPH_ERODE; 1=MORPH_DILATE; 2=MORPH_OPEN; 3=MORPH_CLOSE; 4=MORPH_GRADIENT; 5=MORPH_TOPHAT; 6=MORPH_BLACKHAT;
	int operation = morph_operator;		/*TODO: VERIFICAR CAMBIOS DE OPERACION DE 0..6*/
	morphologyEx(finalBinaryImage, finalBinaryImage, operation, element);

	//Converts finalBinaryImage to 3-Channel image
	cvtColor(finalBinaryImage, finalBinaryImage, CV_GRAY2BGR);

	// Convert matrix data in finalBinaryImage into an IplImage using temporal variables
	IplImage ipltemp = finalBinaryImage;
	cvCopy(&ipltemp, bwImage);

	// Apply fixed-level threshold to each array element in source image of type IplImage
	// Constructor: cvThreshold(InputArray src, OutputArray finalBinaryImage, double thresh, double maxval, int type)
	// type: 0: Binary - 1: Binary Inverted - 2: Threshold Truncated - 3: Threshold to Zero - 4: Threshold to Zero Inverted
	cvThreshold(bwImage, bwImage, 100, 255, 0);


	// Divide multichannel array into several single-channel arrays in IplImages [replaces cvtColor()]
	cvSplit(bwImage, bwImage1C, NULL, NULL, NULL);

	// Get the blobs from binarized image bwImage1C, and save it in labelImg
	unsigned int result = cvLabel(bwImage1C, labelImg, blobs);

	// Filter blobs whose area is not in the range defined in the trackbar. The area computed as the percentage of the container window
	cvFilterByArea(blobs, int((float(MinSize) / 100.0)*(WINDOW_WIDTH * WINDOW_HEIGHT)), int((float(MaxSize) / 100.0)*(WINDOW_WIDTH * WINDOW_HEIGHT)));

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

	// Copy matrix of first argument to finalBinaryImage
	finalBinaryImage = Mat(bwImage, true);

	// Draw a rectangle with the next constructor: rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
	// img: Image to draw the rectangle - pt1: Origin vertex - pt2: Vertex opposite to pt1
	int const rectangleThickness = 3;
	rectangle(finalDepthImage, Point(0, 0), Point(WINDOW_WIDTH*detectedDevices - rectangleThickness, WINDOW_HEIGHT/ScaleHeight - rectangleThickness), Scalar(0, 0, 255)/*BRG*/, rectangleThickness);
	rectangle(finalBinaryImage, Point(0, 0), Point(WINDOW_WIDTH*detectedDevices - rectangleThickness, WINDOW_HEIGHT/ScaleHeight - rectangleThickness), Scalar(0, 255, 0), rectangleThickness);

	// Design of video containers
	Size sizeLeft = finalDepthImage.size();													// Size of acquired gray-color image
	Size sizeRight = finalBinaryImage.size();												// Size of processed binary-color image

	Mat imageContainer(sizeLeft.height, sizeLeft.width + sizeRight.width, CV_8UC3);			// Create a matrix that contains both videos

	Mat leftImage(imageContainer, Rect(0, 0, sizeLeft.width, sizeLeft.height));				// Size of left container
	finalDepthImage.copyTo(leftImage);														// Assign image to left container

	Mat rightImage(imageContainer, Rect(sizeLeft.width, 0, sizeRight.width, sizeRight.height));			// Size of right container
	finalBinaryImage.copyTo(rightImage);																// Assing image to right container

	imshow(main_window_name, imageContainer);
}


// Main procedure
int main(int argc, char** argv)
{
	if (argc != 2 && argc != 4 && argc != 5)
	{
		cout << "Invalid number of inputs." << endl;
		return EXIT_FAILURE;
	}
	
	
	Device device[MAX_POSSIBLE_SENSORS];										// Interface to a sensor devices connected
	VideoStream** streams = new openni::VideoStream*[MAX_POSSIBLE_SENSORS];		// Save streams from depth sensor
	VideoStream color_stream[MAX_POSSIBLE_SENSORS];								// Save color stream // It is not used
	VideoStream depth_stream[MAX_POSSIBLE_SENSORS];								// Save depth stream
	VideoMode videoMode[MAX_POSSIBLE_SENSORS];									// Save video mode for sensor configuration

	const char* deviceURI[MAX_POSSIBLE_SENSORS];			// Specify Uniform Resource Identifier of each detected device


	// Check initialization of drivers
	Status rc;												// Variable to get status messages
	rc = OpenNI::initialize();								// Initialize drivers and make API aware of connected devices
	if (rc != STATUS_OK)
	{
		cout << "Driver initialization failed:" << OpenNI::getExtendedError() << endl;
		return EXIT_FAILURE;
	}

	// Detect how many sensor are connected
	Array<DeviceInfo> deviceInfoList;
	OpenNI::enumerateDevices(&deviceInfoList);

	// List device that are connected
	detectedDevices = deviceInfoList.getSize();

	// Check number of detected devices
	if (detectedDevices > MAX_POSSIBLE_SENSORS)
	{
		cout << "Cannot detect more than " << MAX_POSSIBLE_SENSORS << " devices." << endl;
		return EXIT_FAILURE;
	}
	if (detectedDevices < 1)
	{
		cout << "Not connected devices." << endl;
		OpenNI::shutdown();
		return EXIT_FAILURE;
	}
	else
	{
		cout << "Number of detected devices: " << detectedDevices << endl;
	}


	// Initialize and set up each one of the connected sensors
	for (int i = 0; i < detectedDevices; i++)
	{
		deviceURI[i] = deviceInfoList[i].getUri();

		rc = device[i].open(deviceURI[i]);							// Connect to physical hardware device
		if (rc != STATUS_OK)
		{
			cout << "SimpleViewer device " << i + 1 << ": Device open failed:" << OpenNI::getExtendedError() << endl;
			OpenNI::shutdown();										// Shutdown drivers and clean up properly
			return EXIT_FAILURE;
		}


		// Create VideoStream with depth sensor
		rc = depth_stream[i].create(device[i], SENSOR_DEPTH);			// Specify device and sensor type: (SENSOR_IR, SENSOR_COLOR, SENSOR_DEPTH)
		if (rc == STATUS_OK)
		{
			rc = depth_stream[i].start();
			// Check depth sensor video stream started properly
			if (rc != STATUS_OK)
			{
				cout << "SimpleViewer device " << i + 1 << ": Couldn't start depth stream:" << OpenNI::getExtendedError() << endl;
				depth_stream[i].destroy();							// Free memory used by the VideoStream
			}
		}
		else
		{
			cout << "SimpleViewer device " << i + 1 << ": Couldn't find depth stream:" << OpenNI::getExtendedError() << endl;
		}

		// Create VideoStream with color sensor
		rc = color_stream[i].create(device[i], SENSOR_COLOR);		// Specify device and sensor type: (SENSOR_IR, SENSOR_COLOR, SENSOR_DEPTH)
		if (rc == STATUS_OK)
		{
			rc = color_stream[i].start();
			// Check color sensor video stream started properly
			if (rc != STATUS_OK)
			{
				cout << "SimpleViewer device " << i + 1 << ": Couldn't start color stream:" << OpenNI::getExtendedError() << endl;
				color_stream[i].destroy();							// Free memory used by the VideoStream
			}
		}
		else
		{
			cout << "SimpleViewer device " << i + 1 << ": Couldn't find color stream.\n" << OpenNI::getExtendedError() << endl;
		}

		// Check if any of the streams is invalid
		if (!depth_stream[i].isValid() || !color_stream[i].isValid())
		{
			cout << "SimpleViewer device " << i + 1 << ": No valid streams." << endl;
			OpenNI::shutdown();									// Shutdown drivers and clean up properly
			return EXIT_FAILURE;
		}
		else
		{
			cout << "Device " << i + 1 << "'s configuration was OK." << endl;
		}

		// Variable to allocate video streams
		streams[i] = &depth_stream[i];
		//streams[i].push_back(&color_stream[i]);
		videoMode[i] = depth_stream[i].getVideoMode();


		// Registration process consists in superimpose depth and RGB images, originally taken from different angles
		// If this feature is enabled, it will be an "shadows" and "holes" in the depthmap, and an to one side of Depthmap will not be shown
		// ImageRegistrationMode: IMAGE_REGISTRATION_OFF = 0 - IMAGE_REGISTRATION_DEPTH_TO_COLOR = 1)
		//if (device[i].isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR))
		//{
		//	device[i].setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
		//}
		//else
		//{
		//	cout << "Device " << i + 1 << " does not support image registration" << endl;
		//}
	}
	cout << endl;

	// Verify that resolution's image match
	for (int i = 1; i < detectedDevices; i++)
	{
		if (videoMode[i].getResolutionX() != videoMode[i-1].getResolutionX() ||
			videoMode[i].getResolutionY() != videoMode[i-1].getResolutionY())
		{
			cout << "Streams of all sensors must have the same resolution." << endl;
			return EXIT_FAILURE;
		}
	}
	
	// Load selected video
	char* loadVideoPath = argv[1];
	VideoCapture cap(loadVideoPath);					// Create a video capturing from the file specified in argument 1

	// Range and quantity of frames to show in the video
	int initialFrame, finalFrame, numberOfFrames;

	// Calculate a range of frames or all the frames of the video depending on the number of arguments
	cout << "Loading Video..." << endl;
	
	// Variable to verify is the range is specified in frames or in time
	bool rangeInFrames;
	
	// Checks if video capturing has been already initialized
	if (!cap.isOpened())
	{
		cout << "Could Not Load Video: " << argv[1] << endl;
		return EXIT_FAILURE;
	}
	else
	{
		// If there is a fifth argument and its value is 1, calculate in time, else calculate in frames
		if (argc == 5 && atoi(argv[4]) == 1)
		{
			rangeInFrames = false;
		}
		else
		{
			rangeInFrames = true;
		}

		if (argc == 5 && atoi(argv[4]) == 1)				// If there are five arguments and last argument is equal to 1, calculate frames between specified time range
		{
			numberOfFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
			float fpsVideo, totalTime, initialTime, endTime;

			fpsVideo = cap.get(CV_CAP_PROP_FPS);
			totalTime = (float(numberOfFrames) / fpsVideo) * 1000;
			initialTime = atof(argv[2]);
			endTime = atof(argv[3]);

			// Verify proper input of arguments
			if (initialTime > totalTime || initialTime <= 0 ||
				endTime > totalTime || endTime <= 0)
			{
				cout << "Invalid range of time. Max possible value is " << totalTime << " miliseconds." << endl;
				return EXIT_FAILURE;
			}

			// Calculate frames of respective times
			initialFrame = int(float(initialTime*numberOfFrames) / totalTime);
			finalFrame = int(float(endTime*numberOfFrames) / totalTime);
			numberOfFrames = finalFrame - initialFrame + 1;
		}
		else if (argc >= 4)										// If there are four arguments, calculate frame between specified range
		{
			numberOfFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
			initialFrame = atoi(argv[2]);
			finalFrame = atoi(argv[3]);

			// Verify proper input of arguments
			if (initialFrame > numberOfFrames - 2 || initialFrame < 0 ||
				finalFrame > numberOfFrames - 1 || finalFrame < 1)
			{
				cout << "Invalid range of frames. Max possible value is " << numberOfFrames << " frames." << endl;
				return EXIT_FAILURE;
			}
			numberOfFrames = finalFrame - initialFrame + 1;
		}
		else												// If there are 2 arguments, calculate frame in all the video
		{
			initialFrame = 0;
			numberOfFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
			finalFrame = numberOfFrames - 1;
		}


		cout << "Video Succesfully Loaded" << endl;
		cout << "Number of frames = " << numberOfFrames << endl;
	}


//#ifdef WIN32
//	system("pause");
//#endif


	/////////////////////// WINDOW CONFIGURATION

	// Constants defined for trackbar creation
	int const max_pixel_value = 255;	// Max value in a pixel
	int const max_operator = 6;			// Max value for operation between SE and image
	int const max_elem = 2;				// Max value for shape of SE
	int const max_kernel_size = 20;		// Max value for size of SE
	int const max_value_size = 100;		// Max value for filtering size of blobs in the image
	int const max_HeightCropping = WINDOW_HEIGHT/ScaleHeight;

	// Definition of trackbar labels
	char* trackbar_MinDistValue = "Min. Dist";			// Labels for depth image binarization thresholds
	char* trackbar_MaxDistValue = "Max. Dist";
	char* trackbar_MinBlobSize = "Min Area";			// Labels for filtering blobs by area
	char* trackbar_MaxBlobSize = "Max Area";
	char* trackbar_Operator = "Operator";				// Label for morphological operation
	char* trackbar_ShapeSE = "SE Shape";				// Label for SE shape -- 0:Rect - 1:Cross - 2:Ellipse
	char* trackbar_SizeSE = "SE Size (2n+1)";			// Label for SE size
	char* trackbar_HeightCropping = "Floor Filter";

	// Windows Creation
	namedWindow(main_window_name, CV_WINDOW_NORMAL);
	namedWindow(video_window_name, CV_WINDOW_NORMAL);
	startWindowThread();


	FileStorage FSArchivo("Configuracion.xml", FileStorage::READ);
	if (FSArchivo.isOpened())
	{
		threshold_value = (int)FSArchivo["UmbralMinimo"];
		threshold_value2 = (int)FSArchivo["UmbralMaximo"];
		MinSize = (int)FSArchivo["MinArea"];
		MaxSize = (int)FSArchivo["MaxArea"];
		morph_operator = (int)FSArchivo["TipoOperacionMorfologica"];
		morph_elem = (int)FSArchivo["FormaElemEstructurante"];
		morph_size = (int)FSArchivo["TamanoElemEstructurante"];
		DistanceCroppingUnderneath = (int)FSArchivo["DistanceCroppingUnderneath"];
		FSArchivo.release();
	}
	



	//cout << threshold_value << endl;cout << threshold_value2 << endl;
	//cout << MinSize << endl;
	//cout << MaxSize << endl;
	//cout << morph_operator << endl;
	//cout << morph_size << endl;
	//cout << DistanceCroppingUnderneath << endl;

	//system("pause");

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
	// Trackbar to filter floor from image
	createTrackbar(trackbar_HeightCropping, main_window_name, &DistanceCroppingUnderneath, max_HeightCropping, TrackObjects);


	// Images used in the TrackObjects function
	bwImage = cvCreateImage(cvSize(WINDOW_WIDTH*detectedDevices, WINDOW_HEIGHT/ScaleHeight), IPL_DEPTH_8U, 3);
	labelImg = cvCreateImage(cvSize(WINDOW_WIDTH*detectedDevices, WINDOW_HEIGHT/ScaleHeight), IPL_DEPTH_LABEL, 1);
	bwImage1C = cvCreateImage(cvSize(WINDOW_WIDTH*detectedDevices, WINDOW_HEIGHT/ScaleHeight), IPL_DEPTH_8U, 1);


	// Variables to allocate frames of video streams
	//VideoFrameRef color_frame[MAX_POSSIBLE_SENSORS];	// Color frames are not used in this program
	VideoFrameRef depth_frame[MAX_POSSIBLE_SENSORS];

	// Infinite loop for window updating and image processing
	//bool exit = false;
	while (true)
	{
		// Loop for reading the images from all detected sensors
		bool captured_allkinects = false;
		bool kinectReaded[MAX_POSSIBLE_SENSORS] = { false };

		while (captured_allkinects == false)
		{
			int changedIndex = -1;
			
			// Wait for a new frame from any of the streams provided. And save the status message in rc
			// Reads all the streams in VideoStream variable and assign to changedIndex the index of the first stream that has a new frame available
			rc = OpenNI::waitForAnyStream(streams, detectedDevices, &changedIndex);

			// Check if has obtained the frame properly
			if (rc != STATUS_OK)
			{
				cout << ("Wait failed\n");
				return EXIT_FAILURE;
			}

			// Depending on the index, read the frame from different sensor
			if (changedIndex >= 0 && changedIndex < detectedDevices)
			{
				depth_stream[changedIndex].readFrame(&depth_frame[changedIndex]);
				kinectReaded[changedIndex] = true;
			}
			
			// Calculate if all detected sensor have been readed
			captured_allkinects = true;
			for (int i = 0; i < detectedDevices; i++)
			{
				captured_allkinects = captured_allkinects & kinectReaded[i];
			}
		}
		
		Mat depthImage_resized[MAX_POSSIBLE_SENSORS];

		for (int i = 0; i < detectedDevices; i++)
		{
			if (depth_frame[i].isValid())
			{
				// Get and process depth image
				depthImage_gray[i] = getDepthImage(depth_frame[i]);								//Get gray image from depth sensor: Resolution 16 bits
				depthImage_gray[i] = getDepthDrawableImage(depthImage_gray[i]);					//Get gray image from depth sensor: Resolution 8 bits
				cvtColor(depthImage_gray[i], depthImage[i], CV_GRAY2BGR);						//Create 3-Channel image from gray image
				//imshow("Depth Image", depthImage_gray);
			}
			resize(depthImage_gray[i], depthImage_resized[i], Size(WINDOW_WIDTH, WINDOW_HEIGHT / ScaleHeight));		// Draw and image with the WIDTH*detectedDevices and reduce its height
		}
		

		// Join images from different sensor into one matrix
		Mat ImTotal(depthImage_resized[0].rows, depthImage_resized[0].cols*detectedDevices, CV_8UC1);
		for (int i = 0; i < detectedDevices; i++)
		{
			Mat joinImages(ImTotal, Rect(i*depthImage_resized[0].cols, 0, depthImage_resized[0].cols, depthImage_resized[0].rows));
			depthImage_resized[i].copyTo(joinImages);
		}
		

		// Crop floor area
		Mat mask(ImTotal, Rect(0,(WINDOW_HEIGHT / ScaleHeight) - DistanceCroppingUnderneath, ImTotal.cols, DistanceCroppingUnderneath));				// Size of floor filter
		if (ImTotal.type() == CV_8UC1)
		{
			mask.setTo(Scalar(255));
		}
		else
		{
			mask.setTo(Scalar(255, 255, 255));
		}
		
			
		// Convert images in necessary color scales
		cvtColor(ImTotal, finalDepthImage, CV_GRAY2BGR);
		cvtColor(finalDepthImage, finalDepthImage_gray, CV_RGB2GRAY);

		
		//cout << finalDepthImage.size();
		//system("pause");


		// Call the function to initialize
		TrackObjects(0, 0);

		// Show the respective frame of the video, based on the centroid of the biggest founded blob 
		cout << "P0 = " << P0 << endl;
		int calculatedFrame = int((P0 / WINDOW_WIDTH)*(numberOfFrames))+initialFrame;
		cout << "Frame = " << calculatedFrame << endl;

		// Show calculatedFrame
		cap.set(CV_CAP_PROP_POS_FRAMES, calculatedFrame);
		Mat frame_video;
		cap >> frame_video;
		imshow(video_window_name, frame_video);

		// Exit of the program
		int key = waitKey(1);
		if (key == 'q' || key == 'Q')
		{
			//exit = true;						// Enable exit flag to close application
			cout << "Press Ctrl+C to exit..." << endl;
			break;
		}
	}



	FileStorage NewConfigurationFile("Configuracion.xml", FileStorage::WRITE);

	if (NewConfigurationFile.isOpened())
	{
		NewConfigurationFile << "UmbralMinimo" << threshold_value;
		NewConfigurationFile << "UmbralMaximo" << threshold_value2;
		NewConfigurationFile << "MinArea" << MinSize;
		NewConfigurationFile << "MaxArea" << MaxSize;
		NewConfigurationFile << "TipoOperacionMorfologica" << morph_operator;
		NewConfigurationFile << "FormaElemEstructurante" << morph_elem;
		NewConfigurationFile << "TamanoElemEstructurante" << morph_size;
		NewConfigurationFile << "DistanceCroppingUnderneath" << DistanceCroppingUnderneath;
		NewConfigurationFile.release();
	}
	



	destroyAllWindows();				// Close cvWindows

	// Free memory of saved images
	cvReleaseImage(&bwImage);
	cvReleaseImage(&labelImg);
	cvReleaseImage(&bwImage1C);


	color_stream->stop();
	depth_stream->stop();

	color_stream->destroy();
	depth_stream->destroy();

	delete[] streams;
	
	OpenNI::shutdown();					// Finish using openni

	return EXIT_SUCCESS;
}