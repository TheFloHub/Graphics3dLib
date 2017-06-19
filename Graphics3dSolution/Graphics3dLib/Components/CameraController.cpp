#include "CameraController.h"
#include "Transform.h"
#include "Camera.h"
#include <Graphics3dLib/Scene/SceneObject.h>
#include <Graphics3dLib/Input/InputManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

G3d::CameraController::CameraController() : 
Component(),
mMoveSpeed(400.0f),
mRotationSpeed(5.0f)
{

}

G3d::CameraController::~CameraController()
{

}

G3d::Component* G3d::CameraController::clone() const
{
	CameraController* pCameraController = new CameraController();
	pCameraController->mIsEnabled = mIsEnabled;
	pCameraController->mMoveSpeed = mMoveSpeed;
	pCameraController->mRotationSpeed= mRotationSpeed;
	return pCameraController;
}

void G3d::CameraController::update(double deltaTime)
{
	if (InputManager::getInstance().getKeyDown(KEY_E))
	{
		mMoveSpeed += 100.0;
	}
	if (InputManager::getInstance().getKeyDown(KEY_Q))
	{
		mMoveSpeed -= 100.0;
	}

	Transform& transform = *(mpSceneObject->getTransform());
	if (InputManager::getInstance().getKey(KEY_W))
	{
		transform.translate(glm::vec3(0.0f, 0.0, mMoveSpeed*deltaTime));
	}
	if (InputManager::getInstance().getKey(KEY_S))
	{
		transform.translate(glm::vec3(0.0f, 0.0, -mMoveSpeed*deltaTime));
	}
	if (InputManager::getInstance().getKey(KEY_A))
	{
		transform.translate(glm::vec3(mMoveSpeed*deltaTime, 0.0, 0.0f));
	}
	if (InputManager::getInstance().getKey(KEY_D))
	{
		transform.translate(glm::vec3(-mMoveSpeed*deltaTime, 0.0, 0.0f));
	}
}