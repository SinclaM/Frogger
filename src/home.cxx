#include "home.hxx"

Home::Home(Game_config const& config, Home::Position pos)
        : body_(pos.x, pos.y, config.home_dims.width, config.home_dims.height),
          occupied_(false)
{ }

std::vector<Home>
make_homes(Game_config const& config)
{
    std::vector<Home> homes;
    for(auto pos : config.home_locations){
        homes.push_back(Home{config, pos});
    }
    return homes;
}

bool
Home::occupied() const
{
    return occupied_;
}

void
Home::occupy()
{
    occupied_ = true;
}

Home::Rectangle
Home::body() const
{
    return body_;
}

bool
all_occupied(std::vector<Home> homes)
{
    for(auto home : homes){
        if(!home.occupied()){
            return false;
        }
    }
    return true;
}

int
occupied_count(std::vector<Home> homes)
{
    int count = 0;
    for(auto home : homes){
        if(home.occupied()){
            count++;
        }
    }
    return count;
}
