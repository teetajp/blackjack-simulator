#include <catch2/catch.hpp>

#include <core/deck.h>
#include <map>

using std::map;
using blackjack::Deck;

TEST_CASE("Deck Constructor") {
  Deck deck;
  REQUIRE(deck.CalculateRemainingCards() == 52);
  const Card& first_card = deck.DrawCard();
  REQUIRE(first_card.GetSuit() == Card::Clubs);
  REQUIRE(first_card.GetRank() == Card::Ace);
  const Card& second_card = deck.DrawCard();
  REQUIRE(second_card.GetSuit() == Card::Clubs);
  REQUIRE(second_card.GetRank() == Card::Two);
  // Draw the other cards until we get the next suit
  size_t clubs_remaining = 0;
  while (deck.DrawCard().GetSuit() != Card::Diamonds) {
    clubs_remaining++;
  }
  REQUIRE(clubs_remaining == 11);
  const Card& fifteenth_card = deck.DrawCard(); // the ace is drawn in the for loop
  REQUIRE(fifteenth_card.GetSuit() == Card::Diamonds);
  REQUIRE(fifteenth_card.GetRank() == Card::Two);
  // todo: go through all the suits
}

TEST_CASE("Add Deck") {
  Deck deck;
  deck.AddDeck(); // should have 104 cards now
  size_t total_cards = 0;
  SECTION("Correct number of cards per suit and rank") {
    map<Card::Suit, size_t> suits_count;
    map<Card::Rank, size_t> ranks_count;
    // Default count should automatically be initialized to 0 for each suit and rank.
    
    for (size_t i = 0; i < 104; i++) {
      const Card& card = deck.DrawCard();
      suits_count[card.GetSuit()]++;
      ranks_count[card.GetRank()]++;
    }
    for (Card::Suit suit : deck.suits) {
      REQUIRE(suits_count[suit] == 26); // 13 cards/suit x 2 decks = 26 cards per suit in deck
    }
    for (Card::Rank rank : deck.ranks) {
      if (rank < 10) { // All non-face/ten card
        REQUIRE(ranks_count[rank] == 8); // 4 cards/rank x 2 decks = 8 cards per rank in deck
      } else if (rank == 10) {
        REQUIRE(ranks_count[rank] == 32); // 8 cards per rank * 4 ranks with rank of 10 = 32 cards with rank of 10
      }
      
    }
  }
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