SET( NAME comms )

SET( SOURCES
  Ssl.h 
  Ssl.cpp

  SslServer.h
  SslServer.cpp
  
  Connection.h
  Connection.cpp

  Packet.h

  StatePacket.h
  StatePacket.cpp
  )

SET( HEADERS
  SslServer.h
  Connection.h
  )

SET( CORELIBS
  ${QT_LIBRARIES}
  ${QT_QTNETWORK_LIBRARY}
  )

QT4_WRAP_CPP( HEADERS_MOC ${HEADERS} )

ADD_LIBRARY( ${NAME} ${SOURCES} ${HEADERS_MOC} )
TARGET_LINK_LIBRARIES( ${NAME} ${CORELIBS} )
