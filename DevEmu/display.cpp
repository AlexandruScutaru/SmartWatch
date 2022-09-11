#include "display.h"
#include "fonts.h"
#include <sstream>

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

    QColor on(Qt::cyan);
    QColor off(Qt::darkBlue);
    for (int row = 0; row < SCREEN_H; row++) {
        on = Qt::cyan;
        if (row < SCREEN_YELLOW_REGION) {
            on = Qt::yellow;
        }
        for (int col = 0; col < SCREEN_W; col++) {
            QPen pen(mBuffer[row][col] == 1 ? on : off);
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
    mCursorX = x;
    mCursorY = y;
}

void Display::setTextSize(uint8_t size) {
    mTextSize = size;
}

void Display::setTextColor(uint16_t color) {
    mTextColor = mBgColor = color;
}

void Display::setTextColor(uint16_t color, uint16_t bg) {
    mTextColor = color;
    mBgColor = bg;
}

void Display::invert(bool invert) {
    mInverted = invert;
}

void Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
    mBuffer[y][x] = color;
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int col = x; col < x + w; col++) {
        mBuffer[y][col] = color;
        mBuffer[y + h - 1][col] = color;
    }

    for (int row = y + 1; row < y + h; row++) {
        mBuffer[row][x] = color;
        mBuffer[row][x + w - 1] = color;
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
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            mBuffer[row + y][col + x] = (bitmap[row * w/8 + (col / 8) % 8] & (1 << ((w - col - 1) % 8))) ? color : bg;
        }
    }
}

size_t Display::print(uint32_t value) {
    std::stringstream ss;
    ss << value;
    auto str = ss.str();
    print(str);
    return str.size();
}

size_t Display::print(int32_t value) {
    std::stringstream ss;
    ss << value;
    auto str = ss.str();
    print(str);
    return str.size();
}

size_t Display::print(double value) {
    std::stringstream ss;
    ss << value;
    auto str = ss.str();
    print(str);
    return str.size();
}

size_t Display::print(char value) {
    for (int8_t i = 0; i < 5; i++) {
        uint8_t line = Fonts::classic[value * 5 + i];
        for (int8_t j = 0; j < 8; j++, line >>= 1) {
            if (line & 1) {
                if (mTextSize == 1) {
                    drawPixel(mCursorX + i, mCursorY + j, mTextColor);
                } else {
                    fillRect(mCursorX + i * mTextSize, mCursorY + j * mTextSize, mTextSize, mTextSize, mTextColor);
                }
            } else if (mTextColor != mBgColor) {
                if (mTextSize == 1) {
                    drawPixel(mCursorX + i, mCursorY + j, mBgColor);
                } else {
                    fillRect(mCursorX + i * mTextSize, mCursorY + j * mTextSize, mTextSize, mTextSize, mBgColor);
                }
            }
        }
    }

    //if (mTextColor != mBgColor) {
    //    fillRect(mCursorX + 5, mCursorY, 1 * mTextSize, 8 * mTextSize, mBgColor);
    //}

    mCursorX += 6 * mTextSize;
    if (mCursorX > 122) {
        mCursorX = 0;
        mCursorY += 8 * mTextSize;
    }

    return 1;
}

size_t Display::print(unsigned char value) {
    std::stringstream ss;
    ss << value;
    auto str = ss.str();
    print(str);
    return str.size();
}

size_t Display::print(const char* value) {
    std::stringstream ss;
    ss << value;
    auto str = ss.str();
    print(str);
    return str.size();
}

size_t Display::print(const std::string& value) {
    for (auto c : value) {
        print(c);
    }
    return value.size();
}

size_t Display::println(uint32_t value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println(int32_t value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println(double value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println(char value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println(unsigned char value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println(const char* value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println(const std::string& value) {
    auto ret = print(value);
    println();
    return ret - 1;
}

size_t Display::println() {
    mCursorX = 0;
    mCursorY += 8 * mTextSize;
    return 1;
}
