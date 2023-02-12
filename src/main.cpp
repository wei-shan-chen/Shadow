#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


#include "shader.h"
#include "matrixStack.h"
#include "item.h"
#include "world.h"
#include "SOM.h"
#include "camera.h"
#include "RAWmodel.h"
#include "Drawmodel.h"
#include "textureMap.h"

#include <stb_image.h>
#include <math.h>
#include <iostream>
#include <array>
#include <thread>
#include <fileSystem>

#define TSIZE 64

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
// model show
bool show = true;
bool showtex = true;
// thread
thread t1;
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SOM_3D", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------

	Shader_Create();
    createTexture();
	createdepthTexture();	
	Shader_init(0, true);
	Shader_init(3, true);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{

		// move(keyboard&mouth)
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//depth shader
		ViewProjection_Create(camera.Position, camera.GetViewMatrix(), camera.Zoom, 2);
		Shader_init(2, true);
		depthShader_model();
		//our shader
		Shader_init(0, false);
		ViewProjection_Create(camera.Position, camera.GetViewMatrix(), camera.Zoom, 0);
		ourShader_model();
		//depthdebug shader
		Shader_init(3, false);
		ViewProjection_Create(camera.Position, camera.GetViewMatrix(), camera.Zoom, 3);
		depthdebug_model();
		//light shader
		Shader_init(1, false);
		ViewProjection_Create(camera.Position, camera.GetViewMatrix(), camera.Zoom, 1);
		lightShader_model();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Model_del();
	glfwTerminate();
	destroy_world();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	// camera
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		camera.ProcessKeyboard(PITCHUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		camera.ProcessKeyboard(PITCHDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		camera.ProcessKeyboard(YAWUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		camera.ProcessKeyboard(YAWDOWN, deltaTime);

	// light
	float v = 3.0f*deltaTime;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,v,0.0);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,-1*v,0.0);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(-1*v,0.0,0.0);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(v,0.0,0.0);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,0.0,v);
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,0.0,-1*v);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}