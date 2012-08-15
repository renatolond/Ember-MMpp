/** ----------------------------------------------------------------------------
 * Embed Media Manager++ -- Renato "Lond" Cerqueira based on Embed Media Manager
 * Created by Lond in August/2012
 * -----------------------------------------------------------------------------
 * This file is part of Embed Media Manager++.
 *
 * Embed Media Manager++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * Embed Media Manager++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Ember Media Manager++.  If not, see <http://www.gnu.org/licenses/>.
 * -----------------------------------------------------------------------------
 */
#include "factory.h" // Class definitions

// Start of Qt headers
#include <QDebug>
#include <QEventLoop>
#include <QFile>
// End of Qt headers

// Start of deps headers
#include "sqlite3.h"
// End of deps headers

// Start of project headers
#include "emptydatabaseinitializer.h"
#include "filedownloader.h"
#include "movie.h"
// End of project headers

namespace nDao
{
sqlite3 *cFactory::m_connection;
sqlite3 *cFactory::m_jobs_connection;

void clear_new(void)
{
  cMovie *movie_dao = cFactory::create_movie_dao();
  qDebug() << "Failing." << (int)cFactory::get_connection();
  movie_dao->clear_new();
}

cFactory::cFactory(void)
{
  m_connection = NULL;
  m_jobs_connection = NULL;
}

void cFactory::create_databases(void)
{
  cFileDownloader *downloader;
  downloader = NULL;

  QUrl xmlUrl("http://pcjco.dommel.be/emm-r/updates/commands_base.xml");
  downloader = new cFileDownloader(xmlUrl); // , this);
  {
    QEventLoop event_loop;
    //emit progress("Downloading database file...", 81);
    QObject::connect(downloader, SIGNAL(downloaded()), &event_loop, SLOT(quit()));
    event_loop.exec();
  }

  downloader->save_to_file("InstallTasks.xml");

  if(sqlite3_open("Media.emm", &m_connection) != SQLITE_OK)
  {
    qDebug("Failed to open database.");
  }

  if(downloader)
  {
    cEmptyDatabaseInitializer p;
    //emit progress("Creating database...", 82);
    p.read_xml_and_create_tables(m_connection);

    QFile::remove("InstallTasks.xml");
  }
}

void cFactory::create_jobs_database()
{
  if(sqlite3_open("JobLogs.emm", &m_jobs_connection) != SQLITE_OK)
  {
    qDebug("Failed to open jobs database.");
  }

  QString jobs_query = (QString)"CREATE TABLE IF NOT EXISTS Jobs("+
      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "+
      "MediaType INTEGER NOT NULL, "+
      "MediaID INTEGER NOT NULL, "+
      "LastDateAdd TEXT "+
      ");";
  QString jobs_entry_query = (QString)"CREATE TABLE IF NOT EXISTS JobsEntry(" +
      "ID INTEGER PRIMARY KEY AUTOINCREMENT, " +
      "ItemType INTEGER NOT NULL, " +
      "Message INTEGER NOT NULL, " +
      "Details INTEGER NOT NULL, " +
      "DateAdd TEXT " +
      ");";
  sqlite3_stmt *statement;
  QByteArray query;

  // Create jobs table
  query = jobs_query.toUtf8();
  if(sqlite3_prepare_v2(m_jobs_connection, query.data(), query.size(), &statement, NULL) == SQLITE_OK)
  {
    // Execute command in sqlite database
    if(sqlite3_step(statement) != SQLITE_DONE)
    {
      qDebug() << "Statement failed." << sqlite3_errmsg(m_jobs_connection);
    }

    if(sqlite3_finalize(statement) != SQLITE_OK)
    {
      qDebug("Finalize failed!");
    }
    statement = NULL;
  }

  // Create JobsEntry table
  query = jobs_entry_query.toUtf8();
  if(sqlite3_prepare_v2(m_jobs_connection, query.data(), query.size(), &statement, NULL) == SQLITE_OK)
  {
    // Execute command in sqlite database
    if(sqlite3_step(statement) != SQLITE_DONE)
    {
      qDebug() << "Statement failed." << sqlite3_errmsg(m_jobs_connection);
    }

    if(sqlite3_finalize(statement) != SQLITE_OK)
    {
      qDebug("Finalize failed!");
    }
    statement = NULL;
  }
}

sqlite3 *cFactory::get_connection()
{
  return m_connection;
}

void cFactory::begin_connection_scope(void)
{
  if(!QFile::exists("JobLogs.emm"))
  {
    create_jobs_database();
  }
  else if(sqlite3_open("JobLogs.emm", &m_jobs_connection) != SQLITE_OK)
  {
    qDebug("Failed to open jobs database.");
  }

  if(!QFile::exists("Media.emm"))
  {
    create_databases();
  }
  else if(sqlite3_open("Media.emm", &m_connection) != SQLITE_OK)
  {
    qDebug("Failed to open database.");
  }
}

void cFactory::end_connection_scope(void)
{
  if(m_connection)
  {
    sqlite3_close(m_connection);
    m_connection = NULL;
  }
  if(m_jobs_connection)
  {
    sqlite3_close(m_jobs_connection);
    m_jobs_connection = NULL;
  }
}

cMovie *cFactory::create_movie_dao()
{
  qDebug() << (int) m_connection;
  return new cMovie();
}

}
