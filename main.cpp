/** ----------------------------------------------------------------------------
 * Embed Media Manager++ -- Renato "Lond" Cerqueira based on Embed Media Manager
 * Created by Lond in July/2012
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
#include <QApplication>
#include "mainwindow.h"

#include <databasemovie.h>
#include <settings.h>

int main(int argc, char *argv[])
{
  boost::shared_ptr<sDatabaseMovie> m(new sDatabaseMovie());
  sSettings::set_current_movie(m);
  QApplication a(argc, argv);
  cMainWindow w;
  w.show();
  
  return a.exec();
}