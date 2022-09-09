#include "display.h"
#include "ui_display.h"

Display::Display(QWidget *parent) :
    QWidget(parent, Qt::SubWindow),
    ui(new Ui::Display)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
}

Display::~Display()
{
    delete ui;
}
