#pragma once

#include "Input/InputButton.h"

#include <QWidget>

namespace Ui {
class Controls;
}

class Controls : public QWidget {
    Q_OBJECT

public:
    enum class ButtonPress {
        Single,
        Double,
        Triple,
        Long
    };

    explicit Controls(QWidget *parent = nullptr);
    ~Controls();

signals:
    void userAction(input::Action action);
    void batteryVoltageChanged(double voltage);

private:
    Ui::Controls *ui;
};
