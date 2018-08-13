#ifndef DOWNLOADERITEMDELEGATE_H
#define DOWNLOADERITEMDELEGATE_H

#include <QStyledItemDelegate>


class DownloaderItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    DownloaderItemDelegate(QObject * parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DOWNLOADERITEMDELEGATE_H
