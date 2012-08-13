#ifndef SETTINGSITEM_H
#define SETTINGSITEM_H

#include <QString>

struct sSettingItem
{
  QString default_value;
  QString name;
  QString section;
  QString value;
};

#endif // SETTINGSITEM_H
