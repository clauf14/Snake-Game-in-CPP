#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace std;

namespace Engine
{
	class AssetMan
	{
	private:

		map<int, unique_ptr<sf::Texture>> textures;
		map<int, unique_ptr<sf::Font>> fonts;

	public:
		AssetMan();
		~AssetMan();

		void addTexture(int id, const string& filePath, bool whenRepeated = false);	//Obtine Textura
		void addFont(int id, const string& filePath);	//Obtine Fontul

		const sf::Texture &getTexture(int id) const;	//Returneaza Textura prin constante
		const sf::Font &getFont(int id) const;	//Returneaza Fontul prin constante
	};
}