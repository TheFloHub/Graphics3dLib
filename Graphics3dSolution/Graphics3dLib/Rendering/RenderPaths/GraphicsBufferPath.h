/**
* @author Florian Feuerstein 
* @date 09.03.2017
*
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <Graphics3dLib/Rendering/RenderPath.h>
#include <vector>

namespace G3d
{

	class Camera;
	class SceneObject;

	class GraphicsBufferPath : public RenderPath
	{
	public:

		GraphicsBufferPath(unsigned int width, unsigned int height);

		virtual ~GraphicsBufferPath();
		
		void render(Camera const* pCamera, std::vector<SceneObject const*> sceneObjects);

		TexturePtr getDepthBuffer();

		TexturePtr getNormalBuffer();

		TexturePtr getAlbedoBuffer();
		
	protected:
		
		GraphicsBufferPath(GraphicsBufferPath const&) = delete;

		GraphicsBufferPath& operator=(GraphicsBufferPath const&) = delete;

	};

}
