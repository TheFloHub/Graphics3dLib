#include "DefaultDepthMaterial.h"
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <glm/gtc/type_ptr.hpp>

G3d::DefaultDepthMaterial::DefaultDepthMaterial() :
	Material(ShaderManager::GetInstance().getDefaultDepth()),
	mMvpMatrixLoc(0)
{
	mpShader->use();
	mMvpMatrixLoc = mpShader->getUniformLocation("modelViewProjectionMatrix");
}

G3d::DefaultDepthMaterial::~DefaultDepthMaterial()
{

}

void G3d::DefaultDepthMaterial::use() const
{
	Material::use(); // enables shader program
	glUniformMatrix4fv(mMvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(Shader::getGlobalMat4("modelViewProjectionMatrix")));
}

