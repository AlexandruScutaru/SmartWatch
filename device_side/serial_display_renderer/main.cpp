//just an experiment to get some serial data
//lots of issues with this, but not the main topic of this project
//as I'm not even sure how useful will this be, but yeah

#include "Serial.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cstring>
#include <cstdio>


const char start[] = "<b>";
const char end[] = "</b>";

int getBufferStart(const char* data, int len);
int getBufferEnd(const char* data, int len);
void render(const char* data, int len, sf::RenderWindow& window);
void drawPixel(int16_t x, int16_t y, sf::RenderWindow& window);

void runBufferExtractionTests();


int main() {
    // runBufferExtractionTests();
    // return 0;

    sf::RenderWindow window(sf::VideoMode(512, 256), "test");
    sf::View view(sf::FloatRect(0, 0, 128, 64));
    view.zoom(1.0);
    window.setView(view);

    Serial* SP = new Serial("\\\\.\\COM5");

    if (SP->IsConnected()) {
        printf("connected to COM port\n");
    }

    char incomingData[2048] = {0};
    int dataLength = 2048;
    int readResult = 0;

    DWORD newTicks = 0;
    DWORD prevTicks = GetTickCount();
    DWORD frameTicks = 0;
    DWORD targetFrameTicks = 1000 / 60;

    char buffer[1025] = {0};
    int buffer_index = 0;

    while (window.isOpen()) {
        newTicks = GetTickCount();
        frameTicks = newTicks - prevTicks;
        prevTicks = newTicks;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }

        if (!SP->IsConnected()) {
            window.close();
            return 0;
        }

        while (readResult = SP->ReadData(incomingData, dataLength)) {
            incomingData[readResult] = 0;

            int start_index = getBufferStart(incomingData, readResult);
            int end_index = getBufferEnd(incomingData, readResult);

            if (end_index >= 0) {
                //buffer is ready
                memcpy(buffer + buffer_index, incomingData, end_index);
                buffer_index += end_index;
                render(buffer, buffer_index, window);

                end_index = getBufferEnd(buffer + start_index, readResult);
            }

            if (start_index < 0) {
                start_index = 0;
            } else {
                memset(buffer, 0, strlen(buffer));
                buffer_index = 0;
            }

            if (end_index < 0) {
                end_index = readResult;
            }

            memcpy(buffer + buffer_index, incomingData+start_index, end_index - start_index);
            buffer_index += end_index - start_index;
        }

        if (frameTicks < targetFrameTicks) {
            Sleep(targetFrameTicks - frameTicks);
        }

    }

    return 0;
}


int getBufferStart(const char* data, int len) {
    int match_index = 0;
    for (int i = 0; i < len; i++) {
        if (data[i] == start[match_index]) {
            if (++match_index == 3){
                return i+1;
            }
        } else {
            match_index = 0;
        }
    }
    return -1;
}

int getBufferEnd(const char* data, int len) {
    int match_index = 0;
    for (int i = 0; i < len; i++) {
        if (data[i] == end[match_index]) {
            if (++match_index == 4){
                return i-3;
            }
        } else {
            match_index = 0;
        }
    }
    return -1;
}

void drawPixel(int16_t x, int16_t y, sf::RenderWindow& window) {
    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    if(y < 16)
        pixel.setFillColor(sf::Color::Yellow);
    else
        pixel.setFillColor(sf::Color::Blue);
    pixel.setPosition(x, y);
    window.draw(pixel);
}

void render(const char* data, int len, sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 64; y++) {
            if (uint8_t(data[x + (y / 8) * 128]) & (1 << (y & 7)))
                drawPixel(x, y, window);
        }
    }
    window.display();
}


void runBufferExtractionTests() {
    const int arrayNb = 20;
    char incomingData[arrayNb][256] = {
        { "asdasda<b>012345678901234567890123456789012345678901234567890123456789</b>jkljkljkl" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "<b>012345678901234567890123456789012345678901234567890123456789</b>jkljkljkl" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "<b>012345678901234567890123456789012345678901234567890123456789</b>" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "012345678901234567890123456789012345678901234567890123456789</b>jkljkljkl" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "012345678901234567890123456789012345678901234567890123456789</b>" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "asdasda<b>012345678901234567890123456789012345678901234567890123456789" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "<b>012345678901234567890123456789012345678901234567890123456789" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "012345678901234567890123456789012345678901234567890123456789" },
        { "012345678901234567890123456789012345678901234567890123456789" },

        { "" },
        { "" },

        { "789</b>JU<b>012345678901234567890123456789012345678901234567890123456789" },
        { "789" },
    };

    for (int arrayIdx = 0; arrayIdx < arrayNb; arrayIdx += 2) {
        printf("Test %d: ", arrayIdx/2 + 1);

        int readResult = strlen(incomingData[arrayIdx]);

        char displayBuffer[2048] = { '\0' };
        int displayBufferIndex = 0;

        int start_index = 0;
        int end_index = 0;

        start_index = getBufferStart(incomingData[arrayIdx], readResult);
        end_index = getBufferEnd(incomingData[arrayIdx], readResult);

        if (start_index >= 0 && end_index >= 0 && end_index < start_index) {
            memcpy(displayBuffer + displayBufferIndex, incomingData[arrayIdx], end_index);
            printf("%s\n", displayBuffer);
            displayBufferIndex += end_index;
            printf("index %d\n", displayBufferIndex);

            int cmp = strncmp(displayBuffer, incomingData[arrayIdx+1], strlen(incomingData[arrayIdx+1]));
            printf("%s\n", cmp ? "failed" : "passed");
            end_index = getBufferEnd(incomingData[arrayIdx]+start_index, readResult);
            continue;
        }

        if (start_index < 0) {
            start_index = 0;
        } else {
            memset(displayBuffer, 0, strlen(displayBuffer));
            displayBufferIndex = 0;
        }

        if (end_index < 0) {
            end_index = readResult;
        }

        memcpy(displayBuffer + displayBufferIndex, incomingData[arrayIdx]+start_index, end_index - start_index);
        displayBufferIndex += end_index - start_index;

        int cmp = strncmp(displayBuffer, incomingData[arrayIdx+1], strlen(incomingData[arrayIdx+1]));
        printf("%s\n", cmp ? "failed" : "passed");
    }
}
