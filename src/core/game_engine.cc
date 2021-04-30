#include <core/game_engine.h>


namespace blackjack {

GameEngine::GameEngine()= default;

void GameEngine::AddPlayer(string name, float buy_in) {
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
  throw std::invalid_argument("Player does not exist");
}

void GameEngine::StartRound(istream &input) {
//  deck_.Shuffle();
//  RequestBets(input);
//  DealCards();
//  
//  if (!PayBlackjacks()) {
//    // True if dealer doesn't have blackjack and the bets' aren't settled
//    PlayerPlays(input);
//    DealerPlays();
//    SettleBets();
//  }
//  ResetHands();
}

void GameEngine::ShuffleDeck() {
  deck_.Shuffle();
}

void GameEngine::PlaceBets(map<string, float>& bets) {
  for (auto player_bet : bets) {
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

void GameEngine::PlayerPlays(vector<PlayerCommand> player_commands) {
  for (auto player_command : player_commands) {
    // Find the matching player
    for (Player& player : players_) {
      if (player_command.name == player.GetName()) {
        // Make sure player can take actions
        if (player.GetResult() == Player::InProgress) {
          
          switch (player_command.command) {
            case PlayerCommand::Hit:
              player.Hit(deck_); // Hand still in progress unless bust
              if (player.GetHand().IsBust())
                player.Lose(); // Update result and take away bet immediately
              break;
            case PlayerCommand::Stand:
              player.SetResult(Player::AwaitingComparison);
              break;
            case PlayerCommand::DoubleDown:
              player.DoubleDown(deck_); // Double bet and draw a final card
              if (player.GetHand().IsBust())
                player.Lose();
          }
        }
      }
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
  vector<const Player*> players;
  for (const Player& player : players_) {
    players.push_back(&player);
  }
  GameStatus status;
  status.players = players; // pointers are marked const, so contents can't be changed through this
//  status.dealers_cards = dealer_.GetHand().GetCards(); // the cards returned here are a copy
  status.dealers_hand = &dealer_.GetHand();  
  return status;
}


} // namespace blackjack