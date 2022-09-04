#pragma once

#include "EventBus.h"

struct TestEvent : public Event {
    int data = 0;
};
