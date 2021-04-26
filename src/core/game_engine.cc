#include <core/game_engine.h>

namespace blackjack {
GameEngine::GameEngine() {
}

void GameEngine::StartRound() {
  ShuffleDeck();
  RequestBets();
  DealCards();
  CheckBlackjack();
  // if dealer has blackjack, settle bets. Push with players who also has blackjack
  // todo: check order of checking blackjack
  PlayerPlays();
  DealerPlays();
  SettleBets();
  ResetHands();
}

void GameEngine::ShuffleDeck() {
  deck_.Shuffle();
}

void GameEngine::DealCards() {
  for (Player& player : players_) {
    player.GetHand().AddCard(deck_.DrawCard());
    player.GetHand().AddCard(deck_.DrawCard());

  }
  dealer_.GetHand().AddCard(deck_.DrawCard());
  dealer_.GetHand().AddCard(deck_.DrawCard());
}

void GameEngine::CheckBlackjack() {
  bool dealer_blackjack = dealer_.
  for (Player& player : players_) {
    
  }
}

void GameEngine::PlayerPlays() {
  // todo: implement
}

void GameEngine::DealerPlays() {
  dealer_.DealerPlay();
}

void GameEngine::SettleBets() {
  size_t dealer_total = dealer_.GetHand().CalculateHandValue();
  for (Player& player : players_) {
    size_t player_total = player.GetHand().CalculateHandValue();
    if (player.GetHand())
  }
}

void GameEngine::ResetHands() {
  for (Player& player : players_) {
    player.GetHand().ResetHand();
  }
  dealer_.GetHand().ResetHand();
}


} // namespace blackjack