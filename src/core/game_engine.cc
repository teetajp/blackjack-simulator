#include <core/game_engine.h>
#include <cinder/app/AppBase.h>

namespace blackjack {

GameEngine::GameEngine() = default;

GameEngine::GameEngine(size_t deck_count, bool load_textures) {
  if (load_textures) {
    LoadTextures();
  }
  for (size_t i = 0; i < deck_count - 1; i++) {
    deck_.AddDeck();
  }
}


void GameEngine::AddPlayer(const string &name, float buy_in) {
  // Check for existing user
  for (const Player &player : players_) {
    if (player.GetName() == name) {
      throw std::invalid_argument("Player with this name already exists.");
    }
  }
  players_.emplace_back(Player(name, buy_in));
}

void GameEngine::ShuffleDeck() {
  deck_.Shuffle();
}

void GameEngine::PlaceBets(map<string, float> &bets) {
  for (const auto &player_bet : bets) {
    // Find a player with the matching name and update the bet
    for (Player &player : players_) {
      if (player_bet.first == player.GetName()) {
        player.PlaceBet(player_bet.second);
      }
    }
  }
}

void GameEngine::DealCards() {
  for (Player &player : players_) {
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
    for (Player &player : players_) {
      if (player.GetHand().HasBlackjack()) {
        player.Push(); // Dealer and player has blackjack, so tie and return their bet
      } else {
        player.Lose(); // Dealer has blackjack but player doesn't, so take their bet
      }
    }
    return true;
  }

  // Dealer does not have blackjack, pay off anyone who has a blackjack
  for (Player &player : players_) {
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
                 [](unsigned char c) { return tolower(c); });

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
  bool players_done = true;
  for (const auto& player : players_) {
    if (players_done && !(player.GetHand().HasBlackjack() || player.GetHand().IsBust()))
      players_done = false;
  }
  
  // Don't need to draw more cards if all players are done and don't need to compare hand to dealer
  if (players_done)
    return;

  dealer_.DealerPlay(&deck_);
}

void GameEngine::SettleBets() {
  size_t dealer_total = dealer_.GetHand().CalculateHandValue();
  if (dealer_.GetHand().CalculateHandValue() > Hand::kMaxHandValue) {
    // Dealer is bust, pay all players who is not bust off.

    for (Player &player : players_) {
      // Look for players who do not have blackjack and aren't bust as their bets aren't settled yet
      if (!player.GetHand().HasBlackjack() && player.GetHand().CalculateHandValue() <= Hand::kMaxHandValue)
        player.Win(); // Pay them off
    }
  } else { // Compare the dealer's total to each player who doesn't have a blackjack and settle bets accordingly
    for (Player &player : players_) {
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
  for (Player &player : players_) {
    player.ResetHand();
  }
  dealer_.GetHand().ResetHand();
}

GameStatus GameEngine::GetGameStatus() {
  // Update all players' available actions and add their const version to the game status
  vector<const Player *> players;
  current_player = nullptr;

  for (Player &player : players_) {
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
  // The file name format for the card should start with a letter c, d, h, or s to represent the suit.
  // And it should be followed by a number 01-13 denoting the rank of the card.
  vector<vector<ci::gl::Texture2dRef>> card_spritesheet;

  for (Card::Suit suit : Deck::suits) {
    vector<ci::gl::Texture2dRef> suited_card_sprites; // a vector of suited card sprites

    for (size_t rank_i = 1; rank_i <= 13; rank_i++) {
      string file_path = "sprites/";

      // Filter the sprites by card suit (first file name char)
      switch (suit) {
        case Card::Clubs:file_path += 'c';
          break;
        case Card::Diamonds:file_path += 'd';
          break;
        case Card::Hearts:file_path += 'h';
          break;
        case Card::Spades:file_path += 's';
          break;
      }

      // Filter sprites by card rank (01-13) for Ace-King.

      string num_rank_s = std::to_string(rank_i);
      if (rank_i < 10) {
        file_path += '0';
      }
      file_path += num_rank_s + ".png";
      // Load a card sprite into the respective cards
      suited_card_sprites.emplace_back(ci::gl::Texture2d::create(ci::loadImage(ci::app::loadAsset(file_path))));
    }
    card_spritesheet.push_back(suited_card_sprites);
  }
  deck_ = Deck(&card_spritesheet);
}

} // namespace blackjack