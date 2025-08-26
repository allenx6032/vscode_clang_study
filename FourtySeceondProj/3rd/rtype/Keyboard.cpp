/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "Keyboard.hpp"

namespace gameEngine {
    Keyboard::Key Keyboard::convertKey(sf::Keyboard::Key key)
    {
        Keyboard::Key convertedKey;
        switch (key) {
            case sf::Keyboard::Key::Unknown:
                convertedKey = Keyboard::Key::Unknown;
                break;
            case sf::Keyboard::Key::A:
                convertedKey = Keyboard::Key::A;
                break;
            case sf::Keyboard::Key::B:
                convertedKey = Keyboard::Key::B;
                break;
            case sf::Keyboard::Key::C:
                convertedKey = Keyboard::Key::C;
                break;
            case sf::Keyboard::Key::D:
                convertedKey = Keyboard::Key::D;
                break;
            case sf::Keyboard::Key::E:
                convertedKey = Keyboard::Key::E;
                break;
            case sf::Keyboard::Key::F:
                convertedKey = Keyboard::Key::F;
                break;
            case sf::Keyboard::Key::G:
                convertedKey = Keyboard::Key::G;
                break;
            case sf::Keyboard::Key::H:
                convertedKey = Keyboard::Key::H;
                break;
            case sf::Keyboard::Key::I:
                convertedKey = Keyboard::Key::I;
                break;
            case sf::Keyboard::Key::J:
                convertedKey = Keyboard::Key::J;
                break;
            case sf::Keyboard::Key::K:
                convertedKey = Keyboard::Key::K;
                break;
            case sf::Keyboard::Key::L:
                convertedKey = Keyboard::Key::L;
                break;
            case sf::Keyboard::Key::M:
                convertedKey = Keyboard::Key::M;
                break;
            case sf::Keyboard::Key::N:
                convertedKey = Keyboard::Key::N;
                break;
            case sf::Keyboard::Key::O:
                convertedKey = Keyboard::Key::O;
                break;
            case sf::Keyboard::Key::P:
                convertedKey = Keyboard::Key::P;
                break;
            case sf::Keyboard::Key::Q:
                convertedKey = Keyboard::Key::Q;
                break;
            case sf::Keyboard::Key::R:
                convertedKey = Keyboard::Key::R;
                break;
            case sf::Keyboard::Key::S:
                convertedKey = Keyboard::Key::S;
                break;
            case sf::Keyboard::Key::T:
                convertedKey = Keyboard::Key::T;
                break;
            case sf::Keyboard::Key::U:
                convertedKey = Keyboard::Key::U;
                break;
            case sf::Keyboard::Key::V:
                convertedKey = Keyboard::Key::V;
                break;
            case sf::Keyboard::Key::W:
                convertedKey = Keyboard::Key::W;
                break;
            case sf::Keyboard::Key::X:
                convertedKey = Keyboard::Key::X;
                break;
            case sf::Keyboard::Key::Y:
                convertedKey = Keyboard::Key::Y;
                break;
            case sf::Keyboard::Key::Z:
                convertedKey = Keyboard::Key::Z;
                break;
            case sf::Keyboard::Key::Num0:
                convertedKey = Keyboard::Key::Num0;
                break;
            case sf::Keyboard::Key::Num1:
                convertedKey = Keyboard::Key::Num1;
                break;
            case sf::Keyboard::Key::Num2:
                convertedKey = Keyboard::Key::Num2;
                break;
            case sf::Keyboard::Key::Num3:
                convertedKey = Keyboard::Key::Num3;
                break;
            case sf::Keyboard::Key::Num4:
                convertedKey = Keyboard::Key::Num4;
                break;
            case sf::Keyboard::Key::Num5:
                convertedKey = Keyboard::Key::Num5;
                break;
            case sf::Keyboard::Key::Num6:
                convertedKey = Keyboard::Key::Num6;
                break;
            case sf::Keyboard::Key::Num7:
                convertedKey = Keyboard::Key::Num7;
                break;
            case sf::Keyboard::Key::Num8:
                convertedKey = Keyboard::Key::Num8;
                break;
            case sf::Keyboard::Key::Num9:
                convertedKey = Keyboard::Key::Num9;
                break;
            case sf::Keyboard::Key::Escape:
                convertedKey = Keyboard::Key::Escape;
                break;
            case sf::Keyboard::Key::LControl:
                convertedKey = Keyboard::Key::LControl;
                break;
            case sf::Keyboard::Key::LShift:
                convertedKey = Keyboard::Key::LShift;
                break;
            case sf::Keyboard::Key::LAlt:
                convertedKey = Keyboard::Key::LAlt;
                break;
            case sf::Keyboard::Key::LSystem:
                convertedKey = Keyboard::Key::LSystem;
                break;
            case sf::Keyboard::Key::RControl:
                convertedKey = Keyboard::Key::RControl;
                break;
            case sf::Keyboard::Key::RShift:
                convertedKey = Keyboard::Key::RShift;
                break;
            case sf::Keyboard::Key::RAlt:
                convertedKey = Keyboard::Key::RAlt;
                break;
            case sf::Keyboard::Key::RSystem:
                convertedKey = Keyboard::Key::RSystem;
                break;
            case sf::Keyboard::Key::Menu:
                convertedKey = Keyboard::Key::Menu;
                break;
            case sf::Keyboard::Key::LBracket:
                convertedKey = Keyboard::Key::LBracket;
                break;
            case sf::Keyboard::Key::RBracket:
                convertedKey = Keyboard::Key::RBracket;
                break;
            case sf::Keyboard::Key::SemiColon:
                convertedKey = Keyboard::Key::SemiColon;
                break;
            case sf::Keyboard::Key::Comma:
                convertedKey = Keyboard::Key::Comma;
                break;
            case sf::Keyboard::Key::Period:
                convertedKey = Keyboard::Key::Period;
                break;
            case sf::Keyboard::Key::Quote:
                convertedKey = Keyboard::Key::Quote;
                break;
            case sf::Keyboard::Key::Slash:
                convertedKey = Keyboard::Key::Slash;
                break;
            case sf::Keyboard::Key::BackSlash:
                convertedKey = Keyboard::Key::BackSlash;
                break;
            case sf::Keyboard::Key::Tilde:
                convertedKey = Keyboard::Key::Tilde;
                break;
            case sf::Keyboard::Key::Equal:
                convertedKey = Keyboard::Key::Equal;
                break;
            case sf::Keyboard::Key::Dash:
                convertedKey = Keyboard::Key::Dash;
                break;
            case sf::Keyboard::Key::Space:
                convertedKey = Keyboard::Key::Space;
                break;
            case sf::Keyboard::Key::Return:
                convertedKey = Keyboard::Key::Return;
                break;
            case sf::Keyboard::Key::BackSpace:
                convertedKey = Keyboard::Key::BackSpace;
                break;
            case sf::Keyboard::Key::Tab:
                convertedKey = Keyboard::Key::Tab;
                break;
            case sf::Keyboard::Key::PageUp:
                convertedKey = Keyboard::Key::PageUp;
                break;
            case sf::Keyboard::Key::PageDown:
                convertedKey = Keyboard::Key::PageDown;
                break;
            case sf::Keyboard::Key::End:
                convertedKey = Keyboard::Key::End;
                break;
            case sf::Keyboard::Key::Home:
                convertedKey = Keyboard::Key::Home;
                break;
            case sf::Keyboard::Key::Insert:
                convertedKey = Keyboard::Key::Insert;
                break;
            case sf::Keyboard::Key::Delete:
                convertedKey = Keyboard::Key::Delete;
                break;
            case sf::Keyboard::Key::Add:
                convertedKey = Keyboard::Key::Add;
                break;
            case sf::Keyboard::Key::Subtract:
                convertedKey = Keyboard::Key::Subtract;
                break;
            case sf::Keyboard::Key::Multiply:
                convertedKey = Keyboard::Key::Multiply;
                break;
            case sf::Keyboard::Key::Divide:
                convertedKey = Keyboard::Key::Divide;
                break;
            case sf::Keyboard::Key::Left:
                convertedKey = Keyboard::Key::Left;
                break;
            case sf::Keyboard::Key::Right:
                convertedKey = Keyboard::Key::Right;
                break;
            case sf::Keyboard::Key::Up:
                convertedKey = Keyboard::Key::Up;
                break;
            case sf::Keyboard::Key::Down:
                convertedKey = Keyboard::Key::Down;
                break;
            case sf::Keyboard::Key::Numpad0:
                convertedKey = Keyboard::Key::Numpad0;
                break;
            case sf::Keyboard::Key::Numpad1:
                convertedKey = Keyboard::Key::Numpad1;
                break;
            case sf::Keyboard::Key::Numpad2:
                convertedKey = Keyboard::Key::Numpad2;
                break;
            case sf::Keyboard::Key::Numpad3:
                convertedKey = Keyboard::Key::Numpad3;
                break;
            case sf::Keyboard::Key::Numpad4:
                convertedKey = Keyboard::Key::Numpad4;
                break;
            case sf::Keyboard::Key::Numpad5:
                convertedKey = Keyboard::Key::Numpad5;
                break;
            case sf::Keyboard::Key::Numpad6:
                convertedKey = Keyboard::Key::Numpad6;
                break;
            case sf::Keyboard::Key::Numpad7:
                convertedKey = Keyboard::Key::Numpad7;
                break;
            case sf::Keyboard::Key::Numpad8:
                convertedKey = Keyboard::Key::Numpad8;
                break;
            case sf::Keyboard::Key::Numpad9:
                convertedKey = Keyboard::Key::Numpad9;
                break;
            case sf::Keyboard::Key::F1:
                convertedKey = Keyboard::Key::F1;
                break;
            case sf::Keyboard::Key::F2:
                convertedKey = Keyboard::Key::F2;
                break;
            case sf::Keyboard::Key::F3:
                convertedKey = Keyboard::Key::F3;
                break;
            case sf::Keyboard::Key::F4:
                convertedKey = Keyboard::Key::F4;
                break;
            case sf::Keyboard::Key::F5:
                convertedKey = Keyboard::Key::F5;
                break;
            case sf::Keyboard::Key::F6:
                convertedKey = Keyboard::Key::F6;
                break;
            case sf::Keyboard::Key::F7:
                convertedKey = Keyboard::Key::F7;
                break;
            case sf::Keyboard::Key::F8:
                convertedKey = Keyboard::Key::F8;
                break;
            case sf::Keyboard::Key::F9:
                convertedKey = Keyboard::Key::F9;
                break;
            case sf::Keyboard::Key::F10:
                convertedKey = Keyboard::Key::F10;
                break;
            case sf::Keyboard::Key::F11:
                convertedKey = Keyboard::Key::F11;
                break;
            case sf::Keyboard::Key::F12:
                convertedKey = Keyboard::Key::F12;
                break;
            case sf::Keyboard::Key::F13:
                convertedKey = Keyboard::Key::F13;
                break;
            case sf::Keyboard::Key::F14:
                convertedKey = Keyboard::Key::F14;
                break;
            case sf::Keyboard::Key::F15:
                convertedKey = Keyboard::Key::F15;
                break;
            case sf::Keyboard::Key::Pause:
                convertedKey = Keyboard::Key::Pause;
                break;
            default:
                convertedKey = Keyboard::Key::Unknown;
                break;
        }
        return convertedKey;
    }

    bool Keyboard::isKeyPressed(Keyboard::Key key)
    {
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
    }
}