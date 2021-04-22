#pragma once

#include <vector>

using std::vector;

namespace blackjack {

class Card {
  // todo: move enums to within public?

 public:
  enum Suit; // all the possible suits of a card

  enum Value; // all the possible symbols and the corresponding values of a card
  
  Card(Suit suit, Value value);
  
  Value GetValue() const;
  
  Suit GetSuit() const;

 private:
  Suit suit_; // the suit of the card
  Value value_; // the symbol of the card and its corresponding value
};
} // namespace blackjack