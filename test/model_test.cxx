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

/// We could also probably add losing life into this test case
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

/// Test cases to add:
//Frog standing on turtles and logs
// Coasters increasing in speed with each home hit
//Losing all lives causes loss
// Running out of time causes loss
// winning the game

TEST_CASE("Frog Standing on moving passive objects")
{


    // Create the coaster to be used in the test, a turtle coaster, to be
    // spawned in at the frog's starting position. Test cases for a log or
    // turtle are essentially identical.
    Coaster c(Game_config(), 6, Coaster::object_type::passive_turtle,
              {Game_config().start.x,
               Game_config().start.y});

    // create the coaster matrix
    Model::Coaster_matrix coasters{{c}};

    // create a model with only the single coaster created above
    Model m(coasters);

    // Create a Posn with the inital frog position
    Model::Position initial_frog_position{m.config.start.x - m.config
    .frog_dims.width /2 , m.config.start.y};

    // Gets the actual frog position
    Model::Position actual_frog_position{m.frog().body().x, m.frog().body()
    .y};

    // Checks that the expected initial frog position and actual initial frog
    // positions are equal
    CHECK(actual_frog_position == initial_frog_position);

    // Checks to make sure a collision is detected with the turtle
    CHECK(m.frog().stict_hits(c.body(), m.config));

    // Create a half second frame
    m.on_frame(1.0 / 2);

    // Checks the collision with the turtle again
    CHECK(m.frog().stict_hits(c.body(), m.config));


    // Creates a posn representing the expected ending position of the frog
    // determined by the movement of the the turtle
    Model::Position frog_ending_pos{m.config.row_velocities[6] / 2 + m
            .config.start.x, m.config.start.y};

    // Gets the frog's actual position
    actual_frog_position = {m.frog().body().x, m.frog().body().y};

    // Checks that the expected final position and ending position are equal
    CHECK(actual_frog_position == frog_ending_pos);


}