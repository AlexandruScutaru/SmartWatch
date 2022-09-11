#include "displaywidget.h"
#include "ui_displaywidget.h"

#include "display.h"
#include "mainwindow.h"

#include <QResizeEvent>
#include <QDebug>


DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent, Qt::SubWindow)
    , ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    mDisplay = std::make_shared<Display>();
    auto displayDownCast = dynamic_cast<Display*>(mDisplay.get());
    if (!displayDownCast)
    {
        qWarning() << "Can't downcast DisplayPtr to Widget";
    }

    QObject::connect(displayDownCast, &Display::displayRequested, this, &DisplayWidget::onDisplayRequested);
    //QObject::connect(&MAIN_WINDOW, &MainWindow::windowMoved, this, &DisplayWidget::onWindowMoved);

    mImageSize = size();
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

DisplayPtr DisplayWidget::getDisplay() {
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
