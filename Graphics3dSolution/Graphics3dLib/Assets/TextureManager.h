/**
* @author Florian Feuerstein  
* @date 03.08.2016
*
* The texture manager contains all loaded textures and provides access to them.
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <string>
#include <map>

namespace G3d
{

	class TextureManager
	{
	public:

		static TextureManager& getInstance();

		~TextureManager();

		TexturePtr load(std::string const& textureName, std::string const& fileName);

		TexturePtr get(std::string const& textureName) const;

		TexturePtr getRGB255() const;

		TexturePtr getRGBA255() const;


		// TODO: should only exist in TerrainClass
		TexturePtr getDefaultHeightMap() const;

		TexturePtr getTerrainNoise() const;

		void initStandardTextures();

	private:
		
		TextureManager();
		TextureManager(TextureManager const&) = delete;
		TextureManager& operator=(TextureManager const&) = delete;

		void createHeightMap();

		void createTerrainNoise();

		std::map<std::string, TexturePtr> mTextureMap;

	};

}
