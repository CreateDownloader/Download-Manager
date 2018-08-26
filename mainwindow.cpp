#include "mainwindow.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QDesktopWidget>
#include <QPropertyAnimation>
#include <QApplication>
#include <QRect>
#include <QStatusBar>
#include <QSettings>


MainWindow::MainWindow(){
    downloader = new DownloadWidget;
    setWindowTitle("Download Manager");
    setCentralWidget(downloader);
    setup();
    loadSettings();
    startUpAnimation();
}

MainWindow::~MainWindow(){
    saveSettings();
}

void MainWindow::setup(){
    QMenu *fileMenu = menuBar()->addMenu("File");

    add = new QAction("New", this);
    fileMenu->addAction(add);
    add->setShortcut(QKeySequence::New);
    connect(add, SIGNAL(triggered(bool)), downloader, SLOT(start()));

    remove = new QAction("Remove", this);
    fileMenu->addAction(remove);
    remove->setShortcut(QKeySequence::Delete);
    connect(remove, SIGNAL(triggered(bool)), downloader, SLOT(remove()));

    fileMenu->addSeparator();

    auto exitFromProgram = new QAction("Exit", this);
    fileMenu->addAction(exitFromProgram);
    exitFromProgram->setShortcut(QKeySequence::Quit);
    connect(exitFromProgram, SIGNAL(triggered(bool)), this, SLOT(close()));

    QMenu *downloadMenu = menuBar()->addMenu("Download");

    resume = new QAction("Resume", this);
    downloadMenu->addAction(resume);
    resume->setShortcut(QKeySequence("CTRL+R"));
    connect(resume, SIGNAL(triggered(bool)), downloader, SLOT(resume()));

    abort = new QAction("Abort", this);
    downloadMenu->addAction(abort);
    abort->setShortcut(QKeySequence("CTRL+A"));
    connect(abort, SIGNAL(triggered(bool)), downloader, SLOT(abort()));
}

void MainWindow::startUpAnimation(){
    QPropertyAnimation *fadein_animation = new QPropertyAnimation(this, "windowOpacity", this);

    fadein_animation->setStartValue(0);
    fadein_animation->setEndValue(1);
    fadein_animation->setDuration(410);
    fadein_animation->start();
}

void MainWindow::saveSettings(){
    QSettings settings("Download Manager", "Dimensions");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::loadSettings(){
    QSettings settings("Download Manager", "Dimensions");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(960, 640)).toSize());
    move(settings.value("pos", QPoint(50, 50)).toPoint());
    settings.endGroup();
}
