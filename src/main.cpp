#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Camera.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"
#include "Material.h"
#include "Light.h"

using namespace std;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from
bool OFFLINE = false;

shared_ptr<Camera> camera;
shared_ptr<Program> prog_normal;
shared_ptr<Program> prog_blinnPhong;
shared_ptr<Shape> bunny_shape;
shared_ptr<Shape> teapot_shape;

bool keyToggles[256] = {false}; // only for English keyboards!

enum ShaderMode { NORMAL, BLINN_PHONG };
ShaderMode currentShaderMode = NORMAL;

enum MaterialMode { PINK, BLUE, GRAY };
MaterialMode currentMaterial = PINK;

shared_ptr<Material> pink_material;
shared_ptr<Material> blue_material;
shared_ptr<Material> gray_material;

enum LightMode { LIGHT_ONE, LIGHT_TWO};
LightMode currentLight = LIGHT_ONE;

shared_ptr<Light> light_one;
shared_ptr<Light> light_two;


// This function is called when a GLFW error occurs
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	switch(key) {
        case GLFW_KEY_S: 
        {
            if(action == GLFW_PRESS) {
                currentShaderMode = (currentShaderMode == NORMAL) ? BLINN_PHONG : NORMAL;
            }
            break;
        }
		case GLFW_KEY_M: 
        {
            if(action == GLFW_PRESS) {
				if(currentMaterial == PINK) {
					currentMaterial = BLUE;
				} else if(currentMaterial == BLUE) {
					currentMaterial = GRAY;
				} else {
					currentMaterial = PINK;
				}
            }
            break;
        }
		case GLFW_KEY_L: 
        {
            if(action == GLFW_PRESS) {
                currentLight = (currentLight == LIGHT_ONE) ? LIGHT_TWO : LIGHT_ONE;
            }
            break;
        }
		case GLFW_KEY_X: 
        { 
            if(action == GLFW_PRESS) {
				if(mods == GLFW_MOD_SHIFT) {
					if(currentLight == LIGHT_ONE)
						light_one->posX += 0.25;
					else
						light_two->posX += 0.25;
				} else {
					if(currentLight == LIGHT_ONE)
						light_one->posX -= 0.25;
					else
						light_two->posX -= 0.25;
				}
            }
            break;
        }
		case GLFW_KEY_Y: 
        { 
            if(action == GLFW_PRESS) {
				if(mods == GLFW_MOD_SHIFT) {
					if(currentLight == LIGHT_ONE)
						light_one->posY += 0.25;
					else
						light_two->posY += 0.25;
				} else {
					if(currentLight == LIGHT_ONE)
						light_one->posY-= 0.25;
					else
						light_two->posY -= 0.25;
				}
            }
            break;
        }
    }
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = (mods & GLFW_MOD_SHIFT) != 0;
		bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
		bool alt   = (mods & GLFW_MOD_ALT) != 0;
		camera->mouseClicked((float)xmouse, (float)ymouse, shift, ctrl, alt);
	}
}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		camera->mouseMoved((float)xmouse, (float)ymouse);
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// https://lencerf.github.io/post/2019-09-21-save-the-opengl-rendering-to-image-file/
static void saveImage(const char *filepath, GLFWwindow *w)
{
	int width, height;
	glfwGetFramebufferSize(w, &width, &height);
	GLsizei nrChannels = 3;
	GLsizei stride = nrChannels * width;
	stride += (stride % 4) ? (4 - stride % 4) : 0;
	GLsizei bufferSize = stride * height;
	std::vector<char> buffer(bufferSize);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
	stbi_flip_vertically_on_write(true);
	int rc = stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);
	if(rc) {
		cout << "Wrote to " << filepath << endl;
	} else {
		cout << "Couldn't write to " << filepath << endl;
	}
}

