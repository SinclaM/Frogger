#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::on_key(ge211::Key key)
{
    // TODO: communicate to the View a way to reorient the sprite based on
    //  direction (or choose from a different sprite)
    if(model_.is_game_over() == false) {
        if (key == ge211::Key::up()) {
            model_.move_frog({0, -1});
        } else if (key == ge211::Key::down()) {
            model_.move_frog({0, 1});
        } else if (key == ge211::Key::left()) {
            model_.move_frog({-1, 0});
        } else if (key == ge211::Key::right()) {
            model_.move_frog({1, 0});
        }
    }

}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

