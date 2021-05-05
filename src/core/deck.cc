#include <core/deck.h>

namespace blackjack {

Deck::Deck() : next_card_index_(0), spritesheet_(nullptr) {
  AddDeck();
}

Deck::Deck(const vector<vector<ci::gl::Texture2dRef>> *spritesheet) : next_card_index_(0), spritesheet_(spritesheet) {
  AddDeck();
}

void Deck::AddDeck() {
  // Populate the deck with 52 cards, with each of the 4 suits containing 13 cards
  size_t suit_i = 0;
  for (Card::Suit suit : suits) {
    size_t rank_i = 0;

    for (Card::Rank rank : ranks) {
      if (spritesheet_ != nullptr) {
        cards_.push_back(*(new Card(suit, rank, (*spritesheet_)[suit_i][rank_i])));
      } else {
        cards_.emplace_back(Card(suit, rank));
      }
      rank_i++;
    }
    suit_i++;
  }
}

const Card &Deck::DrawCard() {
  if (next_card_index_ >= cards_.size()) {
    throw std::out_of_range("No cards remaining to draw.");
  }
  return cards_[next_card_index_++]; // Increment the card index after returning the card on top
}

void Deck::Shuffle() {
  // Use the built in shuffle function to rearranged our vector of cards
  size_t seed = (size_t) std::chrono::system_clock::now().time_since_epoch().count(); // obtain a time-based seed
  std::shuffle(cards_.begin(), cards_.end(), std::default_random_engine(seed));
  next_card_index_ = 0;
}

size_t Deck::CalculateRemainingCards() const {
  // If there is one card in the deck, then its size of the deck is 1, but the index of the card is 0.
  // So size() - card_index = number of remaining cards
  return cards_.size() - next_card_index_;
}
} // namespace blackjack