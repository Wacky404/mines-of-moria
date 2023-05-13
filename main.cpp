#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

//Left Off: All I need to do is the .txt file

struct Attributes
{
    int might;
    int accuracy;
    int endurance;
    int HP;
    int AC;
    int Level;
};

class Object
{
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

void loadGame(Object temp, std::vector<Object> &monsters)
{
    std::ifstream gameload;
    std::string fileName = "gamesave.txt";
    gameload.open (fileName, std::ios::in);
    if(!gameload.is_open())
    {
        std::cout << "Error. File '" << fileName << "' couldn't be opened." << std::endl;
        EXIT_FAILURE;
    }

    //gameload >> reinterpret_cast<unsigned char &>(temp.name);
    int j = 0;
    while(gameload >> reinterpret_cast<unsigned char &>(temp.name) >> temp.stats.AC >> temp.stats.accuracy >> temp.stats.endurance >> temp.stats.HP >> temp.stats.Level >> temp.stats.might)
    {
        monsters.at(j) = temp;
        j++;
    }
    /*for(int i = 1; i < 5; i++)
    {
        gameload >> reinterpret_cast<unsigned char &>(temp.name) >> temp.stats.AC >> temp.stats.accuracy >> temp.stats.endurance >> temp.stats.HP >> temp.stats.Level >> temp.stats.might;
        monsters.at(i -1) = temp;
    }*/
    gameload.close();

}

void saveGame(std::vector<Object> &monsters)
{
    std::string fileName = "gamesave.txt";
    std::fstream gamesave;
    gamesave.open(fileName, std::ofstream::out | std::ofstream::trunc); // append here if I don't need to truncate file
    if(!gamesave.is_open())
    {
        std::cout << "Error. File '" << fileName << "' couldn't be opened." << std::endl;
        EXIT_FAILURE;
    }
    for(auto & monster : monsters)
    {
        gamesave << printType(monster.name) << " " << monster.stats.AC << " " << monster.stats.accuracy << " " << monster.stats.endurance << " " << monster.stats.HP << " " << monster.stats.Level << " " << monster.stats.might << std::endl;
    }
    gamesave.close();
}

void displayBattle(std::vector<Object> monsters) //this will be used as user option
{
    std::cout << "(" << printType(monsters.at(4).name) << ")" << " " << "Level: " << monsters.at(4).stats.Level << "\n";
    std::cout << "Monster and Player health: \n";
    for(int i = 0; i < monsters.size(); i++)
    {
        std::cout << " " << i << ")" << printType(monsters.at(i).name) << ": " << monsters.at(i).stats.HP << " HP" << "\n";
        if(monsters.at(i).stats.HP <= 0)
        {
            std::cout << "  " << printType(monsters.at(i).name) << " is DEAD\n";
        }
    }
}

void defend(std::vector<Object> &monsters, int randDamage, int j, int &playerAttacked)
{
    std::random_device seed;
    std::default_random_engine e(seed());

    if(playerAttacked == 0)
    {
        std::uniform_int_distribution objectDefense(monsters.at(4).stats.AC, monsters.at(4).stats.Level);
        int givenDefense = objectDefense(e);
        randDamage = randDamage - givenDefense;
        while(randDamage < 0 || randDamage > 29)
        {
            int reset = objectDefense(e);
            int givenDefense =  reset;
            randDamage = randDamage - givenDefense;
        }

        std::string verb2 = "damage to";
        std::cout << randDamage << " " << verb2 << " " << printType(monsters.at(4).name) << std::endl;
        monsters.at(4).stats.HP = monsters.at(j).stats.HP - randDamage;
    }
    if (playerAttacked != 0)
    {
        j = playerAttacked - 1;
        std::uniform_int_distribution objectDefense(monsters.at(j).stats.AC, monsters.at(j).stats.Level);
        int givenDefense = objectDefense(e);
        randDamage = randDamage - givenDefense;
        while(randDamage < 0 || randDamage > 45)
        {
            int reset = objectDefense(e);
            int givenDefense =  reset;
            randDamage = randDamage - givenDefense;
        }

        std::string verb2 = "damage to";
        std::cout << randDamage << " " << verb2 << " " << printType(monsters.at(j).name) << std::endl;
        monsters.at(j).stats.HP = monsters.at(j).stats.HP - randDamage;
    }
}

void attack(std::vector<Object> &monsters, int j, int &playerAttacked)
{
    std::random_device seed;
    std::default_random_engine e(seed());
    int numDamage = 1 / monsters.at(j).stats.accuracy;
    int monsterMight = monsters.at(j).stats.might;
    std::normal_distribution<> damageDone(monsterMight, numDamage);

    int randDamage = damageDone(e);
    std::string verb = "deals";
    std::cout << printType(monsters.at(j).name) << " " << verb << " ";

    defend(monsters, randDamage, j, playerAttacked);
}

void heal(std::vector<Object> &monsters) //this will be used as user option
{
    monsters.at(4).stats.HP = monsters.at(4).stats.HP + monsters.at(4).stats.endurance;
    std::cout << printType(monsters.at(4).name) << " is healed by " << monsters.at(4).stats.HP << " HP" << std::endl;
}

bool monsterAttack(std::vector<Object> &monsters)
{
    for(int j = 0; j < monsters.size(); j++)
    {
        if(monsters.at(j).stats.HP > 0 && j != 4)
        {
            int playerAttacked = 0;
            attack(monsters, j, playerAttacked);
            return false;
        }
        if(j == monsters.size())
        {
            return true;
        }
    }
}

void playerAttack(std::vector<Object> &monsters) //this will be used as user option
{
    std::cout << "Choose who to attack!: 1)" << printType(monsters.at(0).name) << " " << "2)" << printType(monsters.at(1).name) << " " << "3)" << printType(monsters.at(2).name) << " " << "4)" << printType(monsters.at(3).name) << "\n";
    int playerAttacked{};
    std::cin >> playerAttacked;

    int j = 4;
    attack(monsters, j, playerAttacked);
}

int main()
{
    Object temp{};
    std::vector<Object> monsters;

    /*std::ifstream gameload;
    std::string fileName = "gamesave.txt";
    gameload.open (fileName, std::ios::in);
    if(!gameload.is_open())
    {
        std::cout << "Error. File '" << fileName << "' couldn't be opened." << std::endl;
        EXIT_FAILURE;
    }
    gameload.seekg(0, std::ios::end);
    std::size_t size = gameload.tellg();
    if (size == 0)
    {
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
    }
    gameload.close();*/

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

    std::cout << "Welcome to Mines of Moria!!!" << std::endl;
    std::cout << "===================================================================================================================================" << std::endl;
    std::cout << "Would you like to: 1 ---> Start a new game| 2 ---> Load a game\n";
    int gameChoice{};
    std::cin >> gameChoice;

    switch(gameChoice)
    {
        case 1:
            goto Newgame;
            break;
        case 2:
            loadGame(temp,monsters);
            goto Startgame;
            break;
        default:
            return 1;
    }

    Newgame:
        std::cout << "===================================================================================================================================" << std::endl;
        std::cout << "Mines of Moria\n";
        std::cout << "You are taking an unexpected journey to Erebor, a great Kingdom to the Dwarves that was lost to Smaug.\n";
        std::cout << "Smaug is a great dragon that overtook the Kingdom from its dwarven inhibitors. You are with a group that is tasked to take it back.\n";
        std::cout << "But you have been split from the company in the mines of Moria and must fight your way through to the other side." << std::endl;
        std::cout << "===================================================================================================================================" << std::endl;

    Startgame:
    std::cout << "You are walking down a long dark corridor, you hear something up ahead.\n";
    std::cout << "MONSTERS HAVE APPEARED!" << std::endl;

    bool exit{true};
    Exit:
    while(exit)
    {
            UI:
            std::cout << "===================================================================================================================================" << std::endl;
            std::cout << "What will you do? 1 ---> Attack!| 2 ---> Heal!| 3 ---> Run Away!| 4 ---> Display Battle.| 5 ---> Exit Game.\n";
            int battleChoice{};
            std::cin >> battleChoice;

            if(battleChoice == 5)
            {
                exit = false;
                goto Exit;
            }

            switch(battleChoice)
            {
                case 1:
                    playerAttack(monsters);
                    break;
                case 2:
                    heal(monsters);
                    break;
                case 3:
                    std::cout << "You died a cowards death. Better to muster your courage and face your challenge head on!" << std::endl;
                    break;
                case 4:
                    break;
                default:
                    return 1;
            }
            if(battleChoice == 3)
            {
                exit = false;
                goto Exit;
            }
            if(battleChoice == 4)
            {
                displayBattle(monsters);
                goto UI;
            }
            std::cout << "===================================================================================================================================" << std::endl;
            std::cout << "A monster is targeting you and preparing to attack!" << std::endl;
            if(monsterAttack(monsters))
            {
                std::cout << "You have defeated all the monsters. Now run for the EXIT!" << std::endl;
                exit = false;
            }
            if(monsters.at(4).stats.HP <= 0)
            {
                std::cout << "YOU ARE DEAD!\n";
                monsters.at(4).stats.HP = 35;
                exit = false;
            }
    }
    saveGame(monsters);
    std::cout << "Thank you for playing: Mines of Moria" << std::endl;
    return 0;
}
