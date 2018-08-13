#include "mainwindow.h"

#include <QApplication>


int main(int argc, char ** argv){
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(icons);

    app.setWindowIcon(QIcon(":/resources/icons/download.png"));

    MainWindow downloadManager;
    downloadManager.show();

    return app.exec();
}
