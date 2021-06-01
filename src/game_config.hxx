#pragma once

#include <ge211.hxx>

/// Hold the main configurations for the game such starting position, the
/// movement distance for the frog, velocities of the coasters, etc...
struct Game_config{

    //
    // TYPE ALIASES
    //

    using Dimension = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    /// Constructor
    Game_config();

    /// Enumeration to refer to lanes
    enum row {racecar_1_row, tractor_row, pink_car_row, racecar_2_row,
            truck_row, empty_row, three_turtles_row, small_log_row,
            long_log_row, two_turtles_row, medium_log_row};

    /// Window dimensions
    Dimension scene_dims;

    /// Frog dimensions
    Dimension frog_dims;

    /// Amount frog moves per step in the x and y directions
    Dimension hop_dist;

    /// The dimensions of coasters
    Dimension coaster_small;
    Dimension coaster_medium;
    Dimension coaster_long;
    Dimension coaster_longest;

    /// Dimensions of the homes for the frog
    Dimension home_dims;



    /// Starting position for frog (top center)
    Position start;



    /// The water kill_zone
    Rectangle kill_zone;



    /// The time a frog has to reach a home
    double lifetime;

    /// The minimum time between frog hops
    double hop_time;

    /// Time the frog waits, dead, before resetting
    double reset_wait_time;

    /// Time for turtle submersion
    double turtle_sumberged_time;

    /// Time until turtle begins submerging
    double turtle_submerging_time;

    /// Time turtles are submerged for
    double turtle_sumbersed_for;

    /// Fraction of the frog which must be colliding with a platform or home
    /// before the frog will fall into the water. The most lenient collision
    /// detection would have a value of 0 (the edges can touch and the frog
    /// will still be on it). The most strict collision detection would have
    /// a value of 1 (the frog must be entirely on the platform or it will
    ///  fall off)
    double frog_collision_fraction;



    /// Top of the first coaster lane
    int bottom_lane_y;

    /// Random deviation added to initial x position of cars, turtles, logs,
    /// etc. The deviation is a random number between -random_deviation_range
    /// and random_deviation_range
    int random_deviation_range;

    /// Points awarded for forward steps
    int forward_step_points;

    /// Points awarded for reaching a home
    int lilly_pad_points;

    /// Frog starting lives
    int frog_starting_lives;

    /// Lower limit for initial, random distance from left side of screen, a
    /// shift applied to all coasters in a row, but different for each row
    int shift_min;

    /// Upper limit for initial, random distance from left side of screen, a
    /// shift applied to all coasters in a row, but different for each row
    int shift_max;

    /// Increase to velocities of coaster after a frog reaches a home
    int velocity_gain;




    /// Velocities of objects for each given row
    std::vector<int> row_velocities;

    /// Number of coasters in each row
    std::vector<int> coaster_rows;


    /// Default spacing between coasters for every lane (before random
    /// deviation)
    std::vector<int> spacings;


    /// Locations of the homes
    std::vector<Position> home_locations;

    //
    // Config for the View
    //

    /// Position of score sprite
    Position score_pos;

    /// Position (top left) of leftmost life sprite
    Position leftmost_life_pos;



    /// Rectangle that will be used for do draw the timer
    Rectangle timer_rec;



    /// Horizontal spacing between life sprites
    int life_spacing;

    /// Small font size for the view
    int small_font_size;

    /// Large font size for the view
    int large_font_size;



    /// Color for the game-over background on loss
    ge211::Color end_game_background_fade_loss;

    /// Color for the game-over background on victory
    ge211::Color end_game_background_fade_win;

    /// Color that the timer will be drawn with
    ge211::Color timer_color;


    //
    // PUBLIC HELPERS
    //

    /// Returns the row velocity in pixels per 4 frames
    int row_velocity(int const) const;

    /// Returns whether a position is a valid position on screen for the frog
    /// to be in
    bool in_scene(Position const) const;

    /// Returns whether a rectangle fits on screen
    bool in_scene(Rectangle const) const;

    /// Returns whether or not a position is outside the object scene, which
    /// is 105 pixels off either the left or right of the actual scene dims
    bool in_object_scene(Position const) const;
};
