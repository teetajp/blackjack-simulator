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

const Card &Deck::DrawCard() {
  if (next_card_index >= cards_.size()) {
    throw std::out_of_range("No cards remaining to draw.");
  }
  return cards_[next_card_index++]; // Increment the card index after returning the card on top
}

void Deck::Shuffle() {
  // Use the built in shuffle function to rearranged our vector of cards
  size_t seed = (size_t) std::chrono::system_clock::now().time_since_epoch().count(); // obtain a time-based seed
  std::shuffle(cards_.begin(), cards_.end(), std::default_random_engine(seed));
  next_card_index = 0;
}

size_t Deck::CalculateRemainingCards() const {
  // If there is one card in the deck, then its size of the deck is 1, but the index of the card is 0.
  // So size() - card_index = number of remaining cards
  return cards_.size() - next_card_index;
}

} // namespace blackjack