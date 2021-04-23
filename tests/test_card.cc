#include <catch2/catch.hpp>

#include <core/card.h>

using blackjack::Card;

TEST_CASE("Card Constructor") {
  Card::Suit suit = Card::Diamonds;
  Card::Value value = Card::Ace;
  Card card(suit, value);
  SECTION("GetSuit") {
    REQUIRE(card.GetSuit() == Card::Diamonds);
  }
  SECTION("GetValue") {
    REQUIRE(card.GetValue() == Card::Ace);
    REQUIRE(card.GetValue() == 1);
  }
}

TEST_CASE("Enums work correctly") {
  SECTION("Suits (in)equality") {
    REQUIRE(Card::Hearts != Card::Clubs);
    REQUIRE(Card::Spades == Card::Spades);
  }
  SECTION("Values") {
    // Note: Ace being worth 1 or 11 will be handled by engine
    SECTION("Inequality") {
      REQUIRE(Card::Ace < Card::Two);
      REQUIRE(Card::Two < Card::Eight);
      REQUIRE(Card::Nine > Card::Three);
    }
    SECTION("Face cards all have the value 10, so they are equal") {
      REQUIRE(Card::King == Card::King);
      REQUIRE(Card::Jack == Card::Queen);
      REQUIRE(Card::King == Card::Jack);
    }
    SECTION("Arithmetic works") {
      REQUIRE(21 == Card::Ace + 2 * Card::King);
    }
  }
}