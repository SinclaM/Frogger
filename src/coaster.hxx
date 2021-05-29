#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

#include <iostream>
/// Interactive objects within the game
class Coaster
{
public:
    //
    // TYPE ALIASES
    //

    /// A direction is always {1, 0}, {-1, 0}, {0, 1}, or {0, -1}.
    /// It has not been made an enum class because using dims simplifies
    /// many operations
    using Direction = ge211::Dims<int>;
    using Dimension = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    //
    // PUBLIC MEMBER FUNCTIONS
    //

    /// Default constructor
    explicit Coaster(Game_config const&, int row_num, Position);

    /// Moves the object to the desired x value
    void move_to(int x, Game_config const&);

    /// Moves the object in time by one unit
    void move(double const dt, Game_config const&);

    /// Returns the position of the coaster
    Position coaster_pos() const;

    /// Gets the body rectangle
    Rectangle body() const;

    /// Gets hostility
    bool is_hostile() const;

    /// Gets the row number
    int row() const;

    /// submerges the turtle
    void submerge_turtle();

private:

    /// The objects hit box
    Rectangle body_;

    /// The real floating point number associated with its horizontal position
    double x_;

    /// Specifies which row the object is in
    /// Rows are numbered bottom to top, starting from zero, and counting only
    /// lanes where coasters move. So, in the current configuration of the
    /// game, there are ten rows (or rows) with the bottommost being row 0,
    /// which is the lane in which the yellow racecars move.
    int row_;

    /// The direction and speed of movement per second;
    int velocity_;

    /// Determines if the interactive object has the ability to kill
    bool hostile_;
};