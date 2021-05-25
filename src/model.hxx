#pragma once

#include <iostream>

#include <ge211.hxx>

#include "game_config.hxx"

#include "frog.hxx"

#include "coaster.hxx"

using namespace std;

class Model
{
public:

    //
    // TYPE ALIASES
    //

    using Direction = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;
    using coaster_matrix = std::vector<std::vector<coaster>>;

private:
    /// The frog
    Frog frog_;

    /// The time left on the timer
    size_t time_left_;

    /// Cool-down so that the frog can't move so fast
    size_t cool_down_;

    /// Vector of Vectors containing the interactive objects in each row
    coaster_matrix coasters_;

public:
    /// The game config
    Game_config const config;

    /// Constructor
    explicit Model(Game_config const& config = Game_config());

    /// Updates the state of the game for one frame
    void on_frame(double dt);

    /// Places the frog back at the starting position and reset the timer
    void reset_frog();

    /// Move the frog in a direction (called by controller)
    void move_frog(Direction);

    /// Gets frog
    Frog frog() const;

    /// Move the interactive objects for one frame
    void move_coasters();

    /// Gets the interactive objects
    coaster_matrix get_coasters() const;
};
