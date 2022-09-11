#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "watchface.h"
#include "displaywidget.h"
#include "display.h"
#include "controls.h"

#include "Misc/TimeData.h"
#include "Misc/BatteryLevelReader.h"
#include "Misc/Logger.h"
#include "Misc/EventBus.h"

#include <QMoveEvent>

#include <array>


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
    LOG_LN("starting");

    mWatchFace = new WatchFace(this);
    ui->watchFaceHolder->layout()->addWidget(mWatchFace);

    mControls = new Controls(this);
    ui->controlsHolder->layout()->addWidget(mControls);

    QObject::connect(mControls, &Controls::userAction, this, &MainWindow::onUserAction);
    QObject::connect(mControls, &Controls::batteryVoltageChanged, this, [this](double voltage){
        mBatteryVoltage = voltage;
    });

    if (auto displayWidget = mWatchFace->getDisplayWidget()) {
        if (auto display = displayWidget->getDisplay()) {
            display->clearAndDisplay();
            //for (int i = 0; i < 32; i+=2) {
            //    display->drawRect(i, i, 128 - 2*i, 64 - 2*i, 1);
            //}
            mStackView.init(display);
        }
    }

    EVENT_BUS.subscribe<MainWindow, TestEvent>(this, &MainWindow::onTestEvent);

    QObject::connect(&mTickTimer, &QTimer::timeout, this, &MainWindow::update);
    mTickTimer.start(30);
}

MainWindow& MainWindow::GetInstance() {
    static MainWindow instance;
    return instance;
}

double MainWindow::getBatteryVoltage() {
    return mBatteryVoltage;
}

void MainWindow::moveEvent(QMoveEvent* event) {
    QWidget::moveEvent(event);
    emit windowMoved();
}

void MainWindow::onUserAction(input::Action action) {
    mStackView.handle(action);
}

void MainWindow::update() {
    mStackView.update(1.0);
    CLOCK_TIME.update(1.0);
    BATTERY_LEVEL_READER.update(1.0);

    mStackView.draw();
}

void MainWindow::onTestEvent(TestEvent& event) {
    LOG_LN("Got EventBus TestEvent::data: " << event.data);
}
