cmake_minimum_required(VERSION 3.19)
project(AutoSortingShapes)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV CONFIG REQUIRED)

#Enabling/Disable tests
set(BUILD_TESTS ON)

include(FetchContent)
set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 1263fb25e57924ff2d3785b5f6d2b6d4fe4af6a7
)
FetchContent_MakeAvailable(threepp)


option(BUILD_TESTS "Build tests" ON)
if (BUILD_TESTS)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.7.1 # or a later release
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)

    #GPT helped me with this one
    file(COPY ${CMAKE_SOURCE_DIR}/data/testing_resources/images DESTINATION ${CMAKE_BINARY_DIR}/tests/data/testing_resources)
endif ()

add_subdirectory(src)

add_executable(AutoSortingShapes main.cpp)

target_link_libraries(AutoSortingShapes PRIVATE
        autoShapeSortingLib
        threepp::threepp
        opencv_core
        opencv_highgui
        opencv_imgproc
)
