#include "RenderPath.h"
#include <Graphics3dLib/GlInfo.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Rendering/FrameBufferObject.h>


G3d::RenderPath::RenderPath(ShaderCPtr pShader, FrameBufferObject* pFrameBuffer) :
m180Rotation(		
	-1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f),
mpShader(pShader),
mpFrameBuffer(pFrameBuffer)
{
	
}

G3d::RenderPath::~RenderPath()
{

}

