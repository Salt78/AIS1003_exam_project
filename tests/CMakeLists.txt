add_executable(tests tests.cpp)
add_test(NAME tests COMMAND tests)

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(tests PRIVATE
        Catch2::Catch2WithMain
        geoDetectionLib
        geoGenerationLib
        threepp::threepp
        ${OpenCV_LIBS}
)