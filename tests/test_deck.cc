#include <catch2/catch.hpp>

#include <core/deck.h>
#include <map>

using std::map;
using blackjack::Deck;

// Function prototype
void CheckAllCards(Deck& deck, size_t num_decks);

TEST_CASE("Deck Constructor") {
  Deck deck;
  REQUIRE(deck.CalculateRemainingCards() == 52);
  CheckAllCards(deck, 1);
}

TEST_CASE("Add Deck") {
  Deck deck; // already has one deck added
  deck.AddDeck(); // should have 2 decks (104 cards) now
  SECTION("Correct number of cards per suit and rank") {
    REQUIRE(deck.CalculateRemainingCards() == 104);
    CheckAllCards(deck, 2);
  }
}

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

TEST_CASE("Shuffle") {
  // Test that after a shuffle, any of the cards is in a different permutation
  Deck deck;
  vector<Card> pre_shuffle;
  for (size_t i = 0; i < 52; i++) {
    const Card& card = deck.DrawCard();
    pre_shuffle.push_back(card);
  }
  
  deck.Shuffle();
  bool has_diff_permutation = false;
  
  for (size_t i = 0; i < 52; i++) {
    Card card = deck.DrawCard();
    
    if (pre_shuffle[i].GetSuit() != card.GetSuit() || pre_shuffle[i].GetRank() != card.GetRank()) {
      has_diff_permutation = true;
      break;
    }
  }
  REQUIRE(has_diff_permutation);
}

void CheckAllCards(Deck& deck, size_t num_decks) {
  map<Card::Suit, size_t> suits_count;
  map<Card::Rank, size_t> ranks_count;
  // Default count should automatically be initialized to 0 for each suit and rank.

  for (size_t i = 0; i < num_decks * 52; i++) { // 52 cards/deck * num_deck = 52 * num_deck cards/deck
    const Card& card = deck.DrawCard();
    suits_count[card.GetSuit()]++;
    ranks_count[card.GetRank()]++;
  }
  
  for (Card::Suit suit : deck.suits) {
    REQUIRE(suits_count[suit] == num_decks * 13); // 13 cards/suit x num_deck decks = 13 * num_deck cards per suit in deck
  }
  
  for (Card::Rank rank : deck.ranks) {
    if (rank < 10) { // All non-face/ten card
      REQUIRE(ranks_count[rank] == num_decks * 4); // 4 cards/rank x num_deck decks = 4 * num_deck cards per rank in deck
    } else if (rank == 10) {
      REQUIRE(ranks_count[rank] == num_decks * 16); // (num_deck * 4) cards per rank * 4 ranks with rank of 10 = 16 * num_deck cards with rank of 10
    }
  }
}