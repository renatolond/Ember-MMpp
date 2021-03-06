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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSystemTrayIcon>

class cLoadingThread;
class cSplashScreen;

namespace Ui {
class uMainWindow;
}

class cMainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit cMainWindow(QWidget *parent = 0);
  ~cMainWindow();
  void setVisible(bool visible);
  void closeEvent(QCloseEvent *event);
  
private slots:
  void on_actionExit_triggered();
  void icon_activated(QSystemTrayIcon::ActivationReason reason);
  void show_main(void);
  void close_splash(void);

private:
  Ui::uMainWindow *ui;
  QSystemTrayIcon *m_tray_icon;
  QAction *m_minimize_action;
  QAction *m_maximize_action;
  QAction *m_restore_action;
  QAction *m_quit_action;
  QMenu *m_tray_icon_menu;
  cLoadingThread *m_loading_thread;
  cSplashScreen *m_splash_screen;
  QThread *m_thread;

  void create_scrape_media_actions(void);
  void create_all_movies_menu(QMenu *menu);
  void create_movies_missing_itens_menu(QMenu *menu);
  void create_new_movies_menu(QMenu *menu);
  void create_marked_movies_menu(QMenu *menu);
  void create_current_filter_menu(QMenu *menu);
  void create_default_scraping_menu(QMenu *menu);

  void create_update_library_actions(void);

  void create_tray_actions(void);
};

#endif // MAINWINDOW_H
