CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

PROJECT( BACKUP )

SET( CMAKE_COLOR_MAKEFILE ON )
SET( CMAKE_VERBOSE_MAKEFILE OFF )
SET( CMAKE_INCLUDE_CURRENT_DIR TRUE )
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )

IF( NOT CMAKE_BUILD_TYPE )
  SET( CMAKE_BUILD_TYPE MinSizeRel ) 
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2" )
ELSEIF (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  SET( CMAKE_BUILD_TYPE Debug ) 
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -O0 -g" )
  ADD_DEFINITIONS( "-Wall" )
ENDIF()

OPTION( BUILD_SERVER "Set to ON to build server program" ON )
OPTION( BUILD_AGENT "Set to ON to build agent program" ON )

# Dependencies.
FIND_PACKAGE( QT4 4.8.1 REQUIRED 
              COMPONENTS QtCore )
INCLUDE( ${QT_USE_FILE} )
ADD_DEFINITIONS( ${QT_DEFINITIONS})

# Add a target to generate API documentation with Doxygen.
FIND_PACKAGE( Doxygen 1.8.0 )
IF( DOXYGEN_FOUND )
  CONFIGURE_FILE( 
    ${PROJECT_SOURCE_DIR}/doc/doc.doxygen 
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
    @ONLY )
  ADD_CUSTOM_TARGET( 
    doc 
    ${DOXYGEN_EXECUTABLE} 
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" 
    VERBATIM )
ENDIF()

ADD_SUBDIRECTORY( src/lib )

IF( BUILD_SERVER MATCHES ON )
  ADD_SUBDIRECTORY( src/server )
ENDIF()

IF( BUILD_AGENT MATCHES ON )
  ADD_SUBDIRECTORY( src/agent )
ENDIF()

MESSAGE( STATUS "--------------------------------------------------" )
MESSAGE( STATUS "BUILD          = ${CMAKE_BUILD_TYPE}" )
MESSAGE( STATUS "BUILD_SERVER   = ${BUILD_SERVER}" )
MESSAGE( STATUS "BUILD_AGENT    = ${BUILD_AGENT}" )
MESSAGE( STATUS "--------------------------------------------------" )

IF( DOXYGEN_FOUND ) 
MESSAGE( STATUS "Doxygen was found - Use 'doc' target to generate." )
MESSAGE( STATUS "--------------------------------------------------" )
ENDIF()
