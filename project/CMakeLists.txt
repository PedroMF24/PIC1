cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 $(root-config --cflags) fPIC $(root-config --incdir)")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")


include_directories(src/)
include_directories(include/)

#add_library($(root-config --libs))
#add_library(($(root-config --cflags)))


# $(shell root-config --cflags) -fPIC // `root-config --cflags --glibs`

# find_package(Freetype REQUIRED)
# target_include_directories()

project(project)

add_executable(
    main.exe
    main.cpp
    src/main.cpp
    src/SM.cpp
    src/ExpConstraints.cpp
    src/FileStream.cpp
    src/Graph.cpp
    src/IDM.cpp
    src/MyRandom.cpp
    src/Parameters.cpp
    src/RootClass.cpp
    src/StopWatch.cpp
    src/TestFuncs.cpp
    src/TheoConstraints.cpp
)


# add_executable(
#     main
#     ../project/main.cpp
#     ../project/src/main.cpp
#     ../project/src/SM.cpp
#     ../project/src/ExpConstraints.cpp
#     ../project/src/FileStream.cpp
#     ../project/src/Graph.cpp
#     ../project/src/IDM.cpp
#     ../project/src/MyRandom.cpp
#     ../project/src/Parameters.cpp
#     ../project/src/RootClass.cpp
#     ../project/src/StopWatch.cpp
#     ../project/src/TestFuncs.cpp
#     ../project/src/TheoConstraints.cpp
# )

