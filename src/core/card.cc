#include <core/card.h>

namespace blackjack {

Card::Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}

Card::Suit Card::GetSuit() const {
  return suit_;
}

Card::Rank Card::GetRank() const {
  return rank_;
}
} // namespace blackjack