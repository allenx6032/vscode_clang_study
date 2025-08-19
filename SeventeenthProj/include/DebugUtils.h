#pragma once

#include "AnimationData.h"

#include <SFML/SFML_Graphics.hpp>

// Used to debug the animation data
// It's easier to notice if the numbers in the data are incorrect this way
void displayAll(sf::RenderTarget& target, const AnimationData& data);
