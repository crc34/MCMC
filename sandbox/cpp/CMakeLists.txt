cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
if(CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-std=gnu++0x)
endif()
add_executable( DisplayImage src/DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
