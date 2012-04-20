SET( NAME agent )

INCLUDE_DIRECTORIES( .. )
INCLUDE_DIRECTORIES( ../lib )

SET( SOURCES
  Main.cpp

  Agent.h
  Agent.cpp
  AgentConfig.h
  AgentConfig.cpp
  DefaultConfig.h
  DefaultConfig.cpp
  )

SET( HEADERS
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
