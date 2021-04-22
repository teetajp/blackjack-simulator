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
  
  void ShuffleDeck();
  
  void StartRound();
  
  void GetBets();
  
  void DealCards();
  
  void CheckBlackjack();
  
  void PlayerPlays();
  
  void DealerPlays();
  
  void SettleBets();
  
  void ResetHands();
  
 private:
  Dealer dealer_;
  Deck deck_;
  vector<Player> players_;
};
} // namespace blackjack