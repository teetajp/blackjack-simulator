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

void GameEngine::PlayerPlays(istream &input) {
  for (Player& player : players_) {
    if (player.GetResult() == Player::InProgress)
      continue; // Only players who didn't hit blackjack yet can take action
    
    std::cout << "Cards in Hand:" << std::endl;
    for (auto card : player.GetHand().GetCards()) {
      std::cout << card.GetRank() << " of " << card.GetRank() << std::endl;
    }
    
    std::cout << "";
  }
  // todo: implement
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