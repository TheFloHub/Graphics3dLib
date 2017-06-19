#include "DeferredShadingPass.h"
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/MeshManager.h>
#include <Graphics3dLib/Assets/Mesh.h>
#include <Graphics3dLib/Components/Camera.h>
#include <Graphics3dLib/Components/Transform.h>
#include <Graphics3dLib/Components/Light.h>
#include <Graphics3dLib/Scene/SceneObject.h>
#include <Graphics3dLib/Rendering/FrameBufferObject.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

G3d::DeferredShadingPass::DeferredShadingPass(unsigned int width, unsigned int height) :
RenderPath(ShaderManager::GetInstance().get("DeferredLight"), nullptr),
mWidth(width),
mHeight(height),
mpInputDepth(),
mpInputNormals(),
mpInputAlbedo(),
mpInputShadowMap(),
mLightTypeLoc(0),
mLightPosDirLoc(0),
mLightColorLoc(0),
mLightIntensityLoc(0),
mNearPlaneLoc(0),
mFarPlaneLoc(0),
mInvProjLoc(0),
mCameraToLightTrafo(0)
{
	mpShader->use();
	glUniform1i(mpShader->getUniformLocation("gDepth"), 0);
    glUniform1i(mpShader->getUniformLocation("gNormal"), 1);
    glUniform1i(mpShader->getUniformLocation("gAlbedo"), 2);
	glUniform1i(mpShader->getUniformLocation("gShadowMap"), 3);

	mLightTypeLoc = mpShader->getUniformLocation("lightType");
	mLightPosDirLoc = mpShader->getUniformLocation("lightPosDir");
	mLightColorLoc = mpShader->getUniformLocation("lightColor");
	mLightIntensityLoc = mpShader->getUniformLocation("lightIntensity");
	mNearPlaneLoc = mpShader->getUniformLocation("nearPlane");
	mFarPlaneLoc = mpShader->getUniformLocation("farPlane");
	mInvProjLoc = mpShader->getUniformLocation("inverseProjection");
	mCameraToLightTrafo = mpShader->getUniformLocation("cameraToLightTrafo");
}

G3d::DeferredShadingPass::~DeferredShadingPass()
{
}

void G3d::DeferredShadingPass::render(Camera const* pCamera, Light const* pLight)
{
	//glEnable(GL_FRAMEBUFFER_SRGB);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mWidth, mHeight);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	// TODO: make light material, split light in 3 shaders without if statements
	glActiveTexture(GL_TEXTURE0);
	mpInputDepth->use();
	glActiveTexture(GL_TEXTURE1);
	mpInputNormals->use();
	glActiveTexture(GL_TEXTURE2);
	mpInputAlbedo->use();
	glActiveTexture(GL_TEXTURE3);
	mpInputShadowMap->use();

	mpShader->use();
	glm::mat4 viewMatrix = m180Rotation*pCamera->getSceneObject()->getTransform()->getWorldToLocalMatrix();
	glm::mat3 viewRotationMatrix = glm::mat3(m180Rotation)*pCamera->getSceneObject()->getTransform()->getWorldToLocalRotationMatrix();

	glm::mat4 cameraToLightTrafo = 
		glm::ortho(-510.0f, 510.0f, -515.0f, 515.0f, -515.0f, 515.0f) *
		m180Rotation * pLight->getSceneObject()->getTransform()->getWorldToLocalMatrix() * pCamera->getSceneObject()->getTransform()->getLocalToWorldMatrix()*m180Rotation;

	glUniform1f(mNearPlaneLoc, pCamera->getNearPlane());
	glUniform1f(mFarPlaneLoc, pCamera->getFarPlane());
	glUniformMatrix4fv(mInvProjLoc, 1, GL_FALSE, glm::value_ptr(pCamera->getInverseProjectionMatrix()));
	glUniformMatrix4fv(mCameraToLightTrafo, 1, GL_FALSE, glm::value_ptr(cameraToLightTrafo));

	glUniform1i(mLightTypeLoc, static_cast<int>(pLight->getType()));
	glUniform3fv(mLightColorLoc, 1, glm::value_ptr(pLight->getColor()));
	glUniform1f(mLightIntensityLoc, pLight->getIntensity());

	if (pLight->isDirectionalLight())
	{
		glm::mat3 modelViewRotationMatrix = viewRotationMatrix * pLight->getSceneObject()->getTransform()->getLocalToWorldRotationMatrix();
		glUniform3f(mLightPosDirLoc, modelViewRotationMatrix[2][0], modelViewRotationMatrix[2][1], modelViewRotationMatrix[2][2]);
	}
	else
	{
		glm::mat4 modelViewMatrix = viewMatrix * pLight->getSceneObject()->getTransform()->getLocalToWorldMatrix();
		glUniform3f(mLightPosDirLoc, modelViewMatrix[3][0], modelViewMatrix[3][1], modelViewMatrix[3][2]);
	}
	MeshManager::getInstance().getScreenAlignedQuad()->render();
	
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	//glDisable(GL_FRAMEBUFFER_SRGB);
}

void G3d::DeferredShadingPass::setInputDepth(TextureCPtr pTexture)
{
	mpInputDepth = pTexture;
}

void G3d::DeferredShadingPass::setInputNormals(TextureCPtr pTexture)
{
	mpInputNormals = pTexture;
}

void G3d::DeferredShadingPass::setInputAlbedo(TextureCPtr pTexture)
{
	mpInputAlbedo = pTexture;
}

void G3d::DeferredShadingPass::setInputShadowMap(TextureCPtr pTexture)
{
	mpInputShadowMap = pTexture;
}
