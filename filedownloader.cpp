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
#include "filedownloader.h"

#include <QFile>
#include <QTextStream>

cFileDownloader::cFileDownloader(QUrl url, QObject *parent) :
  QObject(parent)
{
  connect(&m_web_ctrl, SIGNAL(finished(QNetworkReply*)),
              SLOT(fileDownloaded(QNetworkReply*)));
  connect(&m_web_ctrl, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
          SLOT(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));

  QNetworkRequest request(url);
  m_web_ctrl.get(request);
  m_has_downloaded = false;
}

cFileDownloader::~cFileDownloader()
{
}

QByteArray cFileDownloader::downloadedData() const
{
  return m_downloaded_data;
}

void cFileDownloader::save_to_file(QString file)
{
  QFile data(file);
  if(data.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream out(&data);
    out << m_downloaded_data;
  }
}

void cFileDownloader::fileDownloaded(QNetworkReply *pReply)
{
  m_downloaded_data = pReply->readAll();
  //emit a signal
  emit downloaded();
}

void cFileDownloader::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility f)
{
  if(f == QNetworkAccessManager::UnknownAccessibility || f == QNetworkAccessManager::NotAccessible)
    qDebug("Error: No accessibility.");
}
