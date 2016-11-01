#include <cassert>


#include "Scene.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include "LonelyZergling.hpp"

int main(int argc, char** argv) {
    Scene scene;
    auto gameObjectLZ = scene.addGameObject("LonelyZergling");
    auto gameObjectEmpty = scene.addGameObject("Empty");
    auto componentLZ = gameObjectLZ->addComponent<LonelyZergling>();
    auto componentLZOtherReference = gameObjectLZ->getComponent<LonelyZergling>();

    assert(componentLZ == componentLZOtherReference);

    componentLZ->Burrow();

    auto lzs = scene.getAllComponent<LonelyZergling>();
    assert(lzs.size() == 1);

    gameObjectLZ->removeComponent(componentLZ);
    componentLZOtherReference = gameObjectLZ->getComponent<LonelyZergling>();
    assert(componentLZOtherReference.get() == nullptr);

    componentLZOtherReference = gameObjectEmpty->getComponent<LonelyZergling>();
    assert(componentLZOtherReference.get() == nullptr);


    return 0;
}