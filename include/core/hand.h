#pragma once

#include "card.h"

namespace blackjack {

/**
 * This class represents a blackjack hand. 
 */
class Hand {
 public:
  /** Default constructor */
  Hand();
  
  /** Add a card to the hand */
  void AddCard(Card card); // todo: make card a reference?

  /** Resets the hand */
  void ResetHand();
  
  /** Returns the total value of the cards in the hand */
  size_t GetHandValue() const;
  
  /** Returns a copied vector of cards in the hand */
  vector<Card> GetCards() const;

  /** Checks whether the hand contains an Ace and a 10-card (Ten, Jack, Queen, King)
    * 
    * @return true if the hand contains a blackjack, else false
    */
  bool HasBlackjack() const;
  
 private:
  vector<Card> cards_; // the cards in the hand
  size_t value_; // the value of the hand

  /** Calculates the total value of the cards in the hand and stores it */
  void CalculateHandValue();
};
} // namespace blackjack