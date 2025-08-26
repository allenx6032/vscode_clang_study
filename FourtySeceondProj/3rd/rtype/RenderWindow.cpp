/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "RenderWindow.hpp"

gameEngine::RenderWindow::RenderWindow()
{
}
gameEngine::RenderWindow::RenderWindow(VideoMode mode, const std::string &title, Uint32 style, const ContextSettings &settings)
{
    sf::VideoMode videoMode(mode.width(), mode.height(), mode.bitsPerPixel());
    sf::ContextSettings contextSettings(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
    _window.create(videoMode, title, style, contextSettings);
}
gameEngine::RenderWindow::~RenderWindow()
{
}

void gameEngine::RenderWindow::create(VideoMode mode, const std::string &title, Uint32 style, const ContextSettings &settings)
{
    sf::VideoMode videoMode(mode.width(), mode.height(), mode.bitsPerPixel());
    sf::ContextSettings contextSettings(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
    _window.create(videoMode, title, style, contextSettings);
}
void gameEngine::RenderWindow::close()
{
    _window.close();
}
bool gameEngine::RenderWindow::isOpen() const
{
    return _window.isOpen();
}
bool gameEngine::RenderWindow::pollEvent(Event &event)
{
    sf::Event tmp;
    while (_window.pollEvent(tmp)) {
        gameEngine::Event e;

        switch (tmp.type) {
            case sf::Event::Closed:
                e.type = gameEngine::Event::Closed;
                break;
            case sf::Event::Resized:
                e.type = gameEngine::Event::Resized;
                break;
            case sf::Event::LostFocus:
                e.type = gameEngine::Event::LostFocus;
                break;
            case sf::Event::GainedFocus:
                e.type = gameEngine::Event::GainedFocus;
                break;
            case sf::Event::TextEntered:
                e.type = gameEngine::Event::TextEntered;
                break;
            case sf::Event::KeyPressed:
                e.type = gameEngine::Event::KeyPressed;
                break;
            case sf::Event::KeyReleased:
                e.type = gameEngine::Event::KeyReleased;
                break;
            case sf::Event::MouseWheelMoved:
                e.type = gameEngine::Event::MouseWheelMoved;
                break;
            case sf::Event::MouseWheelScrolled:
                e.type = gameEngine::Event::MouseWheelScrolled;
                break;
            case sf::Event::MouseButtonPressed:
                e.type = gameEngine::Event::MouseButtonPressed;
                break;
            case sf::Event::MouseButtonReleased:
                e.type = gameEngine::Event::MouseButtonReleased;
                break;
            case sf::Event::MouseMoved:
                e.type = gameEngine::Event::MouseMoved;
                break;
            case sf::Event::MouseEntered:
                e.type = gameEngine::Event::MouseEntered;
                break;
            case sf::Event::MouseLeft:
                e.type = gameEngine::Event::MouseLeft;
                break;
            default:
                e.type = gameEngine::Event::Undefined;
                break;
        }
        if (e.type == gameEngine::Event::Undefined)
            continue;

        e.size.width        = tmp.size.width;
        e.size.height       = tmp.size.height;

        e.text.unicode      = tmp.text.unicode;

        e.key.code          = gameEngine::Keyboard::convertKey(tmp.key.code);
        e.key.alt           = tmp.key.alt;
        e.key.control       = tmp.key.control;
        e.key.shift         = tmp.key.shift;
        e.key.system        = tmp.key.system;

        switch (tmp.mouseButton.button) {
            case sf::Mouse::Button::Left:
                e.mouseButton.button = gameEngine::Mouse::Button::Left;
                break;
            case sf::Mouse::Button::Right:
                e.mouseButton.button = gameEngine::Mouse::Button::Right;
                break;
            case sf::Mouse::Button::Middle:
                e.mouseButton.button = gameEngine::Mouse::Button::Middle;
                break;
            case sf::Mouse::Button::XButton1:
                e.mouseButton.button = gameEngine::Mouse::Button::XButton1;
                break;
            case sf::Mouse::Button::XButton2:
                e.mouseButton.button = gameEngine::Mouse::Button::XButton2;
                break;
            default:
                break;
        }
        e.mouseButton.x     = tmp.mouseButton.x;
        e.mouseButton.y     = tmp.mouseButton.y;

        e.mouseWheel.delta  = tmp.mouseWheel.delta;
        e.mouseWheel.x      = tmp.mouseWheel.x;
        e.mouseWheel.y      = tmp.mouseWheel.y;

        e.mouseMove.x       = tmp.mouseMove.x;
        e.mouseMove.y       = tmp.mouseMove.y;

        _events.push(e);
    }
    if (_events.empty())
        return false;
    event = _events.front();
    _events.pop();
    return true;
}
void gameEngine::RenderWindow::clear(const Color &color)
{
    _window.clear(sf::Color(color.r, color.g, color.b, color.a));
}
void gameEngine::RenderWindow::display()
{
    _window.display();
}
void gameEngine::RenderWindow::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    _window.draw(drawable, states);
}

gameEngine::Vector2f gameEngine::RenderWindow::mapPixelToCoords(const gameEngine::Vector2i &point) const
{
    sf::Vector2f tmp = _window.mapPixelToCoords(sf::Vector2i(point.x, point.y));
    return gameEngine::Vector2f(tmp.x, tmp.y);
}

void gameEngine::RenderWindow::setView(const gameEngine::View &view)
{
    _view = view;
    _window.setView(view);
}

gameEngine::View gameEngine::RenderWindow::getView() const
{
    return _view;
}

sf::RenderWindow &gameEngine::RenderWindow::getSfmlRenderWindow()
{
    return _window;
}

