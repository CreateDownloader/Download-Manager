#ifndef NEWDOWNLOADDIALOG_H
#define NEWDOWNLOADDIALOG_H

#include <QDialog>
#include <QLineEdit>


class DownloadDialog : public QDialog{
    Q_OBJECT
public:
    DownloadDialog();
    QLineEdit *downloadUrl = nullptr;
private:
    void setup();
};

#endif // NEWDOWNLOADDIALOG_H
