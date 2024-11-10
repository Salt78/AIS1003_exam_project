add_library(geoGenerationLib geoGeneration.cpp gridManager.cpp)
add_library(geoDetectionLib
        geoDetection.cpp
        detectedObjects.cpp
        geoManipulator.cpp)

target_include_directories(geoGenerationLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(geoDetectionLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(glad CONFIG REQUIRED)

target_link_libraries(geoGenerationLib PRIVATE threepp::threepp)
target_link_libraries(geoDetectionLib PRIVATE
        threepp::threepp
        ${OpenCV_LIBS}
        glad::glad)

