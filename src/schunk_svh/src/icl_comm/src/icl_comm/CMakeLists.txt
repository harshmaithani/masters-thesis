ICMAKER_SET("icl_comm")

ICMAKER_ADD_SOURCES(
  InterfaceAddress.cpp
  ByteOrderConversion.cpp
  )

ICMAKER_ADD_HEADERS(
  ByteOrderConversion.h
  ImportExport.h
  InterfaceAddress.h
  )

ICMAKER_LOCAL_CPPDEFINES(-DICL_COMM_EXPORT_SYMBOLS)
ICMAKER_GLOBAL_CPPDEFINES(-D_IC_BUILDER_ICL_COMM_)
ICMAKER_INCLUDE_DIRECTORIES(${ICL_COMM_INCLUDE_DIRS})

ICMAKER_EXTERNAL_DEPENDENCIES(EXPORT
  Boost
  Boost_FILESYSTEM
  Boost_SYSTEM
)

ICMAKER_INTERNAL_DEPENDENCIES(
  icl_core
  icl_core_config
  icl_core_logging
)

ICMAKER_BUILD_LIBRARY()
ICMAKER_INSTALL_HEADERS(${icmaker_target})
