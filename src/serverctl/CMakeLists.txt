SET( NAME serverctl )

INCLUDE_DIRECTORIES( .. )
INCLUDE_DIRECTORIES( ../lib )

SET( SOURCES
  Main.cpp

  CommandBuilder.h
  CommandBuilder.cpp

  HelpContext.h
  HelpContext.cpp

  AgentContext.h
  AgentContext.cpp
  )

SET( HEADERS
  )

SET( LIBS
  ${QT_LIBRARIES}
  util 
  cmd
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_EXECUTABLE( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${LIBS} )

ADD_DEPENDENCIES(
  ${NAME}
  util
  cmd
  )
