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
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDialog>

namespace Ui {
class cSplashScreen;
}

class cSplashScreen : public QDialog
{
  Q_OBJECT
  
public:
  explicit cSplashScreen(QWidget *parent = 0);
  ~cSplashScreen();
  
  void show_message(QString msg);

public slots:
  void update_progress(QString msg, int progress);

private:
  Ui::cSplashScreen *ui;
};

#endif // SPLASHSCREEN_H
