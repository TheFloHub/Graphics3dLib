#include "ShaderManager.h"
#include "Shader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

// include shader source files here
//#include "resources/shader/DeferredLight_vert.h"
//#include "resources/shader/DeferredLight_frag.h"
//#include "resources/shader/Diffuse_vert.h"
//#include "resources/shader/Diffuse_frag.h"
//#include "resources/shader/Specular_vert.h"
//#include "resources/shader/Specular_frag.h"
//#include "resources/shader/Terrain_vert.h"
//#include "resources/shader/Terrain_frag.h"

G3d::ShaderManager& G3d::ShaderManager::getInstance()
{
	static ShaderManager instance;
	return instance;
}

G3d::ShaderManager::ShaderManager() :
mShaderMap()
{
}

G3d::ShaderManager::~ShaderManager()
{
}

G3d::ShaderPtr G3d::ShaderManager::loadFromFile(
	std::string const& shaderName, 
	std::string const& vertexShaderFileName,
	std::string const& fragmentShaderFileName)
{
	ShaderPtr pShader = get(shaderName);
	if (pShader)
	{
		return pShader;
	}

	std::ifstream vertexShaderFile(vertexShaderFileName);
	std::string vertexShader((std::istreambuf_iterator<char>(vertexShaderFile)), std::istreambuf_iterator<char>());

	std::ifstream fragmentShaderFile(fragmentShaderFileName);
	std::string fragmentShader((std::istreambuf_iterator<char>(fragmentShaderFile)), std::istreambuf_iterator<char>());

	if (vertexShader.empty() || fragmentShader.empty())
	{
		return pShader;
	}

	return (mShaderMap.insert(std::make_pair(shaderName, ShaderPtr(new Shader(vertexShader, fragmentShader))))).first->second;
}

G3d::ShaderPtr G3d::ShaderManager::get(std::string const& shaderName) const
{
	std::map<std::string, ShaderPtr>::const_iterator iter = mShaderMap.find(shaderName);
	if (iter != mShaderMap.end())
	{
		return iter->second;
	}
	return ShaderPtr();
}

G3d::ShaderPtr G3d::ShaderManager::getPBRMaterial() const
{
	return get("PBRMaterial"); 
}

G3d::ShaderPtr G3d::ShaderManager::getDiffuse() const
{
	return get("Diffuse");
}

G3d::ShaderPtr G3d::ShaderManager::getSpecular() const
{
	return get("Specular");
}

G3d::ShaderPtr G3d::ShaderManager::getTerrain() const
{
	return get("Terrain");
}

G3d::ShaderPtr G3d::ShaderManager::getTerrainDepth() const
{
	return get("TerrainDepth");
}

G3d::ShaderPtr G3d::ShaderManager::getDefaultDepth() const
{
	return get("DefaultDepth");
}

G3d::ShaderPtr G3d::ShaderManager::getTerrainShadowMap() const
{
	return get("TerrainShadowMap");
}

bool G3d::ShaderManager::initStandardShader()
{
	std::string baseHome("D:\\Eigene Dokumente\\Visual Studio 2015\\Projects\\Graphics3dLibSolution\\Graphics3dLib\\resources\\shader\\");
	std::string baseWork("D:\\GitHubProjects\\Graphics3dLib\\Graphics3dSolution\\Graphics3dLib\\Resources\\Shader\\");

	std::string base = baseWork;
	
	// TODO: make Visual Studio resource files or so
	if (!loadFromFile("Diffuse", base + "Diffuse.vert", base + "Diffuse.frag"))
		return false;

	if (!loadFromFile("Specular", base + "Specular.vert", base + "Specular.frag"))
		return false;

	if (!loadFromFile("DeferredLight", base + "DeferredLight.vert", base + "DeferredLight.frag"))
		return false;

	if (!loadFromFile("DefaultDepth", base + "DefaultDepth.vert", base + "DefaultDepth.frag"))
		return false;

	if (!loadFromFile("PBRMaterial", base + "PBRMaterial.vert", base + "PBRMaterial.frag"))
		return false;

	if (!loadFromFile("FinalShading", base + "FinalShading.vert", base + "FinalShading.frag"))
		return false;

	//mShaderMap.insert(std::make_pair("DeferredLight", ShaderPtr(new Shader(DeferredLight_vert, DeferredLight_frag))));
	//mShaderMap.insert(std::make_pair("Diffuse", ShaderPtr(new Shader(Diffuse_vert, Diffuse_frag))));
	//mShaderMap.insert(std::make_pair("Specular", ShaderPtr(new Shader(Specular_vert, Specular_frag))));
	//mShaderMap.insert(std::make_pair("Terrain", ShaderPtr(new Shader(Terrain_vert, Terrain_frag))));
	return true;
}
