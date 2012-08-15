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
#include "loadingthread.h"

#include <QEventLoop>

#include "sqlite3.h"

#include "filedownloader.h"
#include "emptydatabaseinitializer.h"

cLoadingThread::cLoadingThread()
{
}

cLoadingThread::~cLoadingThread()
{
}

void cLoadingThread::process()
{
  // See if any pending file needs to install. Do this before loading
  // modules/themes/etc
  emit progress("Basic setup...", 10);

  // Load modules?
  // In EmberMM it runs modulesmanager and loads the API.

  // Backup old log

  //advanced_settings.load_defaults -- clsAdvancedSettings.vb:337
  //load advanced settings xml

  //create modules and modules/lang folders

  emit progress("Loading settings...", 20);
  // load from Settings.xml

  emit progress("Creating default options...", 30);
  // Create default options
  emit progress("Loading modules...", 40);

  // runtime objects seems like they are dll's or something like that.
  // MenuMediaList, MenuTVShowList, MediaList, TopMenu, MainTool, TrayMenu,
  // DelegateLoadMedia, DelegateOpenImageViewer.
  // load everything

  // see isCL flag, for command-line. What is the best approach?

  // load modules, external scrapers, external tv scrapers, then find out the
  // versions from each, and load external languages for each one.

  // loads the gui if isCL is false, something about double buffer? Maybe for
  // previewing?

  // Create temp dir

  // if isCL, then loads all CL arguments. Think this should be moved to main

  emit progress("Loading translations...", 50);

  emit progress("Positioning controls...", 60);

  // Here is where he position all the panels and main window. This can't be
  // done here in the loading thread, as it cannot change the gui. But it should
  // be able to emit a signal so that the GUI, now knowing the size, can take
  // care of it

  emit progress("Loading database...", 70);
  QUrl xmlUrl("http://pcjco.dommel.be/emm-r/updates/commands_base.xml");
  m_downloader = new cFileDownloader(xmlUrl, this);
  {
    QEventLoop event_loop;
    emit progress("Downloading database file...", 81);
    //  connect(m_downloader, SIGNAL(downloaded()), SLOT(load_things()));
    connect(m_downloader, SIGNAL(downloaded()), &event_loop, SLOT(quit()));
    event_loop.exec();
  }
//  {
//    //qDebug("Still running...");
//  }

  m_downloader->save_to_file("InstallTasks.xml");

  sqlite3 *connection;
  if(sqlite3_open("Media.emm", &connection) != SQLITE_OK)
  {
    qDebug("Failed to open database.");
  }

  cEmptyDatabaseInitializer p;
  p.read_xml_and_create_tables();

  emit progress("Setting menus...", 80);

  emit progress("Ok!", 100);

//  emit show_main();
//  emit close_splash();

//  emit finished();
}

