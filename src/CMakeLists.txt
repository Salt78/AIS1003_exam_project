add_library(autoShapeSortingLib
        geoGeneration.cpp
        gridManager.cpp
        geoDetection.cpp
        geoManipulator.cpp
        shapeColorHandler.cpp
)


target_include_directories(autoShapeSortingLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(autoShapeSortingLib PRIVATE
        threepp::threepp
        ${OpenCV_LIBS})

