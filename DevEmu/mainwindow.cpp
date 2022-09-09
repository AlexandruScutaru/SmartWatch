#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "watchface.h"

#include <QMoveEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mWatchFace = new WatchFace(this);
    ui->watchFaceHolder->layout()->addWidget(mWatchFace);
    ui->watchFaceHolder->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveEvent(QMoveEvent* event) {
    QWidget::moveEvent(event);
    if (mWatchFace) {
        static_cast<WatchFace*>(mWatchFace)->onWindowMoved();
    }
}
