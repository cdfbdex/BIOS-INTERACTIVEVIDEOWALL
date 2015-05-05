project(BIOS-Video_Player)

find_package(Qt4 COMPONENTS QtCore QtGui Phonon QtNetwork QtMultimedia REQUIRED)
find_package(OpenCV REQUIRED)
include(${QT_USE_FILE})

IF(WIN32)
	SET(QT_USE_MAIN true)
ENDIF(WIN32)


set(INTERACTIVE_VIDEO_WALL_HEADERS IVW_mainWindow.h IVW_settingsWindow.h)
set(INTERACTIVE_VIDEO_WALL_SOURCES IVW_mainWindow.cpp IVW_settingsWindow.cpp main.cpp IVW_setIcon.rc)
set(INTERACTIVE_VIDEO_WALL_UIS IVW_mainWindow.ui IVW_settingsWindow.ui)
set(INTERACTIVE_VIDEO_WALL_RESOURCES qplayer.qrc)

qt4_wrap_cpp(INTERACTIVE_VIDEO_WALL_MOC ${INTERACTIVE_VIDEO_WALL_HEADERS})
qt4_wrap_ui(INTERACTIVE_VIDEO_WALL_UIS_H ${INTERACTIVE_VIDEO_WALL_UIS})
qt4_add_resources(INTERACTIVE_VIDEO_WALL_RESOURCES_CPP ${INTERACTIVE_VIDEO_WALL_RESOURCES})

include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_executable(IVW_Video_Player
    ${INTERACTIVE_VIDEO_WALL_SOURCES}
    ${INTERACTIVE_VIDEO_WALL_MOC}
    ${INTERACTIVE_VIDEO_WALL_UIS_H}
    ${INTERACTIVE_VIDEO_WALL_RESOURCES_CPP} 
)

IF(WIN32)
	target_link_libraries(IVW_Video_Player ${QT_LIBRARIES} ${OpenCV_LIBS} ${QT_QTMAIN_LIBRARY})
ELSE()
	target_link_libraries(IVW_Video_Player ${QT_LIBRARIES} ${OpenCV_LIBS})
ENDIF()


IF(WIN32) # Check if we are on Windows
 if(MSVC) # Check if we are using the Visual Studio compiler
   set_target_properties(IVW_Video_Player PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
 elseif(CMAKE_COMPILER_IS_GNUCXX)
   # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
 else()
   message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
 endif()
elseif(UNIX)
 # Nothing special required
else()
 message(SEND_ERROR "You are on an unsupported platform! (Not Win32 or Unix)")
ENDIF()


install(TARGETS IVW_Video_Player RUNTIME DESTINATION bin COMPONENT Runtime BUNDLE DESTINATION . COMPONENT Runtime)