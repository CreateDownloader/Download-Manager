#include "downloaditemdelegate.h"

#include <QTextCharFormat>
#include <QTextCursor>
#include <QApplication>


DownloadItemDelegate::DownloadItemDelegate(QObject * parent)
    : QStyledItemDelegate(parent){

}

void DownloadItemDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const{
    if(index.column() == 1){
        int progress = index.data().toInt();
        QStyleOptionProgressBar progressbar;

        progressbar.rect = option.rect;
        progressbar.minimum = 0;
        progressbar.maximum = 100;
        progressbar.progress = progress;
        progressbar.text = tr("%1%2").arg(progress).arg("%");
        progressbar.textVisible = true;

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressbar, painter);
     } else if(index.column() != 1 && index.isValid()){
        QStyleOptionViewItem customText(option);

        QTextCharFormat format;
        format.setTextOutline(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        QTextCursor cursor;
        cursor.select(QTextCursor::Document);
        cursor.mergeCharFormat(format);

        customText.font.setWeight(600);
        customText.palette.setColor(QPalette::HighlightedText, "#D19F49");
        customText.palette.setColor(QPalette::Highlight, "#0995DB");

        QStyledItemDelegate::paint(painter, customText, index);
     } else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize DownloadItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const{
    Q_UNUSED(index);
    return option.widget->size();
}
