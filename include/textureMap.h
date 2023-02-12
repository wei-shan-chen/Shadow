#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>
#include <omp.h>

#include "BounderVoxel.h"
#include "SOM.h"
#include "logger.h"

void createTexture();
void createdepthTexture();
void bindTexture(int act, int bind);

extern unsigned int texture;
extern unsigned int depthtex;
extern unsigned int depthFBO;
extern const unsigned int SHADOW_WIDTH, SHADOW_HEIGHT;
// extern 
#endif