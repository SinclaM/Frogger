#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

/// A player controlled frog
class Frog
{
public:

    //
    // TYPE ALIASES
    //
    using Direction = ge211::Dims<int>;
    using Dimesion = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    //
    // PUBLIC MEMBER FUNCTIONS
    //

    /// Default constructor
    explicit Frog(Game_config const&);

    /// Move body_ by the step size in the specified direction
    void move(Direction, Game_config const&);

    /// Move body_ (top left_ to specified position
    void move_to(Position, Game_config const&);

    /// Gets top left of frog's body
    Position top_left() const;

    /// Gets frog's body
    Rectangle body() const;

private:

    //
    // PRIVATE MEMBER VARIABLES
    //

    /// The frog's hit box, a positioned rectangle
    Rectangle body_;

    /// How far the frog moves per hop
    int hop_dist_;
};

