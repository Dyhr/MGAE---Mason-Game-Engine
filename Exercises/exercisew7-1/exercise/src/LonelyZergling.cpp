#include "LonelyZergling.hpp"
#include <iostream>

LonelyZergling::LonelyZergling(GameObject *gameObject):Component(gameObject)
{
}



void LonelyZergling::Burrow(){
    std::cout << "This zergling used Burrow, it was very effective"<<std::endl;
}