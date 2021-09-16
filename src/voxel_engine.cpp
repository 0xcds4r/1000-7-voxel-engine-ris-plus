#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ctime>

// GLM
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/VoxelRenderer.h"
#include "graphics/LineBatch.h"
#include "window/Window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "loaders/png_loading.h"
#include "voxels/voxel.h"
#include "voxels/Chunk.h"
#include "voxels/Chunks.h"
#include "voxels/Block.h"
#include "voxels/Blocks.h"
#include "voxels/Items.h"
#include "voxels/WorldGenerator.h"
#include "voxels/Level.h"
#include "files/files.h"
#include "files/WorldFiles.h"
#include "lighting/LightSolver.h"
#include "lighting/Lightmap.h"
#include "lighting/Lighting.h"
#include "physics/Hitbox.h"
#include "physics/PhysicsSolver.h"

// GUI
#include "gui/gui.h"
#include "gui/chat.h"

int WIDTH = 1280;
int HEIGHT = 720;

float vertices[] = {
		// x    y
	   -0.01f,-0.01f,
	    0.01f, 0.01f,

	   -0.01f, 0.01f,
	    0.01f,-0.01f,
};

int attrs[] = {
		2,  0 //null terminator
};

Mesh *crosshair;
Shader *shader, *linesShader, *crosshairShader, *shaderEntity;
Texture *texture, *textureEntity;
LineBatch *lineBatch;
Hitbox* hitbox = 0;
Camera* camera = 0;

bool bIgnoreControllable = false;

// Shaders, textures, renderers
int initialize_assets() 
{
	shader = load_shader("res/main.glslv", "res/main.glslf");
	if (shader == nullptr){
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}

	shaderEntity = load_shader("res/main.glslv", "res/main.glslf"); // ~
	if (shaderEntity == nullptr){
		std::cerr << "failed to load shader" << std::endl;
		Window::terminate();
		return 1;
	}

	crosshairShader = load_shader("res/crosshair.glslv", "res/crosshair.glslf");
	if (crosshairShader == nullptr){
		std::cerr << "failed to load crosshair shader" << std::endl;
		Window::terminate();
		return 1;
	}

	linesShader = load_shader("res/lines.glslv", "res/lines.glslf");
	if (linesShader == nullptr){
		std::cerr << "failed to load lines shader" << std::endl;
		Window::terminate();
		return 1;
	}

	texture = load_texture("res/block.png");
	if (texture == nullptr){
		std::cerr << "failed to load texture" << std::endl;
		delete shader;
		Window::terminate();
		return 1;
	}

	textureEntity = load_texture("res/img.png"); // ~
	if (textureEntity == nullptr){
		std::cerr << "failed to load texture" << std::endl;
		delete shaderEntity;
		Window::terminate();
		return 1;
	}

	return 0;
}

uint32_t GetTickCount()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

#include "voxels/TimeCycle.h"

bool bDayStatus = true;
void draw_world(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	// Draw VAO
	shader->use();
	shader->uniformMatrix("u_projview", camera->getProjection()*camera->getView());

	TimeCycle::update(shader);

	texture->bind();
	mat4 model(1.0f);

	for (size_t i = 0; i < Level::getChunks()->getChunkVolume(); i++)
	{
		Chunk* chunk = Level::getChunks()->getChunkByPos(i);
		if (chunk == nullptr) {
			continue;
		}

		Mesh* mesh = Level::getChunks()->getChunkMeshByPos(i);
		if (mesh == nullptr) {
			continue;
		}

		model = glm::translate(mat4(1.0f), vec3(chunk->x*CHUNK_W+0.5f, chunk->y*CHUNK_H+0.5f, chunk->z*CHUNK_D+0.5f));
		shader->uniformMatrix("u_model", model);
		mesh->draw(GL_TRIANGLES);
	}

	linesShader->use();
	linesShader->uniformMatrix("u_projview", camera->getProjection()*camera->getView());
	glLineWidth(1.85f);
	lineBatch->render();
}

// Deleting GL objects like shaders, textures
void finalize_assets()
{
	delete shader;
	delete texture;
	// delete crosshair;
	// delete crosshairShader;
	delete linesShader;
	delete lineBatch;
}

