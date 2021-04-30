#pragma once

#include "card.h"
#include "hand.h"
#include <string>

using std::string;

namespace blackjack {

/**
 * Represents the player in a game of blackjack.
 * Holds information about the player's name, cards, balance, and bet.
 */
class Player {
 public:
  /** Default constructor */
  Player();
  
  /** Constructor with specified name and balance
   * 
   * @param name the name of the player
   * @param balance how much the player is beginning the game with
   */
  Player(string name, float balance);

  /** When the player wins the round by having a total more than the dealer or the dealer busts,
   *  Adds the double the bet to the player's balance and resets the bet to zero.
   */
  void Win();

  /** The player busts when their hand total is over 21 and loses when they have a total less than the dealer.
   *  Resets the bet to 0 without adding any money back the player's balance.
   */
  void Lose();

  /** When the dealer and player have the same hand total, they push.
   *  Adds the bet amount back to the player's balance and reset the bet to 0.
   */
  void Push();

  /** When the player has blackjack, they get paid 1.5x the original bet size.
   *  Adds 2.5x the bet amount to the player's balance and reset the bet.
   */
  void Blackjack();

  /** Post a bet for the specified amount.
   *  Removes the bet amount from the player's balance.
   * 
   * @param bet the amount to bet in the round
   */
  void PlaceBet(float bet);

  /** Gets the name of the player */
  string GetName() const;

  /** Gets the amount of money the player has at the table */
  float GetBalance() const;
  
  /** Gets the amount the player bet in the round */
  float GetBet() const;
  
  /** Gets the player's hand */
  Hand& GetHand();
  
  /** Returns whether the player's turn is done for the round*/
  bool IsTurnDone() const;
  
  /** Set whether the player's turn is done */
  void SetTurnDone(bool turn_done);
  
 private:
  string name_; // the name of the player
  float balance_; // the amount of money the player has
  float bet_; // the amount that the player bet in the round
  Hand hand_; // the player's hand containing their cards
  bool turn_done_; // whether the player's turn is done for the round
};
} // namespace naivebayes