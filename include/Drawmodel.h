#ifndef DRAWMODEL_H
#define DRAWMODEL_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "matrixStack.h"
#include "shader.h"
#include "textureMap.h"
#include "Item.h"
#include "world.h"
#include "logger.h"

void Shader_Create();
void Shader_init(int n, bool settex);
void ViewProjection_Create(glm::vec3 position, glm::mat4 viewMatrix, float zoom, int n);
void ourShader_model();
void depthShader_model();
void depthdebug_model();
void lightShader_model();
// void Model_Floor_Create(Shader shader);
// void Model_cube_create(Shader shader);
// void Model_lightCube_create(Shader shader);
void Model_del();


extern glm::vec3 lightPos;
extern const unsigned int SCR_WIDTH, SCR_HEIGHT;

#endif