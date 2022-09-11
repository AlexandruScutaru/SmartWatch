#pragma once

#include <QWidget>
#include <QPixmap>

#include <string>
#include <vector>

class Display;


namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget {
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();

    Display* getDisplay();

private slots:
    void onDisplayRequested(const QPixmap& image);
    void onWindowMoved();

private:
    void resizeEvent(QResizeEvent* event) override;

    void drawImage(const QSize& size);

    Ui::DisplayWidget *ui;

    Display* mDisplay{ nullptr };
    QPixmap mImage;
    QSize mImageSize;
};
