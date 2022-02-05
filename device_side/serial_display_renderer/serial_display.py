import serial
import sys
from graphics import *

window = GraphWin('Watch', 512, 256, autoflush = False)


def drawPixel(x, y):
    global window

    pixel = Rectangle(Point(x, y), Point(x + 4, y + 4))
    if(y < 64):
        pixel.setFill("yellow")
    else:
        pixel.setFill("blue")

    pixel.draw(window)


def renderDisplayBuffer(buffer):
    global window
    for item in window.items[:]:
        item.undraw()

    for x in range(128):
        for y in range(64):
            if (buffer[x + (y // 8) * 128]) & (1 << (y & 7)):
                drawPixel(x << 2, y << 2)

    window.update()


def handleBuffer(port):
    global window

    with serial.Serial(port, 115200) as ser:
        buf = b''
        while (True):
            buf += ser.read(ser.inWaiting())
            while b"<b>" not in buf or b"</b>" not in buf:
                buf += ser.read(ser.inWaiting())

            while b"<b>" in buf and b'</b>' in buf:
                start = buf.find(b'<b>')
                buf = buf[start+3:]
                end = buf.find(b'</b>')
                renderDisplayBuffer(buf[:end])
                buf = buf[end+4:]


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: {} COM_PORT".format(sys.argv[0]))
        sys.exit(1)

    window.setCoords(0, 255, 511, 0)
    window.setBackground(color_rgb(0, 0, 0))

    handleBuffer(sys.argv[1])
