#include "mainwindow.h"

#include <QtWidgets/QMenuBar>
#include <QPropertyAnimation>
#include <QFile>
#include <QGuiApplication>
#include <QRect>


MainWindow::MainWindow(){
    downloader = new downloaderWidget;
    setCentralWidget(downloader);

    setup();

    QPropertyAnimation * animation = new QPropertyAnimation(this, "size");
    animation->setDuration(350);
    animation->setEndValue(QSize(920, 480));
    animation->start();
}

void MainWindow::startDownload(){
    downloader->setDownload();
}

void MainWindow::setup(){
    QMenu *downloadMenu = menuBar()->addMenu("Download");

    auto addDownload = new QAction("New", this);
    downloadMenu->addAction(addDownload);
    addDownload->setShortcut(QKeySequence::New);
    connect(addDownload, SIGNAL(triggered(bool)), this, SLOT(startDownload()));

    auto remove = new QAction("Remove", this);
    downloadMenu->addAction(remove);
    remove->setShortcut(QKeySequence::Delete);
    connect(remove, SIGNAL(triggered(bool)), downloader, SLOT(remove()));

    downloadMenu->addSeparator();

    auto exitFromProgram = new QAction("Exit", this);
    downloadMenu->addAction(exitFromProgram);
    exitFromProgram->setShortcut(QKeySequence::Quit);
    connect(exitFromProgram, SIGNAL(triggered(bool)), this, SLOT(close()));
}

