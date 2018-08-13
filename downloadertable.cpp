#include "downloadertable.h"


DownloaderTable::DownloaderTable(QObject * parent)
    : QAbstractTableModel(parent){

}

int DownloaderTable::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return downloadsInfo.size();
}

int DownloaderTable::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 5;
}

QVariant DownloaderTable::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch(section){
            case 0:
                return "Name";
            case 1:
                return "Progress";
            case 2:
                return "Size";
            case 3:
                return "Speed";
            case 4:
                return "Time left";
        }
    }
    return QVariant();
}

QVariant DownloaderTable::data(const QModelIndex &index, int role) const{
    if(!index.isValid()) return QVariant();

    if(index.isValid() && role == Qt::DisplayRole){
        const auto & dataInfo = downloadsInfo.at(index.row());
        if(index.column() == 0)
            return dataInfo.name;
        else if(index.column() == 1)
            return dataInfo.progress;
        else if(index.column() == 2)
            return dataInfo.size;
        else if(index.column() == 3)
            return dataInfo.speed;
        else if(index.column() == 4)
            return dataInfo.timeLeft;
    }

    if(role == Qt::TextAlignmentRole)
        switch(index.column()){
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                return Qt::AlignCenter;
            default:
                return Qt::AlignLeft;
        }

    return QVariant();
}

bool DownloaderTable::insertRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), row, row + count - 1);
    REP(i, count)
            downloadsInfo.insert(row, { QString(), qint64(), QString(), QString(), QString() });
    endInsertRows();
    return true;
}

bool DownloaderTable::removeRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    REP(i, count)
            downloadsInfo.removeAt(row);
    endRemoveRows();
    return true;
}

bool DownloaderTable::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())  return false;

    if(role == Qt::EditRole){
        auto setDataInfo = downloadsInfo.value(index.row());
        if(index.column() == 0)
            setDataInfo.name = value.toString();
        else if(index.column() == 1)
            setDataInfo.progress = value.toInt();
        else if(index.column() == 2)
            setDataInfo.size = value.toString();
        else if(index.column() == 3)
            setDataInfo.speed = value.toString();
        else if(index.column() == 4)
            setDataInfo.timeLeft = value.toString();
        else
            return false;

        downloadsInfo.replace(index.row(), setDataInfo);
        return true;
    }
    return false;
}

int DownloaderTable::getRowOfDownloadByName(const QString & findName) const{
    for(auto it = downloadsInfo.begin(); it != downloadsInfo.end(); it++)
        if(it->name == findName){
            singleDownloadInfo checkIndex;
            checkIndex.name = findName;
            return downloadsInfo.indexOf(checkIndex);
        }

    return -1;
}

bool DownloaderTable::checkForDuplicateName(const QString & checkName){
    for(auto it = downloadsInfo.begin(); it != downloadsInfo.end(); it++)
        if(it->name == checkName) return true;
    return false;
}

QList<singleDownloadInfo> DownloaderTable::getDownloadsInfo() const{
    return downloadsInfo;
}

Qt::ItemFlags DownloaderTable::flags(const QModelIndex &index) const{
    if(!index.isValid()) return Qt::ItemIsEditable;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled;
}
