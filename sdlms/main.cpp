#include <SDL2/SDL.h>
#include <stdio.h>
#include "Core/World.h"
#include "Systems/RenderSystem.h"
#include "Systems/SoundSystem.h"
#include "Systems/UpdateSystem.h"
#include "Systems/CameraSystem.h"
#include "Systems/PhysicSystem.h"
#include "Systems/PlayerSystem.h"
#include "Components/Sound.h"
#include "Components/Camera.h"
#include "Components/Player.h"
#include "Components/Physic/Normal.h"
#include "Entities/Character.h"
#include "Core/Map.h"
#include "Core/FreeType.h"
#include "Resource/Wz.h"

int width = 1366;
int height = 768;

int main(int argc, char *argv[])
{
    World world;
    Wz *wz = new Wz("./Data/"); // wz文件路径
    world.add_resource(wz);

    Window::create_window("sdlMS", width, height);

    FreeType::init();

    Map *map = new Map(&world);
    map->load_map(104000000);

    SoundSystem sous{};
    world.add_system(&sous);

    PlayerSystem plas{};
    world.add_system(&plas);

    PhysicSystem phys{};
    world.add_system(&phys);

    CameraSystem cams{};
    world.add_system(&cams);

    UpdateSystem upd{};
    world.add_system(&upd);

    RenderSystem rsys{};
    world.add_system(&rsys);

    Character *cha = new Character(&world);
    Transform *t = new Transform{(float)0, (float)0};
    Camera *camera = new Camera(0, 0, width, height);
    Normal *nor = new Normal();
    Player *pla = new Player(); //玩家控制的角色
    cha->add_component(t);
    cha->add_component(camera);
    cha->add_component(nor);
    cha->add_component(pla);
    world.add_component(t, 3000000);
    world.add_component(camera, 0);
    world.add_component(nor);
    world.add_component(pla);

    while (!world.is_game_quit())
    {

        world.poll_events();
        world.tick_delta_time();

        Window::clear();

        world.process_systems();

        Window::update();

        // SDL_Delay(20); // 控制帧率
    }
    return 0;
}