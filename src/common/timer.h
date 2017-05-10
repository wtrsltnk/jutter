#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer
{
    friend class TimerManager;
    Timer* _next;
    float _delay;
    std::function<void ()> _callback;

    Timer(float delay, std::function<void ()> callback);
    static class TimerManager* _instance;
public:
    static TimerManager& Manager();

};

class TimerManager
{
    friend class Timer;
    TimerManager();
    Timer* _firstInLine;
    float _time;
public:
    void update(float elapsed);
    Timer* addTimer(float delay, std::function<void ()> callback);
    void cancelTimer(Timer* timer);

};

#endif // TIMER_H
