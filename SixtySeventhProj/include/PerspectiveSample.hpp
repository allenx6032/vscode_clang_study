// Ouzel by Elviss Strazdins

#ifndef PERSPECTIVESAMPLE_HPP
#define PERSPECTIVESAMPLE_HPP

#include "ouzel/audio/Effects.hpp"
#include "ouzel/audio/Listener.hpp"
#include "ouzel/audio/Submix.hpp"
#include "ouzel/gui/Widgets.hpp"
#include "ouzel/input/Cursor.hpp"
#include "ouzel/scene/Animator.hpp"
#include "ouzel/scene/Camera.hpp"
#include "ouzel/scene/Layer.hpp"
#include "ouzel/scene/Scene.hpp"

namespace samples
{
    class PerspectiveSample: public ouzel::scene::Scene
    {
    public:
        PerspectiveSample();

    private:
        void updateArrowPosition();

        ouzel::audio::Submix submix;
        ouzel::audio::Listener listener;

        ouzel::scene::Layer layer;
        ouzel::scene::Camera camera;
        ouzel::scene::Actor cameraActor;

        ouzel::math::Vector<float, 3> cameraRotation{};

        ouzel::scene::SpriteRenderer floorSprite;
        ouzel::scene::Actor floor;

        ouzel::scene::SpriteRenderer characterSprite;
        ouzel::scene::Actor character;
        ouzel::audio::Submix jumpSubmix;
        ouzel::audio::Voice jumpVoice;
        ouzel::audio::Panner jumpPanner;

        ouzel::scene::StaticMeshRenderer boxModel;
        ouzel::scene::Actor box;

        ouzel::scene::SpriteRenderer arrowSprite;
        ouzel::scene::Actor arrow;

        ouzel::scene::Rotate rotate;

        ouzel::EventHandler handler;

        ouzel::scene::Layer guiLayer;
        ouzel::scene::Camera guiCamera;
        ouzel::scene::Actor guiCameraActor;
        ouzel::gui::Menu menu;
        ouzel::gui::Button backButton;

        ouzel::input::Cursor cursor;
    };
}

#endif // PERSPECTIVESAMPLE_HPP
