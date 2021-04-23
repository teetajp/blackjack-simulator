#include <core/card.h>

namespace blackjack {

Card::Card(Suit suit, Value value) : suit_(suit), value_(value) {}

Card::Suit Card::GetSuit() const {
  return suit_;
}

Card::Value Card::GetValue() const {
  return value_;
}
} // namespace blackjack