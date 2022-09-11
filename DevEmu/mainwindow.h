#pragma once

#include <Ui/Views/StackView.h>
#include "Input/InputButton.h"
#include "Misc/EventTypes.h"

#include <QMainWindow>
#include <QTimer>

class WatchFace;
class Controls;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    ~MainWindow();

    // not a fan of this but wanted a quick way
    // to notify some widgets about the main window being moved
    void init();
    static MainWindow& GetInstance();

    double getBatteryVoltage();

signals:
    void windowMoved();

public slots:
    void onUserAction(input::Action action);

private slots:
    void update();

private:
    MainWindow(QWidget *parent = nullptr);
    void moveEvent(QMoveEvent* event) override;

    WatchFace* mWatchFace{ nullptr };
    Controls* mControls{ nullptr };
    StackView mStackView;

    double mBatteryVoltage = 3.8 / 2.0;
    QTimer mTickTimer;

    Ui::MainWindow *ui;

public: // Non-Qt EventBus events
    void onTestEvent(TestEvent& event);

};

#define MAIN_WINDOW MainWindow::GetInstance()
