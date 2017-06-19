#include "TextureManager.h"
#include "Texture.h"
#include <glm/gtc/noise.hpp>
#include <random>

G3d::TextureManager& G3d::TextureManager::GetInstance()
{
	static TextureManager instance;
	return instance;
}

G3d::TextureManager::TextureManager() :
mTextureMap()
{
}

G3d::TextureManager::~TextureManager()
{
}

G3d::TexturePtr G3d::TextureManager::load(std::string const& textureName, std::string const& fileName)
{
	TexturePtr pTexture = get(textureName);
	if (pTexture)
	{
		return pTexture;
	}
	return (mTextureMap.insert(std::make_pair(textureName, TexturePtr(new Texture(fileName))))).first->second;
}

G3d::TexturePtr G3d::TextureManager::get(std::string const& textureName) const
{
	std::map<std::string, TexturePtr>::const_iterator iter = mTextureMap.find(textureName);
	if (iter != mTextureMap.end())
	{
		return iter->second;
	}
	return TexturePtr();
}

G3d::TexturePtr G3d::TextureManager::getRGB255() const
{
	return get("RGB255");
}

G3d::TexturePtr G3d::TextureManager::getRGBA255() const
{
	return get("RGBA255");
}

G3d::TexturePtr G3d::TextureManager::getDefaultHeightMap() const
{
	return get("DefaultHeightMap");
}

G3d::TexturePtr G3d::TextureManager::getTerrainNoise() const
{
	return get("TerrainNoise");
}

void G3d::TextureManager::initStandardTextures()
{
	std::vector<unsigned char> data(4*4*3, 255);
	mTextureMap.insert(
		std::make_pair(
		"RGB255", 
		TexturePtr( new Texture(4, 4, 3, data) )));

	data = std::vector<unsigned char>(4*4*4, 255);
	mTextureMap.insert(
		std::make_pair(
		"RGBA255", 
		TexturePtr( new Texture(4, 4, 4, data) )));

	createHeightMap();
	createTerrainNoise();
}

void G3d::TextureManager::createHeightMap()
{
	std::vector<float> data;
	data.reserve(512*512);

	for (float y = 0; y < 512; ++y)
	{
		for (float x = 0; x < 512; ++x)
		{
			data.push_back(0.5f + 0.5f*glm::simplex(glm::vec2(x/100.0f, y/100.0f)));	
		}
	}

	//for (float y = 0; y < 512; ++y)
	//{
	//	for (float x = 0; x < 512; ++x)
	//	{
	//		float xt = x - 256.0f;
	//		float yt = y - 256.0f;
	//		data.push_back(std::max(std::max(1.0 - 0.01*xt*xt - 0.01*yt*yt, 1.0 - 0.01*x*x - 0.01*yt*yt), 0.0));	
	//	}
	//}

	mTextureMap.insert(
		std::make_pair(
		"DefaultHeightMap", 
		TexturePtr( new Texture(512, 512, 1, data) )));
}

void G3d::TextureManager::createTerrainNoise()
{
	unsigned int size = 512;
	std::vector<float> data;
	data.reserve(size*size);

	//for (float y = 0; y < 1024; ++y)
	//{
	//	for (float x = 0; x < 1024; ++x)
	//	{
	//		data.push_back(0.5f + 0.5f*glm::simplex(glm::vec2(x/10.0f, y/10.0f)));	
	//	}
	//}

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	for (float y = 0; y < (float)size; ++y)
	{
		for (float x = 0; x < (float)size; ++x)
		{
			data.push_back(distribution(generator));	
		}
	}

	mTextureMap.insert(
		std::make_pair(
		"TerrainNoise", 
		TexturePtr( new Texture(size, size, 1, data) )));
}
