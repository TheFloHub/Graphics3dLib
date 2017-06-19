/**
* @author Florian Feuerstein 
* @date 09.03.2017
*
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <Graphics3dLib/Rendering/FrameBufferObject.h>
#include <Graphics3dLib/Assets/Shader.h>
#include <memory>
#include <glm/glm.hpp>

namespace G3d
{
	// TODO: do we really need this class?
	class RenderPath
	{
	public:

		RenderPath(ShaderCPtr pShader, FrameBufferObject* pFrameBuffer);

		virtual ~RenderPath();
		
	protected:
		
		RenderPath(RenderPath const&) = delete;

		RenderPath& operator=(RenderPath const&) = delete;

		glm::mat4 m180Rotation;
				
		ShaderCPtr mpShader; 

		std::unique_ptr<FrameBufferObject> mpFrameBuffer;

	};

}