// This function is called once to initialize the scene and OpenGL
static void init()
{
	// Initialize time.
	glfwSetTime(0.0);
	
	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	prog_normal = make_shared<Program>();
	prog_normal->setShaderNames(RESOURCE_DIR + "normal_vert.glsl", RESOURCE_DIR + "normal_frag.glsl");
	prog_normal->setVerbose(true);
	prog_normal->init();
	prog_normal->addAttribute("aPos");
	prog_normal->addAttribute("aNor");
	prog_normal->addUniform("MV");
	prog_normal->addUniform("P");
	prog_normal->setVerbose(false);


	prog_blinnPhong = make_shared<Program>();
	prog_blinnPhong->setShaderNames(RESOURCE_DIR + "blinnphong_vert.glsl", RESOURCE_DIR + "blinnphong_frag.glsl");
	prog_blinnPhong->setVerbose(true);
	prog_blinnPhong->init();
	prog_blinnPhong->addAttribute("aPos");
	prog_blinnPhong->addAttribute("aNor");
	prog_blinnPhong->addUniform("MV");
	prog_blinnPhong->addUniform("P");
	prog_blinnPhong->addUniform("lightPos1");
	prog_blinnPhong->addUniform("lightColor1");
	prog_blinnPhong->addUniform("lightPos2");
	prog_blinnPhong->addUniform("lightColor2");
	prog_blinnPhong->addUniform("ka");
	prog_blinnPhong->addUniform("kd");
	prog_blinnPhong->addUniform("ks");
	prog_blinnPhong->addUniform("s");
	prog_blinnPhong->setVerbose(false);
	
	camera = make_shared<Camera>();
	camera->setInitDistance(2.0f); // Camera's initial Z translation
	
	bunny_shape = make_shared<Shape>();
	bunny_shape->loadMesh(RESOURCE_DIR + "bunny.obj");
	bunny_shape->init();

	teapot_shape = make_shared<Shape>();
	teapot_shape->loadMesh(RESOURCE_DIR + "teapot.obj");
	teapot_shape->init();
	
	GLSL::checkError(GET_FILE_LINE);

	// MATERIALS
	pink_material = make_shared<Material>();
	blue_material = make_shared<Material>();
	gray_material = make_shared<Material>();

	//// Pink Material
	pink_material->kax = 0.2f;
	pink_material->kay = 0.2f;
	pink_material->kaz = 0.2f;

	pink_material->kdx = 0.8f;
	pink_material->kdy = 0.7f;
	pink_material->kdz = 0.7f;

	pink_material->ksx = 1.0f;
	pink_material->ksy = 0.9f;
	pink_material->ksz = 0.8f;

	pink_material->s = 200.0f;

	//// Blue Material
	blue_material->kax = 0.1f;
	blue_material->kay = 0.1f;
	blue_material->kaz = 0.5f;

	blue_material->kdx = 0.5f;
	blue_material->kdy = 0.5f;
	blue_material->kdz = 1.0f;

	blue_material->ksx = 1.0f;
	blue_material->ksy = 0.9f;
	blue_material->ksz = 0.8f;

	blue_material->s = 200.0f;

	//// Gray Material
	gray_material->kax = 0.2f;
	gray_material->kay = 0.2f;
	gray_material->kaz = 0.2f;

	gray_material->kdx = 0.5f;
	gray_material->kdy = 0.5f;
	gray_material->kdz = 0.5f;

	gray_material->ksx = 0.7f;
	gray_material->ksy = 0.7f;
	gray_material->ksz = 0.7f;

	gray_material->s = 200.0f;

	// Lights
	light_one = make_shared<Light>();
	light_two = make_shared<Light>();

	//// Light One
	light_one->posX = 1.0f;
	light_one->posY = 1.0f;
	light_one->posZ = 1.0f;

	light_one->colX = 0.8f;
	light_one->colY = 0.8f;
	light_one->colZ = 0.8f;

	//// Light Two
	light_two->posX = -1.0f;
	light_two->posY = 1.0f;
	light_two->posZ = 1.0f;

	light_two->colX = 0.2f;
	light_two->colY = 0.2f;
	light_two->colZ = 0.0f;
}

