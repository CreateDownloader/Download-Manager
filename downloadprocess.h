#ifndef DOWNLOADPROGRESSSINGLECONNECT_H
#define DOWNLOADPROGRESSSINGLECONNECT_H

#include "downloadtable.h"

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QObject>
#include <QTime>
#include <QUrl>


class DownloadProcess : public QObject{
    Q_OBJECT
public:
    DownloadProcess(QUrl, DownloadTable*);
    void start();
    const QUrl &getUrl() const;
signals:
    void downloadFinished(QNetworkReply*);
public slots:
    void downloadProgress(qint64,qint64);
protected:
    QString timeHuman(const int);
    QString sizeHuman(const qint64);
private:
    DownloadTable *dataModel = nullptr;
    QUrl url;
    QString size;
    QTime downloadTime;
    QNetworkReply *currentDownload = nullptr;
    QNetworkAccessManager *manager = nullptr;
};

#endif // DOWNLOADPROGRESSSINGLECONNECT_H
