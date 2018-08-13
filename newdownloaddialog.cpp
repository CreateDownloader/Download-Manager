#include "newdownloaddialog.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>


newDownloadDialog::newDownloadDialog(){
    setup();
}

void newDownloadDialog::setup(){
    QGridLayout *dataLayout;
    dataLayout = new QGridLayout;

    linkToData = new QLineEdit;
    linkToData->setPlaceholderText(tr("URL"));
    dataLayout->addWidget(linkToData, 0, 1);

    QHBoxLayout *buttonsLayout;
    buttonsLayout = new QHBoxLayout;

    auto okButton = new QPushButton("Ok");
    auto cancelButton = new QPushButton("Cancel");
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    dataLayout->addLayout(buttonsLayout, 1, 1, Qt::AlignRight);

    QVBoxLayout  *mainLayout;
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(dataLayout);

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

    setWindowTitle(tr("New Download"));
    resize(270, 100);
    setLayout(mainLayout);
}
