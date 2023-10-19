//#include "AssetMan.hpp"
//
//Engine::AssetMan::AssetMan()
//{
//}
//
//Engine::AssetMan::~AssetMan()
//{
//}
//
//void Engine::AssetMan::AddTexture(int id, const string& filePath, bool wantRepeated = false)
//{
//	auto texture = make_unique<Texture>();
//
//	if (texture->loadFromFile(filePath))
//	{
//		texture->setRepeated(wantRepeated);
//		m_textures[id] = move(texture);
//	}
//}
//void Engine::AssetMan::AddFont(int id, const string& filePath)
//{
//	auto font = make_unique<Font>();
//
//	if (font->loadFromFile(filePath))
//	{
//		m_fonts[id] = move(font);
//	}
//}
//
//const Texture& Engine::AssetMan::GetTexture(int id) const
//{
//	return *(m_textures.at(id).get());
//}
//const Font& Engine::AssetMan::GetFont(int id) const
//{
//	return *(m_fonts.at(id).get()); 
//}