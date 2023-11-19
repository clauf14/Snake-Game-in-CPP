#include "AssetMan.hpp"

Engine::AssetMan::AssetMan()
{
}

Engine::AssetMan::~AssetMan()
{
}

void Engine::AssetMan::addTexture(int id, const std::string& filePath, bool wantRepeated)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(filePath))
    {
        texture->setRepeated(wantRepeated);
        textures[id] = std::move(texture);
    }
}

void Engine::AssetMan::addFont(int id, const std::string& filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        fonts[id] = std::move(font);
    }
}

const sf::Texture& Engine::AssetMan::getTexture(int id) const
{
    return *(textures.at(id).get());
}

const sf::Font& Engine::AssetMan::getFont(int id) const
{
    return *(fonts.at(id).get());
}