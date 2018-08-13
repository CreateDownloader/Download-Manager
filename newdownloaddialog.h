#ifndef NEWDOWNLOADDIALOG_H
#define NEWDOWNLOADDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>


class newDownloadDialog : public QDialog{
    Q_OBJECT
public:
    newDownloadDialog();
    QLineEdit *linkToData = nullptr;
private:
    void setup();
};

#endif // NEWDOWNLOADDIALOG_H
