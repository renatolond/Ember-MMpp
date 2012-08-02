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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "splashscreen.h"

cMainWindow::cMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::uMainWindow)
{
  setWindowIcon(QIcon(":/icons/images/Resources/Logo.png"));
  ui->setupUi(this);

  create_scrape_media_actions();
  create_update_library_actions();

  cSplashScreen *splash = new cSplashScreen(this);
  splash->show();
}

cMainWindow::~cMainWindow()
{
  delete ui;
}

void cMainWindow::on_actionExit_triggered()
{
  this->close();
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
