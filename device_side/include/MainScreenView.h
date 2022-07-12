#include "IView.h"

#include "TopBar.h"
#include "ClockFace.h"

class StackView;

class MainScreenView : public IView {
public:
    MainScreenView(StackView& stackView);
    ~MainScreenView();

    void handle(input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    TopBar mTopBar;
    ClockFace mClockFace;
    StackView& mStackView;
};
