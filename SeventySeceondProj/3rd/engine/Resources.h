#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include "raylib/raylib.h"
#include "raylib/raymath.h"

class Resources
{
private:
	std::unordered_map<std::string, Model> models;
public:
	Resources();
	virtual ~Resources();

	void loadPrimitives();

	bool hasModel(std::string name);
	Model* getModel(std::string name);
	void loadModel(std::string path, std::string name);
};

