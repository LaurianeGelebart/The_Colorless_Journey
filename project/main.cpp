#include <vector>
#include "glimac/FreeflyCamera.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

#include "IHM.hpp"
#include "Obstacle.hpp"
#include "Boid.hpp"
#include "ObjModel.hpp"


std::vector<Boid> boids; 
std::vector<Obstacle> obstacles; 


void add_or_remove_boids(IHM &ihm)
{
    int nb_boids = boids.size(); 
     if (nb_boids<ihm.get_nb_boids()){ 
        for(int i=0 ; i< ihm.get_nb_boids()-nb_boids ; i++){
            Boid b ; 
            boids.push_back(b);
        }
        nb_boids = ihm.get_nb_boids(); 
    } 
    else if (nb_boids>ihm.get_nb_boids()){
        for(int i=0 ; i< nb_boids-ihm.get_nb_boids() ; i++){
            boids.pop_back();
        }
        nb_boids = ihm.get_nb_boids();
    }
}


void add_or_remove_obstacles(IHM &ihm)
{
    int nb_obstacles = obstacles.size(); 
    if (nb_obstacles<ihm.get_nb_obstacles()){
        for(int i=0 ; i< ihm.get_nb_obstacles()-nb_obstacles ; i++){
            Obstacle o ; 
            obstacles.push_back(o);
        }
        nb_obstacles = ihm.get_nb_obstacles(); 
    } 
    else if (nb_obstacles>ihm.get_nb_obstacles()){
        for(int i=0 ; i< nb_obstacles-ihm.get_nb_obstacles() ; i++){
            obstacles.pop_back();
        }
        nb_obstacles = ihm.get_nb_obstacles();
    }
}


struct ObstaclesProgram 
{
    p6::Shader m_Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    //GLint uLightPos_vs;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    // ObstaclesProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/pointlight.fs.glsl"))
    ObstaclesProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/directionallight.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");

        uKd        = glGetUniformLocation(m_Program.id(), "uKd");
        uKs        = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        //uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightDir_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    }
};


struct BoidsProgram 
{
    p6::Shader m_Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    //GLint uLightPos_vs;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    // BoidsProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/pointlight.fs.glsl"))
    BoidsProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/directionallight.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");

        uKd        = glGetUniformLocation(m_Program.id(), "uKd");
        uKs        = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        //uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightDir_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    }
};





/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  window_width  = 1920;
    int  window_height = 1080;
    auto ctx = p6::Context{{window_width, window_height, "Project qui se passe super bien"}};
    ctx.maximize_window();
    
    ObstaclesProgram obstaclesProgram;
    BoidsProgram boidsProgram;
    FreeflyCamera ViewMatrix; 
    ObjModel objModel; 

    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    IHM ihm ; 

     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b ; 
         boids.push_back(b);
     }

     for(int i=0 ; i<ihm.get_nb_obstacles() ; i++){
         Obstacle o ; 
         obstacles.push_back(o);
     }

     objModel.LoadFromFile("./assets/models/cube.obj"); 
    


// Création d'un  VBO:
    GLuint vboSphere;
    glGenBuffers(1, &vboSphere);
    glBindBuffer(GL_ARRAY_BUFFER, vboSphere);

    const std::vector<glimac::ShapeVertex> sphere = glimac::sphere_vertices(1, 32, 16);  

    glBufferData(GL_ARRAY_BUFFER, sphere.size()*sizeof(glimac::ShapeVertex), sphere.data(), GL_STATIC_DRAW);

// Création d'un  VBO:
    GLuint vboSquare;
    glGenBuffers(1, &vboSquare);
    glBindBuffer(GL_ARRAY_BUFFER, vboSquare);

    // const std::vector<glimac::ShapeVertex> vertices = glimac::square_vertices(1, 32, 16);  
    std::vector<float> vertices = objModel.getVertextData(); 
    int vertexCount = objModel.getVertextCount(); 

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);


// Création d'un VAO:
    GLuint vao;
    glGenVertexArrays(1, &vao) ; 
    glBindVertexArray(vao) ; 

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    // const GLuint VERTEX_ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ; 
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ; 
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE) ; 

    glBindBuffer(GL_ARRAY_BUFFER, vboSphere);
    glBindBuffer(GL_ARRAY_BUFFER, vboSquare);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    // glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0) ; 

    glEnable(GL_DEPTH_TEST) ; 




