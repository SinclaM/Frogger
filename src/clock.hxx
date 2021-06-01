#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

#include <iostream>
/// Clocks are used to in accordance with timed events. They count the time
/// that passed and can be paused and reset.
class Clock
{
public:
    /// The constructor, which initializes max_time_ and
    /// current_time to the given parameter and paused_ to false
    Clock(double const, bool const);

    /// Returns current_time
    double time() const;

    /// Return whether the clock is paused or not
    bool is_paused() const;

    /// Removes dt seconds from the current_time_, or sets current_time_ to 0
    /// if subtracting dt would make it negative, so long as the clock is not
    /// paused.
    void dec(double const dt);

    /// Sets current_time to max_time
    void reset();

    /// Pauses the clock
    void pause();

    /// Resumes the clock
    void resume();

    /// Sets the time on a clock, used for testing
    void set_time(double);

private:
    /// The maximum time on the clock (in seconds)
    double max_time_;

    /// The current left on the clock
    double current_time_;

    /// The state of the clock. If it is paused, a call to dec will do nothing,
    /// otherwise it will tick down.
    bool paused_;
};

/// Stream insertion (printing) for `Clock`. Used for testing
std::ostream&
operator<<(std::ostream&, Clock const&);