SET( NAME cmd )

SET( SOURCES
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
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_LIBRARY( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${CORELIBS} )
