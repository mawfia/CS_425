#pragma once

#include <math.h>

#include "Component.h"
#include "ScriptManager.h"
#include "Engine.h"

#define PI 3.14159265359


using namespace std;

namespace engine {

	void PhysicsManager::CheckBoundaries() {



	}

    void PhysicsManager::Separation(EntityID id1, EntityID id2) {
        
        Pvector location1 = engine->ECS.Get<Sprite>(id1).GetLocation();
        //Velocity entity1_v = engine->ECS.Get<Velocity>(id1);

        Pvector location2 = engine->ECS.Get<Sprite>(id2).GetLocation();

        //Pvector location1(entity1.x, entity1.y);
        //Pvector location2(entity2.x, entity2.y);
        Pvector velocity1 = engine->ECS.Get<Velocity>(id1).Get(); //(entity1_v.x, entity1_v.y);

        float d = location1.distance(location2);

        if ((d > 0) && (d < desiredSeparation)) {
            Pvector diff(0, 0);
            diff = diff.subTwoVector(location1, location2);
            diff.normalize();
            diff.divScalar(d);
            separation.addVector(diff);
            separation_count++;
        }

    }

    void PhysicsManager::Alignment(EntityID id1, EntityID id2) {
        
        Sprite entity1 = engine->ECS.Get<Sprite>(id1);
        Velocity entity1_v = engine->ECS.Get<Velocity>(id1);
        Sprite entity2 = engine->ECS.Get<Sprite>(id2);
        Velocity entity2_v = engine->ECS.Get<Velocity>(id2);

        Pvector location1(entity1.x, entity1.y);
        Pvector location2(entity2.x, entity2.y);
        Pvector velocity1(entity1_v.x, entity1_v.y);
        Pvector velocity2(entity2_v.x, entity2_v.y);

        float d = location1.distance(location2);

        if ((d > 0) && (d < neighbordist)) {
            alignment.addVector(velocity2);
            alignment_count++;
        }
    }

    void PhysicsManager::Cohesion(EntityID id1, EntityID id2) {

        //Sprite entity1 = 
        //Sprite entity2 = engine->ECS.Get<Sprite>(id2);

        Pvector location1 = engine->ECS.Get<Sprite>(id1).GetLocation();  //(entity1.x, entity1.y);
        Pvector location2 = engine->ECS.Get<Sprite>(id2).GetLocation(); //(entity2.x, entity2.y);

        float d = location1.distance(location2);

        if ((d > 0) && (d < neighbordist)) {
            cohesion.addVector(location2);
            cohesion_count++;
        }
    }

    Pvector PhysicsManager::Seek(EntityID id) {

        Velocity entity_v = engine->ECS.Get<Velocity>(id);
        Pvector velocity(entity_v.x, entity_v.y);

        Acceleration entity_a = engine->ECS.Get<Acceleration>(id);
        Pvector acceleration(entity_a.x, entity_a.y);

        Pvector desired;

        desired.subVector(cohesion);
        desired.normalize();
        desired.mulScalar(maxSpeed);

        acceleration.subTwoVector(desired, velocity);
        acceleration.limit(maxForce);
        return acceleration;
    }

    float PhysicsManager::Angle(const Pvector& v) {

        return (float)(atan2(v.x, -v.y) * 180 / PI);
    }

	void PhysicsManager::Update() {

        maxSpeed = engine->script.lua["maxSpeed"];
        maxForce = engine->script.lua["maxForce"];
        desiredSeparation = engine->script.lua["desiredSeparation"];
        neighbordist = engine->script.lua["neighbordist"];

        engine->ECS.ForEach<Sprite, Health>([&](EntityID id) {

            auto& entity = engine->ECS.Get<Sprite>(id);
            auto& entity_v = engine->ECS.Get<Velocity>(id);
            auto& entity_a = engine->ECS.Get<Acceleration>(id);

            // Check user boundaries
            if (entity.name == "spaceship") {
                if (entity.x > .9) entity.x = 0.9;
                if (entity.x < -.9) entity.x = -0.9;
                if (entity.y > .9) entity.y = 0.9;
                if (entity.y < -.9) entity.y = -0.9;
            }
       
            if (entity.name == "enemy") {

                //Check non-user collisions
                if (entity.x > .9) entity_v.x = -entity_v.x;
                if (entity.x < -.9) entity_v.x = -entity_v.x;
                if (entity.y > .9) entity_v.y = -entity_v.y;
                if (entity.y < -.9) entity_v.y = -entity_v.y;


                separation.set(0, 0);
                separation_count = 0;
                alignment.set(0, 0);
                alignment_count = 0;
                cohesion_count = 0;
                cohesion.set(0, 0);

                Pvector velocity1(entity_v.x, entity_v.y);
                Pvector location1(entity.x, entity.y);
                Pvector acceleration1(entity_a.x, entity_a.y);

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

                        Separation(id, id2);
                        Alignment(id, id2);
                        Cohesion(id, id2);
                    }


                });

                // Finish Separation Calculations
                if (separation_count > 0) separation.divScalar((float)separation_count);

                if (separation.magnitude() > 0) {
                    separation.normalize();
                    separation.mulScalar(maxSpeed);
                    separation.subVector(velocity1);
                    separation.limit(maxForce);
                }

                
                // Finish Alignment Calculations
                if (alignment_count > 0) {
                    alignment.divScalar((float)alignment_count);
                    alignment.normalize();
                    alignment.mulScalar(maxSpeed);

                    alignment = alignment.subTwoVector(alignment, velocity1);
                    alignment.limit(maxForce);
                }
                else {
                    alignment.set(0, 0);
                }

                // Finish Cohesion Calculations
                if (cohesion_count > 0) {
                    cohesion.divScalar(cohesion_count);
                    cohesion = Seek(id);
                }
                else {
                    cohesion.set(0, 0);
                }

                // Arbitrarily weight these forces
                separation.mulScalar(.035);
                alignment.mulScalar(.015);
                cohesion.mulScalar(.015);

                

                // Apply Force to current force vector
                acceleration1.addVector(separation);
                acceleration1.addVector(alignment);
                acceleration1.addVector(cohesion);


                // Modifies velocity, location, and acceleration with the three laws applied
                acceleration1.mulScalar(0.4);
                velocity1.addVector(acceleration1);
                velocity1.limit(maxSpeed);
                location1.addVector(velocity1);
                acceleration1.mulScalar(0);
                
                

                entity.SetLocation(location1);
                entity_v.Set(velocity1);
                entity_a.Set(acceleration1);

                entity.rotate = Angle(velocity1);

            }
        });

	}

}