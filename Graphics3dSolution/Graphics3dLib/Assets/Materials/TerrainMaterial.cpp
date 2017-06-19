#include "TerrainMaterial.h"
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/TextureManager.h>
#include "glew.h"
#include <glm/gtc/type_ptr.hpp>

G3d::TerrainMaterial::TerrainMaterial() :
	Material(ShaderManager::GetInstance().getTerrain()),
	mpHeightMap(TextureManager::GetInstance().getRGB255()), // TODO: Luminence0 ?
	mpNoise(TextureManager::GetInstance().getTerrainNoise()),
	mMvpMatrixLoc(0),
	mNormalMatrixLoc(0)
{
	mpNoise->lowQuality();
	mpShader->use();
	GLuint program = mpShader->getHandle();
	glUniform1i(glGetUniformLocation(program, "heightMap"), 0);
	glUniform1i(glGetUniformLocation(program, "noiseSampler"), 1);
	mMvpMatrixLoc = glGetUniformLocation(program, "modelViewProjectionMatrix");
	mNormalMatrixLoc = glGetUniformLocation(program, "normalMatrix");
}

G3d::TerrainMaterial::~TerrainMaterial()
{

}

void G3d::TerrainMaterial::use() const
{
	Material::use(); // enables shader program
	glUniformMatrix4fv(mMvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(Shader::getGlobalMat4("modelViewProjectionMatrix")));
	glUniformMatrix3fv(mNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(Shader::getGlobalMat3("normalMatrix")));
	glActiveTexture(GL_TEXTURE0);
	mpHeightMap->use();
	glActiveTexture(GL_TEXTURE1);
	mpNoise->use();
}

void G3d::TerrainMaterial::setHeightMap(TextureCPtr pHeightMap)
{
	mpHeightMap = pHeightMap;
}

