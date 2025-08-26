/*
** EPITECH PROJECT, 2023
** vox
** File description:
** cpp
*/

#include "textBox.hpp"

Entity TextBox::init(float posx, float posy, sf::Font &font, float scalex, float scaley , int offsetX, int offsetY)
{
    Entity box = _ge.ecsSpawnEntity();
    component::Drawable drawable = { true };
    _ge.ecsAddComponent(box, drawable);
    component::Transform pos = { posx, posy, 0, 0, 0, 0, scalex, scaley, 1 };
    _ge.ecsAddComponent(box, pos);
    component::Texture texture("Ui/Table.png");
    _ge.ecsAddComponent(box, texture);
    _rect = sf::IntRect(0, 0, 361, 101);
    component::Sprite sprite(sf::IntRect(0, 0, 361, 101));
    _ge.ecsAddComponent(box, sprite);

    _text.setFont(font);
    _text.setCharacterSize(TEXTBOX_FONT_SIZE);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(posx + offsetX , posy + offsetY);
    _text.setString(_inputText);
    _posX = posx;
    _posY = posy;
    _entity = box;
    return box;
}

void TextBox::changeTexture(std::string textureName)
{
    Entity box = _ge.ecsEntityFromIndex(_entity);
    auto &texture = _ge.ecsGetComponents<component::Texture>()[box];
    auto &sprite = _ge.ecsGetComponents<component::Sprite>()[box];
    auto &tex = _ge.assetGetAsset<component::Texture>(textureName);
    sprite._sprite.setTexture(tex._texture);
    texture._texture = tex._texture;
}

void TextBox::update(gameEngine::Event &event)
{
    if (event.text.unicode != 9 && event.text.unicode != 0)  {
        if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13) {
            if (_inputText.size() < _maxSize) {
                _inputText += static_cast<char>(event.text.unicode);
                _text.setString(_inputText);
            }
        } else if (event.text.unicode == 8) {
            if (_inputText.size() > 0) {
                _inputText.pop_back();
                _text.setString(_inputText);
            }
        }
    }
}

sf::Text &TextBox::getText()
{
    return _text;
}
