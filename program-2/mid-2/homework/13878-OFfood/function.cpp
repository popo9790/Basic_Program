#include "function.h"
#include <bits/stdc++.h>

using namespace std;

// constructor
Food::Food()
    : name(""), fly(0), pos(){};

Food::Food(string &foodname)
    : name(foodname), fly(0), pos(){};

// copy constructor
Food::Food(const Food &sub)
    : name(sub.name), fly(sub.fly), pos(sub.pos){};

// functions
// floor = 0; stomac = 1; trash can = 2;
// eaten: the food is eaten, change its position
// thrown: the food is thrown, change its position
// on_floor: return whether the food is on the floor
// get_name: return the Food's name
// get_fly: return the amount of the fly

void Food::eaten()
{
    this->pos = STOMACH;
}

void Food::thrown()
{
    this->pos = TRASHCAN;
}

bool Food::on_floor()
{
    return this->pos == FLOOR;
}

string Food::get_name()
{
    return this->name;
}

int Food::get_fly()
{
    return this->fly;
}

// operators
// < : use this operator to sort the food so the output of on-floor food satisfy the requirement
// == : determine whether the food's name is same as a string
// << : output the food as the mentioned output format
bool Food::operator<(const Food &sub) const
{
    if (this->pos < sub.pos) // let on-floor to front
        return 1;

    int ret = this->name.compare(sub.name);

    if (this->pos == sub.pos && ret < 0) // 相等才比字典旭
        return 1;
    return 0;
}

bool Food::operator==(const string &sub)
{
    return this->name == sub;
}

ostream &operator<<(ostream &output, Food tmp)
{
    output << tmp.get_name();
    return output;
}

Fruit::Fruit()
    : Food(){};

Fruit::Fruit(string &foodname)
    : Food(foodname){};

// five_min_pass: 5 min passes
// sickness: return whether the fruit makes someone sick
// += : mix the food together
void Fruit::five_min_pass()
{
    if (this->pos == FLOOR)
        this->fly += 4;
}

bool Fruit::sickness()
{
    return this->fly >= 10 && this->pos == STOMACH;
}

void Fruit::operator+=(Fruit &sub)
{
    this->fly += sub.get_fly();
    this->name = sub.get_name() + this->name; // 重點！！
}

void Fruit::operator+=(Meat &sub)
{
    this->fly += sub.get_fly();
    this->name = sub.get_name() + this->name;
}

Meat::Meat()
    : Food(){};

Meat::Meat(string &foodname)
    : Food(foodname){};

// five_min_pass: 5 min passes
// sickness: return whether the meat makes someone sick
// += : mix the food together
void Meat::five_min_pass()
{
    if (this->pos == FLOOR)
        this->fly += 5;
}

bool Meat::sickness()
{
    return this->fly >= 20 && this->pos == STOMACH;
}

void Meat::operator+=(Fruit &sub)
{
    this->fly += sub.get_fly();
    this->name = sub.get_name() + this->name;
}

void Meat::operator+=(Meat &sub)
{
    this->fly += sub.get_fly();
    this->name = sub.get_name() + this->name;
}