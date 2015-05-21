cmake_minimum_required(VERSION 2.8)
#project( MultiHandInteraction )
find_package( OpenCV REQUIRED )
find_package(cvblob REQUIRED)


#######################################
# Build setup 
#######################################

OPTION (ENABLE_OPENNI2_NITE2 ON)

IF( ENABLE_OPENNI2_NITE2 )
set(OPENNI2_DEFINITIONS ${PC_OPENNI_CFLAGS_OTHER})
FIND_LIBRARY( OPENNI2_LIBRARY
             NAMES OpenNI2
             HINTS ${PC_OPENNI2_LIBDIR} ${PC_OPENNI2_LIBRARY_DIRS} /usr/lib
             PATHS "$ENV{PROGRAMFILES}/OpenNI2/Lib${OPENNI2_SUFFIX}" "$ENV{PROGRAMW6432}/OpenNI2/Lib${OPENNI2_SUFFIX}" "$ENV{PROGRAMW6432}/OpenNI2"
             PATH_SUFFIXES lib lib64
)
FIND_PATH( OPENNI2_INCLUDE_DIR OpenNI.h
          HINTS ${PC_OPENNI2_INCLUDEDIR} ${PC_OPENNI2_INCLUDE_DIRS} 
                  /usr/include/openni2 /usr/include/ni2
                  PATHS "$ENV{PROGRAMFILES}/OpenNI2/include" "$ENV{PROGRAMW6432}/OpenNI2/include"
          PATH_SUFFIXES openni2 ni2)

FIND_LIBRARY( NITE2_LIBRARY
             NAMES NiTE2
             HINTS ${PC_OPENNI2_LIBDIR} ${PC_OPENNI2_LIBRARY_DIRS} /usr/lib
             PATHS "$ENV{PROGRAMFILES}/PrimeSense/NiTE2/lib${OPENNI2_SUFFIX}" "$ENV{PROGRAMW6432}/PrimeSense/NiTE2/lib${OPENNI2_SUFFIX}"
             PATH_SUFFIXES lib
)
FIND_PATH( NITE2_INCLUDE_DIR NiTE.h
          HINTS ${PC_OPENNI2_INCLUDEDIR} ${PC_OPENNI2_INCLUDE_DIRS} /usr/include/openni2 /usr/include/nite2
          PATHS "$ENV{PROGRAMFILES}/PrimeSense/NiTE2/include" "$ENV{PROGRAMW6432}/PrimeSense/NiTE2/include"
          PATH_SUFFIXES openni2         
)
ENDIF( ENABLE_OPENNI2_NITE2 )
link_directories( ${OPENNI2_LIBRARY} ${NITE2_LIBRARY} ${cvBlob_LIB_DIR} )
INCLUDE_DIRECTORIES( ${OPENNI2_INCLUDE_DIR} ${NITE2_INCLUDE_DIR} ${cvBlob_INCLUDE_DIRS} "../../3rdparty/oscpack/" "../../3rdparty/TUIO/" "/")
#target_link_libraries( project ${OPENNI2_LIBRARY} ${NITE2_LIBRARY} )

SET(HEADERS
  NiteSampleUtilities.h
  #OSCPACK
  ../../3rdparty/oscpack/ip/IpEndpointName.h
  ../../3rdparty/oscpack/ip/NetworkingUtils.h
  ../../3rdparty/oscpack/ip/PacketListener.h
  ../../3rdparty/oscpack/ip/TimerListener.h
  ../../3rdparty/oscpack/ip/UdpSocket.h
  ../../3rdparty/oscpack/osc/MessageMappingOscPacketListener.h
  ../../3rdparty/oscpack/osc/OscException.h
  ../../3rdparty/oscpack/osc/OscHostEndianness.h
  ../../3rdparty/oscpack/osc/OscOutboundPacketStream.h
  ../../3rdparty/oscpack/osc/OscPacketListener.h
  ../../3rdparty/oscpack/osc/OscPrintReceivedElements.h
  ../../3rdparty/oscpack/osc/OscReceivedElements.h
  ../../3rdparty/oscpack/osc/OscTypes.h
  #TUIO
  ../../3rdparty/TUIO/TuioClient.h
  ../../3rdparty/TUIO/TuioContainer.h
  ../../3rdparty/TUIO/TuioCursor.h
  ../../3rdparty/TUIO/TuioListener.h
  ../../3rdparty/TUIO/TuioObject.h
  ../../3rdparty/TUIO/TuioPoint.h
  ../../3rdparty/TUIO/TuioServer.h
  ../../3rdparty/TUIO/TuioTime.h

)

IF(WIN32) # Check if we are on Windows
	SET(SOURCE
		main.cpp
		#OSCPACK
		../../3rdparty/oscpack/ip/win32/NetworkingUtils.cpp
		../../3rdparty/oscpack/ip/win32/UdpSocket.cpp
		../../3rdparty/oscpack/ip/IpEndpointName.cpp
		../../3rdparty/oscpack/osc/OscOutboundPacketStream.cpp
		../../3rdparty/oscpack/osc/OscPrintReceivedElements.cpp
		../../3rdparty/oscpack/osc/OscReceivedElements.cpp
		../../3rdparty/oscpack/osc/OscTypes.cpp
		#TUIO
		../../3rdparty/TUIO/TuioClient.cpp
		../../3rdparty/TUIO/TuioServer.cpp
		../../3rdparty/TUIO/TuioTime.cpp		
	)
else()
	SET(SOURCE
		main.cpp
		#OSCPACK
		../../3rdparty/oscpack/ip/posix/NetworkingUtils.cpp
		../../3rdparty/oscpack/ip/posix/UdpSocket.cpp
		../../3rdparty/oscpack/ip/IpEndpointName.cpp
		../../3rdparty/oscpack/osc/OscOutboundPacketStream.cpp
		../../3rdparty/oscpack/osc/OscPrintReceivedElements.cpp
		../../3rdparty/oscpack/osc/OscReceivedElements.cpp
		../../3rdparty/oscpack/osc/OscTypes.cpp
		#TUIO
		../../3rdparty/TUIO/TuioClient.cpp
		../../3rdparty/TUIO/TuioServer.cpp
		../../3rdparty/TUIO/TuioTime.cpp		
	)
ENDIF()

INCLUDE_DIRECTORIES( ${OPENNI2_INCLUDE_DIR} ${NITE2_INCLUDE_DIR} "../../3rdparty/cvblob/include")

add_executable( MultiHandInteraction ${SOURCE} ${HEADERS})
IF(WIN32) # Check if we are on Windows
	target_link_libraries( MultiHandInteraction ${OpenCV_LIBS} ${OPENNI2_LIBRARY} ${NITE2_LIBRARY}  cvblob winmm ws2_32)
ELSE()
	target_link_libraries( MultiHandInteraction ${OpenCV_LIBS} ${OPENNI2_LIBRARY} ${NITE2_LIBRARY}  cvblob)
ENDIF()
