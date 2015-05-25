cmake_minimum_required(VERSION 2.6)
project (MCMC)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(main/include)
include_directories(Chain/include)
include_directories(Chain/tests)
include_directories(MCMCDatabaseConnection/tests)
include_directories(MCMCDatabaseConnection/include)
include_directories(DatabaseConnector/tests)
include_directories(DatabaseConnector/include)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests main/src/main.cpp MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp DatabaseConnector/src/DatabaseConnector.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread mysqlcppconn)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -g")
    set(CMAKE_EXE_LINKER_FLAGS "-s")
endif()
