#include "downloadtable.h"


DownloadTable::DownloadTable(QObject * parent)
    : QAbstractTableModel(parent){

}

int DownloadTable::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return downloadsInfo.size();
}

int DownloadTable::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 5;
}

QVariant DownloadTable::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role != Qt::DisplayRole) return QVariant();

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

QVariant DownloadTable::data(const QModelIndex &index, int role) const{
    if(!index.isValid()) return QVariant();

    if(index.isValid() && role == Qt::DisplayRole){
        const auto & dataInfo = downloadsInfo.at(index.row());
        switch(index.column()){
            case 0:
                 return dataInfo.name;
            case 1:
                return dataInfo.progress;
            case 2:
                return dataInfo.size;
            case 3:
                return dataInfo.speed;
            case 4:
                return dataInfo.timeLeft;
        }
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

bool DownloadTable::insertRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), row, row + count - 1);
    REP(i, count) downloadsInfo.insert(row, {QString(), qint64(), QString(), QString(), QString()});
    endInsertRows();
    return true;
}

bool DownloadTable::removeRows(int row, int count, const QModelIndex &parent){
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    REP(i, count) downloadsInfo.removeAt(row);
    endRemoveRows();
    return true;
}

bool DownloadTable::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())  return false;

    if(role == Qt::EditRole){
        auto downloadProcessInfo = downloadsInfo.value(index.row());

        switch(index.column()){
            case 0:
                downloadProcessInfo.name = value.toString();
                break;
            case 1:
                 downloadProcessInfo.progress = value.toInt();
                break;
            case 2:
                downloadProcessInfo.size = value.toString();
                break;
            case 3:
                downloadProcessInfo.speed = value.toString();
                break;
            case 4:
                downloadProcessInfo.timeLeft = value.toString();
                break;
            default:
                return false;
        }

        downloadsInfo.replace(index.row(), downloadProcessInfo);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool DownloadTable::filenameExist(const QString filename){
    singleDownloadInfo checkFilename;
    checkFilename.name = filename;
    return downloadsInfo.contains(checkFilename);
}

int DownloadTable::getRowOfDownloadByName(const QString &findName) const{
    singleDownloadInfo checkFilename;
    checkFilename.name = findName;
    return downloadsInfo.contains(checkFilename) ? downloadsInfo.indexOf(checkFilename) : -1;
}

Qt::ItemFlags DownloadTable::flags(const QModelIndex &index) const{
    if(!index.isValid()) return Qt::ItemIsEditable;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled;
}
