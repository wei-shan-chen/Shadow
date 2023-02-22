#include "Drawmodel.h"

const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
glm::vec3 lightPos = glm::vec3(50.0,50.0,50.0);
Camera camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float rate;

MatrixStack model;
MatrixStack view;
MatrixStack projection;
std::vector<glm::mat4> shadowTransforms;

Shader ourShader;
Shader lightShader;
Shader depthShader;

Item cube;
Item lightcube;
Item ground;
Item voxel;

float near_plane = 0.01f, far_plane = 10000000.0f;

void Shader_Create();
void Shader_init(int n, bool settex);
void ViewProjection_Create(int n);
void Model_Floor_Create(Shader shader);
void Model_create(Shader shader);
void Model_lightCube_create(Shader shader);
void ourShader_model();
void depthShader_model();

void Shader_Create()
{
    RAWmodel rawmodel;

    rawmodel.LoadFile("raw/ball67.inf", "raw/ball67.raw");
    create_world(rawmodel.bounderVoxelData, rawmodel.bounderNum);

    // modify camera
    float x = rawmodel.infdata.resolution[0];
    float y = rawmodel.infdata.resolution[2];
    float z = rawmodel.infdata.resolution[1];
    rate = max(max(x,y),z) / 2.0;
    camera.modifyPositionAndmoveSpeed(glm::vec3(x / -2.0, y / 2.0, z * 4.0), rate);

    // modify light
    lightPos = glm::vec3(x, y * 1.3, z * 2);

    ourShader = Shader("shader/shader.vs", "shader/shader.fs");
    lightShader = Shader("shader/lightShader.vs", "shader/lightShader.fs");
    depthShader = Shader("shader/depthShader.vs", "shader/depthShader.fs", "shader/depthShader.gs");

    cube = Item(world.cube);
    ground = Item((world.square));
    lightcube = Item(world.lightcube);
    voxel = Item(world.voxel);
}
void Shader_init(int n, bool settex){
    if(n == 0){
        ourShader.use();
        if(settex){
            ourShader.setInt("texturemap", 0);
            ourShader.setInt("shadowMap", 1);
            ourShader.setFloat("bias", 1.0);
        }
    }else if(n == 1){
        lightShader.use();
    }else if(n == 2){
        depthShader.use(); 
        if(settex){
            for (unsigned int i = 0; i < 6; ++i)
                depthShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
            depthShader.setFloat("far_plane", far_plane);
            depthShader.setVec3("lightPos", lightPos);
        }
    }
}   
void ViewProjection_Create(int n){
    
    if(n == 0){
        view.Save(camera.GetViewMatrix());
        projection.Save(glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near_plane, far_plane));
        ourShader.setMat4("view", view.Top());
        ourShader.setMat4("projection", projection.Top());
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setFloat("far_plane", far_plane);
    }else if(n == 1){
        lightShader.setMat4("view", view.Top());
        lightShader.setMat4("projection", projection.Top());
    }else if(n == 2){
        MatrixStack shadowProj;
        shadowProj.Save(glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane));
        
        shadowTransforms.clear();
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
  
    }
}
void ourShader_model(){
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bindTexture(0,0);//texture
    bindTexture(1,1);//depthtexture
    Model_Floor_Create(ourShader);
    Model_create(ourShader);
}
void lightShader_model(){
    Model_lightCube_create(lightShader);
}
void depthShader_model(){
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        bindTexture(0,0);
        Model_create(depthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Model_Floor_Create(Shader shader){
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 20000.0f, 1.0f, 20000.0f)));
    model.Save(glm::translate(model.Top(), glm::vec3(-0.5f, 0.0f, -0.5)));
    shader.setMat4("model", model.Top());
    shader.setBool("shader",true);
    glBindVertexArray(ground.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model.Pop();
    // log_debug("%ld", ground.VAO);

}
void Model_create(Shader shader){;
    model.Push();
    // model.Save(glm::scale(model.Top(), glm::vec3( 0.05f, 0.05f, 0.05f)));
    shader.setMat4("model", model.Top());
    shader.setBool("shader",false);
    glBindVertexArray(voxel.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.voxel.size());
    model.Pop();
    
    // model.Push();
    // shader.setMat4("model", model.Top());
    // shader.setBool("shader",false);
    // glBindVertexArray(cube.VAO);
    // glDrawArrays(GL_TRIANGLES, 0, world.cube.size());
    // model.Pop();

}
void Model_lightCube_create(Shader shader){
    model.Push();
    model.Save(glm::translate(model.Top(),lightPos));
    model.Save(glm::scale(model.Top(), glm::vec3( 0.2f, 0.2f, 0.2f)));
    shader.setMat4("model", model.Top());
    glBindVertexArray(lightcube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.lightcube.size());
    model.Pop();
}
void Model_del(){
    cube.Item_del();
    ground.Item_del();
    lightcube.Item_del();
    voxel.Item_del();
}