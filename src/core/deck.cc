#include <core/deck.h>

namespace blackjack {

Deck::Deck() : next_card_index(0) {
  AddDeck();
}

const Card& Deck::GetCard() const {
  return cards_[next_card_index];
}

void Deck::AddDeck() {
  // Populate the deck with 52 cards, with each of the 4 suits containing 13 cards
  for (Card::Suit suit : suits) {
    for (Card::Value value : values) {
      cards_.emplace_back(Card(suit, value));
    }
  }
}

void Deck::Shuffle() {
  // Use the built in shuffle function to shuffle our vector
  std::random_shuffle(cards_.begin(), cards_.end());
}
} // namespace blackjack