#include "downloaderwidget.h"
#include "newdownloaddialog.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableView>
#include <QProgressBar>
#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QHBoxLayout>


downloaderWidget::downloaderWidget(QWidget *parent)
    : QTableView(parent){
    downloadTable = new DownloaderTable;
    downloadPainter = new DownloaderItemDelegate;
    setup();
    load();
}

downloaderWidget::~downloaderWidget(){
    save();
}

void downloaderWidget::setup(){
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(downloadTable);
    proxy->setFilterKeyColumn(0);

    setModel(proxy);
    setSortingEnabled(true);
    resizeColumnsToContents();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setColumnWidth(0, 350);
    setColumnWidth(1, 150);
    setColumnWidth(2, 100);
    setColumnWidth(3, 100);
    horizontalHeader()->setStretchLastSection(true);
    setItemDelegate(downloadPainter);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showDownloadedFileLocation(QModelIndex)));
}

void downloaderWidget::Download(QUrl & url){
    DownloadProgressSingleConnect *downloadProcess;
    downloadProcess = new DownloadProgressSingleConnect(url, downloadTable);

    connect(downloadProcess, SIGNAL(downloadFinished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));

    downloads.append(downloadProcess);
}

void downloaderWidget::showDownloadedFileLocation(QModelIndex index){
    QFileDialog fileDialog(this, tr("Open file"), QDir::homePath());
    QModelIndex currentIndex = downloadTable->index(index.row(), 0, QModelIndex());
    QString downloadedFileName = downloadTable->data(currentIndex, Qt::DisplayRole).toString();
    fileDialog.selectFile(downloadedFileName);
    auto fileDialogCode = fileDialog.exec();
    if(fileDialogCode != QFileDialog::AcceptOpen) QDesktopServices::openUrl(downloadedFileName);
}


QString downloaderWidget::saveFileName(QUrl & url){
    QString path = url.path();
    QString filename = QFileInfo(path).fileName();

    if(filename.isEmpty()) filename = "download";

    int i = 0;
    if(QFile::exists(filename + QString::number(i))){
        while(QFile::exists(filename + QString::number(i))) ++i;
        filename += QString::number(i);
    }

    return filename;
}

bool downloaderWidget::saveToDisk(const QString & filename, QIODevice * data){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)) return false;
    file.write(data->readAll());
    file.close();
    return true;
}

bool downloaderWidget::isHttpRedricted(QNetworkReply * reply){
    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return httpCode == 301 || httpCode == 302 || httpCode == 303
            || httpCode == 305 || httpCode == 307 || httpCode == 308;
}

QString downloaderWidget::getDownloadLink(){
    newDownloadDialog dialog;
    QString getLinkToData;

    if(dialog.exec()) getLinkToData = dialog.linkToData->text();
    return getLinkToData;
}

void downloaderWidget::remove(){
    QSortFilterProxyModel *proxySelected = static_cast<QSortFilterProxyModel*>(this->model());
    QItemSelectionModel *selectionModel = this->selectionModel();

    QModelIndexList indexies = selectionModel->selectedRows();

    foreach(QModelIndex index, indexies){
        int row = proxySelected->mapToSource(index).row();
        downloadTable->removeRows(row, 1, QModelIndex());
    }
}

void downloaderWidget::setDownload(){
    QString url = getDownloadLink();
    QUrl urlToData = QUrl::fromEncoded(url.toLocal8Bit());

    if(downloadTable->checkForDuplicateName(urlToData.fileName())){
        QMessageBox::information(this, "Duplicate data!",
                                 tr("There is %1 already in downloads!").arg(urlToData.fileName()));
        return;
    }

    if(!url.isEmpty()){
        QRegularExpression urlRegex("^(?:http|ftp)s?://");
        QRegularExpressionMatch match = urlRegex.match(url);

        if(!match.hasMatch()){
            QMessageBox::critical(this, "Error", "Incorrect URL", QMessageBox::Ok);
            return;
        }

        downloadTable->insertRows(0, 1, QModelIndex());
        QModelIndex index = downloadTable->index(0, 0, QModelIndex());
        downloadTable->setData(index, urlToData.fileName(), Qt::EditRole);

        Download(urlToData);
    }
}

void downloaderWidget::downloadFinished(QNetworkReply * reply){
    QUrl url = reply->url();

    for(int i = 0; i<downloads.size(); i++){
            if(downloads.at(i)->getUrl() == url){
                downloads.remove(i);
                break;
        }
    }

    if(!reply->error()){
        if(!isHttpRedricted(reply)){
            QString filename = saveFileName(url);

            int row = downloadTable->getRowOfDownloadByName(filename);
            QModelIndex index = downloadTable->index(row, 4, QModelIndex());
            downloadTable->setData(index, "00:00:00", Qt::EditRole);

            if(saveToDisk(filename, reply))
                QMessageBox::information(this, "Download successed!", tr("Download of %1 succesed!").arg(filename));
        }else{
            downloadTable->removeRows(0, 1, QModelIndex());
            QMessageBox::information(this, "Http Redricted", tr("HTTP Error"));
       }
    }else{
        downloadTable->removeRows(0, 1, QModelIndex());
        QMessageBox::information(this, "Download Error", tr("Download error %1").arg(url.errorString()));
    }
}

void downloaderWidget::save(){
    QFile file(".download_data");

    if(file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);
        int n = downloadTable->rowCount(QModelIndex());
        int m = downloadTable->columnCount(QModelIndex());
        QModelIndex index;
        stream<<n<<m;

        REP(i, n){
                REP(j, m){
                    index = downloadTable->index(i, j, QModelIndex());
                    stream << downloadTable->data(index, Qt::DisplayRole);
            }
        }
    }

    file.close();
}

void downloaderWidget::load(){
    QFile file(".download_data");

    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        int n, m;
        stream >> n >> m;
        downloadTable->insertRows(0, n, QModelIndex());
        QModelIndex index;

        REP(i, n){
                REP(j, m){
                    index = downloadTable->index(i, j);
                    downloadTable->setData(index, stream, Qt::EditRole);
            }
        }
    }

    file.close();
}
