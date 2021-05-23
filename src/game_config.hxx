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

    /// Amount frog moves per step
    int hop_dist;

    /// Starting position for frog
    Position start;

    /// The time a frog has to reach a home
    int lifetime;

    /// Returns whether a position is a valid position on screen
    bool in_scene(Position const) const;

    /// Returns whether a rectangle fits on screen
    bool in_scene(Rectangle const) const;
};