/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-theo.liennard
** File description:
** Game Engine
*/

#include "JsonManager.hpp"

void JsonManager::jsonLoadFile(const std::string &path)
{
    if (path.find(".json") == std::string::npos)
        throw gameEngine::json::InvalidJsonFile("Invalid file extension");

    std::ifstream file(path);
    if (!file || !file.good())
        throw gameEngine::json::InvalidJsonFile("File does not exist");
    if (!file.is_open())
        throw gameEngine::json::InvalidJsonFile("File could not be opened");

    if (_jsonFiles.find(path) != _jsonFiles.end())
        _jsonFiles[path].clear();

    file >> _jsonFiles[path];
    file.close();
}

nlohmann::json &JsonManager::jsonGetFile(const std::string &path)
{
    if (_jsonFiles.find(path) == _jsonFiles.end())
        throw gameEngine::json::JsonFileNotFound("The json file " + path + " was not found");
    return _jsonFiles[path];
}
