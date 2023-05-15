#include <vector>
#include <map>

#include "glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "p6/p6.h"

// #include "Arpenteur.hpp"
// #include "Boid.hpp"
// #include "Cloud.hpp"
// #include "Content.hpp"
// #include "FacesGroup.hpp"
// #include "FreeflyCamera.hpp"
// #include "IHM.hpp"
// #include "Loader.hpp"
// #include "Obstacle.hpp"
// #include "Object.hpp"
// #include "ObjectProgram.hpp"
// #include "Texture.hpp"
// #include "TrackballCamera.hpp"

#include "GameEnvironment.hpp"

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
    glDisable(GL_CULL_FACE) ;

    GameEnvironment game; 

    game.initScene();

/* ---------------------------------------------------------------------------- */
/* ------------------ Declare your infinite update loop ----------------------- */
/* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.7f, 0.6f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game.render(ctx);
        game.inputManagement(ctx);
        game.cameraManagement(ctx);

    };

    ctx.start();
    game.deleteScene();
}