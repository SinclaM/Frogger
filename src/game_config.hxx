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

    /// Starting position for frog (top center)
    Position start;

    /// The time a frog has to reach a home
    double lifetime;

    /// The minimum time between frog hops
    double hop_time;

    /// Car dimensions
    Dimension car_dims;

    /// The water kill_zone
    Rectangle kill_zone;

    /// Time the frog waits, dead, before resetting
    double reset_wait_time;

    /// Velocities of objects for each given row
    std::vector<int> row_velocities;

    /// Number of cars in each row
    std::vector<int> car_rows;

    /// Top of the first coaster lane
    int bottom_lane_y;

    /// Default spacing between coasters for every lane (before random
    /// deviation)
    std::vector<int> spacings;

    /// Random deviation added to initial x position of cars, turtles, logs,
    /// etc. The deviation is a random number between -random_deviation_range
    /// and random_deviation_range
    int random_deviation_range;

    /// The dimensions of coasters
    Dimension coaster_small;
    Dimension coaster_medium;
    Dimension coaster_long;
    Dimension coaster_longest;

    /// Returns whether a position is a valid position on screen for the frog
    /// to be in
    bool in_scene(Position const) const;

    /// Returns whether a rectangle fits on screen
    bool in_scene(Rectangle const) const;

    /// Returns the row velocity in pixels per 4 frames
    int row_velocity(int const) const;


    /// Returns whether or not a position is outside the object scene, which
    /// is 105 pixels off either the left or right of the actual scene dims
    bool in_object_scene(Position const) const;
};