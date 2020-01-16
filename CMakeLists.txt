cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)


find_package(Threads)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Weffc++ -std=c++11 -Wextra")
include_directories(/usr/local/Cellar/boost/1.72.0/include/boost)
link_libraries(/usr/local/Cellar/boost/1.72.0/include/boost)
find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    #add_executable(10_file_io ${SOURCE_FILES})
    #target_link_libraries(${Boost_Echo_Client} ${Boost_LIBRARIES})
    include_directories(.)
    include_directories(include)
    include_directories(src)
    #link_libraries("-lboost_system -pthread")
endif()
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()


add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/keyboardHandler.h
        include/serverHandler.h
        include/ClientRunner.h
        include/UserData.h
        include/Book.h
        src/connectionHandler.cpp
        src/keyboardHandler.cpp
        src/serverHandler.cpp
        src/echoClient.cpp
        src/ClientRunner.cpp
        src/main.cpp
        src/UserData.cpp
        src/Book.cpp
        makefile)

