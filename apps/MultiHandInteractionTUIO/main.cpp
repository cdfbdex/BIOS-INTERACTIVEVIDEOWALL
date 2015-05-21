/*******************************************************************************
*                                                                              *
*   PrimeSense NiTE 2.0 - Simple Tracker Sample                                *
*   Copyright (C) 2012 PrimeSense Ltd.                                         *
*                                                                              *
*******************************************************************************/


/*
R=
[ 9.9984628826577793e-01, 1.2635359098409581e-03, -1.7487233004436643e-02, 
 -1.4779096108364480e-03, 9.9992385683542895e-01, -1.2251380107679535e-02,
  1.7470421412464927e-02, 1.2275341476520762e-02, 9.9977202419716948e-01 ]

T=
[ 1.9985242312092553e-02, -7.4423738761617583e-04, -1.0916736334336222e-02 ]
*/



#include "NiTE.h"
#include <NiteSampleUtilities.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <cvblob.h>
#include <opencv2/opencv.hpp>
#include <OpenNI.h>

#include <iostream>
#include <vector>




using namespace cv;
using namespace cvb;
using namespace std;

//TUIO SERVER
#include "TuioServer.h"
using namespace TUIO;
TuioServer* tuio;
TuioTime time1;
std::list<TuioCursor*> stickyCursorList;



void Iniciar_TUIO(const char* host, int port, bool Mode)
{
	bool tuio3dMode = Mode;

	if ((strcmp(host,"default")==0) && (port==0)) 
		tuio = new TuioServer(tuio3dMode);
	else 
		tuio = new TuioServer(host, port, tuio3dMode);

}


int main(int argc, char** argv)
{
	nite::HandTracker handTracker;
	nite::Status niteRc;

	niteRc = nite::NiTE::initialize();
	if (niteRc != nite::STATUS_OK)
	{
		printf("NiTE initialization failed\n");
		return 1;
	}

	niteRc = handTracker.create();
	if (niteRc != nite::STATUS_OK)
	{
		printf("Couldn't create user tracker\n");
		return 3;
	}

	handTracker.startGestureDetection(nite::GESTURE_WAVE);
	handTracker.startGestureDetection(nite::GESTURE_CLICK);
	printf("\nWave or click to start tracking your hand...\n");

	nite::HandTrackerFrameRef handTrackerFrame;

	//Iniciar_TUIO("192.168.29.149",3333, false);
	Iniciar_TUIO("localhost",3333, false);
	double fx_rgb = 5.2921508098293293e+02, fy_rgb = 5.2556393630057437e+02, cx_rgb = 3.2894272028759258e+02, cy_rgb = 2.6748068171871557e+02;
	while (!wasKeyboardHit())
	{
		niteRc = handTracker.readFrame(&handTrackerFrame);
		if (niteRc != nite::STATUS_OK)
		{
			printf("Get next frame failed\n");
			continue;
		}


		time1 = TUIO::TuioTime::getSessionTime();
		tuio->initFrame(time1);
		time1 = TUIO::TuioTime::getSessionTime();
		tuio->initFrame(time1);

		const nite::Array<nite::GestureData>& gestures = handTrackerFrame.getGestures();
		for (int i = 0; i < gestures.getSize(); ++i)
		{
			if (gestures[i].isComplete())
			{
				nite::HandId newId;
				handTracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
			}
		}

		const nite::Array<nite::HandData>& hands = handTrackerFrame.getHands();
		for (int i = 0; i < hands.getSize(); ++i)
		{
			const nite::HandData& hand = hands[i];
			if (hand.isTracking())
			{
				double X=0.0, Y=0.0, Z=0.0;
				double XP=0.0, YP=0.0, ZP=0.0;

				X = hand.getPosition().x/100.0;
				Y = hand.getPosition().y/100.0;
				Z = hand.getPosition().z/100.0;


				XP = ((9.9984628826577793e-01)*X) + ((1.2635359098409581e-03)*Y) + ((-1.7487233004436643e-02)*Z) + (1.9985242312092553e-02);
				YP = ((-1.4779096108364480e-03)*X) + ((9.9992385683542895e-01)*Y) + ((-1.2251380107679535e-02)*Z) + (-7.4423738761617583e-04);
				ZP = ((1.7470421412464927e-02)*X) + ((1.2275341476520762e-02)*Y) + ((9.9977202419716948e-01)*Z) + (-1.0916736334336222e-02);
				
				double P2D_rgb_x, P2D_rgb_y;
				

				P2D_rgb_x = (XP * fx_rgb / ZP) + cx_rgb;
				P2D_rgb_y = (YP * fy_rgb / ZP) + cy_rgb;

				CvLabel label = hand.getId();
				CvPoint2D64f XY;
				XY.x = hand.getPosition().x;
				XY.x = hand.getPosition().y;

				std::list<TuioCursor*> cursorList = tuio->getTuioCursors();
				bool existe_blob = false;
				TuioCursor *Mano=NULL;
				for (std::list<TuioCursor*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) 
				{
					if ((*tuioCursor)->getCursorID() == label)
					{
						Mano = (*tuioCursor);
						existe_blob = true;
						break;
					}
				}

				if(existe_blob==false)
				{
					tuio->addTuioCursor(P2D_rgb_x/640.0, (480.0 - P2D_rgb_y)/480.0, 0);
				}else{
					tuio->updateTuioCursor(Mano, P2D_rgb_x/640.0, (480.0 - P2D_rgb_y)/480.0, 0);
				}	

				//printf("%d. (%5.2f, %5.2f, %5.2f)\n", hand.getId(), hand.getPosition().x, hand.getPosition().y, hand.getPosition().z);
				printf("%d. (%5.2f, %5.2f, %5.2f)\n", hand.getId(), P2D_rgb_x, P2D_rgb_y, hand.getPosition().z);
			}
		}
		tuio->stopUntouchedMovingCursors();				
		tuio->removeUntouchedStoppedCursors();
		tuio->commitFrame();

		nite::NiTE::shutdown();

	}
}