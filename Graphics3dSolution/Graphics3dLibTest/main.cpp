#include <Graphics3dLib/GlInfo.h>
#include <Graphics3dLib/Assets/Mesh.h>
#include <Graphics3dLib/Assets/MeshManager.h>
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/TextureManager.h>
#include <Graphics3dLib/Assets/Materials/PBRMaterial.h>
#include <Graphics3dLib/Assets/Materials/PBRTexturedMaterial.h>
#include <Graphics3dLib/Assets/MaterialManager.h>
#include <Graphics3dLib/Input/InputManager.h>

#include <Graphics3dLib/Components/Camera.h>
#include <Graphics3dLib/Components/CameraController.h>
#include <Graphics3dLib/Components/Light.h>
#include <Graphics3dLib/Components/MeshRenderer.h>
#include <Graphics3dLib/Components/Transform.h>

#include <Graphics3dLib/Scene/SceneObject.h>
#include <Graphics3dLib/Rendering/SceneRenderer.h>

#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

using namespace G3d;

// Globals
std::unique_ptr<SceneObject> pRoot;
std::unique_ptr<SceneRenderer> pRenderer;
Camera* pCamera = nullptr;

bool initGL(int width, int height)
{	
	//glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Fist init standard assets in this order
	if (ShaderManager::getInstance().initStandardShader() == false)
	{
		std::cout << "Initialization of standard shader failed." << std::endl;
		return false;
	}
	MeshManager::getInstance().initStandardMeshes();
	TextureManager::getInstance().initStandardTextures();
	MaterialManager::getInstance().initStandardMaterials();

	// load resources from hard disk
	MeshPtr pMeshPlane = MeshManager::getInstance().getPlane();

	MeshPtr pMeshSphere;
	//MeshPtr pMeshTeddy;
	TexturePtr pRustedIronAlbedo;
	TexturePtr pRustedIronMetallic;
	TexturePtr pRustedIronRoughness;
	TexturePtr pRustedIronNormal;
	try
	{
		pMeshSphere = MeshManager::getInstance().load("Sphere", "D:\\3dModels\\capsule.obj");
		//pMeshTeddy = MeshManager::getInstance().load("Teddy", "D:\\3dModels\\isosphere.obj");
		pRustedIronAlbedo = TextureManager::getInstance().load("RustedIronAlbedo", "D:\\3dModels\\comicWall\\albedo.png"); // D:\\3dModels\\rustediron\\albedo.png
		pRustedIronMetallic = TextureManager::getInstance().load("RustedIronMetallic", "D:\\3dModels\\rustediron\\metallic.png");
		pRustedIronRoughness = TextureManager::getInstance().load("RustedIronRoughness", "D:\\3dModels\\comicWall\\roughness.png");
		pRustedIronNormal = TextureManager::getInstance().load("RustedIronNormal", "D:\\3dModels\\comicWall\\normal.png"); // D:\\3dModels\\rustediron\\normal.png
	}
	catch (std::exception const& exception)
	{
		std::cout << exception.what() << std::endl;
		return false;
	}
	catch (...)
	{
		std::cout << "Unknown exception in Init()." << std::endl;
		return false;
	}


	// graph
	pRoot = std::unique_ptr<SceneObject>(new SceneObject("Root"));

	// camera
	SceneObject* pCameraObj = new SceneObject("Camera");
	pCamera = new Camera(width, height, 0.1f, 100.0f, 80.0f);
	pCameraObj->addComponent(pCamera);
	pCameraObj->addComponent(new CameraController);
	pCameraObj->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	//pCameraObj->getTransform()->setRotation(10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	pRoot->addChild(pCameraObj);

	// lights
	float intensity = 300.0f;
	//SceneObject* pPointLight1 = new SceneObject("PointLight1");
	//pPointLight1->addComponent(new Light(Light::POINT));
	//pPointLight1->getTransform()->setPosition(glm::vec3(-10.0f, -10.0f, -10.0f));
	//pPointLight1->getComponent<Light>()->setIntensity(intensity);
	//pRoot->addChild(pPointLight1);

	//SceneObject* pPointLight2 = new SceneObject("PointLight2");
	//pPointLight2->addComponent(new Light(Light::POINT));
	//pPointLight2->getTransform()->setPosition(glm::vec3( 10.0f, -10.0f, -10.0f));
	//pPointLight2->getComponent<Light>()->setIntensity(intensity);
	//pRoot->addChild(pPointLight2);

	//SceneObject* pPointLight3 = new SceneObject("PointLight3");
	//pPointLight3->addComponent(new Light(Light::POINT));
	//pPointLight3->getTransform()->setPosition(glm::vec3(-10.0f,  10.0f, -10.0f));
	//pPointLight3->getComponent<Light>()->setIntensity(intensity);
	//pRoot->addChild(pPointLight3);

	//SceneObject* pPointLight4 = new SceneObject("PointLight4");
	//pPointLight4->addComponent(new Light(Light::POINT));
	//pPointLight4->getTransform()->setPosition(glm::vec3( 10.0f,  10.0f, -10.0f));
	//pPointLight4->getComponent<Light>()->setIntensity(intensity);
	//pRoot->addChild(pPointLight4);

	SceneObject* pDirectionalLight = new SceneObject("DirectionalLight");
	pDirectionalLight->addComponent(new Light(Light::DIRECTIONAL));
	pDirectionalLight->getComponent<Light>()->setIntensity(10.0f);
	pDirectionalLight->getTransform()->rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	pRoot->addChild(pDirectionalLight);


	// spheres
	int numRows = 7;
	int numColumns = 7;
	float spacing = 2.5;

	for (int row = 0; row < numRows; ++row)
	{
		for (int col = 0; col < numColumns; ++col)
		{
			//PBRMaterialPtr pMaterial = PBRMaterialPtr(new PBRMaterial);
			//pMaterial->setAlbedo(1.0f, 0.0f, 0.0f);
			//pMaterial->setMetallic((float)row/(float)numRows);
			//pMaterial->setRoughness(glm::clamp((float)col/(float)numColumns, 0.05f, 1.0f));
			//pMaterial->setMetallic(0.0f);
			//pMaterial->setRoughness(0.05f);

			PBRTexturedMaterialPtr pMaterial = PBRTexturedMaterialPtr(new PBRTexturedMaterial);
			pMaterial->setAlbedo(pRustedIronAlbedo);
			//pMaterial->setMetallic(pRustedIronMetallic);
			pMaterial->setRoughness(pRustedIronRoughness);
			pMaterial->setNormal(pRustedIronNormal);

			SceneObject* pSphere = new SceneObject("Sphere");
			pSphere->addComponent(new MeshRenderer(pMeshSphere, pMaterial)); // pMeshSphere pMeshPlane
			pSphere->getTransform()->setPosition(glm::vec3((float)(col - (numColumns / 2)) * spacing, (float)(row - (numRows / 2)) * spacing, 0.0f));
			pSphere->getTransform()->setRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			
			pRoot->addChild(pSphere);
		}
	}

	// renderer
	pRenderer = std::unique_ptr<SceneRenderer>(new SceneRenderer(width, height));

	CHECKGLERROR();
	return true;
}

