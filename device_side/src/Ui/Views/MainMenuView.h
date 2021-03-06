#pragma once

#include "IView.h"

class ListWidget;
class StackView;

class MainMenuView : public IView {
public:
    MainMenuView(StackView& stackView);
    ~MainMenuView();

    void init() override;
    void handle(input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    void setupMenu();

    std::shared_ptr<ListWidget> mListWidget;
    StackView& mStackView;

};
