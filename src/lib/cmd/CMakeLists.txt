SET( NAME cmd )

INCLUDE_DIRECTORIES( .. )

SET( SOURCES
  CommandConsole.h
  CommandConsole.cpp

  CommandExecuter.h
  CommandExecuter.cpp

  CommandTreeNode.h
  CommandTreeNode.cpp

  CommandFunction.h

  CommandOption.h
  CommandOption.cpp

  PositionalCommand.h
  PositionalCommand.cpp

  CommandType.h
  )

SET( HEADERS
  )

SET( CORELIBS
  ${QT_LIBRARIES}
  util
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_LIBRARY( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${CORELIBS} )

ADD_DEPENDENCIES(
  ${NAME}
  util
  )
