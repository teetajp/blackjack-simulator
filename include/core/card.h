#pragma once

#include <vector>

using std::vector;

namespace blackjack {

// todo: rename class to rank
/**
 * Represents a card in a standard 52-card deck.
 * Each card contains a suit and a symbol with a value attached to it.
 */
class Card {
 public:
  enum Suit { // all the possible suits of a card
  Clubs, Diamonds, Hearts, Spades
  };

  enum Value { // all the possible symbols and the corresponding values of a card
    Ace = 1, // Ace can be 1 or 11 (handled by engine)
    Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10,
    Jack = 10, Queen = 10, King = 10 // Face cards are worth 10
  };
  
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