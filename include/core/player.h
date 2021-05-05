#pragma once

#include "card.h"
#include "hand.h"
#include "deck.h"
#include <string>

using std::string;

namespace blackjack {

/** All the actions a player can take during a round */
static const vector<string> kAllActions = {
    "hit", "stand", "double"
};

/**
 * Represents the player in a game of blackjack.
 * Holds information about the player's name, cards, balance, and bet.
 */
class Player {
 public:

  enum Result { // state of the player after the round
    Won, Tied, Lost, AwaitingComparison, InProgress, NotPlaying
  };

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

  /** Doubles the bet of a player and draws a final card */
  void DoubleDown(Deck &deck);

  /** Adds a card to the hand */
  void Hit(Deck &deck);

  /** Clears all the cards from the player's hand */
  void ResetHand();

  /** Set the state of the player (won, lost, tied, in progress) */
  void SetResult(Result result);

  /** Updates the actions a player can take */
  void UpdateActions();

  /** Gets the name of the player */
  string GetName() const;

  /** Gets the amount of money the player has at the table */
  float GetBalance() const;

  /** Gets the amount the player bet in the round */
  float GetBet() const;

  /** Gets the player's hand */
  const Hand &GetHand() const;

  /** Returns the result of the round */
  Result GetResult() const;

  /** Returns the actions a player can take currently */
  vector<string> GetActions() const;

  /** Returns the result in the form of a string */
  string ResultToString() const;

 private:
  string name_; // the name of the player
  float balance_; // the amount of money the player has
  float bet_; // the amount that the player bet in the round
  Hand hand_; // the player's hand containing their cards
  Result result_; // result of the round
  vector<string> available_actions_; // actions the player can take currently
};
} // namespace naivebayes