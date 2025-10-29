#include <blah/blah.h>
using namespace Blah;

Batch batch;

int main()
{
    Config config;
    config.name = "blah app";
    config.on_render = []()
    {
        auto target = App::backbuffer();
        target->clear(Color::black);

        auto center = Vec2f(target->width(), target->height()) / 2;
        auto rotation = Time::seconds * Calc::TAU;
        auto transform = Mat3x2f::create_transform(center, Vec2f::zero, Vec2f::one, rotation);

        batch.push_matrix(transform);
        batch.rect(Rectf(-32, -32, 64, 64), Color::red);
        batch.pop_matrix();

        batch.render(target);
        batch.clear();
    };

    return App::run(&config);
}