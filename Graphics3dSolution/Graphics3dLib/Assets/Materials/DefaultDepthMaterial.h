/**
* @author Florian Feuerstein
* @date 01.08.2016
*
*
*/

#pragma once

#include <Graphics3dLib/Assets/Material.h>

namespace G3d
{

	class DefaultDepthMaterial : public Material
	{
	public:

		DefaultDepthMaterial();

		virtual ~DefaultDepthMaterial();

		void use() const override;

	protected:

		GLuint mMvpMatrixLoc;

	private:

		DefaultDepthMaterial(Material const&) = delete;

		DefaultDepthMaterial& operator=(DefaultDepthMaterial const&) = delete;

	};

	typedef std::shared_ptr<DefaultDepthMaterial> DefaultDepthMaterialPtr;
	typedef std::shared_ptr<DefaultDepthMaterial const> DefaultDepthMaterialCPtr;
}

