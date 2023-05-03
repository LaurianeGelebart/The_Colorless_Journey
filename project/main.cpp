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
#include "Object.hpp"
#include "ObjectProgram.hpp"
#include "ObjModel.hpp"


std::vector<Boid> boids;
std::vector<Obstacle> obstacles;



void add_or_remove_boids(IHM &ihm, ObjectProgram &puitProgram, ObjModel &puit)
{
    int nb_boids = boids.size();
     if (nb_boids<ihm.get_nb_boids()){
        for(int i=0 ; i< ihm.get_nb_boids()-nb_boids ; i++){
            Boid b(puit, puitProgram) ;
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
void add_or_remove_obstacles(IHM &ihm, ObjectProgram &magicProgram, ObjModel &magic)
{
    int nb_obstacles = obstacles.size();
    if (nb_obstacles<ihm.get_nb_obstacles()){
        for(int i=0 ; i< ihm.get_nb_obstacles()-nb_obstacles ; i++){
            Obstacle o(magic, magicProgram) ;
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




/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  window_width  = 1280;
    int  window_height = 720;
    auto ctx = p6::Context{{window_width, window_height, "Project qui se passe super bien"}};
    ctx.maximize_window();

        ObjModel magic ;
        ObjModel puit ;

        ObjectProgram magicProgram ; 
        ObjectProgram puitProgram ; 

    std::vector<Material> materials ; 

    FreeflyCamera ViewMatrix;

    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    IHM ihm ;

    puit.LoadFromFile("./assets/models/puit.obj", materials);
    magic.LoadFromFile("./assets/models/magique.obj", materials);


     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b(puit, puitProgram) ;
         boids.push_back(b);
     }

     for(int i=0 ; i<ihm.get_nb_obstacles() ; i++){
         Obstacle o(magic, magicProgram) ;
         obstacles.push_back(o);
     }



// Création VAO1:
    GLuint vao;
    glGenVertexArrays(1, &vao) ;
    glBindVertexArray(vao) ;

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS) ;

    glBindBuffer(GL_ARRAY_BUFFER, boids[0]._vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), 0); //(const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0) ;

    glEnable(GL_DEPTH_TEST) ;


// Création VAO2:
    GLuint vao2;
    glGenVertexArrays(1, &vao2) ;
    glBindVertexArray(vao2) ;

    // const GLuint VERTEX_ATTR_POSITION = 0;
    // const GLuint VERTEX_ATTR_NORMAL = 1;
    // const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION) ;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL) ;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS) ;

    glBindBuffer(GL_ARRAY_BUFFER, obstacles[0]._vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), 0); //(const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
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
        if (Q) ViewMatrix.rotateLeft(0.5);
        if (D) ViewMatrix.rotateLeft(-0.5);

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

//Dessin
		glBindVertexArray(vao) ;
        for(size_t i=0 ; i<boids.size() ; i++){

            boids[i].draw(ViewMatrix, window_width, window_height) ;
            boids[i].collision(boids, obstacles, ihm, ctx) ;
            boids[i].update_position() ;

        };
		glBindVertexArray(0) ;

		glBindVertexArray(vao2) ;
        for(size_t i=0 ; i<obstacles.size() ; i++){
            // obstacles[i].draw(ViewMatrix, window_width, window_height) ;
        };
        glBindVertexArray(0) ;

        ihm.draw();

       add_or_remove_boids(ihm, puitProgram, puit) ;
       add_or_remove_obstacles(ihm, magicProgram, magic) ;

    };

    ctx.start();
    // glDeleteBuffers(0, &vboPumpkin);
    // glDeleteBuffers(0, &vboSphere);
    // glDeleteBuffers(0, &vboTeapot);
    glDeleteVertexArrays(0, &vao);
    glDeleteVertexArrays(0, &vao2);
    glfwTerminate();
}