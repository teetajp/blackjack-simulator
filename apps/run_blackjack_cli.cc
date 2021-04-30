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
void DisplayPostRoundInfo(GameEngine& engine);
void PrintHand(string name, const blackjack::Hand& hand);

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
    
    RequestBets(engine);
    
    engine.ShuffleDeck();
    engine.DealCards();

    if (engine.PayBlackjacks()) {
      // Dealer has blackjack and the bets are settled. Now we just need to display the cards
      cout << "Dealer has blackjack. Bets are settled accordingly.";
    } else {
      // Enters this if statement when dealer doesn't have blackjack and action from players is needed
//      engine.PlayerPlays(cin);
//      engine.DealerPlays();
//      engine.SettleBets();
    }
    DisplayPostRoundInfo(engine);
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
  // todo: implement error handling
  GameStatus status = engine.GetGameStatus();
  map<string, float> bets;
  
  cout << "Each player must place a bet." << std::endl;
  for (auto player : status.players) {
    cout << "Player " << player->GetName() << "'s Bet:";
    float bet = 0;
    cin >> bet;
    bets[player->GetName()] = bet;
  }
  cout << std::endl;
  engine.PlaceBets(bets);
}

void DisplayPostRoundInfo(GameEngine& engine) {
  GameStatus status = engine.GetGameStatus();

  PrintHand("Dealer", *status.dealers_hand);
  cout << "----------------------" << std::endl;
  
  for (auto player : status.players) {
    cout << "Player " << player->GetName() << std::endl;
    cout << "Balance: " << player->GetBalance() << std::endl;
    PrintHand(player->GetName(), player->GetHand());
    cout << "Result: " << player->ResultToString() << std::endl;
    cout << "----------------------" << std::endl;
  }
}

void PrintHand(string name, const blackjack::Hand& hand){
  cout << name << "'s cards: ";
  
  // Print all the cards
  for (auto card : hand.GetCards()) {
    cout << card.ToString();
    
    if (card != hand.GetCards().back()) {
       cout << ", ";
    } else {
      cout << std::endl;
    }
  }
  
  cout << "Hand Value: " << hand.CalculateHandValue() << std::endl;
  
  if (hand.HasBlackjack()) {
    cout << name << " has blackjack." << std::endl;
    cout << "----------------------" << std::endl;
  }
}