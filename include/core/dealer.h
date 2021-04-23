#pragma once

#include "card.h"
#include "hand.h"

namespace blackjack {

/**
 * Represents the dealer in a game of blackjack.
 * Dealer is dealt cards and must act according to the rules.
 */
class Dealer {
 public:
  /** Default constructor */
  Dealer();

  /** Adds cards to the dealer's hand until the total is 17 or more.
   *  If the dealer hits soft 17 (Ace counted as 11), then dealer must hit.
   *  Dealer busts if the total is over 21.
   */
  void DealerPlay();

 private:
  Hand hand_; // the dealer's hand containing their cards
};
} // namespace blackjack