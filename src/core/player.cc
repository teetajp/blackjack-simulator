#include <core/player.h>

namespace blackjack {

// todo: remove magic numbers
Player::Player() : name_("Player"), balance_(100.0f), bet_(0.0f), turn_done_(false) {}

Player::Player(string name, float balance) : name_(name), balance_(balance), bet_(0), turn_done_(false) {}

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
  balance_ += 2.5f * bet_;
  bet_ = 0;
}

void Player::PlaceBet(float bet) {
  bet_ = bet;
  balance_ -= bet_;
}

float Player::GetBet() const {
  return bet_;
}

string Player::GetName() const {
  return name_;
}

float Player::GetBalance() const {
  return balance_;
}

Hand& Player::GetHand() {
  Hand& hand = hand_;
  return hand;
}

bool Player::IsTurnDone() const {
  return turn_done_;
}

void Player::SetTurnDone(bool turn_done) {
  turn_done_ = turn_done;
}
} // namespace blackjack