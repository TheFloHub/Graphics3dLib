/**
* @author Florian Feuerstein 
* @date 01.08.2016
*
* The scene renderer is responsible for rendering the whole scene
* with all lights, cameras and objects.
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <Graphics3dLib/Rendering/RenderPaths/GraphicsBufferPath.h>
#include <Graphics3dLib/Rendering/RenderPaths/ShadowMapPath.h>
#include <Graphics3dLib/Rendering/RenderPaths/DeferredShadingPass.h>
#include <Graphics3dLib/Rendering/RenderPaths/FinalShadingPass.h>
#include "glew.h"
#include <glm/glm.hpp>
#include <vector>

namespace G3d
{

	// forward declarations
	class SceneObject;
	class Light;
	class Camera;

	class SceneRenderer
	{
	public:

		SceneRenderer(unsigned int width, unsigned int height);

		~SceneRenderer();

		void render(SceneObject const* pRoot);

		void setImageSize(unsigned int width, unsigned int height);

	private:

		SceneRenderer(SceneRenderer const&) = delete;

		SceneRenderer& operator=(SceneRenderer const&) = delete;
		
		void traverseGraph(
			SceneObject const* pCurrentNode,
			std::vector<SceneObject const*>& sceneObjects, 
			std::vector<Light const*>& lights, 
			std::vector<Camera const*>& cameras) const;

		unsigned int mWidth;

		unsigned int mHeight;
		
		// G Buffer Path
		GraphicsBufferPath mGraphicsBufferPath;

		// Shadow Map Path
		ShadowMapPass mShadowMapPath;
		
		// Deferred Shading Pass
		DeferredShadingPass mDeferredShadingPath;

		// Final Shading Pass (ambient / HDR / Gamma correction)
		FinalShadingPass mFinalShadingPass;

	};

}