void errorCallback(int error, const char* description)
{
	std::cout << "GLFW Error: " << description << std::endl;
}

void resizeCallback(GLFWwindow* pWindow, int width, int height)
{
	if (width > 0 && height > 0)
	{
		//pCamera->SetImageSize(width, height);
		//pRenderer->SetImageSize(width, height);
	}
}


int main(void)
{
	GLFWwindow* window = nullptr;

	glfwSetErrorCallback(errorCallback);

	// Initialize GLFW library 
	if (glfwInit() == false)
	{
		std::cout << "GLFW initialization failed." << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	// Create a windowed mode window and its OpenGL context 
	int const width = 1024;
	int const height = 1024;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW couldn't create a window." << std::endl;
		glfwTerminate();
		system("pause");
		exit(EXIT_FAILURE);
	}

	glfwSetFramebufferSizeCallback(window, resizeCallback);
	InputManager::getInstance().init(window);

	// Make the window's context current 
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed." << std::endl;
		glfwTerminate();
		system("pause");
		exit(EXIT_FAILURE);
	}

	// Initialize G3dLib
	if (initGL(width, height) == false)
	{
		std::cout << "G3dLib initialization failed." << std::endl;
		glfwTerminate();
		system("pause");
		exit(EXIT_FAILURE);
	}

	// Frames per second
	double fpsSum = 0;
	size_t fpsIndex = 0;
	std::vector<double> fpsVector(100, 0.0);

	// Loop until the user closes the window 
	double lastTime = glfwGetTime();
	double currentTime = 0.0;
	double deltaTime = 0.0;
	while (!glfwWindowShouldClose(window))
	{
		// Poll for and process events 
		glfwPollEvents();

		// update
		pRoot->update(deltaTime);

		// render
		pRenderer->render(pRoot.get());
		CHECKGLERROR();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Reset inputs
		InputManager::getInstance().resetFrame();

		// Update time
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Frames per second
		fpsSum -= fpsVector[fpsIndex];
		fpsSum += deltaTime;
		fpsVector[fpsIndex] = deltaTime;
		++fpsIndex;
		if (fpsIndex == fpsVector.size())
		{
			fpsIndex = 0;
		}
		//std::cout << 1.0/(fpsSum/(double)fpsVector.size()) << std::endl;
		glfwSetWindowTitle(window, (std::string("FPS: ") + std::to_string((int)(1.0 / (fpsSum / (double)fpsVector.size())))).c_str());
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}