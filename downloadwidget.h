#ifndef DOWNLOADERWIDGET_H
#define DOWNLOADERWIDGET_H

#include <QTableView>
#include <QTime>
#include <QSortFilterProxyModel>

#include "downloadertable.h"
#include "downloaderitemdelegate.h"
#include "downloadprogresssingleconnect.h"


class downloaderWidget : public QTableView{
    Q_OBJECT
public:
    downloaderWidget(QWidget *parent = 0);
    ~downloaderWidget();
    void Download(QUrl &);
    static QString saveFileName(QUrl&);
    bool saveToDisk(const QString&, QIODevice*);
    static bool isHttpRedricted(QNetworkReply*);
    QString getDownloadLink();
    void setDownload();
    void save();
    void load();
public slots:
    void downloadFinished(QNetworkReply*);
    void showDownloadedFileLocation(QModelIndex);
    void remove();
private:
    void setup();
    DownloaderTable  *downloadTable = nullptr;
    DownloaderItemDelegate *downloadPainter = nullptr;
    QSortFilterProxyModel *proxy = nullptr;
    QVector<DownloadProgressSingleConnect*> downloads;
};

#endif // DOWNLOADERWIDGET_H
