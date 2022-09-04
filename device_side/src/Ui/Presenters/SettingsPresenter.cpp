#include "SettingsPresenter.h"

#include "Misc/Logger.h"
#include "Misc/EventBus.h"
#include "Misc/EventTypes.h"


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
    TestEvent event;
    event.data = 1;
    EVENT_BUS.publish<TestEvent>(std::move(event));
}

void SettingsPresenter::myCheckboxToggled(bool checked) {
    LOG_LN("Checkbox toggled to: " << checked);
}
