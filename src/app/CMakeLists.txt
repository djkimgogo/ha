cmake_minimum_required(VERSION 2.8)
project( baseApp )
find_package( OpenCV REQUIRED )
find_package (Threads)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../visualization/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty
  ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../database/include
)

add_executable( ${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_common.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/haBaseApp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_processor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_lines.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_circles.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_patterns.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_signs.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_colors.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_gps.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../imgproc/src/ha_sqlite_orm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../visualization/src/ha_visualizer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../database/include/ha_db_gps-odb.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/../database/include/ha_db_image-odb.cxx
)

add_executable( stereoCalibApp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/haStereoCalibApp.cpp
)

add_executable( stereoMatchApp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/haStereoMatchApp.cpp
)

link_directories(
    /usr/lib/x86_64-linux-gnu
    # /usr/lib
    /usr/local/lib
    )

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} gps sqlite3 odb-sqlite odb)
target_link_libraries( stereoCalibApp ${OpenCV_LIBS} )
target_link_libraries( stereoMatchApp ${OpenCV_LIBS})
