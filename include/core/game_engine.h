#pragma once

#include <core/card.h>
#include <core/deck.h>
#include <core/dealer.h>
#include <core/player.h>
#include <vector>
#include <iostream>
#include <map>


using std::map;
using std::istream;
using std::vector;

namespace blackjack {

/** Holds the information that the client needs to know to interact with the engine */
struct GameStatus {
  vector<const Player*> players; // all the players and their information
  const Hand* dealers_hand; // the cards in the dealer's hand
  const Player* player_to_act; // the player whose turn it is to act
};


/**
 * The Game Engine class runs the game, taking in input from the user and outputting the results
 * For each round, the players has to first post their bets. Then the dealer deals the 2 cards to each player and finally to himself.
 * If any player hits blackjack (has an Ace and a ten-card) for the first two cards, and the dealer does not, the player gets paid 2:1 their bet amount.
 * If the dealer checks and has blackjack, the dealer collects all bet except any player who also hit blackjack, which they split.
 * If no blackjack by dealer, then the player can hit, stand, or double down. If the player gets over 21, then they bust, losing their bet.
 * Once the player stands or busts, the dealer stands if he has 17 or over, and if its 16 or under or a soft 17, the dealer must hit.
 * If the dealer does not bust, then the dealer pays anyone who has more than the dealer. Any player with the same total as the dealer keeps their bet.
 * Any player with a total less than the dealer loses their bet.
 */
class GameEngine {
 public:
  /** Default Constructor */
  GameEngine();

  /** Adds a player to the game
   * 
   * @param name the name of the player
   * @param buy_in how much chips the player wants to buy and play with
   */
  void AddPlayer(const string& name, float buy_in);

  /** Shuffles the current deck */
  void ShuffleDeck();

  /** Updates the players' bet
   * 
   * @param bets a mapping of player name to their bet
   */
  void PlaceBets(map<string, float>& bets);

  /** Deals cards to all the players in order then the dealer */
  void DealCards();

  /** Checks whether the dealer has blackjack, if the dealer does,
   *  then settle the bets with the players depending on whether player also has blackjack.
   *  If dealer doesn't have blackjack, then pay any player with blackjack off accordingly.
   * 
   * @return true if the dealer has blackjack (implies round would be over), false otherwise.
   */
  bool PayBlackjacks();

  /** Calls the players, in order, to take hit, stand, or double down */ // todo: edit doc
  void PlayerPlays(string command);

  /** Calls the dealer to hit or stand until they reach a hand total of 17 or more */
  void DealerPlays();

  /** Check whether each player won, lost/bust, or push and pay/take their bets accordingly */
  void SettleBets();
  
  /** Resets the dealer's and all the players' hand */
  void ResetHands();
  
  /** Gets the status of the game, including each player's information and dealer's hand */
  GameStatus GetGameStatus();
  
  /** Loads the card textures into each card in the deck */
  void LoadTextures();
  
 private:
  Deck deck_; // deck of cards in play
  Dealer dealer_; // the person assigned as dealer
  vector<Player> players_; // the players who are playing in the round
  Player* current_player; // player whose turn it is
};
} // namespace blackjack