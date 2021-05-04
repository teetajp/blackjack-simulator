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
  engine_.AddPlayer("Player", 100.f); // Single player for now
  auto texture = ci::loadImage(R"(D:\Projects\Cinder\my-projects\final-project-teetajp\data\sprites\cards.png)");
  spritesheet_ = ci::gl::Texture2d::create(texture);
}

// todo: turn magic numbers into constants
void BlackjackApp::draw() {
  ci::gl::clear(kBackgroundColor); // Clear the screen to the default background color
  ci::gl::drawStringCentered("Press H to hit. S to stand. D to double down.",
      vec2(getWindowCenter().x, getWindowHeight() - kMargin), ci::Color("black"), ci::Font("Arial", (float) kInstructionsFontSize));
  
//  ci::gl::draw(spritesheet_);
  // draw the texture itself in the upper right corner	
  ci::gl::setMatricesWindow( getWindowSize() );
  ci::Rectf drawRect( 0, 0, (float) spritesheet_->getWidth() / 3,
                      (float) spritesheet_->getHeight() / 3 );
  ci::gl::draw( spritesheet_, drawRect);
  /* Create bounds and shade in the background */
  
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
        // Start the round once players and bets are in (errors?)
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
}