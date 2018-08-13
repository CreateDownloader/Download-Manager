#include "downloadprogresssingleconnect.h"


DownloadProgressSingleConnect::DownloadProgressSingleConnect(QUrl url, DownloaderTable *dataModel){
    this->dataModel = dataModel;
    this->url = url;

    QNetworkRequest request(url);
    QNetworkReply *currentDownload;

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SIGNAL(downloadFinished(QNetworkReply*)));

    currentDownload = manager->get(request);

    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));

    downloadTime.start();
}

QString DownloadProgressSingleConnect::sizeHuman(qint64 fileSize){
    QStringList sizeExt;
    sizeExt << "KB" << "MB" << "GB" << "TB";

    QStringListIterator it(sizeExt);
    QString units("bytes");

    float num = fileSize;

    while(num >= 1024.0 && it.hasNext()){
        units = it.next();
        num /= 1024.0;
    }

    return QString().setNum(num, 'f', 2) + " " + units;
}

QString DownloadProgressSingleConnect::timeHuman(const int secondsToFinishDownload){
    int seconds = secondsToFinishDownload%60;
    int minutes = secondsToFinishDownload/60;
    int hours = minutes/60;
    minutes%=60;

    QString secondsFormat = seconds < 10 ? "0" + QString::number(seconds) : QString::number(seconds);
    QString minutesFormat = minutes < 10 ? "0" + QString::number(minutes) : QString::number(minutes);
    QString hoursFormat = hours < 10 ? "0" + QString::number(hours) : QString::number(hours);

    return hoursFormat + ":" + minutesFormat + ":" + secondsFormat;
}

void DownloadProgressSingleConnect::downloadProgress(qint64 received, qint64 total){
    double downloadSpeed = received * 1000.0 / downloadTime.elapsed();
    int progress = (100*received)/total;
    size = sizeHuman(total);

    QString unit;
    if(downloadSpeed < 1024) unit = "bytes/sec";
    else if(downloadSpeed < 1024 * 1024){
        downloadSpeed /= 1024;
        unit = "kB/s";
    }else{
        downloadSpeed /= (1024 * 1024);
        unit = "MB/s";
    }

    QString speedFormat;
    speedFormat.sprintf("%6.2f", downloadSpeed);

    QString speed = speedFormat+ " " + unit;

    int secondsToFinishDownload = total/downloadSpeed;
    secondsToFinishDownload/=1000;
    QString timeLeft = timeHuman(secondsToFinishDownload);

    QString filenameToFind = url.fileName();
    int row = dataModel->getRowOfDownloadByName(filenameToFind);

    QModelIndex index = dataModel->index(row, 1, QModelIndex());
    dataModel->setData(index, progress, Qt::EditRole);

    index = dataModel->index(row, 2, QModelIndex());
    dataModel->setData(index, size, Qt::EditRole);

    index = dataModel->index(row, 3, QModelIndex());
    dataModel->setData(index, speed, Qt::EditRole);

    index = dataModel->index(row, 4, QModelIndex());
    dataModel->setData(index, timeLeft, Qt::EditRole);
}

const QUrl & DownloadProgressSingleConnect::getUrl() const{
    return url;
}



