# BIOS-INTERACTIVEVIDEOWALL
This is a Human Computer Interface using few Kinects to play a video according to person's position in one direction.

USER GUIDE

1. Execute CMake in main folder to generate the project of Visual Studio 2013.
2. Open Visual Studio project and compile it in Release mode.
3. Open \bin\Release folder and verify that .exe has been created properly.
4. Open \lib\Release folder, copy cvblob.dll and paste it in the folder \bin\Release.
5. Copy the selected video in the folder \bin\Release.

EXECUTING PROGRAM

Open a command window in the folder \bin\Release. And write the corresponding
command depending on the selected mode:

MODE 1: Process all the frames of the video
..\bin\Release\ InteractiveWallNKinect.exe VideoName.avi
Parameters:
  - InteractiveWallNKinect.exe: Main application
  - VideoName.avi: Path or filename of the video with its extension

MODE 2: Process a specified range of frames in the video
..\bin\Release\ InteractiveWallNKinect.exe VideoName.avi 1800 2000
Parameters:
  - InteractiveWallNKinect.exe: Main application
  - VideoName.avi: Path or filename of the video with its extension
  - 1800: Start frame of the range that should be processed in the video
  - 2000: End frame of the range that should be processed in the video
