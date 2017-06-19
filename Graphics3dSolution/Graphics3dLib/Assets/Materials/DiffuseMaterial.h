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

	class DiffuseMaterial : public Material
	{
	public:

		DiffuseMaterial();

		virtual ~DiffuseMaterial();

		void use() const override;

		void setDiffuseColor(float red, float green, float blue);

		void setTiling(float x, float y);

		void setTexture(TextureCPtr pTexture);

	protected:

		float mRed;

		float mGreen;

		float mBlue;

		float mTilingX;

		float mTilingY;

		TextureCPtr mpTexture;

		GLuint mMvpMatrixLoc;

		GLuint mNormalMatrixLoc;

		GLuint mDiffuseColorLoc;

		GLuint mTilingLoc;

	private:
		
		DiffuseMaterial(Material const&) = delete;

		DiffuseMaterial& operator=(DiffuseMaterial const&) = delete;

	};
	
	typedef std::shared_ptr<DiffuseMaterial> DiffuseMaterialPtr;
	typedef std::shared_ptr<DiffuseMaterial const> DiffuseMaterialCPtr;
}

