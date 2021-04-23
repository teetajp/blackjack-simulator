#include <catch2/catch.hpp>

#include <core/card.h>

using blackjack::Card;

TEST_CASE("Card Constructor") {
  Card::Suit suit = Card::Diamonds;
  Card::Rank rank = Card::Ace;
  Card card(suit, rank);
  SECTION("GetSuit") {
    REQUIRE(card.GetSuit() == Card::Diamonds);
  }SECTION("GetRank") {
    REQUIRE(card.GetRank() == Card::Ace);
    REQUIRE(card.GetRank() == 1);
  }
}

TEST_CASE("Enums work correctly") {
  SECTION("Suits (in)equality") {
    REQUIRE(Card::Hearts != Card::Clubs);
    REQUIRE(Card::Spades == Card::Spades);
  }SECTION("Ranks") {
    // Note: Ace being worth 1 or 11 will be handled by engine
    SECTION("Inequality") {
      REQUIRE(Card::Ace < Card::Two);
      REQUIRE(Card::Two < Card::Eight);
      REQUIRE(Card::Nine > Card::Three);
    }SECTION("Face cards all have the value 10, so they are equal") {
      REQUIRE(Card::King == Card::King);
      REQUIRE(Card::Jack == Card::Queen);
      REQUIRE(Card::King == Card::Jack);
    }SECTION("Arithmetic works") {
      REQUIRE(21 == Card::Ace + 2 * Card::King);
    }
  }
}

TEST_CASE("Equals/not equals operator overload") {
  SECTION("Same suit and rank") {
    Card first(Card::Hearts, Card::Queen);
    Card second(Card::Hearts, Card::Queen);
    REQUIRE(first == second);
    REQUIRE_FALSE(first != second);
  }SECTION("Different suit and rank") {
    SECTION("Different suit") {
      Card first(Card::Hearts, Card::Queen);
      Card second(Card::Spades, Card::Queen);
      REQUIRE_FALSE(first == second);
      REQUIRE(first != second);
    }SECTION("Different rank") {
      Card first(Card::Spades, Card::Ace);
      Card second(Card::Spades, Card::King);
      REQUIRE_FALSE(first == second);
      REQUIRE(first != second);
    }
  }
}