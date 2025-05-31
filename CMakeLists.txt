cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(e-learning)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} stdc++fs)

add_custom_target(run
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

set(DIST_DIR "${CMAKE_BINARY_DIR}/dist")
get_filename_component(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)

file(GLOB DATA_CSV_FILES "${CMAKE_SOURCE_DIR}/data/*.csv")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/data")
foreach(csv_file ${DATA_CSV_FILES})
  configure_file(${csv_file} ${CMAKE_BINARY_DIR}/data/ COPYONLY)
endforeach()

add_custom_target(dist
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${DIST_DIR}/
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${MINGW_BIN_PATH}/libgcc_s_seh-1.dll" "${MINGW_BIN_PATH}/libstdc++-6.dll" "${MINGW_BIN_PATH}/libwinpthread-1.dll" "${MINGW_BIN_PATH}/libmcfgthread-1.dll" ${DIST_DIR}/ || exit 0
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${DIST_DIR}/data
  COMMAND ${CMAKE_COMMAND} -E make_directory ${DIST_DIR}/data
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/*.csv ${DIST_DIR}/data/
  COMMAND ${CMAKE_COMMAND} -E echo "Distribution package created in ${DIST_DIR}/"
  COMMAND ${CMAKE_COMMAND} -E echo "Contents: executable, DLLs, and data files"
  DEPENDS ${PROJECT_NAME}
  COMMENT "Creating distribution package with executable, DLLs, and data files"
)

add_custom_target(clean-dist
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${DIST_DIR}
  COMMENT "Cleaning distribution directory"
)