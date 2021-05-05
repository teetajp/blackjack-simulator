#include <blackjack_app.h>

namespace blackjack {

/* Before round:
 * 1. Reset background to green
 * 2. Show instructions text
 * 3. Press + 
 *
 * Draw dealer + card stack
 * Connect game engine to GUI, make default buy-in
 * start w/ one hand, can add more hand (implement one hand first), press esc to get out of table
 * Deal right to left
 * Add H: hit, S: stand, D: double, enter to start
 * Use up/down button to increase/decrease bet size
 * Add sprites
 *  
 * Dealer sprite:
 * 1. no cards on table at first, when dealt, two cards,
 *    one face up, second down
 * 2. check for blackjack, if yes, win, show and display dealer win text
 *    - show under each player hand whether win or lose
 * 3. if not, once players finish action, remove face down card, and reveal the card
 *
 * Player sprites:
 * 1. (for user-friendly ui) add member var <last bet> and allow player to rebet last one so don't have to slide the bet each time
 * 2. show both player cards face up, stacked (revealing card on left)
 * 3. show options depending on result
 * 4. once stand/out of action: move to next player on left
 * 5. display result after done
 * 
 * Reset the table after each round
 * 
 * Use booleans to separate game stages
 */


BlackjackApp::BlackjackApp(){
  ci::app::setWindowSize((int) ((double) kAspectRatio * kWindowSize), (int) kWindowSize);
  engine_.AddPlayer(kDefaultPlayerName, 100.f); // Single player for now
  card_back_ = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadAsset("sprites/card_back_01.png")));
  card_height_ = card_back_->getHeight();
  card_width_ = card_back_->getWidth();
  bets_[kDefaultPlayerName] = 0;
  ci::audio::SourceFileRef sourceFile = ci::audio::load(ci::app::loadAsset("sounds/shuffling-cards-4.wav"));
  shuffle_sound_ = ci::audio::Voice::create(sourceFile);
}

void BlackjackApp::update() {
  status_ = engine_.GetGameStatus();
}
// todo: turn magic numbers into constants
void BlackjackApp::draw() {
  // TODO: Resize cards
  update();
  ci::gl::clear(kBackgroundColor);
  ci::gl::setMatricesWindow(getWindowSize());

  // Draw the house rules texts
  ci::gl::drawStringCentered("BLACKJACK PAYS 3 TO 2",
                             vec2(getWindowCenter().x, (float) card_back_->getHeight() + 4 * kMargin - kFontSize),
                             ci::Color("black"),
                             ci::Font("Arial", (float) kFontSize));
  ci::gl::drawStringCentered("DEALER MUST STAND ON 17 AND DRAW TO 16",
                             vec2(getWindowCenter().x, (float) card_back_->getHeight() + 4 * kMargin),
                             ci::Color("black"),
                             ci::Font("Arial", (float) kFontSize));

  // Draw instruction texts
  ci::gl::drawStringCentered(
      "Before Round: [Up Arrow] - Increment bet, [Down Arrow] - Decrement bet, [Enter] - Confirm Bet/Start Round",
      vec2(getWindowCenter().x, getWindowHeight() - kMargin - kFontSize),
      ci::Color("black"),
      ci::Font("Arial", (float) kFontSize));
  ci::gl::drawStringCentered(
      "During Round: [H] - Hit, [S] - Stand, [D] - Double Down | After Round: [BACKSPACE] - Start New Round",
      vec2(getWindowCenter().x, getWindowHeight() - kMargin),
      ci::Color("black"),
      ci::Font("Arial", (float) kFontSize));

  // Draw a divider between instructions and the game area
  ci::gl::color(ci::Color("black"));
  float game_area_height = (float) getWindowHeight() - kMargin - 2 * kFontSize;
  ci::gl::drawSolidRect(ci::Rectf(vec2(kMargin, game_area_height),
                                  vec2(getWindowWidth() - kMargin, game_area_height + 5)));

  // Draw a card deck in the upper right corner
  ci::gl::color(ci::Color("white"));
  for (size_t i = 0; i < 10; i++) {
    size_t card_gap = i * 2; // Used to create a stacking effect
    ci::Rectf
        card_rect((float) getWindowWidth() - card_back_->getWidth() - kMargin - card_gap, (float) kMargin + card_gap,
                  (float) getWindowWidth() - kMargin - card_gap, (float) card_back_->getHeight() + kMargin + card_gap);
    ci::gl::draw(card_back_, card_rect);
  }

  DisplayPlayerInfo(game_area_height);

  if (round_started_) {
    DisplayPlayerCards(game_area_height - kMargin - 2 * kFontSize);
    DisplayDealer();
  }
}

