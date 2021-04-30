#include <core/player.h>

namespace blackjack {

static const char * ResultStrings[] = { "Won", "Tied", "Lost", "In Progress", "Not in this Round" };

Player::Player() : name_("Player"), balance_(100.0f), bet_(0.0f), result_(NotPlaying) {}

Player::Player(string name, float balance) : name_(name), balance_(balance), bet_(0), result_(NotPlaying) {}

void Player::Win() {
  balance_ += 2 * bet_; // won the amount the player bet and return what the player bet
  bet_ = 0; // reset the bet
  result_ = Won;
}

void Player::Lose() {
  bet_ = 0; // Reset the bet without returning the player's bet 
  result_ = Lost;
}

void Player::Push() {
  balance_ += bet_; // Return the bet, so player doesn't gain or lose anything
  bet_ = 0; // Reset the bet
  result_ = Tied;
}

void Player::Blackjack() {
  balance_ += 2.5f * bet_;
  bet_ = 0;
  result_ = Won;
}

void Player::PlaceBet(float bet) {
  bet_ = bet;
  
  if (bet_ <= 0 || bet_ > balance_) {
    result_ = NotPlaying;
  } else {
    balance_ -= bet_;
    result_ = InProgress;
  }
}

void Player::Hit(Deck &deck) {
  hand_.AddCard(deck.DrawCard());
}

void Player::ResetHand() {
  hand_.ResetHand();
  result_ = NotPlaying;
}

void Player::SetResult(Result result) {
  result_ = result;
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

const Hand& Player::GetHand() const{
  const Hand& hand = hand_;
  return hand;
}

Player::Result Player::GetResult() const {
  return result_;
}

string Player::ResultToString() const {
  return ResultStrings[result_];
}
} // namespace blackjack