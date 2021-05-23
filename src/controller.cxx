#include "controller.hxx"

Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if(key == ge211::Key::up()){
        model_.move_frog({0, -1});
    }else if(key == ge211::Key::down()){
        model_.move_frog({0, 1});
    }else if(key == ge211::Key::left()){
        model_.move_frog({-1, 0});
    }else if(key == ge211::Key::right()){
        model_.move_frog({1, 0});
    }
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}
