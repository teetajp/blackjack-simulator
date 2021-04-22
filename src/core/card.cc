#include <core/card.h>

namespace blackjack {


enum Card::Suit { Clubs, Diamonds, Hearts, Spades };

enum Card::Value {
  Ace = 1, // Ace can be 1 or 10 (handled by engine)
  Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10,
  Jack = 10,
  Queen = 10,
  King = 10
};

Card::Card(Suit suit, Value value) : suit_(suit), value_(value) {}
} // namespace blackjack