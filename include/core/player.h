#pragma once

#include <core/card.h>
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
    
  /** Calculates the total value of the cards in the player's hand */
  size_t CalculateHandTotal() const;
  
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
  void PostBet(size_t bet);
  
  /** Add a card to the player's hand */
  void AddCard(Card card);

  /** Resets the player's hand */
  void ResetHand();

  /** Gets the amount the player bet in the round */
  size_t GetBet() const;
  
  /** Gets the name of the player */
  string GetName() const;
  
  // todo: decide whether to keep as vect of Card or string
  // determine how this will interact with the cli and gui
  vector<Card> GetHand() const;
 private:
  string name_; // the name of the player
  vector<Card> hand_; // the cards in the player's hand
  size_t balance; // the amount of money the player has
  size_t bet_; // the amount that the player bet in the round
};
} // namespace naivebayes