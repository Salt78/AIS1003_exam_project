cmake_minimum_required(VERSION 3.19)
project(threeppxopencv)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

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
endif ()

add_executable(threeppxopencv main.cpp)

target_link_libraries(threeppxopencv PRIVATE
        threepp::threepp
        ${OpenCV_LIBS}
        autoShapeSortingLib)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

######### Emscripten #######
if (DEFINED EMSCRIPTEN)

    set(LINK_FLAGS " --bind -sUSE_GLFW=3 -sGL_DEBUG=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
    -sFULL_ES3 -sASSERTIONS -sALLOW_MEMORY_GROWTH -sWASM=1")

    set_target_properties("demo"
            PROPERTIES SUFFIX ".html"
            LINK_FLAGS "${LINK_FLAGS}"
    )

endif ()
###########################

message(STATUS "Include directories for geoDetectionLib: ${CMAKE_SOURCE_DIR}/include")