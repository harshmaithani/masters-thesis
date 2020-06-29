// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// This file is part of FZIs ic_workspace.
//
// This program is free software licensed under the LGPL
// (GNU LESSER GENERAL PUBLIC LICENSE Version 3).
// You can find a copy of this license in LICENSE folder in the top
// directory of the source code.
//
// © Copyright 2014 FZI Forschungszentrum Informatik, Karlsruhe, Germany
//
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Klaus Uhl <uhl@fzi.de>
 * \date    2009-07-03
 *
 * \brief   Contains icl_logging::SQLiteLogDb
 *
 * \b icl_logging::SQLiteLogDb
 *
 */
//----------------------------------------------------------------------
#ifndef ICL_CORE_LOGGING_SQLITE_LOG_DB_H_INCLUDED
#define ICL_CORE_LOGGING_SQLITE_LOG_DB_H_INCLUDED

#include <sqlite3.h>

#include <icl_core/TimeStamp.h>

namespace icl_core {
namespace logging {

class SQLiteLogDb
{
public:
  SQLiteLogDb(const icl_core::String& db_filename, bool rotate);
  ~SQLiteLogDb();

  void openDatabase();
  void closeDatabase();
  void writeLogLine(const char *app_id, const char *timestamp,
                    const char *log_stream, const char *log_level, const char *filename,
                    size_t line, const char *class_name, const char *object_name,
                    const char *function_name, const char *message_text);

private:
  icl_core::String m_db_filename;
  sqlite3 *m_db;
  sqlite3_stmt *m_insert_stmt;

  bool m_rotate;
  int64_t m_last_rotation;

  static icl_core::String m_create_sql;
  static icl_core::String m_insert_sql;
};

}
}

#endif
