#pragma once 

#include "IView.h"

#include "Ui/Components/TopBar.h"
#include "Ui/Components/ClockFace.h"

class StackView;

class MainScreenView : public IView {
public:
    MainScreenView(StackView& stackView);
    ~MainScreenView();

    void init() override;
    void handle(input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    TopBar mTopBar;
    ClockFace mClockFace;
    StackView& mStackView;
};
