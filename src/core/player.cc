#include <core/player.h>

namespace blackjack {

// todo: remove magic numbers
Player::Player() : name_("Player"), balance_(100), bet_(0), turn_done(false) {}

Player::Player(string name, size_t balance) : name_(name), balance_(balance), bet_(0), turn_done(false) {}

size_t Player::GetBet() const {
  return bet_;
}

string Player::GetName() const {
  return name_;
}

void Player::Win() {
  balance_ += 2 * bet_; // won the amount the player bet and return what the player bet
  bet_ = 0; // reset the bet
}

void Player::Lose() {
  bet_ = 0; // Reset the bet without returning the player's bet 
}

void Player::Push() {
  balance_ += bet_; // Return the bet, so player doesn't gain or lose anything
  bet_ = 0; // Reset the bet
}

void Player::Blackjack() {
  balance_ += 2.5 * bet_;
  bet_ = 0;
}

void Player::PostBet(size_t bet) {
  bet_ = bet;
  balance_ -= bet_;
}

Hand& Player::GetHand() {
  Hand& hand = hand_;
  return hand;
}

bool Player::IsTurnDone() const {
  return turn_done;
}
} // namespace blackjack