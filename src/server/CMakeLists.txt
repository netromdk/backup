SET( NAME server )

INCLUDE_DIRECTORIES( .. )
INCLUDE_DIRECTORIES( ../lib )

SET( SOURCES
  Main.cpp

  ServerConfig.h
  ServerConfig.cpp
  )

SET( HEADERS
  )

SET( LIBS
  ${QT_LIBRARIES}
  conf
  util
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_EXECUTABLE( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${LIBS} )

ADD_DEPENDENCIES(
  ${NAME}
  conf
  util
  )
