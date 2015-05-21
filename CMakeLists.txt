cmake_minimum_required(VERSION 2.8)

project( BIOS-Interactive_Video_Wall )

add_subdirectory(3rdparty/cvblob)
add_subdirectory(apps/InteractiveVideoWall)
add_subdirectory(apps/MultiHandInteractionTUIO)
add_subdirectory(apps/MultiUserInteractionTUIO)
add_subdirectory(apps/VideoPlayer)
