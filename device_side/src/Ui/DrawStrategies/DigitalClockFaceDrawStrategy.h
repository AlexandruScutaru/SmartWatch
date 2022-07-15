#include "IClockFaceDrawStrategy.h"


class DigitalClockFaceDrawStrategy : public IClockFaceDrawStrategy {
public:
    void draw(DisplayPtr display, const clock_time::TimeData& time) override;
};
