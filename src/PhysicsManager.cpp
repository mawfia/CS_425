#pragma once

#include <math.h>

#include "Component.h"
#include "ScriptManager.h"
#include "Engine.h"



using namespace std;

namespace engine {

	void PhysicsManager::CheckBoundaries() {



	}

    float PhysicsManager::CheckDistance(Sprite& s1, Sprite& s2) {


        float dx = s1.x - s2.x;
        float dy = s1.y - s2.y;

        return sqrt( (dx * dx) + (dy * dy) );
    }

	void PhysicsManager::Update() {

        engine->ECS.ForEach<Sprite, Health>([&](EntityID id) {

            // Check boundaries
            auto& entity = engine->ECS.Get<Sprite>(id);

            if (entity.x > .9) entity.x = 0.9;
            if (entity.x < -.9) entity.x = -0.9;
            if (entity.y > .9) entity.y = 0.9;
            if (entity.y < -.9) entity.y = -0.9;


            //Check collisions
            if (entity.name == "enemy") {


                engine->ECS.ForEach<Sprite, Health>([&](EntityID id2) {

                    auto& entity2 = engine->ECS.Get<Sprite>(id2);

                    if (entity2.name == "missile" || entity2.name == "spaceship") {


                        bool collisionX = entity.x + entity.scale >= entity2.x - entity2.scale && entity2.x + entity2.scale >= entity.x - entity.scale;
                        bool collisionY = entity.y + entity.scale >= entity2.y - entity2.scale && entity2.y + entity2.scale >= entity.y - entity.scale;

                        if (collisionX && collisionY) {

                            engine->ECS.Get<Health>(id).percent = 0;
                            engine->ECS.Get<Health>(id2).percent = 0;

                        }


                    }

                    if (entity2.name == "enemy" && id != id2) {


                        float d = CheckDistance(entity, entity2);

                    }


                });

            }

        });

	}

}