// Ouzel by Elviss Strazdins

#ifndef SPRITESSAMPLE_HPP
#define SPRITESSAMPLE_HPP

#include "ouzel/gui/Widgets.hpp"
#include "ouzel/scene/Animators.hpp"
#include "ouzel/scene/Camera.hpp"
#include "ouzel/scene/Layer.hpp"
#include "ouzel/scene/Scene.hpp"

namespace samples
{
    class SpritesSample: public ouzel::scene::Scene
    {
    public:
        SpritesSample();

    private:
        ouzel::scene::Layer layer;
        ouzel::scene::Camera camera;
        ouzel::scene::Actor cameraActor;

        ouzel::scene::SpriteRenderer characterSprite;
        ouzel::scene::Actor character;
        ouzel::scene::SpriteRenderer fireSprite;
        ouzel::scene::Actor fireActor;
        ouzel::scene::SpriteRenderer triangleSprite;
        ouzel::scene::Actor triangleActor;

        ouzel::scene::Move move;

        ouzel::EventHandler handler;

        ouzel::gui::Button hideButton;
        ouzel::gui::Button wireframeButton;

        ouzel::scene::Layer guiLayer;
        ouzel::scene::Camera guiCamera;
        ouzel::scene::Actor guiCameraActor;
        ouzel::gui::Menu menu;
        ouzel::gui::Button backButton;
    };
}

#endif // SPRITESSAMPLE_HPP
