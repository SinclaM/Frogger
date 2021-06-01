#include "clock.hxx"

Clock::Clock(double const max_time, bool const paused)
        : max_time_(max_time),
          current_time_(max_time),
          paused_(paused)
{ }


double
Clock::time() const
{
    return current_time_;
}

bool
Clock::is_paused() const
{
    return paused_;
}

void
Clock::dec(double const dt)
{
    if(!paused_ && current_time_ > 0){
        if(current_time_ > dt){
            current_time_ -= dt;
        }else{
            current_time_ = 0;
        }
    }
}

void
Clock::reset()
{
    current_time_ = max_time_;
}

void
Clock::pause()
{
    paused_ = true;
}

void
Clock::resume()
{
    paused_ = false;
}

void
Clock::set_time(double time)
{
    current_time_ = time;
}


std::ostream&
operator<<(std::ostream& o, Clock const& clock)
{
    return o << "Current time : " << clock.time() << ", Paused? : "
             << clock.is_paused() << std::endl;
}
