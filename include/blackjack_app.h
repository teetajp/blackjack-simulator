#pragma once

#include <cinder/audio/audio.h>
#include <cinder/audio/Voice.h>
#include "core/game_engine.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace blackjack {

/** Runs a game of blackjack with a GUI
 * 
 *  Game flow:
 *  1. (X) Draw the table
 *  2. (X) Start with one player w/ default buy-in of $100
 *  3. (X-) Player places bet between $0 and balance by pressing up/down key
 *  4. (X) Press enter once betting is done to start the round
 *  5. (X) Shuffle cards (play card shuffling sound effect)
 *  6. Deal cards, (deal animation preferred but hard to make, so save that once game is done)
 *     - Display players' cards then dealer's cards with one face up, one face down
 *  7. Dealer checks for blackjack if ace/ten card, then settle bets if he has it (go to end). If not, continue
 *     - Show message for any player w/ blackjack
 *  8. Each player takes action until out of moves or bust
 *  9. If some players not bust or blackjack, dealer shows card and dealer plays. If not bust, continue.
 *  10. Compare card value for player and dealer, pay players off accordingly.
 *     - Show an game result message.
 */
 class BlackjackApp : public ci::app::App {
  public:
   /** Default constructor */
   BlackjackApp();
   
   /** Called before the start of every round */
   void draw() override;
   
//   void update() override;

   /** Before each round, allow user to add/remove player and adjust bets */
   void keyDown(ci::app::KeyEvent event) override;
   
  private:
   static constexpr double kAspectRatio = (double) 4/3; // the ratio of horizontal pixel to vertical pixels 
   static const size_t kWindowSize = 900; // default window size in pixels
   static const size_t kMargin = 50; // margin from the window
   static const size_t kInstructionsFontSize = 30; // font size for the text telling playings what keys do what
   static const size_t kMaxPlayers = 3; // the maximum number of players/hand in this table (for this app)
   const ci::Color kBackgroundColor = ci::Color("green"); // casino green for the blackjack table
   const vector<float> kBetSizes = {0.f, 1.f, 5.f, 10.f, 20.f, 50.f, 100.f};
   const string kDefaultPlayerName = "Player";

   /* Resources */
  // todo: put some of the member variables here into their respective classes
   ci::gl::Texture2dRef card_back_; // sprite of the card back
   ci::audio::VoiceRef shuffle_sound_; // sound to play when deck is shuffled
   
   /* Game Engine-related */
   GameEngine engine_; // the blackjack game engine
   map<string, float> bets_; // the bets of each player for the round
   bool round_started_ = false; // whether the round has started  
   GameStatus status_; // players' information in the game
   bool bet_confirmed = false; // whether a player has confirmed their bet (turn into vector for 2+ players)
   
   
  /** Displays the balance and bet for each player */
  void DisplayPlayerInfo(size_t game_area_height);
  
  void DisplayCards();
  
  /** Displays the dealer's cards */
  void DisplayDealerCards();
 };
}