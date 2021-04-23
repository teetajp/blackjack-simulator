#include <core/hand.h>

namespace blackjack {

Hand::Hand() : value_(0) {}

void Hand::AddCard(Card card) {
  cards_.push_back(card);
  CalculateHandValue();
}

void Hand::ResetHand() {
  cards_.clear();
  value_ = 0;
}

size_t Hand::GetHandValue() const {
  return value_;
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
  if ((cards_[0].GetRank() == Card::Ace || cards_[1].GetRank() == Card::Ace) &&
      (cards_[0].GetRank() == 10 || cards_[1].GetRank() == 10)) {
    return true;
  }
  return false;
}

void Hand::CalculateHandValue() {
  for (const Card& card : cards_) {
    value_ += card.GetRank();
  }
  
}
} // namespace blackjack