void BlackjackApp::keyDown(ci::app::KeyEvent event) {
  // Before the round starts, user may add/remove player, and players increase/decrease bets
  if (!round_started_) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_RETURN:
        // Once everyone has confirmed their bets, start the round
        if (bet_confirmed) {
          engine_.PlaceBets(bets_);
          engine_.ShuffleDeck();
          shuffle_sound_->start();
          engine_.DealCards();
          round_started_ = true;
          bets_settled = false;
          draw();
          
          if (engine_.PayBlackjacks()) { // Dealer has blackjack
            engine_.ResetHands();
            round_started_ = false;
            bets_settled = true;
            bet_confirmed = false;
          }
        } else if (!bet_confirmed) { // Player is confirming their bet
          bet_confirmed = true;
          // todo: if 2+ players, change indicator onto other players to confirm their bets
        }
        return;
      case ci::app::KeyEvent::KEY_UP:
        // Increments bet amount by $5, maximum is the player's balance
        for (auto size : kBetSizes) {
          // Set the player's bet size to the first larger bet size
          if (bets_[kDefaultPlayerName] < size && size <= status_.players.front()->GetBalance()) {
            bets_[kDefaultPlayerName] = size;
            draw();
            return;
          }
        }
        return;
      case ci::app::KeyEvent::KEY_DOWN:
        // Decrements bet amount by $5, minimum is $1
        for (auto it = kBetSizes.rbegin(); it != kBetSizes.rend();
             ++it) { // Iterate from back to front (largest to smallest)
          if (bets_[kDefaultPlayerName] > *it) { // Set the player's bet size to the first smaller bet size
            bets_[kDefaultPlayerName] = *it;
            draw();
            return;
          }
        }
        return;
      case ci::app::KeyEvent::KEY_PLUS:
        // (Implement after single-player func. is done/ NOT part of project requirement)
        // Add player (must be at start of round before bets)
        return;
      case ci::app::KeyEvent::KEY_MINUS:
        // (Implement after single-player func. is done/ NOT part of project requirement)
        // Remove player (must be at start of round before bets)
        return;
    }
  }
  // During the round, players may hit stand or double down when it is their turn

  if (status_.player_to_act != nullptr) {
    switch (event.getCode()) {
      case ci::app::KeyEvent::KEY_h:engine_.PlayerPlays("hit");
        break;
      case ci::app::KeyEvent::KEY_s:engine_.PlayerPlays("stand");
        break;
      case ci::app::KeyEvent::KEY_d:engine_.PlayerPlays("double");
        break;
    }
    update();
  } else {
    if (round_started_ && status_.player_to_act == nullptr) { // No one left to act, so continue to end of the game
      engine_.DealerPlays();
      engine_.SettleBets();
      bets_settled = true;
    }
    if (bets_settled && event.getCode() == ci::app::KeyEvent::KEY_BACKSPACE) {
      engine_.ResetHands();
      round_started_ = false;
      bet_confirmed = false;
    }
  }
  draw();
}

