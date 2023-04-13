project(CalculateAlign)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} sourceFiles)

add_library(${PROJECT_NAME} MODULE ${sourceFiles})

target_link_libraries(${PROJECT_NAME} LLVM)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)