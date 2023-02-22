#ifndef DRAWMODEL_H
#define DRAWMODEL_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RAWmodel.h"
#include "matrixStack.h"
#include "shader.h"
#include "textureMap.h"
#include "Item.h"
#include "world.h"
#include "logger.h"
#include "camera.h"

void Shader_Create();
void Shader_init(int n, bool settex);
void ViewProjection_Create(int n);
void ourShader_model();
void depthShader_model();
void lightShader_model();
void Model_del();

extern Camera camera;
extern glm::vec3 lightPos;
extern const unsigned int SCR_WIDTH, SCR_HEIGHT;
extern float rate;

#endif