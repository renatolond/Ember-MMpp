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
#include "splashscreen.h"
#include "ui_splashscreen.h"

cSplashScreen::cSplashScreen(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::cSplashScreen)
{
  ui->setupUi(this);
}

cSplashScreen::~cSplashScreen()
{
  delete ui;
}

void cSplashScreen::show_message(QString msg)
{
  ui->message_label->setText(msg);
}

void cSplashScreen::update_progress(QString msg, int progress)
{
  ui->message_label->setText(msg);
  ui->progressBar->setValue(progress);
}
