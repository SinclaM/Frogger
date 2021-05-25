#pragma once

#include <ge211.hxx>

struct Game_config{

    //
    // TYPE ALIASES
    //

    using Dimension = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    /// Constructor
    Game_config();

    /// Window dimensions
    Dimension scene_dims;

    /// Frog dimensions
    Dimension frog_dims;

    /// Amount frog moves per step in the x and y directions
    Dimension hop_dist;

    /// Starting position for frog
    Position start;

    /// The time a frog has to reach a home
    unsigned int lifetime;

    /// The minimum time between frog hops
    unsigned int hop_time;

    /// Car dimensions
    Dimension car_dims;

    /// The water kill_zone
    Rectangle kill_zone;

    /// Time the frog waits, dead, before resetting
    unsigned int reset_wait_time;

    /// Velocities of objects for each given row
    std::vector<int> row_velocities;

    /// Number of cars in each row
    std::vector<int> car_rows;




    /// Returns whether a position is a valid position on screen
    bool in_scene(Position const) const;

    /// Returns whether a rectangle fits on screen
    bool in_scene(Rectangle const) const;

    /// Returns the row velocity
    int row_velocity(int const) const;
};