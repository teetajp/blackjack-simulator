#pragma once

namespace blackjack {

/**
 * Represents the dealer in a game of blackjack.
 * Dealer is dealt cards and must act according to the rules.
 */
class Dealer {
 public:
  /** Checks whether the dealer has an Ace and a 10-card (Ten, Jack, Queen, King)
   * 
   * @return true if the dealer has blackjack, else false
   */
  bool HasBlackjack() const;
  
  /** Adds cards to the dealer's hand until the total is 17 or more.
   *  If the dealer hits soft 17 (Ace counted as 11), then dealer must hit.
   *  Dealer busts if the total is over 21.
   */
  void DealerPlay();

  /** Calculates the total value of the cards in the dealer's hand */
  size_t CalculateHandTotal() const;
  
  /** Clears the hand */
  void ResetHand();
  
 private:
  vector<Card> hand_; // the two cards dealt to the dealer at the start of the round
};
} // namespace blackjack