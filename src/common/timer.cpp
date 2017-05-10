#include "timer.h"

Timer::Timer(float delay, std::function<void ()> callback) : _delay(delay), _callback(callback) { }

TimerManager* Timer::_instance = nullptr;

TimerManager& Timer::Manager()
{
    if (Timer::_instance== nullptr) Timer::_instance = new TimerManager();

    return *Timer::_instance;
}

TimerManager::TimerManager() : _firstInLine(nullptr), _time(0.0f) { }

void TimerManager::update(float elapsed)
{
    this->_time += elapsed;

    while (this->_firstInLine != nullptr && this->_firstInLine->_delay < this->_time)
    {
        auto timer = this->_firstInLine;
        this->_firstInLine = this->_firstInLine->_next;
        timer->_callback();
        delete timer;
    }
}

Timer* TimerManager::addTimer(float delay, std::function<void ()> callback)
{
    auto timer = new Timer(this->_time + delay, callback);
    if (this->_firstInLine == nullptr || this->_firstInLine->_delay > timer->_delay)
    {
        timer->_next = this->_firstInLine;
        this->_firstInLine = timer;
        return timer;
    }

    auto i = this->_firstInLine;
    while (i->_next != nullptr && i->_next->_delay < timer->_delay)
    {
        i = i->_next;
    }

    timer->_next = i->_next;
    i->_next = timer;

    return timer;
}

void TimerManager::cancelTimer(Timer* timer)
{
    if (this->_firstInLine == timer)
    {
        this->_firstInLine = this->_firstInLine->_next;
        delete timer;
        return;
    }

    auto i = this->_firstInLine;
    while (i != nullptr && i->_next != timer)
    {
        i = i->_next;
    }

    if (i != nullptr) i->_next = timer->_next;
}
