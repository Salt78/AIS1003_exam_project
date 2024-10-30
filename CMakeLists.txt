cmake_minimum_required(VERSION 3.19)
project(threeppxopencv)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

add_subdirectory(src)

set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 3f509a0df61cd3be88e4f71785cfea24a9c688fb
)
FetchContent_MakeAvailable(threepp)

add_executable(threeppxopencv src/main.cpp)
target_link_libraries(threeppxopencv PRIVATE threepp::threepp)

find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(threeppxopencv PRIVATE ${OpenCV_LIBS})

find_package(glad CONFIG REQUIRED)
target_link_libraries(threeppxopencv PRIVATE glad::glad)

target_link_libraries(threeppxopencv PRIVATE GridManagerLib)

target_link_libraries(threeppxopencv PRIVATE SceneriesLib)




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
