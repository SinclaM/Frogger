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

    /// Number of coasters in each row
    std::vector<int> coaster_rows;

    /// Dimensions of short log
    Dimension short_log_dims;

    ///Dimensions of medium log
    Dimension medium_log_dims;

    /// Dimensions of long log
    Dimension long_log_dims;

    /// Dimensions of for three turtles
    Dimension three_turtle_dims;

    /// Time for turtle submersion
    double turtle_sumberged_time;

    /// Time until turtle begins submerging
    double turtle_submerging_time;

    /// Time turtles are submerged for
    double turtle_sumbersed_for;

    /// Dimensions for two turtles
    Dimension two_turtle_dims;

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

    /// Dimensions of the homes for the frog
    Dimension home_dims;

    /// Locations of the homes
    std::vector<Position> home_locations;

    /// Points awarded for foward steps
    int forward_step_points;

    /// Points awarded for reaching a lillypad
    int lilly_pad_points;

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