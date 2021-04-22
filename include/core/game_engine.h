#pragma once

#include <core/card.h>
#include <core/deck.h>
#include <core/dealer.h>
#include <core/player.h>
#include <vector>

using std::vector;

namespace blackjack {

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
  GameEngine();
  
  /** Resets all the hands and bets and starts the round */
  void StartRound();

  /** Shuffles the deck */
  void ShuffleDeck();
  
  /** Prompts all players to post a bet*/
  void RequestBets();
  
  /** Deals cards to all the players in order then the dealer */
  void DealCards();
  
  /** Calls all players player and the dealer to check for blackjack and act correspondingly */
  void CheckBlackjack();
  
  /** Calls the players, in order, to take hit, stand, or double down */
  void PlayerPlays();
  
  /** Calls the dealer to hit or stand until they reach a hand total of 17 or more */
  void DealerPlays();
  
  /** Check whether each player won, lost/bust, or push and pay/take their bets accordingly */
  void SettleBets();
  
  /** Resets all the players and the dealer's hand */
  void ResetHands();
  
 private:
  Deck deck_; // deck of cards in play
  Dealer dealer_; // the person assigned as dealer
  vector<Player> players_; // the players who are playing in the round
};
} // namespace blackjack