#include <core/card.h>

namespace blackjack {

enum Suit { Clubs, Diamonds, Hearts, Spades };

enum Value {
  Ace = 1, // Ace can be 1 or 11 (handled by engine)
  Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10,
  Jack = 10, Queen = 10, King = 10 // Face cards are worth 10
};

Card::Card(Suit suit, Value value) : suit_(suit), value_(value) {}

Card::Suit Card::GetSuit() const {
  return suit_;
}

Card::Value Card::GetValue() const {
  return value_;
}
} // namespace blackjack