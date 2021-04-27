#include <core/game_engine.h>

namespace blackjack {
GameEngine::GameEngine() : dealer_(&deck_) {}

void GameEngine::AddPlayer(string name, size_t buy_in) {
  // Check for existing user
  for (const Player& player : players_) {
    if (player.GetName() == name) {
      throw std::invalid_argument("Player with this name already exists.");
    }
  }
  players_.emplace_back(Player(name, buy_in));  
}

const Player& GameEngine::GetPlayer(string name) const {
  for (const Player& player : players_) {
    if (player.GetName() == name)
      return player;
  }
}

void GameEngine::StartRound() {
  deck_.Shuffle();
  RequestBets();
  DealCards();
  
  if (!CheckBlackjack()) {
    // True if dealer doesn't have blackjack and the bets' aren't settled
    PlayerPlays();
    DealerPlays();
    SettleBets();
  }
  ResetHands();
}

void GameEngine::RequestBets() {
  // todo: find a way to implement
}

void GameEngine::DealCards() {
  for (Player& player : players_) {
    player.GetHand().AddCard(deck_.DrawCard());
    player.GetHand().AddCard(deck_.DrawCard());

  }
  dealer_.GetHand().AddCard(deck_.DrawCard());
  dealer_.GetHand().AddCard(deck_.DrawCard());
}

bool GameEngine::CheckBlackjack() {
  if (dealer_.GetHand().HasBlackjack()) {
    // Any player who also has blackjack ties with the dealer, otherwise they lose the round
    for (Player& player : players_) {
      if (player.GetHand().HasBlackjack()) {
        player.Push(); // Dealer and player has blackjack, so tie and return their bet
      } else {
        player.Lose(); // Dealer has blackjack but player doesn't, so take their bet
      }
      player.SetTurnDone(true); // Round is over for everyone
    }
    return true;
  }
  
  // Dealer does not have blackjack, pay off anyone who has a blackjack
  for (Player& player : players_) {
    if (player.GetHand().HasBlackjack()) {
      // Pay the player off as they won and set their turn as done
      player.Blackjack();
      player.SetTurnDone(true);
    }
  }
  // The players who do not have blackjack will continue and take action next
  return false;
}

void GameEngine::PlayerPlays() {
  // todo: implement
}

void GameEngine::DealerPlays() {
  dealer_.DealerPlay();
}

void GameEngine::SettleBets() {
  size_t dealer_total = dealer_.GetHand().CalculateHandValue();
  if (dealer_.GetHand().CalculateHandValue() > Hand::kMaxHandValue) {
    // Dealer is bust, pay all players who is not bust off.
    
    for (Player& player : players_) {
      // Look for players who do not have blackjack and aren't bust as their bets aren't settled yet
      if (!player.GetHand().HasBlackjack() && player.GetHand().CalculateHandValue() <= 21)
        player.Win(); // Pay them off
    }
  } else { // Compare the dealer's total to each player who doesn't have a blackjack and settle bets accordingly
    for (Player& player : players_) {
      size_t player_total = player.GetHand().CalculateHandValue();
      
      // Players w/ blackjack already have their bets settled
      if (!player.GetHand().HasBlackjack()) {
        if (player_total > dealer_total) {
          player.Win();
        } else if (player_total == dealer_total) {
          player.Push();
        } else if (player_total < dealer_total || player_total > Hand::kMaxHandValue) {
          player.Lose();
        }
      }
    }
  }
}

void GameEngine::ResetHands() {
  // Reset all player's hand
  for (Player& player : players_) {
    player.GetHand().ResetHand();
  }
  dealer_.GetHand().ResetHand();
}


} // namespace blackjack