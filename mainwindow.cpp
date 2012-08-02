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
#include "mainwindow.h" // Base class

// start of qt files
#include <QCloseEvent>
#include <QMessageBox>
#include <QSystemTrayIcon>
// end of qt files

// Start of auto generated files
#include "ui_mainwindow.h"
// End of auto generated files

// Start of project files
#include "loadingthread.h"
#include "splashscreen.h"
// End of project files

cMainWindow::cMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::uMainWindow)
{
  QIcon icon = QIcon(":/icons/images/Resources/Logo.png");
  setWindowIcon(icon);
  ui->setupUi(this);

  create_scrape_media_actions();
  create_update_library_actions();

  m_splash_screen = new cSplashScreen(this);
  m_splash_screen->show();

  m_thread = new QThread();
  m_loading_thread = new cLoadingThread();
  m_loading_thread->moveToThread(m_thread);
  connect(m_loading_thread, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
  connect(m_loading_thread, SIGNAL(progress(QString,int)), m_splash_screen, SLOT(update_progress(QString,int)));
  connect(m_loading_thread, SIGNAL(show_main()), this, SLOT(show_main()));
  connect(m_loading_thread, SIGNAL(close_splash()), this, SLOT(close_splash()));
  connect(m_thread, SIGNAL(started()), m_loading_thread, SLOT(process()));
  connect(m_loading_thread, SIGNAL(finished()), m_thread, SLOT(quit()));
  connect(m_loading_thread, SIGNAL(finished()), m_loading_thread, SLOT(deleteLater()));
  //connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));

  m_thread->start();

  if(QSystemTrayIcon::isSystemTrayAvailable())
  {
    m_tray_icon = new QSystemTrayIcon(this);
    m_tray_icon->setIcon(icon);
    m_tray_icon->show();
    connect(m_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(icon_activated(QSystemTrayIcon::ActivationReason)));
    create_tray_actions();
  }
}

cMainWindow::~cMainWindow()
{
  m_thread->wait();
  delete m_thread;
  delete ui;
}

void cMainWindow::setVisible(bool visible)
{
  m_minimize_action->setEnabled(visible);
  m_maximize_action->setEnabled(!isMaximized());
  m_restore_action->setEnabled(isMaximized() || !visible);
  QMainWindow::setVisible(visible);
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
  if (m_tray_icon->isVisible()) {
      QMessageBox::information(this, tr("Systray"),
                               tr("The program will keep running in the "
                                  "system tray. To terminate the program, "
                                  "choose <b>Quit</b> in the context menu "
                                  "of the system tray entry."));
      hide();
      event->ignore();
  }
}

void cMainWindow::on_actionExit_triggered()
{
  this->close();
}

void cMainWindow::icon_activated(QSystemTrayIcon::ActivationReason reason)
{
  switch(reason)
  {
  case QSystemTrayIcon::Trigger:
  case QSystemTrayIcon::DoubleClick:
  case QSystemTrayIcon::MiddleClick:
  default:
    ;
  }
}

void cMainWindow::show_main()
{
  this->show();
}

void cMainWindow::close_splash()
{
  m_splash_screen->close();
}

void cMainWindow::create_scrape_media_actions()
{
  QMenu *menu = new QMenu();

  create_all_movies_menu(menu);
  create_movies_missing_itens_menu(menu);
  create_new_movies_menu(menu);
  create_marked_movies_menu(menu);
  create_current_filter_menu(menu);
  // custom scraper

  ui->scrapeMediaToolButton->setMenu(menu);
}

void cMainWindow::create_all_movies_menu(QMenu *menu)
{
  QMenu *all_movies_menu = new QMenu("All Movies");
  create_default_scraping_menu(all_movies_menu);
  menu->addMenu(all_movies_menu);
}

void cMainWindow::create_movies_missing_itens_menu(QMenu *menu)
{
  QMenu *movies_missing_itens_menu = new QMenu("Movies Missing Items");
  create_default_scraping_menu(movies_missing_itens_menu);
  menu->addMenu(movies_missing_itens_menu);
}

void cMainWindow::create_new_movies_menu(QMenu *menu)
{
  QMenu *new_movies_menu = new QMenu("New Movies");
  create_default_scraping_menu(new_movies_menu);
  menu->addMenu(new_movies_menu);
}

void cMainWindow::create_marked_movies_menu(QMenu *menu)
{
  QMenu *marked_movies_menu = new QMenu("Marked Movies");
  create_default_scraping_menu(marked_movies_menu);
  menu->addMenu(marked_movies_menu);
}

void cMainWindow::create_current_filter_menu(QMenu *menu)
{
  QMenu *current_filter_menu = new QMenu("Current Filter");
  create_default_scraping_menu(current_filter_menu);
  menu->addMenu(current_filter_menu);
}

void cMainWindow::create_default_scraping_menu(QMenu *menu)
{
  QMenu *automatic = new QMenu("Automatic (Force Best Match)");
  QAction *all_items = new QAction("All Items", this);
  automatic->addAction(all_items);

  QMenu *ask = new QMenu("Ask (Require Input If No Exact Match)");
  all_items = new QAction("All Items", this);
  ask->addAction(all_items);

  menu->addMenu(automatic);
  menu->addMenu(ask);
}

void cMainWindow::create_update_library_actions()
{
  QMenu *menu = new QMenu();

  QAction *movies = new QAction("Movies", this);
  menu->addAction(movies);
  QAction *tv_shows = new QAction("TV Shows", this);
  menu->addAction(tv_shows);

  ui->updateLibraryToolButon->setMenu(menu);
}

void cMainWindow::create_tray_actions()
{
  m_tray_icon_menu = new QMenu(this);

  m_minimize_action = new QAction(tr("Mi&nimize"), this);
  connect(m_minimize_action, SIGNAL(triggered()), this, SLOT(hide()));
  m_tray_icon_menu->addAction(m_minimize_action);

  m_maximize_action = new QAction(tr("Ma&ximize"), this);
  connect(m_maximize_action, SIGNAL(triggered()), this, SLOT(showMaximized()));
  m_tray_icon_menu->addAction(m_maximize_action);

  m_restore_action = new QAction(tr("&Restore"), this);
  connect(m_restore_action, SIGNAL(triggered()), this, SLOT(showNormal()));
  m_tray_icon_menu->addAction(m_restore_action);

  m_tray_icon_menu->addSeparator();

  m_quit_action = new QAction(tr("&Quit"), this);
  connect(m_quit_action, SIGNAL(triggered()), qApp, SLOT(quit()));
  m_tray_icon_menu->addAction(m_quit_action);

  m_tray_icon->setContextMenu(m_tray_icon_menu);
}
