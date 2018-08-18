#include "downloadprocess.h"


DownloadProcess::DownloadProcess(QUrl url, DownloadTable *dataModel){
    this->dataModel = dataModel;
    this->url = url;

    manager = new QNetworkAccessManager(this);
}

void DownloadProcess::start(){
    QNetworkRequest request(url);
    currentDownload = manager->get(request);

    downloadTime.start();

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SIGNAL(downloadFinished(QNetworkReply*)));
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
}

QString DownloadProcess::sizeHuman(qint64 fileSize){
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

QString DownloadProcess::timeHuman(const int secondsToFinishDownload){
    int seconds = secondsToFinishDownload%60;
    int minutes = secondsToFinishDownload/60;
    int hours = minutes/60;
    minutes%=60;

    QString secondsFormat = seconds < 10 ? "0" + QString::number(seconds) : QString::number(seconds);
    QString minutesFormat = minutes < 10 ? "0" + QString::number(minutes) : QString::number(minutes);
    QString hoursFormat = hours < 10 ? "0" + QString::number(hours) : QString::number(hours);

    return hoursFormat + ":" + minutesFormat + ":" + secondsFormat;
}

void DownloadProcess::downloadProgress(qint64 received, qint64 total){
    double downloadSpeedInfo = received * 1000.0 / downloadTime.elapsed();
    double downloadSpeed  = downloadSpeedInfo;
    int progress = (100*received)/total;
    size = sizeHuman(total);

    QString unit;
    if(downloadSpeedInfo < 1024) unit = "bytes/sec";
    else if(downloadSpeedInfo < 1024 * 1024){
        downloadSpeedInfo /= 1024;
        unit = "kB/s";
    }else{
        downloadSpeedInfo /= (1024 * 1024);
        unit = "MB/s";
    }

    QString speedFormat;
    speedFormat.sprintf("%6.2f", downloadSpeedInfo);

    QString speed = speedFormat+ " " + unit;

    int secondsToFinishDownload = (total-received)/downloadSpeed;
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

const QUrl & DownloadProcess::getUrl() const{
    return url;
}
