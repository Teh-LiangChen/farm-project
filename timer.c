#include "timer.h"

void StartTimer(sTimer *timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool TimerDone(sTimer timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

float GetElapsed(sTimer timer)
{
    return GetTime() - timer.startTime;
}
