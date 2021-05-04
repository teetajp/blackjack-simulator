#pragma once

#include "core/game_engine.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace blackjack {

/** Runs a game of blackjack with a GUI
 * 
 *  Game flow:
 *  1. Draw the table
 *  2. Start with one player w/ default buy-in of $100
 *  3. Player places bet between $0 and balance by pressing up/down key
 *  4. Press enter once betting is done to start the round
 *  5. Shuffle cards (play card shuffling sound effect)
 *  6. Deal cards, (deal animation preferred but hard to make, so save that once game is done)
 *     - Display players' cards then dealer's cards with one face up, one face down
 *  7. Dealer checks for blackjack if ace/ten card, then settle bets if he has it (go to end). If not, continue
 *     - Show message for any player w/ blackjack
 *  8. Each player takes action until out of moves or bust
 *  9. If some players not bust or blackjack, dealer shows card and dealer plays. If not bust, continue.
 *  10. Compare card value for player and dealer, pay players off accordingly.
 *     - Show an game result merssage.
 */
 class BlackjackApp : public ci::app::App {
  public:
   /** Default constructor */
   BlackjackApp();
   
   /** Called before the start of every round */
   void draw() override;
   
   void update() override;

   void keyDown(ci::app::KeyEvent event) override;
   
   
  private:
   static constexpr  double kWindowSize = 875; // default window size in pixels
   static constexpr double kMargin = 100; // margin from the window
   static const size_t kInstructionsFontSize = 30; // font size for the text telling playings what keys do what
   static const size_t kMaxPlayers = 3; // the maximum number of players/hand in this table (for this app)
   const ci::Color kBackgroundColor = ci::Color("green"); // casino green for the blackjack table
   
   
   GameEngine engine;
   bool round_started = false;
   
   
   
 };
}