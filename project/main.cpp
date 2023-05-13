#include <vector>
#include <map>

#include "glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "p6/p6.h"

#include "Arpenteur.hpp"
#include "Boid.hpp"
#include "Cloud.hpp"
#include "Content.hpp"
#include "FacesGroup.hpp"
#include "FreeflyCamera.hpp"
#include "IHM.hpp"
#include "Loader.hpp"
#include "Obstacle.hpp"
#include "Object.hpp"
#include "ObjectProgram.hpp"
#include "Texture.hpp"
// #include "TrackballCamera.hpp"


#include "test.hpp"



/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  window_width  = 1280;
    int  window_height = 720;
    auto ctx = p6::Context{{window_width, window_height, "Project qui se passe super bien"}};
    ctx.maximize_window();

    glEnable(GL_DEPTH_TEST) ;

    ObjectProgram magicProgram ; 
    ObjectProgram puitProgram ; 

    std::vector<Boid> boids;
    std::vector<Obstacle> obstacles;
    std::vector<Cloud> clouds;
    std::map<std::string, Material> materialMap;

    FreeflyCamera ViewMatrix;

    bool Z = false;
    bool S = false;
    bool Q = false;
    bool D = false;

    IHM ihm ;
    Loader loader ; 
    int nb_slot = 0;

    std::vector<FacesGroup> puit = loader.LoadFromFile("./assets/models/puit.obj", materialMap, nb_slot);
    std::vector<FacesGroup> magic = loader.LoadFromFile("./assets/models/magique.obj", materialMap, nb_slot);
    std::vector<FacesGroup> content = loader.LoadFromFile("./assets/models/content.obj", materialMap, nb_slot);
    std::vector<FacesGroup> fir1 = loader.LoadFromFile("./assets/models/fir1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> fir2 = loader.LoadFromFile("./assets/models/fir2.obj", materialMap, nb_slot);
    std::vector<FacesGroup> fir3 = loader.LoadFromFile("./assets/models/fir3.obj", materialMap, nb_slot);
    std::vector<FacesGroup> mushroom1 = loader.LoadFromFile("./assets/models/mushroom1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> mushroom2 = loader.LoadFromFile("./assets/models/mushroom2.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rock1 = loader.LoadFromFile("./assets/models/rock1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rock2 = loader.LoadFromFile("./assets/models/rock2.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rock3 = loader.LoadFromFile("./assets/models/rock3.obj", materialMap, nb_slot);
    std::vector<FacesGroup> house = loader.LoadFromFile("./assets/models/house.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rocks = loader.LoadFromFile("./assets/models/rocks.obj", materialMap, nb_slot);
    std::vector<FacesGroup> rail = loader.LoadFromFile("./assets/models/rail.obj", materialMap, nb_slot);
    std::vector<FacesGroup> barel = loader.LoadFromFile("./assets/models/barel.obj", materialMap, nb_slot);
    std::vector<FacesGroup> cloud = loader.LoadFromFile("./assets/models/cloud1.obj", materialMap, nb_slot);
    std::vector<FacesGroup> panneau = loader.LoadFromFile("./assets/models/panneau.obj", materialMap, nb_slot);
    std::vector<FacesGroup> sphere = loader.LoadFromFile("./assets/models/sphere.obj", materialMap, nb_slot);


    Vec magicPos = Vec(12.0, 0.0, -12.0); 
    
     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b(sphere, puitProgram, magicPos) ;
         boids.push_back(b);
     }

    for(int i=0; i < ihm.get_nb_obstacles(); i++){
        float j = p6::random::number(); 
        if(j < 0.2) {
            obstacles.push_back(Obstacle(fir1, magicProgram));
        } else if(j < 0.4) {
            obstacles.push_back(Obstacle(fir2, magicProgram));
        } else if (j < 0.6){
            obstacles.push_back(Obstacle(fir3, magicProgram));
        } else if(j < 0.65) {
            obstacles.push_back(Obstacle(mushroom1, magicProgram));
        } else if (j < 0.7){
            obstacles.push_back(Obstacle(mushroom2, magicProgram));
        }else if (j < 0.8){
            obstacles.push_back(Obstacle(rock1, magicProgram));
        } else if(j < 0.9) {
            obstacles.push_back(Obstacle(rock2, magicProgram));
        } else {
            obstacles.push_back(Obstacle(rock3, magicProgram));
        }
    }

    obstacles.push_back(Obstacle(house, magicProgram, Vec(-4.0, 0.0, 0.0))) ;
    obstacles.push_back(Obstacle(puit, magicProgram, Vec(3.0, 0.0, 4.0))) ;
    obstacles.push_back(Obstacle(rail, magicProgram, Vec(-18.0, 0.0, 18.0))) ;
    obstacles.push_back(Obstacle(rocks, magicProgram, Vec(-4.0, 0.0, 4.0))) ;
    obstacles.push_back(Obstacle(barel, magicProgram, Vec(-4.0, 0.0, 0.0))) ;
    obstacles.push_back(Obstacle(magic, magicProgram, magicPos)) ;
    obstacles.push_back(Obstacle(panneau, magicProgram, Vec(-10.0, 0.0, 13.0))) ;


    for(int i=0 ; i<3 ; i++){
         Cloud c(cloud, puitProgram) ;
         clouds.push_back(c);
     }

    Content box(content, magicProgram) ;
    Arpenteur Gaspard(barel, puitProgram) ; 

glDisable(GL_CULL_FACE) ; 


/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.7f, 0.6f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//gestion event
        if (Z) ViewMatrix.moveFront(0.1);
        if (S) ViewMatrix.moveFront(-0.1);
        if (Q) ViewMatrix.moveLeft(0.1);
        if (D) ViewMatrix.moveLeft(-0.1);

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
        for(auto& boid : boids){
            boid.draw(ViewMatrix, window_width, window_height, materialMap) ;
            boid.collision(boids, obstacles, ihm, ctx) ;
            boid.update_position() ;
        };


        for(auto& obstacle : obstacles){
            obstacle.draw(ViewMatrix, window_width, window_height, materialMap) ;
        };

        for(auto& cloud : clouds){
            cloud.draw(ViewMatrix, window_width, window_height, materialMap) ;
            cloud.update_position(ctx) ;
        }

        // contentCube.draw(ViewMatrix, window_width, window_height, materialMap) ;
        box.draw(ViewMatrix, window_width, window_height, materialMap) ;
        Gaspard.draw(ViewMatrix, window_width, window_height, materialMap) ;
        Gaspard.update_position(ViewMatrix); 

        ihm.draw();

        // ihm.add_or_remove_boids(boids, puitProgram, puit, magicPos) ;
        // ihm.add_or_remove_obsZtacles(obstacles, puitProgram, magic) ;

    };

    ctx.start();
    for(auto obstacle : obstacles){
        obstacle.deleteVAO_VBO() ; 
    }
    for(auto boid : boids){
        boid.deleteVAO_VBO() ; 
    }
    glfwTerminate();
}