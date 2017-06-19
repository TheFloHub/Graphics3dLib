#include "TerrainDepthMaterial.h"
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/TextureManager.h>
#include "glew.h"
#include <glm/gtc/type_ptr.hpp>

G3d::TerrainDepthMaterial::TerrainDepthMaterial() :
	Material(ShaderManager::GetInstance().getTerrainDepth()),
	mpHeightMap(TextureManager::GetInstance().getRGB255()), // TODO: Luminence0 ?
	mMvpMatrixLoc(0)
{
	mpShader->use();
	GLuint program = mpShader->getHandle();
	glUniform1i(glGetUniformLocation(program, "heightMap"), 0);
	mMvpMatrixLoc = glGetUniformLocation(program, "modelViewProjectionMatrix");
}

G3d::TerrainDepthMaterial::~TerrainDepthMaterial()
{

}

void G3d::TerrainDepthMaterial::use() const
{
	Material::use(); // enables shader program
	glUniformMatrix4fv(mMvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(Shader::getGlobalMat4("modelViewProjectionMatrix")));
	glActiveTexture(GL_TEXTURE0);
	mpHeightMap->use();
}

void G3d::TerrainDepthMaterial::setHeightMap(TextureCPtr pHeightMap)
{
	mpHeightMap = pHeightMap;
}