// This function is called every frame to draw the scene.
static void render()
{
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'z']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);
	
	double t = glfwGetTime();
	if(!keyToggles[(unsigned)' ']) {
		// Spacebar turns animation on/off
		t = 0.0f;
	}
	
	// Matrix stacks
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);
	
	
	if(currentShaderMode == NORMAL) {
		prog_normal->bind();
		MV->pushMatrix();
		MV->translate(-0.5f, -0.5f, 0.0f);
		MV->rotate(t, 0.0f, 1.0f, 0.0f);
		MV->scale(0.5f);
		glUniformMatrix4fv(prog_normal->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(prog_normal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
		glm::mat4 MV_matrix = MV->topMatrix(); 
		glm::mat3 normalMatrix = glm::mat3(MV_matrix); 
		normalMatrix = glm::inverse(normalMatrix); 
		normalMatrix = glm::transpose(normalMatrix);
		glUniformMatrix3fv(prog_normal->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
		bunny_shape->draw(prog_normal);
		MV->popMatrix();

		prog_normal->bind();
		MV->pushMatrix();
		MV->translate(glm::vec3(0.5f, 0.0f, 0.0f)); 
		glm::mat4 S(1.0f);
		S[0][1] = 0.5f*cos(t);
		MV->multMatrix(S);
    	MV->rotate(static_cast<float>(M_PI), glm::vec3(0.0f, 1.0f, 0.0f)); 
    	MV->scale(glm::vec3(0.5f));
		glUniformMatrix4fv(prog_normal->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(prog_normal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
		MV_matrix = MV->topMatrix(); 
		normalMatrix = glm::mat3(MV_matrix); 
		normalMatrix = glm::inverse(normalMatrix); 
		normalMatrix = glm::transpose(normalMatrix);
		glUniformMatrix3fv(prog_normal->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
		teapot_shape->draw(prog_normal);
		MV->popMatrix();

		prog_normal->unbind();
	} else if(currentShaderMode == BLINN_PHONG) {
		if (currentMaterial == PINK) {
				prog_blinnPhong->bind();
				MV->pushMatrix();
				MV->translate(-0.5f, -0.5f, 0.0f);
				MV->rotate(t, 0.0f, 1.0f, 0.0f);
				MV->scale(0.5f);
				glUniformMatrix4fv(prog_blinnPhong->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glm::mat4 MV_matrix = MV->topMatrix(); 
				glm::mat3 normalMatrix = glm::mat3(MV_matrix); 
				normalMatrix = glm::inverse(normalMatrix); 
				normalMatrix = glm::transpose(normalMatrix);
				glUniformMatrix3fv(prog_blinnPhong->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniform3f(prog_blinnPhong->getUniform("lightPos1"), light_one->posX, light_one->posY, light_one->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor1"), light_one->colX, light_one->colY, light_one->colZ);
				glUniform3f(prog_blinnPhong->getUniform("lightPos2"), light_two->posX, light_two->posY, light_two->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor2"), light_two->colX, light_two->colY, light_two->colZ);
				glUniform3f(prog_blinnPhong->getUniform("ka"), pink_material->kax, pink_material->kay, pink_material->kaz);
				glUniform3f(prog_blinnPhong->getUniform("kd"), pink_material->kdx, pink_material->kdy, pink_material->kdz);
				glUniform3f(prog_blinnPhong->getUniform("ks"), pink_material->ksx, pink_material->ksy, pink_material->ksz);
				glUniform1f(prog_blinnPhong->getUniform("s"), pink_material->s);
				bunny_shape->draw(prog_blinnPhong);
				MV->popMatrix();

				MV->pushMatrix();
				MV->translate(glm::vec3(0.5f, 0.0f, 0.0f)); 
				glm::mat4 S(1.0f);
				S[0][1] = 0.5f*cos(t);
				MV->multMatrix(S);
    			MV->rotate(static_cast<float>(M_PI), glm::vec3(0.0f, 1.0f, 0.0f)); 
    			MV->scale(glm::vec3(0.5f));
				
				glUniformMatrix4fv(prog_blinnPhong->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				MV_matrix = MV->topMatrix(); 
				normalMatrix = glm::mat3(MV_matrix); 
				normalMatrix = glm::inverse(normalMatrix); 
				normalMatrix = glm::transpose(normalMatrix);
				glUniformMatrix3fv(prog_blinnPhong->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniform3f(prog_blinnPhong->getUniform("lightPos1"), light_one->posX, light_one->posY, light_one->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor1"), light_one->colX, light_one->colY, light_one->colZ);
				glUniform3f(prog_blinnPhong->getUniform("lightPos2"), light_two->posX, light_two->posY, light_two->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor2"), light_two->colX, light_two->colY, light_two->colZ);
				glUniform3f(prog_blinnPhong->getUniform("ka"), pink_material->kax, pink_material->kay, pink_material->kaz);
				glUniform3f(prog_blinnPhong->getUniform("kd"), pink_material->kdx, pink_material->kdy, pink_material->kdz);
				glUniform3f(prog_blinnPhong->getUniform("ks"), pink_material->ksx, pink_material->ksy, pink_material->ksz);
				glUniform1f(prog_blinnPhong->getUniform("s"), pink_material->s);
				teapot_shape->draw(prog_blinnPhong);
				MV->popMatrix();

				prog_blinnPhong->unbind();
		} else if(currentMaterial == BLUE) {
				prog_blinnPhong->bind();
				MV->pushMatrix();
				MV->translate(-0.5f, -0.5f, 0.0f);
				MV->rotate(t, 0.0f, 1.0f, 0.0f);
				MV->scale(0.5f);
				glUniformMatrix4fv(prog_blinnPhong->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glm::mat4 MV_matrix = MV->topMatrix(); 
				glm::mat3 normalMatrix = glm::mat3(MV_matrix); 
				normalMatrix = glm::inverse(normalMatrix); 
				normalMatrix = glm::transpose(normalMatrix);
				glUniformMatrix3fv(prog_blinnPhong->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniform3f(prog_blinnPhong->getUniform("lightPos1"), light_one->posX, light_one->posY, light_one->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor1"), light_one->colX, light_one->colY, light_one->colZ);
				glUniform3f(prog_blinnPhong->getUniform("lightPos2"), light_two->posX, light_two->posY, light_two->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor2"), light_two->colX, light_two->colY, light_two->colZ);
				glUniform3f(prog_blinnPhong->getUniform("ka"), blue_material->kax, blue_material->kay, blue_material->kaz);
				glUniform3f(prog_blinnPhong->getUniform("kd"), blue_material->kdx, blue_material->kdy, blue_material->kdz);
				glUniform3f(prog_blinnPhong->getUniform("ks"), blue_material->ksx, blue_material->ksy, blue_material->ksz);
				glUniform1f(prog_blinnPhong->getUniform("s"), blue_material->s);
				bunny_shape->draw(prog_blinnPhong);
				MV->popMatrix();
				
				MV->pushMatrix();
				MV->translate(glm::vec3(0.5f, 0.0f, 0.0f)); 
				glm::mat4 S(1.0f);
				S[0][1] = 0.5f*cos(t);
				MV->multMatrix(S);
    			MV->rotate(static_cast<float>(M_PI), glm::vec3(0.0f, 1.0f, 0.0f)); 
    			MV->scale(glm::vec3(0.5f));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				MV_matrix = MV->topMatrix(); 
				normalMatrix = glm::mat3(MV_matrix); 
				normalMatrix = glm::inverse(normalMatrix); 
				normalMatrix = glm::transpose(normalMatrix);
				glUniformMatrix3fv(prog_blinnPhong->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniform3f(prog_blinnPhong->getUniform("lightPos1"), light_one->posX, light_one->posY, light_one->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor1"), light_one->colX, light_one->colY, light_one->colZ);
				glUniform3f(prog_blinnPhong->getUniform("lightPos2"), light_two->posX, light_two->posY, light_two->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor2"), light_two->colX, light_two->colY, light_two->colZ);
				glUniform3f(prog_blinnPhong->getUniform("ka"), blue_material->kax, blue_material->kay, blue_material->kaz);
				glUniform3f(prog_blinnPhong->getUniform("kd"), blue_material->kdx, blue_material->kdy, blue_material->kdz);
				glUniform3f(prog_blinnPhong->getUniform("ks"), blue_material->ksx, blue_material->ksy, blue_material->ksz);
				glUniform1f(prog_blinnPhong->getUniform("s"), blue_material->s);
				teapot_shape->draw(prog_blinnPhong);
				MV->popMatrix();

				prog_blinnPhong->unbind();
		} else if(currentMaterial == GRAY) {
				prog_blinnPhong->bind();
				MV->pushMatrix();
				MV->translate(-0.5f, -0.5f, 0.0f);
				MV->rotate(t, 0.0f, 1.0f, 0.0f);
				MV->scale(0.5f);
				glUniformMatrix4fv(prog_blinnPhong->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glm::mat4 MV_matrix = MV->topMatrix(); 
				glm::mat3 normalMatrix = glm::mat3(MV_matrix); 
				normalMatrix = glm::inverse(normalMatrix); 
				normalMatrix = glm::transpose(normalMatrix);
				glUniformMatrix3fv(prog_blinnPhong->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniform3f(prog_blinnPhong->getUniform("lightPos1"), light_one->posX, light_one->posY, light_one->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor1"), light_one->colX, light_one->colY, light_one->colZ);
				glUniform3f(prog_blinnPhong->getUniform("lightPos2"), light_two->posX, light_two->posY, light_two->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor2"), light_two->colX, light_two->colY, light_two->colZ);
				glUniform3f(prog_blinnPhong->getUniform("ka"), gray_material->kax, gray_material->kay, gray_material->kaz);
				glUniform3f(prog_blinnPhong->getUniform("kd"), gray_material->kdx, gray_material->kdy, gray_material->kdz);
				glUniform3f(prog_blinnPhong->getUniform("ks"), gray_material->ksx, gray_material->ksy, gray_material->ksz);
				glUniform1f(prog_blinnPhong->getUniform("s"), gray_material->s);
				bunny_shape->draw(prog_blinnPhong);
				MV->popMatrix();

				MV->pushMatrix();
				MV->translate(glm::vec3(0.5f, 0.0f, 0.0f)); 
				glm::mat4 S(1.0f);
				S[0][1] = 0.5f*cos(t);
				MV->multMatrix(S);
    			MV->rotate(static_cast<float>(M_PI), glm::vec3(0.0f, 1.0f, 0.0f)); 
    			MV->scale(glm::vec3(0.5f));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog_blinnPhong->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				MV_matrix = MV->topMatrix(); 
				normalMatrix = glm::mat3(MV_matrix); 
				normalMatrix = glm::inverse(normalMatrix); 
				normalMatrix = glm::transpose(normalMatrix);
				glUniformMatrix3fv(prog_blinnPhong->getUniform("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
				glUniform3f(prog_blinnPhong->getUniform("lightPos1"), light_one->posX, light_one->posY, light_one->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor1"), light_one->colX, light_one->colY, light_one->colZ);
				glUniform3f(prog_blinnPhong->getUniform("lightPos2"), light_two->posX, light_two->posY, light_two->posZ);
				glUniform3f(prog_blinnPhong->getUniform("lightColor2"), light_two->colX, light_two->colY, light_two->colZ);
				glUniform3f(prog_blinnPhong->getUniform("ka"), gray_material->kax, gray_material->kay, gray_material->kaz);
				glUniform3f(prog_blinnPhong->getUniform("kd"), gray_material->kdx, gray_material->kdy, gray_material->kdz);
				glUniform3f(prog_blinnPhong->getUniform("ks"), gray_material->ksx, gray_material->ksy, gray_material->ksz);
				glUniform1f(prog_blinnPhong->getUniform("s"), gray_material->s);
				teapot_shape->draw(prog_blinnPhong);
				MV->popMatrix();

				prog_blinnPhong->unbind();
		}
	}
	MV->popMatrix();
	P->popMatrix();
	
	GLSL::checkError(GET_FILE_LINE);
	
	if(OFFLINE) {
		saveImage("output.png", window);
		GLSL::checkError(GET_FILE_LINE);
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A3 RESOURCE_DIR" << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");
	
	// Optional argument
	if(argc >= 3) {
		OFFLINE = atoi(argv[2]) != 0;
	}

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "Nitin Pendekanti", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	glGetError(); // A bug in glewInit() causes an error that we can safely ignore.
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	GLSL::checkVersion();
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Set char callback.
	glfwSetCharCallback(window, char_callback);
	// Set cursor position callback.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Set mouse button callback.
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Set the window resize call back.
	glfwSetFramebufferSizeCallback(window, resize_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
