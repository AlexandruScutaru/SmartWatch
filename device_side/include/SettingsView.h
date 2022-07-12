#pragma once

#include "IView.h"
#include "Widget.h"

class ListWidget;
class StackView;

class SettingsView : public IView {
public:
    SettingsView(StackView& stackView);
    ~SettingsView();

    void handle(input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    void setupMenu();

    std::shared_ptr<ListWidget> mListWidget;
    StackView& mStackView;

};
