cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(src)
link_libraries("-lboost_system -pthread")
find_package(Threads)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Weffc++ -std=c++11 -Wextra")


add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/keyboardHandler.h
        include/serverHandler.h
        include/StompBookClubClient.h
        include/UserData.h
        include/Book.h
        src/connectionHandler.cpp
        src/keyboardHandler.cpp
        src/serverHandler.cpp
        src/echoClient.cpp
        src/StompBookClubClient.cpp
        src/main.cpp
        src/UserData.cpp
        src/Book.cpp
        makefile)


#add_executable(Boost_Echo_Client
#        include/connectionHandler.h
#        include/StompBookClubClient.h
#        include/UserData.h
#        include/Book.h
#        src/connectionHandler.cpp
#        src/echoClient.cpp
#        src/StompBookClubClient.cpp
#        src/main.cpp
#        src/UserData.cpp
#        src/Book.cpp
#        makefile)
