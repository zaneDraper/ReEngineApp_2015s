#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	//m_pSystem->SetWindowResolution(RESOLUTIONS::HD_1280X720);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
<<<<<<< HEAD:E06_Lerp/AppClass.cpp
	//Set the camera at a position other than the default
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 2.5f, 12.0f), vector3(0.0f, 2.5f, 11.0f), REAXISY);
	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 35.0f));

	//m_nObjects initialization
	srand(time(NULL));
	m_nObjects = rand() % 23 + 5;

	//start and end vectors
	vector3 start = vector3(-m_nObjects, 0.0f, 0.0f);
	vector3 end = vector3(m_nObjects, 0.0f, 0.0f);

	m_pLightMngr->SetColor(REWHITE, 0);
	m_pLightMngr->SetIntensity(0.1f, 0);
	m_pLightMngr->SetColor(REWHITE, 1);
	m_pLightMngr->SetIntensity(0.5f, 1);
	m_pLightMngr->SetPosition(vector3(0.0f, 1.0f,-1.0f), 1);

	//m_pSphere = PrimitiveClass(Sphere)
	//m_pMatrix = new 

	//Load a model onto the Mesh manager
	//m_pMeshMngr->LoadModel("tests\\Cubev.fbx", "Unikitty");
	/*int nCubes = 10;
	vector3 v3Start(-nCubes/2.0f, 0.0f, -nCubes / 2.0f);
	m_pMeshMngr->LoadModel("Cube.obj", "ElCubo");
	m_pMeshMngr->SetShaderProgramByName("ElCubo", "Phong");
	for (uint n = 0; n < nCubes; n++)
	{
		if (v3Start != vector3(0.0f))
		{
			String sName = "Cube_" + std::to_string(n);
			m_pMeshMngr->LoadModel("Cube.obj", sName, false, glm::translate(v3Start));
			m_pMeshMngr->SetShaderProgramByName(sName, "Phong");
		}
		v3Start += vector3(1.0f, 0.0f, 1.0f);
	}*/
=======
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
>>>>>>> 1ff633c8d38024521334e915ae750d4f7d39581f:00_Sandbox/AppClass.cpp
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}