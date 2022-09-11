#include "watchface.h"
#include "ui_watchface.h"

#include "displaywidget.h"
#include "mainwindow.h"

#include <QResizeEvent>
#include <QMoveEvent>

inline constexpr double displayHorScaleFactor = 0.6;
inline constexpr double displayVerScaleFactor = 0.245;
inline constexpr double displayWScaleFactor = 0.587;
inline constexpr double displayHScaleFactor = 0.62;


WatchFace::WatchFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchFace)
{
    ui->setupUi(this);

    mWatchIllustrationImage = QPixmap(":/images/watch_illustration.png");
    drawImage(size());

    mDisplayWidget = new DisplayWidget(this);
    updateDisplayGeometry();
    mDisplayWidget->show();
    mDisplayWidget->raise();

    QObject::connect(&MAIN_WINDOW, &MainWindow::windowMoved, this, &WatchFace::onWindowMoved);
}

WatchFace::~WatchFace()
{
    delete ui;
}

DisplayWidget* WatchFace::getDisplayWidget() {
    return mDisplayWidget;
}

void WatchFace::drawImage(const QSize& size) {
    auto scaledImage = mWatchIllustrationImage.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->watchIllustrationLabel->setPixmap(scaledImage);
    mWatchIllustrationSize = scaledImage.size();
}

void WatchFace::updateDisplayGeometry() {
    auto w = int(mWatchIllustrationSize.width() * displayHorScaleFactor);
    auto h = int(mWatchIllustrationSize.height() * displayVerScaleFactor);

    auto center = size() / 2;
    auto centerGlobal = mapToGlobal(QPoint(center.width(), center.height()));
    auto x = centerGlobal.x() - int(mWatchIllustrationSize.width() * displayWScaleFactor) / 2;
    auto y = centerGlobal.y() - int(mWatchIllustrationSize.height() * displayHScaleFactor) / 2;

    mDisplayWidget->setGeometry({x, y, w, h});
}

void WatchFace::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    drawImage(event->size());
    updateDisplayGeometry();
}

void WatchFace::onWindowMoved() {
    updateDisplayGeometry();
}