void BlackjackApp::DisplayPlayerInfo(float game_area_height) {
  // todo: extend to multiple players and put coordinates for display as member variable in player class
  // Display the player balance
  float balance = status_.players.front()->GetBalance();

  if (!round_started_) {
    balance -= bets_[kDefaultPlayerName]; // Bet has not been placed, so show theoretical balance change
  }

  // Convert balance and bet to a two-decimal point string
  // Snippet from: https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << balance;
  string balance_s = stream.str();

  stream.str(string()); // Reset the stream
  stream << std::fixed << std::setprecision(2) << bets_[kDefaultPlayerName];
  string bet_s = stream.str();

  // todo: assign each player an x-coordinate so everything is left-justified
  ci::gl::drawString("Balance: $" + balance_s,
                     vec2(getWindowCenter().x - 2 * kMargin, game_area_height - kMargin),
                     ci::Color("black"),
                     ci::Font("Arial", (float) kFontSize));

  // Display the default or last bet
  ci::gl::drawString("Bet:        $" + bet_s,
                     vec2(getWindowCenter().x - 2 * kMargin, game_area_height - kMargin - kFontSize),
                     ci::Color("black"),
                     ci::Font("Arial", (float) kFontSize));

  // Display the player's hand value
  string hand_value = std::to_string(status_.players.front()->GetHand().CalculateHandValue());
  ci::gl::drawString("Hand Value: " + hand_value,
                     vec2(getWindowCenter().x - 2 * kMargin, game_area_height - kMargin - 2 * kFontSize),
                     ci::Color("black"),
                     ci::Font("Arial", (float) kFontSize));

  // Display player's state
  string result = status_.players.front()->ResultToString();
  if (status_.players.front()->GetHand().HasBlackjack()) {
    result += " (Blackjack)";
  }
  ci::gl::drawString("Result: " + result,
                     vec2(getWindowCenter().x - 2 * kMargin, game_area_height - kMargin - 3 * kFontSize),
                     ci::Color("black"),
                     ci::Font("Arial", (float) kFontSize));
}

void BlackjackApp::DisplayPlayerCards(float player_cards_height) {
  ci::gl::color(ci::Color("white"));
  const vector<Card> &player_cards = status_.players.front()->GetHand().GetCards();

  for (size_t i = 0; i < player_cards.size(); i++) {
    const ci::gl::Texture2dRef &card_sprite = player_cards[i].GetSprite();
    size_t card_gap = i * 25;
    ci::Rectf card_rect((float) getWindowCenter().x - card_sprite->getWidth() + card_gap,
                        (float) player_cards_height - card_sprite->getHeight() - kMargin,
                        (float) getWindowCenter().x + card_gap,
                        (float) player_cards_height - kMargin);
    ci::gl::draw(card_sprite, card_rect);
  }
}

void BlackjackApp::DisplayDealer() {
  const vector<Card> &dealer_cards = status_.dealers_hand->GetCards();

  // All players are out of actions, or dealer has blackjack
  if (status_.player_to_act == nullptr
      || status_.dealers_hand->HasBlackjack()) { // No one left to act, so show other dealer card(s)
    // Draw all dealer's cards face up.
    for (size_t i = 0; i < dealer_cards.size(); i++) {
      const ci::gl::Texture2dRef &card_sprite = dealer_cards[i].GetSprite();
      size_t card_gap = i * 25;
      ci::Rectf card_rect((float) getWindowCenter().x - card_width_ + card_gap, (float) kMargin,
                          (float) getWindowCenter().x + card_gap, (float) kMargin + card_height_);
      ci::gl::draw(card_sprite, card_rect);
    }
    // Display dealer hand value
    string hand_value = std::to_string(status_.dealers_hand->CalculateHandValue());
    ci::gl::drawString("Hand Value: " + hand_value,
                       vec2(getWindowCenter().x - 2 * kMargin, kMargin + card_height_ + kFontSize),
                       ci::Color("black"),
                       ci::Font("Arial", (float) kFontSize));
  } else { // Players have yet to act, so show only one card face up
    // Draw the first card face up
    const ci::gl::Texture2dRef &card_sprite = dealer_cards.front().GetSprite();
    ci::Rectf face_up_rect((float) getWindowCenter().x - card_width_ - kMargin * 0.5f, (float) kMargin,
                           (float) getWindowCenter().x - kMargin * 0.5f, (float) kMargin + card_height_);
    ci::gl::draw(card_sprite, face_up_rect);

    // Draw the second card face down
    ci::Rectf face_down_rect((float) getWindowCenter().x + kMargin * 0.5f,
                             (float) kMargin,
                             (float) getWindowCenter().x + card_width_ + kMargin * 0.5f,
                             (float) kMargin + card_height_);
    ci::gl::draw(card_back_, face_down_rect);
  }
}

} // namespace blackjack

