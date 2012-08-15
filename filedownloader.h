/** ----------------------------------------------------------------------------
 * Embed Media Manager++ -- Renato "Lond" Cerqueira based on Embed Media Manager
 * Created by Lond in August/2012
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
#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class cFileDownloader : public QObject
{
  Q_OBJECT
public:
  explicit cFileDownloader(QUrl url, QObject *parent = 0);
  virtual ~cFileDownloader();
  QByteArray downloadedData() const;
  bool m_has_downloaded;

  void save_to_file(QString file);
signals:
  void downloaded();

private slots:
  void fileDownloaded(QNetworkReply* pReply);
  void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility f);

private:
  QNetworkAccessManager m_web_ctrl;
  QByteArray m_downloaded_data;
};

#endif // FILEDOWNLOADER_H
