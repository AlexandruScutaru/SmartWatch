#pragma once

#include <cstdint>

#include <QObject>
#include <QColor>
#include <QPoint>
#include <QPixmap>

#include <string>
#include <vector>


class Display : public QObject {
    Q_OBJECT

public:
    Display();

    void init();
    void clear();
    void display();
    void clearAndDisplay();
    void setCursor(int16_t x, int16_t y);
    void setTextSize(uint8_t size);
    void setTextColor(uint16_t color);
    void setTextColor(uint16_t color, uint16_t bg);
    void invert(bool invert);

    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);

    size_t print(uint32_t value);
    size_t print(int32_t value);
    size_t print(double value);
    size_t print(char value);
    size_t print(unsigned char value);
    size_t print(const char* value);
    size_t print(const std::string& value);

    size_t println(uint32_t value);
    size_t println(int32_t value);
    size_t println(double value);
    size_t println(char value);
    size_t println(unsigned char value);
    size_t println(const char* value);
    size_t println(const std::string& value);
    size_t println();

signals:
    void displayRequested(const QPixmap& image);

private:
    uint8_t mTextSize = 1;
    uint8_t mTextColor = 1;
    uint8_t mBgColor = 0;
    QPoint mCursorPos = {0, 0};
    std::vector<std::vector<bool>> mBuffer;
    QPixmap mDisplayImage;

};
