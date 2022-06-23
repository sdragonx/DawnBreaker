cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Dawnbreaker")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

#SET(FREEGLUT_REPLACE_GLUT ON CACHE BOOL "" FORCE)

IF(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
ENDIF()

add_subdirectory(
  "${CMAKE_CURRENT_LIST_DIR}/third_party/SOIL/"
  "${CMAKE_CURRENT_BINARY_DIR}/SOIL"
  EXCLUDE_FROM_ALL
)

IF (APPLE)
ELSE()
  add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/"
    "${CMAKE_CURRENT_BINARY_DIR}/freeglut"
    EXCLUDE_FROM_ALL
  )
  set(FREEGLUT_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/include")
ENDIF()


add_library(
  ProvidedFramework
  STATIC
  src/ProvidedFramework/ObjectBase.h
  src/ProvidedFramework/ObjectBase.cpp
  src/ProvidedFramework/WorldBase.h
  src/ProvidedFramework/WorldBase.cpp
  src/ProvidedFramework/GameManager.h
  src/ProvidedFramework/GameManager.cpp
  src/ProvidedFramework/SpriteManager.h
  src/ProvidedFramework/SpriteManager.cpp
  src/utils.h
)

IF (APPLE)
  target_link_libraries(
    ProvidedFramework
    SOIL
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework GLUT"
  )

  target_include_directories(
    ProvidedFramework
    PUBLIC
    src/
    src/ProvidedFramework/
  )
ELSE()
  target_link_libraries(
    ProvidedFramework
    freeglut
    SOIL
  )

  target_include_directories(
    ProvidedFramework
    PUBLIC 
    ${FREEGLUT_INCLUDE_DIR}
    src/
    src/ProvidedFramework/
  )
ENDIF()

#####################################################################
# base
add_library(
  PartForYou
  STATIC
  src/PartForYou/GameWorld.h
  src/PartForYou/GameWorld.cpp
  src/PartForYou/GameObjects.h
  src/PartForYou/GameObjects.cpp
  src/PartForYou/Explosion.cpp
  src/PartForYou/Explosion.h
  src/PartForYou/Star.cpp
  src/PartForYou/Star.h
  src/utils.h
)

target_include_directories(
  PartForYou
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

target_link_libraries(
  PartForYou
  ProvidedFramework
)

#####################################################################
# Bullets
add_library(
  Bullets
  STATIC
  src/PartForYou/BlueBullet.cpp
  src/PartForYou/BlueBullet.h
  src/PartForYou/BulletBase.cpp
  src/PartForYou/BulletBase.h
  src/PartForYou/RedBullet.cpp
  src/PartForYou/RedBullet.h
  src/PartForYou/Meteor.cpp
  src/PartForYou/Meteor.h
  src/utils.h
)

target_include_directories(
  Bullets
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

target_link_libraries(
  Bullets
  PartForYou
)


#####################################################################
# Items
add_library(
  Items
  STATIC
  src/PartForYou/HPRestoreGoodie.cpp
  src/PartForYou/HPRestoreGoodie.h
  src/PartForYou/ItemBase.cpp
  src/PartForYou/ItemBase.h
  src/PartForYou/MeteorGoodie.cpp
  src/PartForYou/MeteorGoodie.h
  src/PartForYou/PowerUpGoodie.cpp
  src/PartForYou/PowerUpGoodie.h
  src/utils.h
)

target_include_directories(
  Items
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

target_link_libraries(
  Bullets
  PartForYou
)

#####################################################################
# Planes
add_library(
  Planes
  STATIC
  src/PartForYou/DawnBreaker.cpp
  src/PartForYou/DawnBreaker.h
  src/PartForYou/PlaneBase.cpp
  src/PartForYou/PlaneBase.h
  src/utils.h
)

target_include_directories(
  Planes
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

target_link_libraries(
  Planes
  PartForYou
  Bullets
)

#####################################################################
# Enemies
add_library(
  Enemies
  STATIC
  src/PartForYou/EnemyBase.cpp
  src/PartForYou/EnemyBase.h
  src/PartForYou/Alphatron.cpp
  src/PartForYou/Alphatron.h
  src/PartForYou/Omegatron.cpp
  src/PartForYou/Omegatron.h
  src/PartForYou/Sigmatron.cpp
  src/PartForYou/Sigmatron.h
  src/utils.h
)

target_include_directories(
  Enemies
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

target_link_libraries(
  Enemies
  PartForYou
  Planes
  Bullets
  Items
)

#####################################################################

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  ProvidedFramework
  PartForYou
  Bullets
  Planes
  Enemies
  Items
)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)
