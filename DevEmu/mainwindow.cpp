#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "watchface.h"
#include "displaywidget.h"
#include "display.h"

#include <QMoveEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init() {
    mWatchFace = new WatchFace(this);
    ui->watchFaceHolder->layout()->addWidget(mWatchFace);

    if (auto displayWidget = mWatchFace->getDisplayWidget()) {
        if (auto display = displayWidget->getDisplay()) {
            display->clear();
            for (int i = 0; i < 32; i+=2) {
                display->drawRect(i, i, 128 - 2*i, 64 - 2*i, 1);
            }
            display->display();
        }
    }
}

MainWindow& MainWindow::GetInstance() {
    static MainWindow instance;
    return instance;
}

void MainWindow::moveEvent(QMoveEvent* event) {
    QWidget::moveEvent(event);
    emit windowMoved();
}
