#include "function.h"
#include <bits/stdc++.h>

using namespace std;

Animal::Animal(Zoo *zoo, string name) : belong(zoo), species(name)
{
    zoo->born(name);
}; // TODO

Dog::Dog(Zoo *zoo) : Animal(zoo, "Dog"){}; // TODO
Dog::~Dog(){};                             // TODO

Cat::Cat(Zoo *zoo) : Animal(zoo, "Cat"){}; // TODO
Cat::~Cat(){};                             // TODO

Caog::Caog(Zoo *zoo) : Animal(zoo, "Caog"), Dog(zoo), Cat(zoo){}; // TODO
void Caog::barking()
{
    cout << "woof!woof!meow!\n";
} // TODO
void Caog::carton()
{
    cout << "it looks so happy!\n";
} // TODO
void Caog::throwBall()
{
    cout << "it looks happy!\n";
} // TODO
Caog::~Caog(){}; // TODO