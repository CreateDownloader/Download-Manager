#include "mainwindow.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QDesktopWidget>
#include <QPropertyAnimation>
#include <QApplication>
#include <QRect>


MainWindow::MainWindow(){
    downloader = new downloaderWidget;
    setCentralWidget(downloader);
    setup();
    startUpAnimation();
}

void MainWindow::startUpAnimation(){
    QPropertyAnimation *fadein_animation = new QPropertyAnimation(this, "windowOpacity", this);
    fadein_animation->setStartValue(0);
    fadein_animation->setEndValue(1);
    fadein_animation->setDuration(410);

    QRect desktop = QApplication::desktop()->screenGeometry();
    QPoint point = desktop.center();

    QPropertyAnimation *move_animation = new QPropertyAnimation(this, "geometry");
    move_animation->setDuration(400);
    move_animation->setEndValue(QRect(point.x() - 1000 * 0.5, point.y() - 600 * 0.5, 1000, 600));

    fadein_animation->start();
    move_animation->start();
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

