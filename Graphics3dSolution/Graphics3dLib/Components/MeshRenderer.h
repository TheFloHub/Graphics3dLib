/**
* @author Florian Feuerstein 
* @date 01.08.2016
*
* A mesh renderer component renders a mesh with a certain material.
*/

#pragma once

#include <Graphics3dLib/SharedPtrTypes.h>
#include "Component.h"

namespace G3d
{

	class MeshRenderer : public Component
	{
	public:

		MeshRenderer(MeshCPtr pMesh, MaterialCPtr pMaterial, MaterialCPtr pDepthMaterial);

		MeshRenderer(MeshCPtr pMesh, MaterialCPtr pMaterial);

		virtual ~MeshRenderer();

		void render() const override;

		void renderDepth() const override;

		void setMaterial(MaterialCPtr pNewMaterial);

	protected:

		Component* clone() const override;

		MeshCPtr mpMesh;

		MaterialCPtr mpMaterial;

		MaterialCPtr mpDepthMaterial;

	private:

		MeshRenderer(MeshRenderer const&) = delete;

		MeshRenderer& operator=(MeshRenderer const&) = delete;

	};

}
