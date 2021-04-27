#include <core/dealer.h>

namespace blackjack {

Dealer::Dealer() = default;

void Dealer::DealerPlay(Deck* deck) {
  if (hand_.HasBlackjack())
    return;
  
  // Hit until dealer has hand total of max_value_to_hit w/o having exactly max_value_to_hit w/ a soft hand
  while (hand_.CalculateHandValue() < max_value_to_hit ||
      hand_.CalculateHandValue() == max_value_to_hit && hand_.HasAce()) {
    hand_.AddCard(deck->DrawCard());
  } 
}

Hand& Dealer::GetHand() {
  return hand_;
}
} // namespace blackjack