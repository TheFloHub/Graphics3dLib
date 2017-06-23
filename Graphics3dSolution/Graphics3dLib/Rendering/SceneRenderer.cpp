#include "SceneRenderer.h"
#include "Graphics3dLib/GlInfo.h"
#include "Graphics3dLib/Scene/SceneObject.h"
#include "Graphics3dLib/Assets/Shader.h"
#include "Graphics3dLib/Assets/ShaderManager.h"
#include "Graphics3dLib/Assets/MeshManager.h"
#include "Graphics3dLib/Assets/Mesh.h"
#include "Graphics3dLib/Assets/Texture.h"
#include "Graphics3dLib/Components/Transform.h"
#include "Graphics3dLib/Components/Camera.h"
#include "Graphics3dLib/Components/Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace G3d;

G3d::SceneRenderer::SceneRenderer(unsigned int width, unsigned int height) : 
mWidth(width),
mHeight(height),
mGraphicsBufferPath(width, height),
mShadowMapPath(1024, 1024),
mDeferredShadingPath(width, height),
mFinalShadingPass(width, height)
{
	mDeferredShadingPath.setInputDepth(mGraphicsBufferPath.getDepthBuffer());
	mDeferredShadingPath.setInputNormals(mGraphicsBufferPath.getNormalBuffer());
	mDeferredShadingPath.setInputAlbedo(mGraphicsBufferPath.getAlbedoBuffer());
	mDeferredShadingPath.setInputShadowMap(mShadowMapPath.getDepthBuffer());
	mFinalShadingPass.setInput(mDeferredShadingPath.getOutputBuffer());
}

G3d::SceneRenderer::~SceneRenderer()
{

}

void G3d::SceneRenderer::setImageSize(unsigned int width, unsigned int height)
{
	if (mWidth!=width || mHeight!=height)
	{
		mWidth = width;
		mHeight = height;
	}
}

void G3d::SceneRenderer::render(SceneObject const* pRoot)
{
	std::vector<SceneObject const*> sceneObjects;
	std::vector<Light const*> lights;
	std::vector<Camera const*> cameras;
	traverseGraph(pRoot, sceneObjects, lights, cameras);
	if (cameras.empty())
	{
		return;
	}
	Camera const* pCamera = cameras[0];

	// 1. Geometry Pass: render scene's geometry/color data into gbuffer
	mGraphicsBufferPath.render(pCamera, sceneObjects);

	// 2. Lighting Pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
	//glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mDeferredShadingPath.clear();
	for (std::vector<Light const*>::const_iterator lightIter=lights.cbegin();
		lightIter!=lights.cend(); ++lightIter)
	{
		mShadowMapPath.render(*lightIter, sceneObjects);
		mDeferredShadingPath.render(pCamera, *lightIter);
	}

	mFinalShadingPass.render();
}

void G3d::SceneRenderer::traverseGraph(
	SceneObject const* pCurrentNode,
	std::vector<SceneObject const*>& sceneObjects, 
	std::vector<Light const*>& lights, 
	std::vector<Camera const*>& cameras) const
{
	if (pCurrentNode->isEnabled())
	{
		sceneObjects.push_back(pCurrentNode);
		Light const* pLight = pCurrentNode->getComponent<Light>();
		if (pLight != nullptr && pLight->isEnabled())
		{
			lights.push_back(pLight);
		}
		Camera const* pCamera = pCurrentNode->getComponent<Camera>(); 
		if (pCamera != nullptr && pCamera->isEnabled())
		{
			cameras.push_back(pCamera);
		}
		for (size_t childIndex = 0; childIndex < pCurrentNode->getNumberOfChildren(); ++childIndex)
		{
			traverseGraph(
				pCurrentNode->getChild(childIndex),
				sceneObjects, lights, cameras);
		}
	}
}
