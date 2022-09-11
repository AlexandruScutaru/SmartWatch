#pragma once

#include <QWidget>
#include <QPixmap>

#include <string>
#include <vector>

class IDisplay;
using DisplayPtr = std::shared_ptr<IDisplay>;

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget {
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();

    DisplayPtr getDisplay();

private slots:
    void onDisplayRequested(const QPixmap& image);
    void onWindowMoved();

private:
    void resizeEvent(QResizeEvent* event) override;

    void drawImage(const QSize& size);

    Ui::DisplayWidget *ui;

    DisplayPtr mDisplay;
    QPixmap mImage;
    QSize mImageSize;
};
