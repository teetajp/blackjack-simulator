#include <core/card.h>

namespace blackjack {

Card::Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}

Card::Suit Card::GetSuit() const {
  return suit_;
}

Card::Rank Card::GetRank() const {
  return rank_;
}

bool operator==(const Card &first, const Card &second) {
  return first.GetSuit() == second.GetSuit() && first.GetRank() == second.GetRank();
}

bool operator!=(const Card &first, const Card &second) {
  return first.GetSuit() != second.GetSuit() || first.GetRank() != second.GetRank();
}
} // namespace blackjack