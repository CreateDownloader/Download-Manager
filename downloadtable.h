#ifndef DOWNLOADERTABLE_H
#define DOWNLOADERTABLE_H

#include <QAbstractTableModel>

#define REP(i, n) for(int i=0; i<n; i++)


struct singleDownloadInfo{
    QString name;
    qint64 progress;
    QString size;
    QString speed;
    QString timeLeft;

    bool operator==(const singleDownloadInfo &);
};

inline bool singleDownloadInfo::operator ==(const singleDownloadInfo & download){
    return this->name == download.name;
}


class DownloadTable : public QAbstractTableModel{
    Q_OBJECT
public:
    DownloadTable(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    int getRowOfDownloadByName(const QString&) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool filenameExist(const QString);
    QList<singleDownloadInfo> getDownloadsInfo() const;
private:
    QList<singleDownloadInfo> downloadsInfo;
};

#endif // DOWNLOADERTABLE_H
