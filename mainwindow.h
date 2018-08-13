#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "downloaderwidget.h"


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
public slots:
    void startDownload();
private:
    downloaderWidget *downloader = nullptr;
    void setup();

};

#endif // MAINWINDOW_H
