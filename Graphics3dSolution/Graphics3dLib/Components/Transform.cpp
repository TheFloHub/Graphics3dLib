#include "Transform.h"
#include <Graphics3dLib/Scene/SceneObject.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <gtx/quaternion.hpp>

G3d::Transform::Transform() : 
Component(),
mScale(1.0f,1.0f,1.0f),
mPosition(0.0f,0.0f,0.0f),
mQuaternion()
{

}

G3d::Transform::~Transform()
{

}

G3d::Component* G3d::Transform::clone() const
{
	Transform* pTransform = new Transform();
	pTransform->mIsEnabled = mIsEnabled;
	pTransform->mScale = mScale;
	pTransform->mPosition = mPosition;
	pTransform->mQuaternion = mQuaternion;
	return pTransform;
}

void G3d::Transform::scale(glm::vec3 const& scale)
{
	mScale *= scale;
}

void G3d::Transform::rotate(float angle, glm::vec3 const& axis)
{
	//mQuaternion = glm::rotate(mQuaternion, angle, axis);
	mQuaternion = glm::angleAxis(glm::radians(angle), axis)*mQuaternion;
}

void G3d::Transform::translate(glm::vec3 const& translation)
{
	mPosition += translation;
}

void G3d::Transform::setScale(glm::vec3 const& scale)
{
	mScale = scale;
}

void G3d::Transform::setRotation(float angle, glm::vec3 const& axis)
{
	mQuaternion = glm::angleAxis(glm::radians(angle), axis);
}

void G3d::Transform::setPosition(glm::vec3 const& position)
{
	mPosition = position;
}

//void G3d::Transform::LookAt(glm::vec3 const& eye, glm::vec3 const& center, glm::vec3 const& up)
//{
//	mQuaternion = glm::quat_cast(glm::lookAt(eye, center, up));
//	mPosition = center;
//}

glm::mat4 G3d::Transform::getLocalToParentMatrix() const
{
	return glm::translate(glm::mat4(), mPosition) * glm::mat4_cast(mQuaternion) * glm::scale(glm::mat4(), mScale);
}

glm::mat4 G3d::Transform::getParentToLocalMatrix() const
{
	glm::vec3 inverseScale(1.0f/mScale.x, 1.0f/mScale.y, 1.0f/mScale.z);
	return glm::scale(glm::mat4(), inverseScale) * glm::mat4_cast(glm::inverse(mQuaternion)) * glm::translate(glm::mat4(), -mPosition);
	// alternative !?: return glm::affineInverse(GetLocalToParentMatrix());
}

glm::mat4 G3d::Transform::getLocalToWorldMatrix() const
{
	if (mpSceneObject != nullptr && mpSceneObject->getParent() != nullptr)
	{
		return mpSceneObject->getParent()->getTransform()->getLocalToWorldMatrix() * getLocalToParentMatrix();
	}
	return getLocalToParentMatrix(); // glm::mat4() or GetLocalToParentMatrix() ?
}

glm::mat4 G3d::Transform::getWorldToLocalMatrix() const
{
	if (mpSceneObject != nullptr && mpSceneObject->getParent() != nullptr)
	{
		return getParentToLocalMatrix() * mpSceneObject->getParent()->getTransform()->getWorldToLocalMatrix();
	}
	return getParentToLocalMatrix(); // glm::mat4() or GetParentToLocalMatrix() ?
}

glm::mat3 G3d::Transform::getLocalToWorldRotationMatrix() const
{
	if (mpSceneObject != nullptr && mpSceneObject->getParent() != nullptr)
	{
		return mpSceneObject->getParent()->getTransform()->getLocalToWorldRotationMatrix() * glm::mat3_cast(mQuaternion);
	}
	return glm::mat3_cast(mQuaternion);
}

glm::mat3 G3d::Transform::getWorldToLocalRotationMatrix() const
{
	if (mpSceneObject != nullptr && mpSceneObject->getParent() != nullptr)
	{
		return glm::mat3_cast(glm::inverse(mQuaternion)) * mpSceneObject->getParent()->getTransform()->getWorldToLocalRotationMatrix();
	}
	return glm::mat3_cast(glm::inverse(mQuaternion)); // glm::mat4() or GetParentToLocalMatrix() ?
}

