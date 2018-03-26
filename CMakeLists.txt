CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )
PROJECT( QtOSG )

	if( NOT MSVC )
		SET( CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic -Wno-long-long" )
	ENDIF()

SET( CMAKE_INCLUDE_CURRENT_DIR ON )
SET( CMAKE_AUTOMOC ON )

# QT5 Handling - sample under OSX : cmake .. -DQT5_DIR=/usr/local/Cellar/qt/5.10.1
IF( DEFINED ENV{QT5_DIR} )
  SET( QT5_DIR $ENV{QT5_DIR} )
ENDIF()

SET( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_DIR} )

FIND_PACKAGE( Qt5Core )
FIND_PACKAGE( Qt5Gui  )
FIND_PACKAGE( Qt5OpenGL )
FIND_PACKAGE( OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer )

INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

SET( WITH_PICK_HANDLER         ON CACHE BOOL "Build with pick handler support" )
SET( WITH_SELECTION_PROCESSING ON CACHE BOOL "Build with selection processing support" )

SET( SOURCES
  MainWindow.cpp
  OSGWidget.cpp
  PickHandler.cpp
  QtOSG.cpp
)

ADD_EXECUTABLE( qtosg ${SOURCES} )

IF( WITH_PICK_HANDLER )
  MESSAGE( STATUS "Building with pick handler support" )

  SET_PROPERTY(
    TARGET qtosg
    APPEND PROPERTY COMPILE_DEFINITIONS WITH_PICK_HANDLER
  )
ENDIF()

IF( WITH_SELECTION_PROCESSING )
  MESSAGE( STATUS "Building with selection processing support" )

  SET_PROPERTY(
    TARGET qtosg
    APPEND PROPERTY COMPILE_DEFINITIONS WITH_SELECTION_PROCESSING
  )
ENDIF()

TARGET_LINK_LIBRARIES( qtosg
  ${OPENSCENEGRAPH_LIBRARIES}
  Qt5::Core
  Qt5::Gui
  Qt5::OpenGL
)

IF( MSVC )
  SET( QT_PLUGINS_DIR "${QT5_DIR}/plugins" )

  ######################################################################
  # Copy Qt plugins to 'Debug & Release' directories & configure qt.conf file
  ######################################################################

  fILE( GLOB qtplugin_dirs RELATIVE
    "${QT_PLUGINS_DIR}"
    "${QT_PLUGINS_DIR}/imageformats*"
    "${QT_PLUGINS_DIR}/platforms*"
  )
  FILE( REMOVE_RECURSE
    "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Debug/QtPlugins"
  )

  FILE( REMOVE_RECURSE
    "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Release/QtPlugins"
  )

  FILE( MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Debug/QtPlugins"
  )

  FILE( MAKE_DIRECTORY
    "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Release/QtPlugins"
  )

  FOREACH( qtplugin ${qtplugin_dirs} )
    FILE( COPY "${QT_PLUGINS_DIR}/${qtplugin}"
      DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Debug/QtPlugins"
    )
    FILE( COPY "${QT_PLUGINS_DIR}/${qtplugin}"
      DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Release/QtPlugins"
    )
  ENDFOREACH()

  FILE( WRITE
    "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Debug/qt.conf"
    "[Paths]\nPlugins = QtPlugins"
  )

  FILE( WRITE
    "${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_OUTPUT_PATH}/Release/qt.conf"
    "[Paths]\nPlugins = QtPlugins"
  )
ENDIF()

INSTALL( TARGETS  qtosg RUNTIME DESTINATION bin )
INSTALL( PROGRAMS qtosg.desktop DESTINATION share/applications )
