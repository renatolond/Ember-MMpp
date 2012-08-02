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
