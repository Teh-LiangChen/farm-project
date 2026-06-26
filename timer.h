#ifndef TIMER_H_
#define TIMER_H_

#include "raylib.h"
#include "raymath.h"

typedef struct
{
    double startTime;
    double lifeTime;
} sTimer;

void StartTimer(sTimer *timer, double lifetime);

bool TimerDone(sTimer timer);

float GetElapsed(sTimer timer);

#endif