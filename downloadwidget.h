#ifndef DOWNLOADERWIDGET_H
#define DOWNLOADERWIDGET_H

#include <QTableView>
#include <QSortFilterProxyModel>
#include <QHash>
#include <QPair>

#include "downloadtable.h"
#include "downloaditemdelegate.h"
#include "downloadprocess.h"


class DownloadWidget : public QTableView{
    Q_OBJECT
public:
    DownloadWidget(QWidget *parent = 0);
    ~DownloadWidget();
    static QString saveFileName(QUrl&);
    static bool isHttpRedricted(QNetworkReply*);
    bool saveToDisk(const QString&, QIODevice*);
    QString getDownloadUrl();
    void download(QUrl &);
    void setupDownload();
    void save();
    void load();
public slots:
    void downloadFinished(QNetworkReply*);
    void showDownloadedFileLocation(QModelIndex);
    void remove();
protected:
    QPair<int, QString> currentSelectedRowWithFilename();
    void insertDownloadingFilenameInTable(const QString);
private:
    void setup();
    DownloadTable *downloadTable = nullptr;
    DownloadItemDelegate *downloadPainter = nullptr;
    QSortFilterProxyModel *proxy = nullptr;
    QHash<QString, DownloadProcess*> downloads;
};

#endif // DOWNLOADERWIDGET_H
