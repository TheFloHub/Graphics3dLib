/**
* @author Florian Feuerstein  
* @date 03.08.2016
*
* The shader manager contains all loaded shaders and provides access to them.
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <string>
#include <map>

namespace G3d
{

	class ShaderManager
	{
	public:

		static ShaderManager& GetInstance();

		~ShaderManager();

		ShaderPtr loadFromFile(
			std::string const& shaderName, 
			std::string const& vertexShaderFileName,
			std::string const& fragmentShaderFileName);

		ShaderPtr get(std::string const& shaderName) const;

		ShaderPtr getDiffuse() const;

		ShaderPtr getSpecular() const;

		ShaderPtr getTerrain() const;

		ShaderPtr getTerrainDepth() const;

		ShaderPtr getDefaultDepth() const;

		ShaderPtr getTerrainShadowMap() const;

		void initStandardShader();

	private:
		
		ShaderManager();

		ShaderManager(ShaderManager const&) = delete;

		ShaderManager& operator=(ShaderManager const&) = delete;

		std::map<std::string, ShaderPtr> mShaderMap;

	};

}