/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.7f, 0.6f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

//gestion event
        if (Z) ViewMatrix.moveFront(0.1);
        if (S) ViewMatrix.moveFront(-0.1);
        if (Q) ViewMatrix.rotateLeft(0.1);
        if (D) ViewMatrix.rotateLeft(-0.1);

        ctx.key_pressed = [&Z, &S, &Q, &D](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W) Z = true;
            if (key.physical == GLFW_KEY_S) S = true;
            if (key.physical == GLFW_KEY_A) Q = true;
            if (key.physical == GLFW_KEY_D) D = true;
        };

        ctx.key_released = [&Z, &S, &Q, &D](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W) Z = false;
            if (key.physical == GLFW_KEY_S) S = false;
            if (key.physical == GLFW_KEY_A) Q = false;
            if (key.physical == GLFW_KEY_D) D = false;
        };

        glBindVertexArray(vao) ;

//dessin des boids    
        boidsProgram.m_Program.use();
        
        glm::mat4 MVMatrix = ViewMatrix.getViewMatrix();  
        MVMatrix = glm::scale(MVMatrix, glm::vec3(0.05));     
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);

        glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix() ; 
        //glm::mat4 MLightMatrix = glm::rotate(glm::mat4(1), ctx.time(), glm::vec3(0,1,0)); 
    // glm::vec3 lightPos = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,0,1) );
        //glm::vec3 lightDir = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,1,0) );
        glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) );
        

        for(size_t i=0 ; i<boids.size() ; i++)
        { 
       
            glUniformMatrix4fv(boidsProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
            glUniformMatrix4fv(boidsProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));        
            
            MVMatrix = glm::translate(MVMatrix, glm::vec3(boids[i].get_position())); 
            glUniformMatrix4fv(boidsProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            
            glUniform1f(boidsProgram.uShininess, 0.5); 
            glUniform3fv(boidsProgram.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5))); 
            glUniform3fv(boidsProgram.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2))); 
            // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos)); 
            glUniform3fv(boidsProgram.uLightDir_vs, 1, glm::value_ptr(lightDir)); 
            glUniform3fv(boidsProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2))); 


            glDrawArrays(GL_TRIANGLES, 0, sphere.size());

        };

        obstaclesProgram.m_Program.use();
      
// dessins des obstacles 
        glm::mat4 oMVMatrix = ViewMatrix.getViewMatrix();  
        oMVMatrix = glm::scale(oMVMatrix, glm::vec3(0.1));     
        glm::mat4 oProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);

        for(size_t i=0 ; i<obstacles.size() ; i++)
        { 
            glUniformMatrix4fv(obstaclesProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(oMVMatrix))));
            glUniformMatrix4fv(obstaclesProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(oProjMatrix * oMVMatrix));        
            
            oMVMatrix = glm::translate(oMVMatrix, glm::vec3(obstacles[i].get_position())); 
            glUniformMatrix4fv(obstaclesProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(oMVMatrix));
            
            glUniform1f(obstaclesProgram.uShininess, 0.5); 
            glUniform3fv(obstaclesProgram.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5))); 
            glUniform3fv(obstaclesProgram.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2))); 
            // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos)); 
            glUniform3fv(obstaclesProgram.uLightDir_vs, 1, glm::value_ptr(lightDir)); 
            glUniform3fv(obstaclesProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2))); 


            glDrawArrays(GL_TRIANGLES, 0, sphere.size());

        };

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        
        glBindVertexArray(0) ; 

        ihm.draw(); 

        for(size_t i=0 ; i<boids.size() ; i++)
        {   
           // boids[i].draw(ctx) ;
            boids[i].collision(boids, obstacles, ihm, ctx) ;
           boids[i].update_position() ; 
        } ;  

        for(size_t j=0 ; j<obstacles.size() ; j++)
        {   
            //obstacles[j].draw(ctx) ;
        } ; 

       add_or_remove_boids(ihm) ; 
       add_or_remove_obstacles(ihm) ; 

    };

    ctx.start();
    glDeleteBuffers(0, &vboSquare); 
    glDeleteBuffers(0, &vboSphere); 
    glDeleteVertexArrays(0, &vao); 
    glfwTerminate();
}