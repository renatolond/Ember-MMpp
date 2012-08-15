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
#include "movie.h" // Class definitions

// Start of Qt headers
#include <QByteArray>
#include <QDebug>
#include <QString>
// End of Qt headers

// Start of deps headers
#include "sqlite3.h"
// End of deps headers

namespace nDao
{

cMovie::cMovie() :
  cFactory()
{
}

void cMovie::clear_new()
{
  if(cFactory::get_connection() == NULL)
  {
    qDebug() << "No connection available." << (int)cFactory::get_connection();
    return;
  }

  QString updateQuery = "UPDATE movies SET new = false";
  sqlite3_stmt *statement;

  QByteArray query = updateQuery.toUtf8();
  if(sqlite3_prepare_v2(cFactory::get_connection(), query.data(), query.size(), &statement, NULL) == SQLITE_OK)
  {
    // Execute command in sqlite database
    if(sqlite3_step(statement) != SQLITE_DONE)
    {
      qDebug() << "Statement failed." << sqlite3_errmsg(cFactory::get_connection());
    }

    if(sqlite3_finalize(statement) != SQLITE_OK)
    {
      qDebug("Finalize failed!");
    }
    statement = NULL;
  }
}

}
