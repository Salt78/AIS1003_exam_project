function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE threepp Catch2::Catch2WithMain autoShapeSortingLib ${OpenCV_LIBS})
    target_include_directories(${name} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    add_test(NAME ${name} COMMAND ${name})
    #target_compile_definitions(${name} PRIVATE DATA_FOLDER="${PROJECT_SOURCE_DIR}/data")
endfunction()






add_subdirectory(grid)


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