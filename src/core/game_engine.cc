#include <core/game_engine.h>

namespace blackjack {

GameEngine::GameEngine()= default;

void GameEngine::AddPlayer(const string& name, float buy_in) {
  // Check for existing user
  for (const Player& player : players_) {
    if (player.GetName() == name) {
      throw std::invalid_argument("Player with this name already exists.");
    }
  }
  players_.emplace_back(Player(name, buy_in));  
}

void GameEngine::ShuffleDeck() {
  deck_.Shuffle();
}

void GameEngine::PlaceBets(map<string, float>& bets) {
  for (const auto& player_bet : bets) {
    // Find a player with the matching name and update the bet
    for (Player& player : players_) {
      if (player_bet.first == player.GetName()) {
        player.PlaceBet(player_bet.second);
      }
    }
  }
}

void GameEngine::DealCards() {
  for (Player& player : players_) {
    // Determine whether a player is playing based on whether their bet is valid
    if (player.GetResult() == Player::InProgress) {
      player.Hit(deck_);
      player.Hit(deck_);
    }
  }
  dealer_.GetHand().AddCard(deck_.DrawCard());
  dealer_.GetHand().AddCard(deck_.DrawCard());
}

bool GameEngine::PayBlackjacks() {
  if (dealer_.GetHand().HasBlackjack()) {
    // Any player who also has blackjack ties with the dealer, otherwise they lose the round
    for (Player& player : players_) {
      if (player.GetHand().HasBlackjack()) {
        player.Push(); // Dealer and player has blackjack, so tie and return their bet
      } else {
        player.Lose(); // Dealer has blackjack but player doesn't, so take their bet
      }
    }
    return true;
  }
  
  // Dealer does not have blackjack, pay off anyone who has a blackjack
  for (Player& player : players_) {
    if (player.GetHand().HasBlackjack()) {
      // Pay the player off as they won and set their turn as done
      player.Blackjack();
    }
  }
  // The players who do not have blackjack will continue and take action next
  return false;
}

void GameEngine::PlayerPlays(string command) {
  // Turn command to all lowercase
  std::transform(command.begin(), command.end(), command.begin(),
                 [](unsigned char c){ return tolower(c); });
  
  // Make sure player can take actions
  if (current_player->GetResult() == Player::InProgress) {
    
    if (command == "hit") {
      current_player->Hit(deck_); // Hand still in progress unless bust
      
      if (current_player->GetHand().IsBust()) {
        current_player->Lose(); // Update result and take away bet immediately
      }
    } else if (command == "stand") {
      current_player->SetResult(Player::AwaitingComparison);
    } else if (command == "double") {
      current_player->DoubleDown(deck_); // Double bet and draw a final card
      
      if (current_player->GetHand().IsBust())
        current_player->Lose();
    }
  }
}

void GameEngine::DealerPlays() {
  dealer_.DealerPlay(&deck_);
}

void GameEngine::SettleBets() {
  size_t dealer_total = dealer_.GetHand().CalculateHandValue();
  if (dealer_.GetHand().CalculateHandValue() > Hand::kMaxHandValue) {
    // Dealer is bust, pay all players who is not bust off.
    
    for (Player& player : players_) {
      // Look for players who do not have blackjack and aren't bust as their bets aren't settled yet
      if (!player.GetHand().HasBlackjack() && player.GetHand().CalculateHandValue() <= Hand::kMaxHandValue)
        player.Win(); // Pay them off
    }
  } else { // Compare the dealer's total to each player who doesn't have a blackjack and settle bets accordingly
    for (Player& player : players_) {
      size_t player_total = player.GetHand().CalculateHandValue();
      
      // Players with "AwaitingComparison" status still need to compare totals to the dealer and settle bets accordingly
      // The rest of the players without this status has had their bets sorted already
      if (player.GetResult() == Player::AwaitingComparison) {
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
    player.ResetHand();
  }
  dealer_.GetHand().ResetHand();
}

GameStatus GameEngine::GetGameStatus() {
  // Update all players' available actions and add their const version to the game status
  vector<const Player*> players;
  current_player = nullptr;
  
  for (Player& player : players_) {
    player.UpdateActions();
    players.push_back(&player);
    
    if (current_player == nullptr && !player.GetActions().empty())
      current_player = &player;
  }
  
  GameStatus status;
  status.players = players; // pointers are marked const, so contents can't be changed through this
  status.dealers_hand = &dealer_.GetHand();  // the cards returned here are a copy
  status.player_to_act = current_player;
  return status;
}

void GameEngine::LoadTextures() {
//  spritesheet_ = 
}
} // namespace blackjack