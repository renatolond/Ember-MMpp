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
