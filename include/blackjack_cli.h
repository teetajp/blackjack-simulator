#include <iostream>

#include <core/game_engine.h>

using blackjack::GameEngine;
using std::cin;
using std::cout;



void AddPlayers(GameEngine& engine) {
  size_t n_players;
  cout << "Specify Number of Players: ";
  cin >> n_players;
  cout << endl;
  
  for (size_t i = 0; i < n_players; i++) {
    cout << "Player " << i + 1 << std::endl;
    cout << "Name: ";
    string name = "";
    cin >> name;
    cout << std::endl << "Buy-in ($): ";
    size_t buy_in = 0;
    cin >> buy_in;
    engine.AddPlayer(name, buy_in);
  }
}