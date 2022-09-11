#include "controls.h"
#include "ui_controls.h"

Controls::Controls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Controls)
{
    ui->setupUi(this);

    QObject::connect(ui->singlePressButton, &QPushButton::pressed, this, [this]() {
        emit userAction(input::Action::SINGLE_PRESS);
    });

    QObject::connect(ui->doublePressButton, &QPushButton::pressed, this, [this]() {
        emit userAction(input::Action::DOUBLE_PRESS);
    });

    QObject::connect(ui->triplePressButton, &QPushButton::pressed, this, [this]() {
        emit userAction(input::Action::TRIPLE_PRESS);
    });

    QObject::connect(ui->longPressButton, &QPushButton::pressed, this, [this]() {
        emit userAction(input::Action::LONG_PRESS);
    });

    QObject::connect(ui->batteryLevelSlider, &QSlider::valueChanged, this, [this](int value) {
        double voltage = 3.3 * value / 4096.0;
        ui->voltageLabel->setText(QString::number(voltage, 'f', 3));
        emit batteryVoltageChanged(voltage);
    });
    ui->batteryLevelSlider->setValue(3700);

    QObject::connect(ui->dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [this](const QDateTime& dateTime) {
    });
}

Controls::~Controls()
{
    delete ui;
}
