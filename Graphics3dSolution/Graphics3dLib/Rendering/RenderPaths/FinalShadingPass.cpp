#include "FinalShadingPass.h"
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/MeshManager.h>
#include <Graphics3dLib/Assets/Mesh.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

G3d::FinalShadingPass::FinalShadingPass(unsigned int width, unsigned int height) :
RenderPath(ShaderManager::getInstance().get("FinalShading"), nullptr),
mWidth(width),
mHeight(height),
mpInput()
{
	mpShader->use();
	glUniform1i(mpShader->getUniformLocation("inputTexture"), 0);
}

G3d::FinalShadingPass::~FinalShadingPass()
{
}

void G3d::FinalShadingPass::render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mWidth, mHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glActiveTexture(GL_TEXTURE0);
	mpInput->use();

	mpShader->use();
	MeshManager::getInstance().getScreenAlignedQuad()->render();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}

void G3d::FinalShadingPass::setInput(TextureCPtr pTexture)
{
	mpInput = pTexture;
}
