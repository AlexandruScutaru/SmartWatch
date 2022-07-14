#pragma once

#include "IView.h"
#include "Widget.h"

class ListWidget;
class StackView;

class SettingsPresenter;
using SettingsPresenterPtr = std::shared_ptr<SettingsPresenter>;

class SettingsView;
using SettingsViewPtr = std::shared_ptr<SettingsView>;


class SettingsView : public IView
                   , public std::enable_shared_from_this<SettingsView>
{
public:
    SettingsView(StackView& stackView);
    ~SettingsView();

    SettingsViewPtr getPtr();

    void init() override;
    void handle(input::Action action) override;
    void update(double dt) override;
    void draw(DisplayPtr display) override;

private:
    void setupMenu();

    std::shared_ptr<ListWidget> mListWidget;
    StackView& mStackView;
    SettingsPresenterPtr mPresenter;

};
