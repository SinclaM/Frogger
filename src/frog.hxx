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

    /// A direction is always {1, 0}, {-1, 0}, {0, 1}, or {0, -1}.
    /// It has not been made an enum class because using dims simplifies
    /// many operations
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

    /// Move body_ (top left) to specified position, if the position is valid.
    /// Returns true if the frog has been moved, false otherwise.
    /// This return type is important because the function Frog::move (which
    /// takes a direction) needs to know if it needs to update where the
    /// frog is facing
    bool move_to(Position, Game_config const&);

    /// Gets top left of frog's body
    Position top_left() const;

    /// Gets frog's direction
    Direction facing() const;

    /// Gets frog's body
    Rectangle body() const;

private:

    //
    // PRIVATE MEMBER VARIABLES
    //

    /// The frog's hit box, a positioned rectangle
    Rectangle body_;

    /// How far the frog moves per hop in x and y directions
    Dimesion hop_dist_;

    /// The direction the frog is facing
    Direction facing_;
};

