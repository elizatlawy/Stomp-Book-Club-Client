cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(src)
link_libraries("-lboost_system")


add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/StompBookClubClient.h
        include/UserData.h
        include/Book.h
        src/connectionHandler.cpp
        src/echoClient.cpp
        src/StompBookClubClient.cpp
        src/main.cpp
        src/UserData.cpp
        src/Book.cpp
        makefile)


