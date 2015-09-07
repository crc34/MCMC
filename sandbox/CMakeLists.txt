cmake_minimum_required(VERSION 2.6)
project (MCMC)

find_package( OpenCV REQUIRED )
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

#IF (MY_COMPILER_OPTION STREQUAL "Intel")
  MESSAGE(STATUS "** Compiling with Intel settings **")
  SET(CMAKE_CXX_COMPILER "mpicc")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -w")
  SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
#ENDIF ()

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -std=c++0x")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(run src/main.cpp)

target_link_libraries(run -lmysqlcppconn -lgsl -lgslcblas)
target_link_libraries(run pthread)
target_link_libraries(run ${OpenCV_LIBS} )
target_link_libraries(run ${MPI_LIBRARIES})

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x")
    set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()
