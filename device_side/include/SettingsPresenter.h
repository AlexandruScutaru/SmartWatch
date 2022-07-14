#pragma once

#include "IView.h"


class SettingsPresenter {
public:
    SettingsPresenter(IViewWeakPtr view);
    ~SettingsPresenter();

    void myButtonPressed();
    void myCheckboxToggled(bool checked);

private:
    IViewWeakPtr mView;
};
