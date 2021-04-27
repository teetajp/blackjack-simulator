#include <core/dealer.h>

namespace blackjack {

Dealer::Dealer(Deck* deck) : deck_(deck) {}

void Dealer::AddPlayer(Player* player) {
  players_.push_back(player);
}





void Dealer::DealerPlay() {
  // Hit until dealer has hand total of max_value_to_hit w/o having exactly max_value_to_hit w/ a soft hand
  while (hand_.CalculateHandValue() < max_value_to_hit ||
      (hand_.CalculateHandValue() == max_value_to_hit && hand_.HasAce() && hit_soft_max_value)) {
    hand_.AddCard(deck_->DrawCard());
  } 
}
} // namespace blackjack