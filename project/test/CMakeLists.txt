cmake_minimum_required(VERSION 3.0)
project(my_project)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find ROOT package and include its directories and libraries
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
    message(STATUS "ROOT found: ${ROOT_USE_FILE}")
else()
    message(FATAL_ERROR "Could not find ROOT")
endif()

include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARY_DIRS})
add_definitions(${ROOT_CXX_FLAGS})

# Add the Eigen include directory
# find_package(Eigen3 REQUIRED)
# include_directories(${EIGEN3_INCLUDE_DIRS})

# Set the path to the source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/main)

# Set the output directories for the executable and the library
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Add the source files to a list
file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)

# Add the executable target(s)
file(GLOB MAIN_FILES ${MAIN_DIR}/*.cpp)
foreach(main_file ${MAIN_FILES})
    get_filename_component(main_name ${main_file} NAME_WE)
    add_executable(${main_name} ${main_file})
    target_link_libraries(${main_name} PRIVATE FC ${ROOT_LIBRARIES})
    target_include_directories(${main_name} PRIVATE ${SRC_DIR} ${EIGEN3_INCLUDE_DIRS})
endforeach()

# Add the library target
add_library(FC STATIC ${SRC_FILES})
target_include_directories(FC PUBLIC ${SRC_DIR} ${EIGEN3_INCLUDE_DIRS})
target_link_libraries(FC PUBLIC ${ROOT_LIBRARIES})

# Add the installation rules
install(TARGETS FC DESTINATION lib)
foreach(main_file ${MAIN_FILES})
    get_filename_component(main_name ${main_file} NAME_WE)
    install(TARGETS ${main_name} DESTINATION bin)
endforeach()
















# =====================================================


# # Set the minimum required version of CMake
# cmake_minimum_required(VERSION 3.5)

# # Set the project name
# project(PIC1)

# # Set the C++ standard
# set(CMAKE_CXX_STANDARD 14)

# # Find the required packages
# find_package(ROOT REQUIRED)

# # Call root-config to get the include directories, compile flags, and library flags
# execute_process(COMMAND root-config --incdir OUTPUT_VARIABLE ROOT_INCLUDE_DIRS)
# execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS)
# execute_process(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS)

# # Strip newline characters from the output of root-config
# string(STRIP ${ROOT_INCLUDE_DIRS} ROOT_INCLUDE_DIRS)
# string(STRIP ${ROOT_CXX_FLAGS} ROOT_CXX_FLAGS)
# string(STRIP ${ROOT_LD_FLAGS} ROOT_LD_FLAGS)

# # Add the include directories and compile flags to the C++ compiler
# include_directories(${ROOT_INCLUDE_DIRS} include)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")

# # Add the source files
# file(GLOB SOURCES "src/*.cpp")
# add_executable(PIC1 ${SOURCES})

# # Link against the required libraries
# target_link_libraries(PIC1 ${ROOT_LD_FLAGS})

# cmake_minimum_required(VERSION 3.12)
# project(my_project)

# set(CMAKE_CXX_STANDARD 17)

# # Find ROOT package and include directories
# find_package(ROOT REQUIRED COMPONENTS RIO Hist Tree)

# # Add include directories for ROOT and other libraries
# include_directories(${ROOT_INCLUDE_DIRS}) # ${EIGEN_INCLUDE_DIRS}

# # Add library directories for ROOT and other libraries
# link_directories(${ROOT_LIBRARY_DIR} ${LIBDIR})

# # Define source files and executable targets
# file(GLOB SRCS src/*.cpp)
# foreach(EXE_FILE ${SRCS})
#     get_filename_component(EXE_NAME ${EXE_FILE} NAME_WE)
#     add_executable(${EXE_NAME} ${EXE_FILE})
#     target_link_libraries(${EXE_NAME} FC ${ROOT_LIBRARIES})
# endforeach()

# # Create static library from object files
# file(GLOB LIB_SRCS src/*.cpp)
# add_library(FC STATIC ${LIB_SRCS})

# # Set compile flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# # Set output directories
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# # Print diagnostic information
# message(STATUS "SRCS: ${SRCS}")
# message(STATUS "ROOT_INCLUDE_DIRS: ${ROOT_INCLUDE_DIRS}")
# message(STATUS "ROOT_LIBRARY_DIR: ${ROOT_LIBRARY_DIR}")
# message(STATUS "ROOT_LIBRARIES: ${ROOT_LIBRARIES}")


# cmake_minimum_required(VERSION 3.0)

# project(PIC1)

# # Add C++11 support
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# # Set the path to the CERN ROOT installation
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)
# # list(APPEND CMAKE_PREFIX_PATH /home/pmfig/root)
# find_package(ROOT REQUIRED COMPONENTS RIO Net)


# # Include directories
# include_directories(${PROJECT_SOURCE_DIR}/src ${ROOT_INCLUDE_DIRS})

# # Add source files
# file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# # Build the executable
# add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp ${SOURCES})

# # Link against ROOT libraries
# target_link_libraries(${PROJECT_NAME} ${ROOT_LIBRARIES})
