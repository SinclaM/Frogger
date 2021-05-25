#pragma once

#include <iostream>

#include <ge211.hxx>

#include "game_config.hxx"

#include "frog.hxx"

#include "coaster.hxx"

#include "clock.hxx"

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

    /// The clock tracking the time the frog has left to reach a home
    Clock life_clock_;

    /// Clock which imposes a cool down on frog movement
    Clock hop_clock_;

    /// An integer used to determine whether the frame is even or odd, used
    /// to make objects move at speeds less than 1 pixel per frame. Iterates
    // to 100 then resets
    int frame_counter;
  
    /// The water kill_zone, which is invisible--never drawn by the View
    Rectangle kill_zone_;

    /// The time the frog waits before resetting after dying
    Clock reset_clock_;

    /// Vector of Vectors conataining the interactive objects in each row
    vector<vector<coaster>> coaster_;

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

    /// Move the interactive objects every four frames
    void move_coasters(
            std::vector<std::vector<coaster>>&);

    /// Gets the interactive objects
    vector<vector<coaster>> get_coaster() const;
};
