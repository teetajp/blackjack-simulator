#include <core/deck.h>

namespace blackjack {

Deck::Deck() : next_card_index(0) {
  AddDeck();
}

void Deck::AddDeck() {
  // Populate the deck with 52 cards, with each of the 4 suits containing 13 cards
  for (Card::Suit suit : suits) {
    for (Card::Rank rank : ranks) {
      cards_.emplace_back(Card(suit, rank));
    }
  }
}

const Card& Deck::DrawCard() {
  if (next_card_index >= cards_.size()) {
    throw std::out_of_range("No cards remaining to draw.");
  }
  return cards_[next_card_index++]; // Increment the card index after returning the card on top
}

void Deck::Shuffle() {
  // Use the built in shuffle function to shuffle our vector
  std::random_shuffle(cards_.begin(), cards_.end());
  next_card_index = 0;
}

size_t Deck::CalculateRemainingCards() const {
  // If there is one card in the deck, then its size of the deck is 1, but the index of the card is 0.
  // So size() - card_index = number of remaining cards
  return cards_.size() - next_card_index;
}

} // namespace blackjack