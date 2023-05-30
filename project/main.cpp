#include <map>
#include <vector>
#include "GameEnvironment.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

/* ---------------------------------------------------------------------------- */
/* --------------------------------- MAIN ------------------------------------- */
/* ---------------------------------------------------------------------------- */
int main()
{
    int  windowWidth  = 1280;
    int  windowHeight = 720;
    auto ctx          = p6::Context{{windowWidth, windowHeight, "Project qui se passe super bien"}};
    ctx.maximize_window();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    GameEnvironment game(windowWidth, windowHeight);

    game.initScene(ctx);

    /* ---------------------------------------------------------------------------- */
    /* ------------------ Declare your infinite update loop ----------------------- */
    /* ---------------------------------------------------------------------------- */
    ctx.update = [&]() {
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game.environmentManagement();
        game.render(ctx);
    };

    ctx.start();
    game.deleteScene();
}