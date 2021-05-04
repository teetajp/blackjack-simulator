#pragma once

#include <vector>
#include <string>

using std::string;
using std::vector;


namespace blackjack {

/**
 * Represents a card in a standard 52-card deck.
 * Each card contains a suit and a rank with a value attached to it.
 */
class Card {
 public:
  enum Suit { // all the possible suits of a card
    Clubs, Diamonds, Hearts, Spades
  };

  enum Rank { // all the possible ranks and the corresponding values of a card
    Ace = 1, // Ace can be 1 or 11 (handled by engine)
    Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10,
    Jack = 10, Queen = 10, King = 10 // Face cards are worth 10
  };

  /** Default constructor
   * 
   * @param suit the suit of the card (Clubs, Diamonds, Hearts, Spades)
   * @param rank the symbol of the card (Ace, 2, 3, ..., 10, Jack, Queen, King)
   */
  Card(Suit suit, Rank rank);

  /** Returns the suit of the card */
  Suit GetSuit() const;

  /** Returns the card rank */
  Rank GetRank() const;
  
  /** Returns a string describing the card */
  string ToString() const;

  /** Equal to operator overload - check if suit AND rank is the same */
  friend bool operator==(const Card &first, const Card &second);

  /** Not equal to operator overload - check if either suit or rank is not the same */
  friend bool operator!=(const Card &first, const Card &second);

 private:
  Suit suit_; // the suit of the card
  Rank rank_; // the rank of the card and its corresponding value
//  ci::gl::Texture2dRef sprite_; // the sprite of the card
};
} // namespace blackjack