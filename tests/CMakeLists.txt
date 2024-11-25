#enable_testing()
add_executable(tests tests.cpp)
add_test(NAME tests COMMAND tests)

target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(tests PRIVATE
        Catch2::Catch2WithMain
        autoShapeSortingLib
        threepp::threepp
        ${OpenCV_LIBS}
)