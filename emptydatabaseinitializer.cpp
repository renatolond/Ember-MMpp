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
#include "emptydatabaseinitializer.h"

#include "sqlite3.h"

#include <QtXml>

void cEmptyDatabaseInitializer::read_xml_and_create_tables(sqlite3 *connection)
{
  QFile *file = new QFile("InstallTasks.xml");

  if(file->open(QIODevice::ReadOnly))
  {
    QDomDocument doc("xmldocument");
    QDomElement docElem;

    QString errormsg;
    int column,line;

    if(!doc.setContent(file, &errormsg, &line, &column))
    {
      return;
    }

    file->close();

    docElem = doc.documentElement();
    QDomElement commands_branch = docElem.firstChildElement("Commands");
    if(!commands_branch.isNull())
    {
      QDomNodeList node_list = commands_branch.elementsByTagName("Command");
      if(!node_list.isEmpty())
      {
        for(int i(0); i < node_list.size(); ++i)
        {
          QDomElement command = node_list.at(i).toElement();
          QString type = command.attribute("Type");
          if(type == "DB")
          {
            QDomElement execute = command.firstChildElement();
            QString text = execute.text();
            QByteArray query = text.toUtf8();
            sqlite3_stmt *statement;
            if(sqlite3_prepare_v2(connection, query.data(), query.size(), &statement, NULL) == SQLITE_OK)
            {
              // Execute command in sqlite database
              if(sqlite3_step(statement) != SQLITE_DONE)
              {
                qDebug() << "Statement failed." << sqlite3_errmsg(connection);
              }

              if(sqlite3_finalize(statement) != SQLITE_OK)
              {
                qDebug("Finalize failed!");
              }
              statement = NULL;
            }
          }
        }
      }
    }
  }
}

cEmptyDatabaseInitializer::cEmptyDatabaseInitializer()
{
}

