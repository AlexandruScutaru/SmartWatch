#ifndef WATCHFACE_H
#define WATCHFACE_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class WatchFace;
}

class WatchFace : public QWidget
{
    Q_OBJECT

public:
    explicit WatchFace(QWidget *parent = nullptr);
    ~WatchFace();

public:
    void onWindowMoved();

private:
    void resizeEvent(QResizeEvent* event) override;

    void drawImage(const QSize& size);
    void updateDisplayGeometry();

    QPixmap mWatchIllustrationImage;
    QSize mWatchIllustrationSize;
    QWidget* mDisplay{ nullptr };

    Ui::WatchFace *ui;
};

#endif // WATCHFACE_H
