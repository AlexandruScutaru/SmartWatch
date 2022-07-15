#include "SettingsPresenter.h"

#include "Misc/Logger.h"


SettingsPresenter::SettingsPresenter(IViewWeakPtr view)
    : mView(view)
{
    LOG_LN("SettingsPresenter::ctor");
}

SettingsPresenter::~SettingsPresenter() {
    LOG_LN("SettingsPresenter::dtor");
}

void SettingsPresenter::myButtonPressed() {
    LOG_LN("Button pressed");
}

void SettingsPresenter::myCheckboxToggled(bool checked) {
    LOG_LN("Checkbox toggled to: " << checked);
}
