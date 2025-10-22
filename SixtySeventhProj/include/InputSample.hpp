// Ouzel by Elviss Strazdins

#ifndef INPUTSAMPLE_HPP
#define INPUTSAMPLE_HPP

#include "ouzel/core/Engine.hpp"
#include "ouzel/gui/Widgets.hpp"
#include "ouzel/input/Cursor.hpp"
#include "ouzel/scene/Camera.hpp"
#include "ouzel/scene/Layer.hpp"
#include "ouzel/scene/Scene.hpp"

namespace samples
{
    class Mover: public ouzel::scene::Component
    {
    public:
        Mover()
        {
            handler.keyboardHandler = [this](const ouzel::KeyboardEvent& event) {
                if (actor)
                {
                    if (event.type == ouzel::Event::Type::keyboardKeyPress)
                    {
                        ouzel::math::Vector<float, 2> position = ouzel::math::Vector<float, 2>(actor->getPosition());

                        switch (event.key)
                        {
                            case ouzel::input::Keyboard::Key::w:
                                position.y() += 10.0F;
                                break;
                            case ouzel::input::Keyboard::Key::s:
                                position.y() -= 10.0F;
                                break;
                            case ouzel::input::Keyboard::Key::a:
                                position.x() -= 10.0F;
                                break;
                            case ouzel::input::Keyboard::Key::d:
                                position.x() += 10.0F;
                                break;
                            default:
                                break;
                        }

                        actor->setPosition(position);
                    }
                }

                return false;
            };

            ouzel::engine->getEventDispatcher().addEventHandler(handler);
        }

        ouzel::EventHandler handler;
    };

    class InputSample: public ouzel::scene::Scene
    {
    public:
        InputSample();

    private:
        ouzel::scene::Layer layer;
        ouzel::scene::Camera camera;
        ouzel::scene::Actor cameraActor;

        ouzel::EventHandler handler;

        ouzel::gui::Button hideButton;
        ouzel::gui::Button discoverButton;
        ouzel::scene::ParticleSystem flameParticleSystem;
        ouzel::scene::Actor flame;

        ouzel::scene::Layer guiLayer;
        ouzel::scene::Camera guiCamera;
        ouzel::scene::Actor guiCameraActor;
        ouzel::gui::Menu menu;
        ouzel::gui::Button backButton;

        ouzel::input::Cursor cursor;

        Mover mover;
    };
}

#endif // INPUTSAMPLE_HPP
