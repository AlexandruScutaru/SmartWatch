#include "watchface.h"
#include "ui_watchface.h"

#include "display.h"

#include <QResizeEvent>
#include <QMoveEvent>

inline constexpr double displayHorScaleFactor = 0.611;
inline constexpr double displayVerScaleFactor = 0.266;
inline constexpr double displayWScaleFactor = 0.597;
inline constexpr double displayHScaleFactor = 0.64;


WatchFace::WatchFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchFace)
{
    ui->setupUi(this);

    mWatchIllustrationImage = QPixmap(":/images/watch_illustration.png");
    drawImage(size());

    mDisplay = new Display(this);
    updateDisplayGeometry();
    mDisplay->show();
    mDisplay->raise();
}

WatchFace::~WatchFace()
{
    delete ui;
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

    mDisplay->setGeometry({x, y, w, h});
}

void WatchFace::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    drawImage(event->size());
    updateDisplayGeometry();
}

void WatchFace::onWindowMoved() {
    updateDisplayGeometry();
}
