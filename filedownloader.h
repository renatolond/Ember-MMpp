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
