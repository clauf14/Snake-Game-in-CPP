#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace std;
using namespace sf;

namespace Engine
{
	class AssetMan
	{
	private:

		map<int, unique_ptr<Texture>> m_textures;
		map<int, unique_ptr<Font>> m_fonts;

	public:
		AssetMan();
		~AssetMan();

		void AddTexture(int id, const string &filePath, bool wantRepeated = false);	//Obtine Textura
		void AddFont(int id, const string& filePath);	//Obtine Fontul

		const Texture &GetTexture(int id) const;	//Returneaza Textura prin constante
		const Font &GetFont(int id) const;	//Returneaza Fontul prin constante
	};
}