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
  
private:
  Ui::cSplashScreen *ui;
};

#endif // SPLASHSCREEN_H
