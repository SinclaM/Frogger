#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

#include "coaster.hxx"

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

    /// If the frog is alive (able to move) or dead (awaiting to be reset)
    bool alive;

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

    /// Gets frog's direction
    Direction facing() const;

    /// Gets frog's body
    Rectangle body() const;

    /// Detects collision between body_ and a rectangle
    bool hits(Rectangle const) const;

    /// Collision detection but less forgiving
    bool stict_hits(Rectangle const, Game_config const&) const;

    /// Moves a frog with a platform
    void move_with(Coaster const, double const dt, Game_config const&);

    /// Increases the frogs score for forward steps
    void increment_score_for_foward_steps(Game_config const&);

    /// Increases the frogs score for lillypads
    void increment_score_for_lillypad(Game_config const&);

    /// Gets the frog's score
    int get_frog_score();

    /// Returns the frog's lives
    int frog_lives_left();

    /// Decrements the frog's lives by one
    void decrement_frog_life();

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

    /// Real x value of the body
    double x_;

    /// The frog's score
    int score_;

    /// The frog's highest y_position in the given life, used to determine
    // when to give points for forward movements
    int highest_y_pos;

    /// The number of lives the frog has
    int lives_;

    /// Increases the frog's score by the specified amount
    void increment_score(int);


};
