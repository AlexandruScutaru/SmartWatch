#include "MainScreenView.h"

#include "Ui/DrawStrategies/DigitalClockFaceDrawStrategy.h"
#include "Display/IDisplay.h"
#include "Misc/Logger.h"
#include "Input/InputButton.h"
#include "MainMenuView.h"
#include "StackView.h"


MainScreenView::MainScreenView(StackView& stackView)
    : mStackView(stackView)
{
    LOG_LN("MainScreenView::ctor");
}

MainScreenView::~MainScreenView() {
    LOG_LN("MainScreenView::dtor");
}

void MainScreenView::init() {
    mClockFace.setClockFaceDrawStrategy(IClockFaceDrawStrategyPtr(new DigitalClockFaceDrawStrategy));
}

void MainScreenView::handle(input::Action action) {
    if (action == input::Action::DOUBLE_PRESS) {
        mStackView.push(views::Create<MainMenuView>(mStackView));
    }
}

void MainScreenView::update(double dt) {
    mTopBar.update(dt);
    mClockFace.update(dt);
}

void MainScreenView::draw(DisplayPtr display) {
    if (!display) {
        return;
    }

    display->clear();

    mTopBar.draw(display);
    mClockFace.draw(display);

    display->display();
}
