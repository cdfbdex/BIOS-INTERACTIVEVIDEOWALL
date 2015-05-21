/*
 TUIO C++ Library - part of the reacTIVision project
 http://reactivision.sourceforge.net/
 
 Copyright (c) 2005-2009 Martin Kaltenbrunner <mkalten@iua.upf.edu>
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "TuioTime.h"
#include "iostream"
using namespace TUIO;

	
long long TuioTime::start_seconds = 0;
long long TuioTime::start_micro_seconds = 0;
long long TuioTime::Processor_Frecuency = 0;

void TuioTime::initSession() {
	
	LARGE_INTEGER PFrequency;
	QueryPerformanceFrequency(&PFrequency);
	Processor_Frecuency = static_cast<long long>(PFrequency.QuadPart);
	TuioTime startTime = TuioTime::getSystemTime();
	start_seconds = startTime.getSeconds();
	start_micro_seconds = startTime.getMicroseconds();
	//Processor_Frecuency = 34;
}

TuioTime TuioTime::getSessionTime() {
	return  (getSystemTime() - getStartTime());
}

TuioTime TuioTime::getStartTime() {
	return TuioTime(start_seconds,start_micro_seconds);
}

TuioTime TuioTime::getSystemTime() {
#ifdef WIN32
	
	//High Precision Timer
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
	LARGE_INTEGER PFrequency;
	QueryPerformanceFrequency(&PFrequency);
	//std::cout<<"timerFreq_ = "<<PFrequency.QuadPart<<std::endl;
	
	TuioTime systemTime(long long(c.QuadPart * MSEC_SECOND / PFrequency.QuadPart));

	//Low Precision Timer
	//TuioTime systemTime(GetTickCount());
#else
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv,&tz);
	TuioTime systemTime(tv.tv_sec,tv.tv_usec);
#endif	
	return systemTime;
}
