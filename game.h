#ifndef GAME_H
#define GAME_H

#include <string>
#include <set>
#include "player.h"

// default number of turns
#ifndef TURNS
#define TURNS 6
#endif

void turn(Player& player, std::set<std::string>* wordList);
void switchTurns(std::string n1, std::string n2, int gamemode);
std::string gamemode2setup(std::string n1, std::string n2, std::set<std::string>* wordList);
void showGameResult(Player& p1, Player& p2, int gamemode);

#endif