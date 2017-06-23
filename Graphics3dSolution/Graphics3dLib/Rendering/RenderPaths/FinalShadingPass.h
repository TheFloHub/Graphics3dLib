/**
* @author Florian Feuerstein
* @date 09.03.2017
*
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include <Graphics3dLib/Rendering/RenderPath.h>
#include <glew.h>

namespace G3d
{

	class FinalShadingPass : public RenderPath
	{
	public:

		FinalShadingPass(unsigned int width, unsigned int height);

		virtual ~FinalShadingPass();

		void render();

		void setInput(TextureCPtr pTexture);

	protected:

		FinalShadingPass(FinalShadingPass const&) = delete;

		FinalShadingPass& operator=(FinalShadingPass const&) = delete;

		unsigned int mWidth;

		unsigned int mHeight;

		TextureCPtr mpInput;
	};

}
