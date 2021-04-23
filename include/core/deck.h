#pragma once

#include <core/card.h>
#include <vector>
#include <algorithm>

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
  const vector<Card::Suit> suits = {Card::Clubs, Card::Diamonds, Card::Hearts, Card::Spades}; // all possible suits
  const vector<Card::Value> values = {Card::Ace, Card::Two, Card::Three, Card::Four, Card::Five, Card::Six, Card::Seven,
                                      Card::Eight, Card::Nine, Card::Ten, Card::Jack, Card::Queen, Card::King}; // all possible values
  
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
  const Card& GetCard() const;
  
  /**
   * Adds another 52-card deck to the current deck
   */
  void AddDeck();
  
 private:
  vector<Card> cards_; // a list of cards where the beginning represents the top and the end represents the bottom of the deck
  size_t next_card_index; // the index of the next card in the deck
};
} // namespace blackjack