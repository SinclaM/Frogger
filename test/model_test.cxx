#include "model.hxx"

#include <catch.hxx>

#include <iostream>

TEST_CASE("Frog moves")
{
    // TODO: Figure out why this is working when hop_clock is being annoying

    Model m;
    m.remove_coasters(); // no cars, please
    ge211::Posn<int> expected(m.frog().body().top_left());
    CHECK(m.frog().body().top_left() == expected);

    // Upward hop
    expected.up_by(m.config.hop_dist.height);
    m.move_frog({0, -1});
    CHECK(m.frog().body().top_left() == expected);

    // Downward hop
    expected.down_by(m.config.hop_dist.height);
    m.move_frog({0, 1});
    CHECK(m.frog().body().top_left() == expected);

    // Rightward hop
    expected.right_by(m.config.hop_dist.width);
    m.move_frog({1, 01});
    CHECK(m.frog().body().top_left() == expected);

    // Leftward hop
    expected.left_by(m.config.hop_dist.width);
    m.move_frog({-1, 0});
    CHECK(m.frog().body().top_left() == expected);

    // Forbidden hop. The frog can't go any farther down than it is initially
    // since that space is reserved for the timer.
    m.move_frog({0, 1});
    CHECK(m.frog().body().top_left() == expected);
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//

TEST_CASE("Frog hits car"){
    // TODO: Fix by setting hop clock to 0
    // Model m;
    // m.remove_coasters();
    // // Place a car right above the frog
    // ge211::Posn<int> pos(m.frog().body().top_left().up_by(
    //                                             m.config.hop_dist.height));
    // Coaster c(m.config, Game_config::racecar_1_row, pos);
    // CHECK_FALSE(m.frog().hits(c.body()));
    // std::cout << m.frog().body() << std::endl << c.body() << std::endl;
    // m.move_frog({0, -1});
    // std::cout << m.frog().body() << std::endl << c.body() << std::endl;
    // CHECK(m.frog().hits(c.body()));
}