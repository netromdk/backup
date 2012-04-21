SET( NAME server )

INCLUDE_DIRECTORIES( .. )
INCLUDE_DIRECTORIES( ../lib )

SET( SOURCES
  Main.cpp

  Server.h
  Server.cpp
  ServerConfig.h
  ServerConfig.cpp
  DefaultConfig.h
  DefaultConfig.cpp
  )

SET( HEADERS
  Server.h      
  )

SET( LIBS
  ${QT_LIBRARIES}
  util
  conf
  comms
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_EXECUTABLE( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${LIBS} )

ADD_DEPENDENCIES(
  ${NAME}
  util
  conf
  comms
  )
