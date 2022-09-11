#include "displaywidget.h"
#include "ui_displaywidget.h"

#include "display.h"
#include "mainwindow.h"

#include <QResizeEvent>


DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent, Qt::SubWindow)
    , ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    mDisplay = new Display();

    QObject::connect(mDisplay, &Display::displayRequested, this, &DisplayWidget::onDisplayRequested);
    //QObject::connect(&MAIN_WINDOW, &MainWindow::windowMoved, this, &DisplayWidget::onWindowMoved);

    mImageSize = size();
}

DisplayWidget::~DisplayWidget()
{
    delete mDisplay;
    delete ui;
}

Display* DisplayWidget::getDisplay() {
    return mDisplay;
}

void DisplayWidget::drawImage(const QSize& size) {
    if (mImage.isNull()) {
        return;
    }

    auto scaledImage = mImage.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(scaledImage);
    mImageSize = scaledImage.size();
}

void DisplayWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    drawImage(event->size());
}

void DisplayWidget::onDisplayRequested(const QPixmap& image) {
    mImage = image;
    drawImage(mImageSize);
}

void DisplayWidget::onWindowMoved() {

}
