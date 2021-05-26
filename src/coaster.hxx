#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

#include <iostream>
/// Interactive objects within the game
class coaster
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

    enum object_type {lilypad, occupied_lilypad, short_log, medium_log,
        long_log, passive_turtle, turtle, submerging_turtle, submerged_turtle,
        car};

    //
    // PUBLIC MEMBER FUNCTIONS
    //

    /// Default constructor
    explicit coaster(Game_config const&, object_type, int row_num, Position);

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

    /// Returns the coaster type
    object_type& coaster_type();

    /// submerges the turtle
    void submerge_turtle();

    /// Returns the row that the coaster is in
    int get_row();

private:

    /// The objects hit box
    Rectangle body_;

    /// The real floating point number associated with its horizontal position
    double x_;

    /// Object Type
    object_type type_;

    /// Specifies which row the object is in
    int row_;

    /// The direction and speed of movement per second;
    int velocity_;

    /// Determines if the interactive object has the ability to kill
    bool hostile_;


};