#ifndef DOWNLOADERITEMDELEGATE_H
#define DOWNLOADERITEMDELEGATE_H

#include <QStyledItemDelegate>


class DownloadItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    DownloadItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DOWNLOADERITEMDELEGATE_H
