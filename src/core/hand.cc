#include <core/hand.h>

namespace blackjack {

Hand::Hand() : has_ace_(false) {}

void Hand::AddCard(const Card& card) {
  cards_.push_back(card);
  if (card.GetRank() == Card::Ace)
    has_ace_ = true;
  // todo: throw an error if card is added while we have blackjack?
}

void Hand::ResetHand() {
  cards_.clear();
  has_ace_ = false;
}

vector<Card> Hand::GetCards() const {
  return cards_;
}

bool Hand::HasBlackjack() const {
  // Error handling
  if (cards_.size() < 2)
    return false;

  /* According to Blackjack rules, 
   * a blackjack is when the hand's first two cards contains and Ace and a ten-valued card */
  return (cards_[0].GetRank() == Card::Ace || cards_[1].GetRank() == Card::Ace) &&
          (cards_[0].GetRank() == 10 || cards_[1].GetRank() == 10);
}

size_t Hand::CalculateHandValue() const {
  size_t total_value = 0;
  bool soft_ace = true;
  
  for (const Card& card : cards_) {
    size_t card_value = card.GetRank();
    
    if (card_value == Card::Ace && total_value + kMaxAceValue <= kMaxHandValue) {
      soft_ace = true;
      card_value = kMaxAceValue; // Ace counted as 11 if it doesn't make the hand go bust
    } else if (total_value + card_value > 21 && soft_ace) {
      // Change the value of the Ace to 1 instead of 11
      total_value -= kMaxAceValue;
      total_value += Card::Ace;
      soft_ace = false;
    }
    total_value += card_value;
  }
  return total_value;
}

bool Hand::HasAce() const {
  return has_ace_;
}
} // namespace blackjack