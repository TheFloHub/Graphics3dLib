#include <Graphics3dLib/GlInfo.h>
#include <Graphics3dLib/Assets/Mesh.h>
#include <Graphics3dLib/Assets/MeshManager.h>
#include <Graphics3dLib/Assets/Shader.h>
#include <Graphics3dLib/Assets/ShaderManager.h>
#include <Graphics3dLib/Assets/Texture.h>
#include <Graphics3dLib/Assets/TextureManager.h>
#include <Graphics3dLib/Assets/Materials/DiffuseMaterial.h>
#include <Graphics3dLib/Assets/Materials/SpecularMaterial.h>
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

bool InitGL(int width, int height)
{	
	//glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	// Fist init standard assets in this order
	ShaderManager::getInstance().initStandardShader();
	MeshManager::getInstance().initStandardMeshes();
	TextureManager::getInstance().initStandardTextures();
	MaterialManager::getInstance().initStandardMaterials();

	// load resources from hard disk
	MeshPtr pMeshPlane = MeshManager::getInstance().getPlane();

	MeshPtr pMeshSphere;
	//MeshPtr pMeshTeddy;
	//TexturePtr pRockTex;
	//TexturePtr pHeightMap; 
	//TexturePtr pImrodTexture; 
	try
	{
		pMeshSphere = MeshManager::getInstance().load("Sphere", "D:\\3dModels\\isosphere.obj");
		//pMeshTeddy = MeshManager::getInstance().load("Teddy", "D:\\3dModels\\isosphere.obj");
		//pRockTex = TextureManager::GetInstance().Load("Rock", "D:\\3dModels\\xy.jpg");
		//pHeightMap = TextureManager::GetInstance().Load("HeightMap", "D:\\3dModels\\heightmap.png");
		//pImrodTexture = TextureManager::GetInstance().Load("ImrodDiffuse", "D:\\3dModels\\imrod_diffuse2.jpg");

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

	// materials
	DiffuseMaterialPtr pDiffuseMaterial = MaterialManager::getInstance().create<DiffuseMaterial>("Diffuse");
	pDiffuseMaterial->setDiffuseColor(1.0f, 0.5f, 0.15f);

	SpecularMaterialPtr pSpecularMaterial = MaterialManager::getInstance().create<SpecularMaterial>("Specular");
	pSpecularMaterial->setShininess(80.0);

	// graph
	pRoot = std::unique_ptr<SceneObject>(new SceneObject("Root"));


	SceneObject* pSphere = new SceneObject("Sphere");
	pSphere->addComponent(new MeshRenderer(pMeshSphere, pDiffuseMaterial));
	pSphere->getTransform()->setPosition(glm::vec3(0.0f, 2.0f, 5.0f));
	//pSphere->GetTransform()->SetScale(glm::vec3(60.0f, 60.0f, 60.0f));

	//SceneObject* pTeddy = new SceneObject("Teddy");
	//pTeddy->AddComponent(new MeshRenderer(pMeshTeddy, pDiffuseMaterial));
	//pTeddy->GetTransform()->SetPosition(glm::vec3(2.0f, 0.0f, 4.0f));
	//pTeddy->GetTransform()->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
	//pTeddy->GetTransform()->SetRotation(195.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	SceneObject* pPlane = new SceneObject("Plane");
	pPlane->addComponent(new MeshRenderer(pMeshPlane, pSpecularMaterial));
	//pPlane->getTransform()->SetPosition(glm::vec3(2.0f, 0.0f, 4.0f));
	pPlane->getTransform()->setScale(glm::vec3(10.0f, 1.0f, 10.0f));
	//pPlane->getTransform()->SetRotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	SceneObject* pCameraObj = new SceneObject("Camera");
	pCamera = new Camera(width, height, 0.1f, 100.0f, 90.0f);
	pCameraObj->addComponent(pCamera);
	pCameraObj->addComponent(new CameraController);
	pCameraObj->getTransform()->setPosition(glm::vec3(0.0f, 2.0f, -2.0f));
	pCameraObj->getTransform()->setRotation(10.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	SceneObject* pDirectionalLight = new SceneObject("DirectionalLight");
	pDirectionalLight->addComponent(new Light(Light::DIRECTIONAL));
	pDirectionalLight->getComponent<Light>()->setIntensity(1.0f);
	pDirectionalLight->getTransform()->rotate(135.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	//SceneObject* pDirectionalLight2 = new SceneObject("DirectionalLight");
	//pDirectionalLight2->AddComponent(new Light(Light::DIRECTIONAL));
	//pDirectionalLight2->GetComponent<Light>()->SetIntensity(0.2f);
	//pDirectionalLight2->GetComponent<Light>()->SetColor(glm::vec3(0.8f, 0.95f, 1.0f));
	//pDirectionalLight2->GetTransform()->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	//pDirectionalLight2->GetTransform()->Rotate(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//pDirectionalLight2->GetTransform()->Rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	//SceneObject* pPointLight1 = new SceneObject("PointLight1");
	//pPointLight1->AddComponent(new Light(Light::POINT));
	//pPointLight1->GetTransform()->Translate(glm::vec3(0.0f, -2.0f, 7.0f));
	//pPointLight1->GetComponent<Light>()->SetIntensity(6.0f);

	//pRoot->AddChild(pTerrain);
	pRoot->addChild(pSphere);
	//pRoot->AddChild(pTeddy);
	pRoot->addChild(pPlane);
	pRoot->addChild(pCameraObj);
	pRoot->addChild(pDirectionalLight);
	//pRoot->AddChild(pDirectionalLight2);
	//pRoot->AddChild(pPointLight1);

	// renderer
	pRenderer = std::unique_ptr<SceneRenderer>(new SceneRenderer(width, height));

	CHECKGLERROR();
	return true;
}

void ErrorCallback(int error, const char* description)
{
	std::cout << "GLFW Error: " << description << std::endl;
}

void ResizeCallback(GLFWwindow* pWindow, int width, int height)
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

	glfwSetErrorCallback(ErrorCallback);

	// Initialize the library 
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Create a windowed mode window and its OpenGL context 
	int const width = 1024;
	int const height = 1024;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetFramebufferSizeCallback(window, ResizeCallback);
	InputManager::getInstance().init(window);

	// Make the window's context current 
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init() failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!InitGL(width, height))
	{
		std::cout << "InitGL() failed." << std::endl;
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