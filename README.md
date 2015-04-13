# BIOS-INTERACTIVEVIDEOWALL
This is a Human Computer Interface using few Kinects to play a video according to person's position in one direction.

CONFIGURE AND BUILD

1. For windows install: CMake (2.4.8) to configure and Visual C++ (2012 or 2013) to build.
2. Install Prerequisites: OpenCV (tested with version 2.4.9), OpenNI2 (tested with version 2.2), NITE2 (tested with version 2.2), Kinect for Windows SDK (tested with version 1.8). 
3. Configure project with CMake and generate solution for your Visual C++.
4. Open Visual Studio project and compile it in Release mode.
5. Open "..\bin\Release" folder and verify that .exe has been created properly.
6. Open "..\lib\Release" folder, copy cvblob.dll and paste it in the folder \bin\Release.
7. Execute the program. A video is needed to run properly.

EXECUTING PROGRAM

Connect all kinects you need up to 10. Open a command window in the folder "..\bin\Release" and write the corresponding
command depending on the selected mode:

MODE 1: Process all the frames of the video

..\bin\Release\>InteractiveWallNKinect.exe <videoname>

Parameters:
  - InteractiveWallNKinect.exe: Main application
  - <videoname>: Any compatible video with OpenCV.

MODE 2: Process a range of frames in the video. Be sure you input a properly range.
..\bin\Release\ InteractiveWallNKinect.exe <videoname> <initialframe> <lastframe>
Parameters:
  - InteractiveWallNKinect.exe: Main application
  - <videoname>: Path or filename of the video with its extension
  - <initialframe>: Start frame of the range that should be processed in the video
  - <lastframe>: End frame of the range that should be processed in the video
