#pragma once

#include <QWidget>
#include <QPixmap>

class DisplayWidget;


namespace Ui {
class WatchFace;
}

class WatchFace : public QWidget {
    Q_OBJECT

public:
    explicit WatchFace(QWidget *parent = nullptr);
    ~WatchFace();

public:
    DisplayWidget* getDisplayWidget();

public slots:
    void onWindowMoved();

private:
    void resizeEvent(QResizeEvent* event) override;

    void drawImage(const QSize& size);
    void updateDisplayGeometry();

    QPixmap mWatchIllustrationImage;
    QSize mWatchIllustrationSize;
    DisplayWidget* mDisplayWidget{ nullptr };

    Ui::WatchFace *ui;
};
