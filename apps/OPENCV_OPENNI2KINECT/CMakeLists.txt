cmake_minimum_required(VERSION 2.8)
#project( OpenCVOpenNI2KINECT3 )
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
link_directories( ${OPENNI2_LIBRARY} ${NITE2_LIBRARY} )
INCLUDE_DIRECTORIES( ${OPENNI2_INCLUDE_DIR} ${NITE2_INCLUDE_DIR} )
#target_link_libraries( project ${OPENNI2_LIBRARY} ${NITE2_LIBRARY} )

add_executable( OpenCVOpenNI2KINECT3 main.cpp)
target_link_libraries( OpenCVOpenNI2KINECT3 ${OpenCV_LIBS} ${OPENNI2_LIBRARY} ${NITE2_LIBRARY}  cvblob)

