#pragma once

#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"

namespace blackjack {

/**
 * Represents the dealer in a game of blackjack.
 * Dealer is dealt cards and must act according to the rules.
 */
class Dealer {
 public:
  /** Default constructor
   * 
   * @param deck where the cards are to be drawn from 
   */
  Dealer(Deck* deck);
  
  /** Adds cards to the dealer's hand until the total is 17 or more.
   *  If the dealer hits soft 17 (Ace counted as 11), then dealer must hit.
   *  Dealer busts if the total is over 21.
   */
  void DealerPlay();
  
  /** Gets the dealer's hand */
  Hand& GetHand();

 private:
  static const size_t max_value_to_hit = 17; // dealer hits on all hand values below this value
  static const bool hit_soft_max_value = true; // whether dealer hits on the max_value_to_hit if they have a soft hand
  Deck* deck_; // deck of cards in play
  Hand hand_; // the dealer's hand containing their cards
  bool turn_done; // whether the dealer's turn is done
};
} // namespace blackjack