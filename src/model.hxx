#pragma once

#include <iostream>

#include <ge211.hxx>

#include "game_config.hxx"

#include "frog.hxx"

#include "coaster.hxx"

#include "clock.hxx"

#include "home.hxx"

class Model
{
public:

    //
    // TYPE ALIASES
    //

    using Direction = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;
    using Dimension = ge211::Dims<int>;
    using Coaster_matrix = std::vector<std::vector<Coaster>>;

private:
    /// The frog
    Frog frog_;

    /// The clock tracking the time the frog has left to reach a home
    Clock life_clock_;

    /// Clock which imposes a cool down on frog movement
    Clock hop_clock_;

    /// The water kill_zone, which is invisible--never drawn by the View
    Rectangle kill_zone_;

    /// The time the frog waits before resetting after dying
    Clock reset_clock_;

    /// Vector of Vectors containing the interactive objects in each row
    Coaster_matrix coasters_;

    /// Clock determining when the turtle submerges
    Clock turtle_timer;

    /// Clock determining when the user sees the indicator that the turtle is
    /// submerging
    Clock turtle_torpedo;

    /// Clock determining how long the turtles are submersed for
    Clock turtles_submersed;

    /// A vector holding all the homes for the frog
    std::vector<Home> homes_;

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

    /// Move the coasters every four frames
    void move_coasters(double const dt, Coaster_matrix&);

    /// Gets the interactive objects
    Coaster_matrix get_coasters() const;

    /// submerges the turtles
    void turtles_submerge();

    /// Checks if the frog is on top of a log or turtle that is above water
    const Coaster* frog_on_platform() const;

    /// Checks if the frog is touching an unoccupied home
    Home* frog_touching_home() const;

    /// Gets the homes
    std::vector<Home> homes() const;

    /// Checks whether the game is over
    bool is_game_over() const;

};
