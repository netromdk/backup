SET( NAME util )

SET( SOURCES
  Utility.h
  Utility.cpp

  Paths.h
  Paths.cpp

  Env.h
  Env.cpp

  Database.h
  Database.cpp
  )

SET( HEADERS
  )

SET( CORELIBS
  ${QT_LIBRARIES}
  ${QT_QTNETWORK_LIBRARY}
  ${QT_QTSQL_LIBRARY}
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_LIBRARY( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${CORELIBS} )
