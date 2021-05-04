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
  auto texture = ci::loadImage(R"(D:\Projects\Cinder\my-projects\final-project-teetajp\data\sprites\card_back_01.png)");
  card_back_ = ci::gl::Texture2d::create(texture);
}

// todo: turn magic numbers into constants
void BlackjackApp::draw() {
  // TODO: Resize cards
  ci::gl::clear(kBackgroundColor);
  ci::gl::setMatricesWindow( getWindowSize());
  
  // Draw the house rules texts
  ci::gl::drawStringCentered("BLACKJACK PAYS 3 TO 2",
                             vec2(getWindowCenter().x, (float) card_back_->getHeight() + 2 * kMargin - kInstructionsFontSize), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  ci::gl::drawStringCentered("DEALER MUST STAND ON 17 AND DRAW TO 16",
                             vec2(getWindowCenter().x, (float) card_back_->getHeight() + 2 * kMargin), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  // todo: make a curve for the text
  
  // Draw instruction texts
  ci::gl::drawStringCentered("Before Round: [Up Arrow] - Increment bet, [Down Arrow] - Decrement bet",
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
  
  /* Create bounds and shade in the background */
  // Good card gap for stacking two is 15-20 on the x
//  vec2 pixel_top_left(0, 0);
//  vec2 pixel_bottom_right(kMargin+500, kMargin+500);
//
//  ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);

 
//  ci::gl::drawSolidRect(pixel_bounding_box);
//  
 
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
        // Start the round once players and bets are in
        engine_.ShuffleDeck();
        // todo: play sound
        engine_.DealCards();
        // todo: display cards
        round_started_ = true;
        return;
      case ci::app::KeyEvent::KEY_UP:
        // Increments bet amount by $5, maximum is the player's balance
        
        return;
      case ci::app::KeyEvent::KEY_DOWN:
        // Decrements bet amount by $5, minimum is $1
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
  
  float bet = 0; // Default bet is 0, let player increment
  bets[kDefaultPlayerName] = bet;
  GameStatus status = engine_.GetGameStatus();
  
  // Display the player balance
  float balance = status.players.front()->GetBalance();

  // Convert balance to a two-decimal point string
  // Snippet from: https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << balance;
  std::string balance_s = stream.str();
  
  ci::gl::drawStringCentered("Balance: " + balance_s,
                             vec2(getWindowCenter().x, game_area_height + kInstructionsFontSize), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  
  // Display the default or last bet
  
    
  
  }
}