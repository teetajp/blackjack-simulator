#pragma once

#include <core/card.h>
#include <vector>

using std::vector;

namespace blackjack {

/**
 * Represents a deck of cards that can be shuffled, have cards taken from, and add decks onto.
 */
class Deck {
 public:
  /**
   * Default constructor
   */
  Deck();
  
  /**
   * Shuffles all the cards in the deck so it is in random order
   */
  void Shuffle();
  
  /** Gets the next card from the top of the deck
   * 
   * @return a card from the top of the deck
   */
  Card GetCard();
  
  /**
   * Adds another 52-card deck to the current deck
   */
  void AddDeck();
  
 private:
  vector<Card> cards_; // a list of cards where the beginning represents the top and the end represents the bottom of the deck
  size_t next_card_index; // the index of the next card in the deck
};
} // namespace blackjack