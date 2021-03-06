#include "worldmanager.h"
#include "readFile.h"
#include <stdexcept>
using namespace std;
WorldManager::WorldManager():
    simulator(4,5)
{
    this->gravity=Vector2(0,-10);
    this->dt=0.02;
    debugDraw=true;
    debugDrawer=0;
}

void WorldManager::OneStep()
{
    shapeManager.applyGravity(gravity);
    std::vector<MyShape*> shapeList=shapeManager.getShapeList();
    simulator.solve(shapeList,dt,debugDrawer);
    shapeManager.clearAllForce();

}

void WorldManager::readFile(std::string fileName)
{
    FileReader reader;
    FileWorldDefinition fSetting;
    reader.readFile(fileName,fSetting,shapeManager);
    gravity=fSetting.gravity;
    recommendFrameTime=1/fSetting.frequency;
    dt=recommendFrameTime*fSetting.speed;
    if(fSetting.debugMode!=0){
        if(debugDrawer==0){
            std::cout<<"please give a DebugDrawer to WorldManager before readFile"<<std::endl;
            throw logic_error("please give a DebugDrawer to WorldManager before readFile");
        }
        simulator.turnOnDebugDraw();
    }
}

std::vector<MyShape *> WorldManager::getShapeList()
{
    return shapeManager.getShapeList();
}

void WorldManager::setDebugDrawer(GraphicManager *debugDrawer)
{
    this->debugDrawer=debugDrawer;
}

void WorldManager::turnOnDebugDraw()
{
    if(debugDrawer==0){
        std::cout<<"please give a DebugDrawer to WorldManager"<<std::endl;
        exit(0);
    }
    simulator.turnOnDebugDraw();
}

void WorldManager::turnOffDebugDraw()
{
    simulator.turnOffDebugDraw();
}

