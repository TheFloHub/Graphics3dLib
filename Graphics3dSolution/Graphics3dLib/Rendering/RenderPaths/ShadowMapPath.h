/**
* @author Florian Feuerstein 
* @date 09.03.2017
*
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <Graphics3dLib/rendering/RenderPath.h>
#include <glew.h>

namespace G3d
{

	class Light;
	class SceneObject;

	class ShadowMapPass : public RenderPath
	{
	public:

		ShadowMapPass(unsigned int width, unsigned int height);

		virtual ~ShadowMapPass();
		
		void render(Light const* pLight, std::vector<SceneObject const*> sceneObjects);

		TexturePtr getDepthBuffer();
		
	protected:
		
		ShadowMapPass(ShadowMapPass const&) = delete;

		ShadowMapPass& operator=(ShadowMapPass const&) = delete;

	};

}
