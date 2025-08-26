/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#pragma once
#include "Color.hpp"
#include "Config.hpp"
#include "View.hpp"
#include "event.hpp"
#include <sfml/SFML_Graphics.hpp>
#include <queue>

#define DEFAULT_MODE_BITS_PER_PIXEL 32
#define DEFAULT_CLEAR_COLOR Color(0, 0, 0, 255)

namespace gameEngine {
    class VideoMode {
        public:
            VideoMode() :
                _videoMode()
            {
            };
            VideoMode(unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = DEFAULT_MODE_BITS_PER_PIXEL) :
                _videoMode(modeWidth, modeHeight, modeBitsPerPixel)
            {
            };

            static VideoMode getDesktopMode();

            unsigned int width() const { return _videoMode.width; };
            unsigned int height() const { return _videoMode.height; };
            unsigned int bitsPerPixel() const { return _videoMode.bitsPerPixel; };

        private:
            sf::VideoMode _videoMode;
    };


    namespace style {
        enum
        {
            None       = 0,                         // <-- No border / title bar (this flag and all others are mutually exclusive)
            Titlebar   = 1 << 0,                    // <-- Title bar + fixed border
            Resize     = 1 << 1,                    // <-- Title bar + resizable border + maximize button
            Close      = 1 << 2,                    // <-- Title bar + close button
            Fullscreen = 1 << 3,                    // <-- Fullscreen mode (this flag and all others are mutually exclusive)

            Default = Titlebar | Resize | Close     // <-- Default window style
        };
    }

    struct ContextSettings
    {
        /**
         * @brief Enumeration of the context attribute flags
         *
         */
        enum Attribute
        {
            Default = 0,      // <-- Non-debug, compatibility context (this and the core attribute are mutually exclusive)
            Core    = 1 << 0, // <-- Core attribute
            Debug   = 1 << 2  // <-- Debug attribute
        };

        /**
         * @brief Default constructor
         *
         * @param depth        Depth buffer bits
         * @param stencil      Stencil buffer bits
         * @param antialiasing Antialiasing level
         * @param major        Major number of the context version
         * @param minor        Minor number of the context version
         * @param attributes   Attribute flags of the context
         * @param sRgb         sRGB capable framebuffer
         *
         */
        explicit ContextSettings(unsigned int depth = 0, unsigned int stencil = 0, unsigned int antialiasing = 0, unsigned int major = 1, unsigned int minor = 1, unsigned int attributes = Default, bool sRgb = false) :
            depthBits        (depth),
            stencilBits      (stencil),
            antialiasingLevel(antialiasing),
            majorVersion     (major),
            minorVersion     (minor),
            attributeFlags   (attributes),
            sRgbCapable      (sRgb)
        {
        }

        // INFO: Member data
        unsigned int depthBits;         // <-- Bits of the depth buffer
        unsigned int stencilBits;       // <-- Bits of the stencil buffer
        unsigned int antialiasingLevel; // <-- Level of antialiasing
        unsigned int majorVersion;      // <-- Major number of the context version to create
        unsigned int minorVersion;      // <-- Minor number of the context version to create
        Uint32       attributeFlags;    // <-- The attribute flags to create the context with
        bool         sRgbCapable;       // <-- Whether the context framebuffer is sRGB capable
    };

    // reproduce the sfml RenderWindow class
    class RenderWindow {
        public:
            RenderWindow();
            RenderWindow(VideoMode mode, const std::string &title, Uint32 style = style::Default, const ContextSettings &settings = ContextSettings());
            ~RenderWindow();

            void create(VideoMode mode, const std::string &title, Uint32 style = style::Default, const ContextSettings &settings = ContextSettings());
            void close();
            bool isOpen() const;
            bool pollEvent(Event &event);
            void clear(const Color &color = DEFAULT_CLEAR_COLOR);
            void display();
            void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);

            gameEngine::Vector2f mapPixelToCoords(const gameEngine::Vector2i &point) const;

            void setView(const gameEngine::View &view);
            gameEngine::View getView() const;

            /**
             * @brief Get the Render Window object
             *
             * @return sf::RenderWindow&
             * @note This function is used to get the sfml window object
             * if needed for some specific functions that are not
             * implemented in the game engine yet
             */
            sf::RenderWindow &getSfmlRenderWindow();

        private:
            gameEngine::View _view;
            sf::RenderWindow _window;
            std::queue<gameEngine::Event> _events;
    };
}