int fLastDistanceBlockBP = 0.0f;
int main() 
{
	Window::initialize(WIDTH, HEIGHT, "MCVE");
	Events::initialize();
	Events::toogleCursor();

	if (initialize_assets())
	{
		Window::terminate();
		return 1;
	}

	Blocks::initialize();
	Items::initialize();
	Level::initialize();
	TimeCycle::setup();
	TimeCycle::setGlobalTick(rand() % 20000);

	VoxelRenderer renderer(1024*1024);
	lineBatch = new LineBatch(4096);
	PhysicsSolver physics(vec3(0,-16.0f,0));

	gui::initialize();

	// crosshair = new Mesh(vertices, 4, attrs);
	camera = new Camera(vec3(32,32,32), radians(90.0f));
	hitbox = new Hitbox(vec3(32,32,32), vec3(0.2f,0.9f,0.2f));

	float lastTime = glfwGetTime();
	float delta = 0.0f;

	float camX = 0.0f;
	float camY = 0.0f;

	float playerSpeed = 8.0f;

	int choosenBlock = 0;
	long frame = 0;

	int iBreakPutSpeed = 0;	
	bool bBreak = false;

	glfwSwapInterval(1); // fuck down vsync plz

	while (!Window::isShouldClose())
	{
		frame++;
		float currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;
		bIgnoreControllable = (Events::isCursorEnabled() || chat::isActive()) ? true : false;
		
		// playerSpeed = (4.0f * cos(1/delta)) + 7.0f; // inverted
		playerSpeed = (4.0f * -cos(1/delta)) + 7.0f;

		if (Events::jpressed(GLFW_KEY_ESCAPE))
		{
			if(!chat::isActive()) 
			{
				Window::setShouldClose(true);
			}
			else 
			{
				Events::toogleCursor();	
				chat::toggle();
			}
		}

		if(Events::jpressed(GLFW_KEY_T) && !chat::isActive())
		{
			Events::toogleCursor();	
			chat::toggle();
		}

		for (int i = 1; i < 6; i++){
			if (Events::jpressed(GLFW_KEY_0+i) && !bIgnoreControllable){
				choosenBlock = i;
			}
		}

		// Controls
		bool sprint = Events::pressed(GLFW_KEY_LEFT_CONTROL) && !bIgnoreControllable;
		bool shift = Events::pressed(GLFW_KEY_LEFT_SHIFT) && hitbox->grounded && !sprint && !bIgnoreControllable;
		if(shift) { playerSpeed -= 5.0f; } else { if(sprint) playerSpeed += 5.0f; }

		float speed = playerSpeed;
		int substeps = (int)(delta * 1000);
		substeps = (substeps <= 0 ? 1 : (substeps > 100 ? 100 : substeps));
		physics.step(Level::getChunks(), hitbox, delta, substeps, shift);
		camera->process(speed, delta);

		if (Events::pressed(GLFW_KEY_SPACE) && hitbox->grounded && !bIgnoreControllable){
			hitbox->velocity.y = 6.0f;
		}

		vec3 dir(0,0,0);
		dir = camera->findDirent();
		hitbox->velocity.x = dir.x * speed;
		hitbox->velocity.z = dir.z * speed;

		Level::getChunks()->setCenter(Level::getData(), camera->position.x, 0, camera->position.z);
		Level::getChunks()->_buildMeshes(&renderer);
		Level::getChunks()->loadVisible(Level::getData());

		if (!Events::isCursorEnabled()) {
			camera->processRotation();
		}

		static uint32_t dwLastMouseBreakPutTick = GetTickCount();

		if(GetTickCount() - dwLastMouseBreakPutTick >= 200 - iBreakPutSpeed)
		{
			vec3 end;
			vec3 norm;
			vec3 iend;
			voxel* vox = Level::getChunks()->rayCast(camera->position, camera->front, 10.0f, end, norm, iend);

			static int iBreakDistance = 7;
			static int iPutDistance = 7;

			if (vox != nullptr)
			{
				fLastDistanceBlockBP = camera->getDistanceFromPoint((int)iend.x, (int)iend.y, (int)iend.z);
				if(fLastDistanceBlockBP <= iBreakDistance && fLastDistanceBlockBP <= iPutDistance) {
					lineBatch->box(iend.x + 0.5f, iend.y + 0.5f, iend.z + 0.5f, 1.005f, 1.005f, 1.005f, 0, 0, 0, 0.5f);
				}

				if (Events::clicked(GLFW_MOUSE_BUTTON_1) && !bIgnoreControllable && fLastDistanceBlockBP <= iBreakDistance)
				{
					int x = (int)iend.x;
					int y = (int)iend.y;
					int z = (int)iend.z;

					Level::setBlock(x, y, z, 0);

					if(!bBreak) {
						iBreakPutSpeed = 0;	
					}

					if(iBreakPutSpeed < 50) {
						iBreakPutSpeed += 5;
					}

					bBreak = true;
					dwLastMouseBreakPutTick = GetTickCount();
				}

				else if (Events::clicked(GLFW_MOUSE_BUTTON_2) && !bIgnoreControllable && fLastDistanceBlockBP <= iPutDistance)
				{
					int x = (int)(iend.x)+(int)(norm.x);
					int y = (int)(iend.y)+(int)(norm.y);
					int z = (int)(iend.z)+(int)(norm.z);

					if (!physics.isBlockInside(x, y, z, hitbox)) 
					{
						if(bBreak) {
							iBreakPutSpeed = 0;	
						}

						if(iBreakPutSpeed < 50) {
							iBreakPutSpeed += 5;
						}

						bBreak = false;
						Level::setBlock(x, y, z, choosenBlock);
						dwLastMouseBreakPutTick = GetTickCount();
					}
				}
				else iBreakPutSpeed = 0;
			}
		}

		draw_world(camera);
		gui::render();

		Window::swapBuffers();
		Events::pullEvents();
	}

	// Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	Level::writeData();
	Level::closeData();

	Lighting::finalize();
	finalize_assets();
	Window::terminate();
	return 0;
}
