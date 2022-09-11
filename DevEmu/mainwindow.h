#pragma once

#include <QMainWindow>

class WatchFace;


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

signals:
    void windowMoved();

private:
    MainWindow(QWidget *parent = nullptr);
    void moveEvent(QMoveEvent* event) override;

    WatchFace* mWatchFace{ nullptr };
    Ui::MainWindow *ui;
};

#define MAIN_WINDOW MainWindow::GetInstance()
