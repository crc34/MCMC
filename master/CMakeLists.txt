cmake_minimum_required(VERSION 2.6)
project (MCMC)

#IF (MY_COMPILER_OPTION STREQUAL "Intel")
  MESSAGE(STATUS "** Compiling with Intel settings **")
  SET(CMAKE_CXX_COMPILER "/opt/intel/bin/icpc")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -w")
  SET(CMAKE_CXX_FLAGS_DEBUG "-g")
#ENDIF ()


# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(main/include)
include_directories(Chain/include)
include_directories(Chain/tests)
include_directories(ChainRunner/include)
include_directories(ChainRunner/tests)
include_directories(MCMCDatabaseConnection/tests)
include_directories(MCMCDatabaseConnection/include)
include_directories(DatabaseConnector/tests)
include_directories(DatabaseConnector/include)
include_directories($ENV{GMOCK_HOME}/include)
link_directories($ENV{GMOCK_HOME}/build)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -std=c++0x")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests main/src/main.cpp MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp DatabaseConnector/src/DatabaseConnector.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} gmock pthread mysqlcppconn)


if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=gnu++0x -g")
    set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()
