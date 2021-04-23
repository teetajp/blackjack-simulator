#include <catch2/catch.hpp>

#include <core/deck.h>

using blackjack::Deck;

TEST_CASE("Deck Constructor") {
  Deck deck;
  REQUIRE(deck.CalculateRemainingCards() == 52);
  const Card& first_card = deck.DrawCard();
  REQUIRE(first_card.GetSuit() == Card::Clubs);
  REQUIRE(first_card.GetValue() == Card::Ace);
  const Card& second_card = deck.DrawCard();
  REQUIRE(second_card.GetSuit() == Card::Clubs);
  REQUIRE(second_card.GetValue() == Card::Two);
  // Draw the other cards until we get the next suit
  size_t clubs_remaining = 0;
  while (deck.DrawCard().GetSuit() != Card::Diamonds) {
    clubs_remaining++;
  }
  REQUIRE(clubs_remaining == 11);
  const Card& fifteenth_card = deck.DrawCard(); // the ace is drawn in the for loop
  REQUIRE(fifteenth_card.GetSuit() == Card::Diamonds);
  REQUIRE(fifteenth_card.GetValue() == Card::Two);
  // todo: go through all the suits
}

TEST_CASE("Add Deck") {
  Deck deck;
  deck.AddDeck(); // should have 104 cards now
  size_t total_cards = 0;
  SECTION("Correct number of cards per suit") {
    size_t clubs = 0;
    size_t diamonds = 0;
    size_t hearts = 0;
    size_t spades = 0;
    for (size_t i = 0; i < 104; i++) {
      const Card::Suit curr_suit = deck.DrawCard().GetSuit();
      
      if (curr_suit == Card::Clubs) {
        clubs++;
      } else if (curr_suit == Card::Diamonds) {
        diamonds++;
      } else if (curr_suit == Card::Hearts) {
        hearts++;
      } else if (curr_suit == Card::Spades) {
        spades++;
      }
    }
    REQUIRE(clubs == 26);
    REQUIRE(diamonds == 26);
    REQUIRE(hearts == 26);
    REQUIRE(spades == 26);
  }
  // SECTION("Correct number of each card rank")
}

// TEST_CASE("Shuffle")
 TEST_CASE("DrawCard") {
  Deck deck;
  SECTION("Draw more than there are cards in the deck") {
    for (size_t i = 0; i < 52; i++) {
      deck.DrawCard();
    }
    REQUIRE_THROWS_AS(deck.DrawCard(), std::out_of_range);
  }
}
 TEST_CASE("CalculateRemainingCards") {
  Deck deck;
  REQUIRE(deck.CalculateRemainingCards() == 52);
  
  SECTION("After drawing a card") {
    deck.DrawCard();
    REQUIRE(deck.CalculateRemainingCards() == 51);
  }
  SECTION("After adding a deck") {
    deck.AddDeck();
    REQUIRE(deck.CalculateRemainingCards() == 104);
  }
  SECTION("After shuffling") {
    deck.Shuffle();
    REQUIRE(deck.CalculateRemainingCards() == 52);
  }
}