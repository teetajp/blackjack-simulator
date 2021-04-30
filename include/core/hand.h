#pragma once

#include "card.h"

namespace blackjack {

/**
 * This class represents a blackjack hand. 
 */
class Hand {
 public:
  static const size_t kMaxHandValue = 21; // the max hand value before going bust
  static const size_t kMaxAceValue = 11; // the higher of the values for ace (can be 1 or 11)
  
  /** Default constructor */
  Hand();

  /** Add a card to the hand */
  void AddCard(const Card &card);

  /** Resets the hand */
  void ResetHand();

  /** Calculates the total value of the cards in the hand and stores it */
  size_t CalculateHandValue() const;

  /** Returns a copied vector of cards in the hand */
  vector<Card> GetCards() const;

  /** Checks whether the hand contains an Ace and a 10-card (Ten, Jack, Queen, King)
    * 
    * @return true if the hand contains a blackjack, else false
    */
  bool HasBlackjack() const;

  /** Returns true if the hand has an ace */
  bool HasAce() const;
  
  /** Returns true if the hand total is over 21 */
  bool IsBust() const;

 private:
  vector<Card> cards_; // the cards in the hand
  bool has_ace_; // whether the hand has an ace
};
} // namespace blackjack