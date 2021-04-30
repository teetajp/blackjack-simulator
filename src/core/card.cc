#include <core/card.h>

namespace blackjack {

Card::Card(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}

Card::Suit Card::GetSuit() const {
  return suit_;
}

Card::Rank Card::GetRank() const {
  return rank_;
}

string Card::ToString() const {
  string description = "";
  
  // Must use if statements, not switch case as switch case can't distinguish between face cards with equal value
  if (rank_ == Card::Ace) {
    description += "Ace";
  } else if (rank_ == Card::Two) {
    description += "Deuce";
  } else if (rank_ == Card::Three) {
    description += "Three";
  } else if (rank_ == Card::Four) {
    description += "Four";
  } else if (rank_ == Card::Five) {
    description += "Five";
  } else if (rank_ == Card::Six) {
    description += "Six";
  } else if (rank_ == Card::Seven) {
    description += "Seven";
  } else if (rank_ == Card::Eight) {
    description += "Eight";
  } else if (rank_ == Card::Nine) {
    description += "Nine";
  } else if (rank_ == Card::Ten) {
    description += "Ten";
  } else if (rank_ == Card::Jack) {
    description += "Jack";
  } else if (rank_ == Card::Queen) {
    description += "Queen";
  } else if (rank_ == Card::King) {
    description += "King";
  }
  description += " of ";
  
  if (suit_ == Card::Clubs) {
    description += "Clubs";
  } else if (suit_ == Card::Diamonds) {
    description += "Diamonds";
  } else if (suit_ == Card::Hearts) {
    description += "Hearts";
  } else {
    description += "Spades";
  }
  return description;
}

bool operator==(const Card &first, const Card &second) {
  return first.GetSuit() == second.GetSuit() && first.GetRank() == second.GetRank();
}

bool operator!=(const Card &first, const Card &second) {
  return first.GetSuit() != second.GetSuit() || first.GetRank() != second.GetRank();
}
} // namespace blackjack