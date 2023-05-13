// Created by Wayne Cole on 4/19/2023.
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

//practicing with file i/o

/*
struct Attributes
{
    int might;
    int accuracy;
    int endurance;
    int HP;
    int AC;
    int Level;
};

class Object{
public:
    enum class Type { Slime, Sprite, Orc, Dragon, Player };

    Type name;
    Attributes stats;
};

std::string printType(Object::Type name)
{
    switch(name)
    {
        case Object::Type::Slime:
            return "Slime";
            break;
        case Object::Type::Sprite:
            return "Sprite";
            break;
        case Object::Type::Orc:
            return "Orc";
            break;
        case Object::Type::Dragon:
            return "Dragon";
            break;
        case Object::Type::Player:
            return "Player";
            break;
    }
}

void print_monsters(std::vector<Object> &monsters, int i)
{
    std::cout << "Object::Type::" << printType(monsters.at(i).name) << " " << monsters.at(i).stats.AC << " " << monsters.at(i).stats.accuracy << " " << monsters.at(i).stats.endurance << " " << monsters.at(i).stats.HP << " " << monsters.at(i).stats.Level << " " << monsters.at(i).stats.might << std::endl;
}

int main()
{
    std::vector<Object> monsters;

    monsters.push_back(Object());
    monsters.back().name = Object::Type::Dragon;
    monsters.back().stats.AC = 5;
    monsters.back().stats.accuracy = 10;
    monsters.back().stats.endurance = 25;
    monsters.back().stats.HP = 50;
    monsters.back().stats.Level = 2;
    monsters.back().stats.might = 13;

    monsters.push_back(Object());
    monsters.back().name = Object::Type::Orc;
    monsters.back().stats.AC = 3;
    monsters.back().stats.accuracy = 2;
    monsters.back().stats.endurance = 17;
    monsters.back().stats.HP = 35;
    monsters.back().stats.Level = 1;
    monsters.back().stats.might = 9;

    monsters.push_back(Object());
    monsters.back().name = Object::Type::Slime;
    monsters.back().stats.AC = 0;
    monsters.back().stats.accuracy = 2;
    monsters.back().stats.endurance = 1;
    monsters.back().stats.HP = 5;
    monsters.back().stats.Level = 3;
    monsters.back().stats.might = 2;

    monsters.push_back(Object());
    monsters.back().name = Object::Type::Sprite;
    monsters.back().stats.AC = 2;
    monsters.back().stats.accuracy = 87;
    monsters.back().stats.endurance = 0;
    monsters.back().stats.HP = 2;
    monsters.back().stats.Level = 5;
    monsters.back().stats.might = 1;

    monsters.push_back(Object());
    monsters.back().name = Object::Type::Player;
    monsters.back().stats.AC = 3;
    monsters.back().stats.accuracy = 4;
    monsters.back().stats.endurance = 15;
    monsters.back().stats.HP = 30;
    monsters.back().stats.Level = 3;
    monsters.back().stats.might = 7;

    */
/*std::vector<int> monsters;
    monsters.push_back(5);
    monsters.push_back(6);
    monsters.push_back(7);
    monsters.push_back(8);
    monsters.push_back(9);
    monsters.push_back(10);
    monsters.push_back(11);*//*


    */
/*std::ofstream gameLoad;
    std::string gameInformation = "gameinfo.txt";
    gameLoad.open(gameInformation);
    if(!gameLoad.is_open())
    {
        std::cout << "Error! File'" << gameInformation << "' could not be opened.";
        return 1;
    }
    std::ostream_iterator<int> out_iterator(gameLoad, "\n");
    std::copy(monsters.begin(), monsters.end(), out_iterator);
    gameLoad.close();*//*



    for(int i = 0; i < monsters.size(); i++)              //outputs contents onto screen for viewing
    {
        print_monsters(monsters, i);
    }
    return 0;
}
*/
