cmake_minimum_required(VERSION 2.6)
project (MCMC)

#IF (MY_COMPILER_OPTION STREQUAL "Intel")
  MESSAGE(STATUS "** Compiling with Intel settings for profiling **")
  SET(CMAKE_CXX_COMPILER "/opt/intel/bin/icpc")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -w")
  SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
#ENDIF ()

# Locate GTest
include_directories($ENV{GMOCK_HOME}/include)
include_directories($ENV{GMOCK_HOME}/gtest/include)
include_directories(main/include)
include_directories(Chain/include)
include_directories(Chain/inl)
include_directories(Chain/tests)
include_directories(ChainRunner/include)
include_directories(ChainRunner/tests)
include_directories(MCMCDatabaseConnection/tests)
include_directories(MCMCDatabaseConnection/include)
include_directories(DatabaseConnector/tests)
include_directories(DatabaseConnector/include)
include_directories(testing)
include_directories(global)
link_directories($ENV{GMOCK_HOME}/build $ENV{GMOCK_HOME}/gtest/build)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -std=c++0x")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests main/src/main.cpp MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp DatabaseConnector/src/DatabaseConnector.cpp)

target_link_libraries(runTests -lmysqlcppconn -lgsl -lgslcblas)
target_link_libraries(runTests pthread)
target_link_libraries(runTests gmock)
target_link_libraries(runTests gtest)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x -g -mkl:parallel -static-intel")
    set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()
