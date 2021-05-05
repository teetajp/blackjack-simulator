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
 *  todo: working on - add players
 */


BlackjackApp::BlackjackApp() {
  ci::app::setWindowSize((int) ((double) kAspectRatio * kWindowSize), (int) kWindowSize);
  engine_.AddPlayer(kDefaultPlayerName, 100.f); // Single player for now
  engine_.LoadTextures();
  card_back_ = ci::gl::Texture2d::create(ci::loadImage(ci::app::loadAsset("sprites/card_back_01.png")));
  bets_[kDefaultPlayerName] = 0;
  ci::audio::SourceFileRef sourceFile = ci::audio::load( ci::app::loadAsset( "sounds/shuffling-cards-4.wav" ) );
  shuffle_sound_ = ci::audio::Voice::create(sourceFile);
}

// todo: turn magic numbers into constants
void BlackjackApp::draw() {
  // TODO: Resize cards
  status_ = engine_.GetGameStatus();
  ci::gl::clear(kBackgroundColor);
  ci::gl::setMatricesWindow( getWindowSize());
  
  // Draw the house rules texts
  ci::gl::drawStringCentered("BLACKJACK PAYS 3 TO 2",
                             vec2(getWindowCenter().x, (float) card_back_->getHeight() + 3 * kMargin - kInstructionsFontSize), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  ci::gl::drawStringCentered("DEALER MUST STAND ON 17 AND DRAW TO 16",
                             vec2(getWindowCenter().x, (float) card_back_->getHeight() + 3 * kMargin), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  // todo: make a curve for the text
  
  // Draw instruction texts
  ci::gl::drawStringCentered("Before Round: [Up Arrow] - Increment bet, [Down Arrow] - Decrement bet, [Enter] - Confirm Bet/Start Round",
      vec2(getWindowCenter().x, getWindowHeight() - kMargin - kInstructionsFontSize), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  ci::gl::drawStringCentered("During Round: [H] - Hit. [S] - Stand. [D] - Double Down.",
                             vec2(getWindowCenter().x, getWindowHeight() - kMargin), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  
  // Draw a divider between instructions and the game area
  ci::gl::color(ci::Color("black"));
  size_t game_area_height = getWindowHeight() - kMargin - 2 * kInstructionsFontSize;
  ci::gl::drawSolidRect(ci::Rectf(vec2(kMargin, game_area_height), vec2(getWindowWidth() - kMargin, game_area_height + 5)));
  
  // Draw a card deck in the upper right corner
  ci::gl::color(ci::Color("white"));
  for (size_t i = 0; i < 10; i++) {
    size_t card_gap = i * 2; // Used to create a stacking effect
    ci::Rectf card_rect((float) getWindowWidth() - card_back_->getWidth() - kMargin - card_gap, (float) kMargin + card_gap,
                        (float) getWindowWidth() - kMargin - card_gap, (float) card_back_->getHeight() + kMargin + card_gap);
    ci::gl::draw(card_back_, card_rect);
  }

  DisplayPlayerInfo(game_area_height);
  
  if (round_started_) {
    DisplayCards();
  }
 
  // todo: dealer on top, deck on side, with two+ holes for dealer cards
  // todo: players on bottom, up to however many players, get 1 player first
  
}

// todo: implement this to get pre-round setup working
void BlackjackApp::keyDown(ci::app::KeyEvent event) {
  // Before the round starts, user may add/remove player, and players increase/decrease bets
  if (!round_started_) {
    switch (event.getCode()) {
      /* The five keys below are only valid commands before each round begins */
      case ci::app::KeyEvent::KEY_RETURN:
        // Once everyone has confirmed their bets, start the round
        if (bet_confirmed && !round_started_) {
          engine_.PlaceBets(bets_);
          engine_.ShuffleDeck();
          shuffle_sound_->start();
          engine_.DealCards();
          // todo: display cards
          round_started_ = true;
          draw();
          // todo: call draw() and implement control flow for when the game starts 
        } else if (!bet_confirmed && !round_started_) { // Player is confirming their bet
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
        for (auto it = kBetSizes.rbegin(); it != kBetSizes.rend(); ++it) { // Iterate from back to front (largest to smallest)
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
  switch (event.getCode()) {
    /* The three keys below are only valid during each round */
    case ci::app::KeyEvent::KEY_h:
      // Hit
      return;
    case ci::app::KeyEvent::KEY_s:
      // Stand
      return;
    case ci::app::KeyEvent::KEY_d:
      // Double down
      return;
  }
}

void BlackjackApp::DisplayPlayerInfo(size_t game_area_height) {
  // todo: extend to multiple players and put coordinates for display as member variable in player class
  
  status_ = engine_.GetGameStatus();
  
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
                             vec2(getWindowCenter().x - 2 * kMargin, game_area_height - kMargin), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  
  // Display the default or last bet
  ci::gl::drawString("Bet:        $" + bet_s,
                             vec2(getWindowCenter().x - 2 * kMargin, game_area_height - kMargin - kInstructionsFontSize), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  }

  void BlackjackApp::DisplayCards() {
    ci::gl::color(ci::Color("white"));
    
    const vector<Card>& player_cards = status_.players.front()->GetHand().GetCards();
    
    for (size_t i = 0; i < player_cards.size(); i++) {
      string a = player_cards[i].ToString();
      std::cout << a << std::endl;
      
      const ci::gl::Texture2dRef& card_sprite = player_cards[i].GetSprite();
      size_t card_gap = i * 25;
      size_t game_area_height = getWindowHeight() - 2 * kMargin - 2 * kInstructionsFontSize;
      ci::Rectf card_rect((float) getWindowCenter().x - card_sprite->getWidth() + card_gap, (float) game_area_height - card_sprite->getHeight() - kMargin,
                          (float) getWindowCenter().x + card_gap, (float) game_area_height - kMargin);
      ci::gl::draw(card_sprite, card_rect);
    }
  }
  
void DrawCards(const vector<Card>& cards) {
  
}
  
  
} // namespace blackjack

