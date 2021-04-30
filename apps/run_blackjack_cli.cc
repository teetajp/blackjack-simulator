#include <iostream>

#include <core/game_engine.h>
#include <map>

using blackjack::GameEngine;
using blackjack::GameStatus;
using std::map;
using std::cin;
using std::cout;

// todo: put all helpers in blackjack_cli.cc

/** Function Prototypes */

void AddPlayers(GameEngine& engine);
void RequestBets(GameEngine& engine);

/** Main method */
int main() {
  GameEngine engine;
  AddPlayers(engine); // Players can only be added at the start of the round
  while (true) {
    // Ask user(s) whether to continue the game
    cout << "Press any button to continue. n to exit." << std::endl;
    string arg;
    cin >> arg;
    if (arg == "n")
      break;
    // Ask player for bets
    RequestBets(engine);
//    engine.ShuffleDeck();
//    engine.DealCards();
//    
//    if (!engine.CheckBlackjack()) {
//      // Enters this if statement when dealer doesn't have blackjack and action from players is needed
//      engine.PlayerPlays(cin);
//      engine.DealerPlays();
//      engine.SettleBets();
//    } else {
//      // display hands
//    }
//    engine.ResetHands();
  }
  
  
}

/** Helper function implementations */

void AddPlayers(GameEngine& engine) {
  size_t n_players;
  cout << "Specify Number of Players:";
  cin >> n_players;
  for (size_t i = 0; i < n_players; i++) {
    cout << "Player " << i + 1 << std::endl;
    cout << "Name:";
    string name = "";
    cin >> name;
    cout << "Buy-in ($):";
    float buy_in = 0;
    cin >> buy_in;
    engine.AddPlayer(name, buy_in);
  }
}

void RequestBets(GameEngine& engine) {
  GameStatus status = engine.GetGameStatus();
  map<string, float> bets;
  
  cout << "Each player must place a bet.";
  for (auto player : status.players) {
    cout << std::endl << "Player: " << player->GetName() << "'s Bet:";
    float bet = 0;
    cin >> bet;
    bets[player->GetName()] = bet;
  }
  engine.PlaceBets(bets);
}