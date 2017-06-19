#include "InputManager.h"
#include <GLFW/glfw3.h>

const size_t G3d::InputManager::MAX_KEY_ID = 500;

const size_t G3d::InputManager::MAX_MOUSE_BUTTON_ID = 10;

G3d::InputManager& G3d::InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}


void G3d::InputManager::keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key<MAX_KEY_ID)
	{
		if (action == GLFW_PRESS)
		{
			getInstance().mKey[key] = 1;
			getInstance().mKeyDown[key] = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			getInstance().mKey[key] = 0;
			getInstance().mKeyUp[key] = 1;
		} 
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
	}
}

void G3d::InputManager::mouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods)
{
	if (button<MAX_MOUSE_BUTTON_ID)
	{
		if (action == GLFW_PRESS)
		{
			getInstance().mMouseButton[button] = 1;
			getInstance().mMouseButtonDown[button] = 1;
		}
		else if (action == GLFW_RELEASE)
		{
			getInstance().mMouseButton[button] = 0;
			getInstance().mMouseButtonUp[button] = 1;
		} 
	}
}


G3d::InputManager::InputManager() :
mKey(MAX_KEY_ID, 0),
mKeyDown(MAX_KEY_ID, 0),
mKeyUp(MAX_KEY_ID, 0),
mMouseButton(MAX_MOUSE_BUTTON_ID, 0),
mMouseButtonDown(MAX_MOUSE_BUTTON_ID, 0),
mMouseButtonUp(MAX_MOUSE_BUTTON_ID, 0)
{
}

G3d::InputManager::~InputManager()
{
}


void G3d::InputManager::init(GLFWwindow* pWindow)
{
	glfwSetKeyCallback(pWindow, keyCallback);
	glfwSetMouseButtonCallback(pWindow, mouseButtonCallback);
}

void G3d::InputManager::resetFrame()
{
	std::fill(mKeyDown.begin(), mKeyDown.end(), 0);
	std::fill(mKeyUp.begin(), mKeyUp.end(), 0);
	std::fill(mMouseButtonDown.begin(), mMouseButtonDown.end(), 0);
	std::fill(mMouseButtonUp.begin(), mMouseButtonUp.end(), 0);
}

bool G3d::InputManager::getKey(KeyboardInput name) const
{
	return mKey[static_cast<size_t>(name)] != 0;
}

bool G3d::InputManager::getKeyDown(KeyboardInput name) const
{
	return mKeyDown[static_cast<size_t>(name)] != 0;
}

bool G3d::InputManager::getKeyUp(KeyboardInput name) const
{
	return mKeyUp[static_cast<size_t>(name)] != 0;
}

bool G3d::InputManager::getMouseButton(MouseInput name) const
{
	return mMouseButton[static_cast<size_t>(name)] != 0;
}

bool G3d::InputManager::getMouseButtonDown(MouseInput name) const
{
	return mMouseButtonDown[static_cast<size_t>(name)] != 0;
}

bool G3d::InputManager::getMouseButtonUp(MouseInput name) const
{
	return mMouseButtonUp[static_cast<size_t>(name)] != 0;
}