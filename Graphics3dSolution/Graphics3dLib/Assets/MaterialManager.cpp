#include "MaterialManager.h"
#include "Material.h"
#include <Graphics3dLib/Assets/Materials/DefaultDepthMaterial.h>

G3d::MaterialManager& G3d::MaterialManager::getInstance()
{
	static MaterialManager instance;
	return instance;
}

G3d::MaterialManager::MaterialManager() :
mMaterialMap()
{
}

G3d::MaterialManager::~MaterialManager()
{
}

G3d::MaterialCPtr G3d::MaterialManager::getDefaultDepthMaterial() const
{
	return get<DefaultDepthMaterial>("DefaultDepthMaterial");
}

void G3d::MaterialManager::initStandardMaterials()
{
	create<DefaultDepthMaterial>("DefaultDepthMaterial");
}
