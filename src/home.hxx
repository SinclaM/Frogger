#pragma once

#include <ge211.hxx>

#include "game_config.hxx"

/// A set of positions at the end of the game that the frog is attempting to
/// reach. Once all the homes have been occupied by the frog, the player wins.
class Home{
public:

    //
    // TYPE ALIASES
    //

    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    //
    // PUBLIC MEMBER FUNCTIONS
    //

    /// Constructor
    explicit Home(const Game_config&, Position);

    /// Gets the body
    Rectangle body() const;

    /// Gets occupation status
    bool occupied() const;

    /// Sets occupation status to occupied
    void occupy();



private:

    //
    // DATA MEMBERS
    //

    /// The rectangular body of the home
    Rectangle body_;

    /// Whether the home is occupied
    bool occupied_;
};

/// Gets how many homes are occupied in a vector
int occupied_count(std::vector<Home>);

/// Determines whether all homes in a vector are occupied
bool all_occupied(std::vector<Home>);

/// Makes a vector of homes as specified by the game config
std::vector<Home> make_homes(const Game_config&);


