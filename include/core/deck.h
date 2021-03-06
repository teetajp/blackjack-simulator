#pragma once

#include <core/card.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cinder/gl/Texture.h>

using std::vector;
using blackjack::Card;

namespace blackjack {

/**
 * Represents a deck of cards that can be shuffled, have cards taken from, and add decks onto.
 */
class Deck {
 public:
  // Need this to populate deck since we can't use ranged-based for loop for enums
  // Source: https://stackoverflow.com/questions/35313043/how-to-use-enum-class-values-as-part-of-for-loop
  static constexpr Card::Suit suits[] = {Card::Clubs, Card::Diamonds, Card::Hearts, Card::Spades}; // all possible suits
  static constexpr Card::Rank
      ranks[] = {Card::Ace, Card::Two, Card::Three, Card::Four, Card::Five, Card::Six, Card::Seven,
                 Card::Eight, Card::Nine, Card::Ten, Card::Jack, Card::Queen,
                 Card::King}; // all possible ranks

  /** Default constructor */
  Deck();

  /** Constructor w/ a spritesheet for the cards */
  Deck(const vector<vector<ci::gl::Texture2dRef>> *spritesheet);

  /**
   * Adds another 52-card deck to the current deck
   */
  void AddDeck();

  /** Draws the next card from the top of the deck
   *    Throws std::out_of_range exception if function is called when there is no card left
   * 
   * @return a card from the top of the deck
   */
  const Card &DrawCard();

  /**
   * Shuffles all the cards in the deck so it is in random order
   */
  void Shuffle();

  /** Calculates the number of remaining cards in the deck that has yet to be drawn */
  size_t CalculateRemainingCards() const;

 private:
  vector<Card>
      cards_; // a list of cards where the beginning represents the top and the end represents the bottom of the deck
  size_t next_card_index_; // the index of the next card in the deck
  const vector<vector<ci::gl::Texture2dRef>> *
      spritesheet_; // 2D vector of card sprites with the mapping [suit][rank], useful since if cards will share the same sprite if there are more than one deck
};
} // namespace blackjack