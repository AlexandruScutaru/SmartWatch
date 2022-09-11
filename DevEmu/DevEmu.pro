QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += SERIAL_LOGGER SSD1306_DISPLAY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    loggerQt.cpp \
    platformutils.cpp \
    controls.cpp \
    display.cpp \
    displaywidget.cpp \
    main.cpp \
    mainwindow.cpp \
    watchface.cpp

HEADERS += \
    controls.h \
    display.h \
    displaywidget.h \
    fonts.h \
    mainwindow.h \
    watchface.h

FORMS += \
    controls.ui \
    displaywidget.ui \
    mainwindow.ui \
    watchface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

INCLUDEPATH += ../device_side/src/

SOURCES += \
    ../device_side/src/Misc/BatteryLevelReader.cpp \
    ../device_side/src/Ui/Components/BatteryIndicator.cpp \
    ../device_side/src/Ui/Components/ClockFace.cpp \
    ../device_side/src/Ui/Components/TopBar.cpp \
    ../device_side/src/Ui/Controls/Button.cpp \
    ../device_side/src/Ui/Controls/CheckBox.cpp \
    ../device_side/src/Ui/Controls/IconButton.cpp \
    ../device_side/src/Ui/Controls/ListWidget.cpp \
    ../device_side/src/Ui/Controls/TextButton.cpp \
    ../device_side/src/Ui/Controls/Widget.cpp \
    ../device_side/src/Ui/DrawStrategies/DigitalClockFaceDrawStrategy.cpp \
    ../device_side/src/Ui/DrawStrategies/HListWidgetDrawStrategy.cpp \
    ../device_side/src/Ui/DrawStrategies/IconListWidgetDrawStrategy.cpp \
    ../device_side/src/Ui/DrawStrategies/VListWidgetDrawStrategy.cpp \
    ../device_side/src/Ui/Presenters/SettingsPresenter.cpp \
    ../device_side/src/Ui/Resources/Icons.cpp \
    ../device_side/src/Ui/Views/MainMenuView.cpp \
    ../device_side/src/Ui/Views/MainScreenView.cpp \
    ../device_side/src/Ui/Views/SettingsView.cpp \
    ../device_side/src/Ui/Views/StackView.cpp \
    ../device_side/src/Misc/TimeData.cpp \
    ../device_side/src/Misc/Timer.cpp
