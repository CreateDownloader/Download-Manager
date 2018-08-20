#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "downloadwidget.h"


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
protected:
    void startUpAnimation();
private:
    DownloadWidget *downloader = nullptr;
    void setup();
    QAction *add = nullptr;
    QAction *remove = nullptr;
    QAction *abort = nullptr;
    QAction *resume = nullptr;

};

#endif // MAINWINDOW_H
