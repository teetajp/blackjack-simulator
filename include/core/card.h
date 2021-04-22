#pragma once

#include <vector>

using std::vector;

namespace blackjack {

/**
 * Represents a card in a standard 52-card deck.
 * Each card contains a suit and a symbol with a value attached to it.
 */
class Card {
 public:
  enum Suit; // all the possible suits of a card

  enum Value; // all the possible symbols and the corresponding values of a card
  
  /** Default constructor
   * 
   * @param suit the suit of the card (Clubs, Diamonds, Hearts, Spades)
   * @param value the value of the card (Ace, 2, 3, ..., 10, Jack, Queen, King)
   */
  Card(Suit suit, Value value);
  
  /** Returns the suit of the card */
  Suit GetSuit() const;

  /** Returns the card value */
  Value GetValue() const;

 private:
  Suit suit_; // the suit of the card
  Value value_; // the symbol of the card and its corresponding value
};
} // namespace blackjack