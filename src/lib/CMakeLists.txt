SET( NAME backup )

SET( SOURCES
  Config.h
  Config.cpp
  ConfigTreeNode.h
  ConfigTreeNode.cpp
  )

SET( HEADERS
  )

SET( CORELIBS
  ${QT_LIBRARIES}
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_LIBRARY( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${CORELIBS} )

