#include "display.h"

#include <QPainter>

constexpr static int SCREEN_W = 128;
constexpr static int SCREEN_H = 64;
constexpr static int SCREEN_YELLOW_REGION = 16;


Display::Display()
    : mBuffer(std::vector<std::vector<bool>>(SCREEN_H, std::vector<bool>(SCREEN_W)))
{}


void Display::init() {}

void Display::clear() {
    for (auto& row : mBuffer) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void Display::display() {
    mDisplayImage = QPixmap(SCREEN_W, SCREEN_H);
    QPainter painter(&mDisplayImage);
    QPen penPixelOn(Qt::cyan);
    QPen penPixelOff(Qt::darkBlue);
    QPen penPixelOnTopSide(Qt::yellow);

    for (int row = 0; row < SCREEN_H; row++) {
        for (int col = 0; col < SCREEN_W; col++) {
            QPen& pen = mBuffer[row][col] == 1 ? row < SCREEN_YELLOW_REGION ? penPixelOnTopSide :  penPixelOn : penPixelOff;
            painter.setPen(pen);
            painter.drawPoint(col, row);
        }
    }

    emit displayRequested(mDisplayImage);
}

void Display::clearAndDisplay() {
    clear();
    display();
}

void Display::setCursor(int16_t x, int16_t y) {
    mCursorPos = {x, y};
}

void Display::setTextSize(uint8_t size) {
    mTextSize = size;
}

void Display::setTextColor(uint16_t color) {
    mTextColor = color;
}

void Display::setTextColor(uint16_t color, uint16_t bg) {
    setTextColor(color);
    mBgColor = bg;
}

void Display::invert(bool invert) {
    std::swap(mTextColor, mBgColor);
}

void Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
    mBuffer[y][x] = color;
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int col = x; col < x + w; col++) {
        mBuffer[y][col] = color;
        mBuffer[SCREEN_H - y - 1][col] = color;
    }

    for (int row = y + 1; row < y + h; row++) {
        mBuffer[row][x] = color;
        mBuffer[row][SCREEN_W - x - 1] = color;
    }
}

void Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int row = y; row < y + h; row++) {
        for (int col = x; col < x + w; col++) {
            mBuffer[row][col] = color;
        }
    }
}

void Display::drawBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    for (int row = y; row < y + h; row++) {
        for (int col = x; col < x + w; col++) {
            mBuffer[row][col] = bitmap[row * w + col] == 1 ? color : bg;
        }
    }
}

size_t Display::print(uint32_t value) { return 0; }
size_t Display::print(int32_t value) { return 0; }
size_t Display::print(double value) { return 0; }
size_t Display::print(char value) { return 0; }
size_t Display::print(unsigned char value) { return 0; }
size_t Display::print(const char* value) { return 0; }
size_t Display::print(const std::string& value) { return 0; }

size_t Display::println(uint32_t value) { return 0; }
size_t Display::println(int32_t value) { return 0; }
size_t Display::println(double value) { return 0; }
size_t Display::println(char value) { return 0; }
size_t Display::println(unsigned char value) { return 0; }
size_t Display::println(const char* value) { return 0; }
size_t Display::println(const std::string& value) { return 0; }
size_t Display::println() { return 0; }
