add_library(SceneriesLib geoGeneration.cpp)
add_library(GridManagerLib gridManager.cpp)
add_library(geoDetectionLib geoDetection.cpp)


target_include_directories(SceneriesLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(GridManagerLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(geoDetectionLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(glad CONFIG REQUIRED)

target_link_libraries(SceneriesLib PRIVATE threepp::threepp)
target_link_libraries(geoDetectionLib PRIVATE threepp::threepp)
target_link_libraries(geoDetectionLib PRIVATE ${OpenCV_LIBS})
target_link_libraries(geoDetectionLib PRIVATE glad::glad)

