#include <catch2/catch.hpp>
#include <core/hand.h>

using blackjack::Card;
using blackjack::Hand;

TEST_CASE("Hand Constructor") {
  Hand hand;
  REQUIRE(hand.GetCards().empty());
  REQUIRE(hand.CalculateHandValue() == 0);
}

TEST_CASE("Add Card") {
  Hand hand;
  Card card(Card::Clubs, Card::Seven);
  hand.AddCard(card);
  REQUIRE(hand.GetCards().size() == 1);
  REQUIRE(hand.GetCards().at(0) == card);
}

TEST_CASE("Reset Hand") {
  Hand hand;
  hand.AddCard(Card(Card::Hearts, Card::Queen));
  hand.ResetHand();
  REQUIRE(hand.GetCards().empty());
  REQUIRE(hand.CalculateHandValue() == 0);
}

TEST_CASE("CalculateHandValue") {
  // Private method so do it by adding cards and getting the hand value
  Hand hand;

  SECTION("One card") {
    hand.AddCard(Card(Card::Hearts, Card::Seven));
    REQUIRE(hand.CalculateHandValue() == 7);
  }
  SECTION("Multiple cards") {
    hand.AddCard(Card(Card::Hearts, Card::Seven));
    hand.AddCard(Card(Card::Clubs, Card::Two));
    hand.AddCard(Card(Card::Diamonds, Card::King));
    REQUIRE(hand.CalculateHandValue() == 19);
  }
  SECTION("Soft Ace (1 Ace + any non-Ace card)") {
    SECTION("Ace + 10-valued card (Blackjack)") {
      hand.AddCard(Card(Card::Spades, Card::Ace));
      hand.AddCard(Card(Card::Clubs, Card::Jack));
      REQUIRE(hand.CalculateHandValue() == 21);
    }SECTION("Ace + non-10-valued card") {
      hand.AddCard(Card(Card::Spades, Card::Ace));
      hand.AddCard(Card(Card::Clubs, Card::Six));
      REQUIRE(hand.CalculateHandValue() == 17);
    }
  }
  SECTION("Hard Ace (Ace counted as 1 since counting it as 11 would make hand go bust)") {
    hand.AddCard(Card(Card::Spades, Card::Ace));
    hand.AddCard(Card(Card::Clubs, Card::Nine));
    hand.AddCard(Card(Card::Clubs, Card::Two));
    REQUIRE(hand.CalculateHandValue() == 12);
  }
  SECTION("Hard Ace + Card that would make hand go bust") {
    hand.AddCard(Card(Card::Spades, Card::Seven));
    hand.AddCard(Card(Card::Clubs, Card::Eight)); // 7 + 8 = 15
    hand.AddCard(Card(Card::Clubs, Card::Ace)); // 7 + 8 + 1 = 16
    hand.AddCard(Card(Card::Hearts, Card::Eight)); // 7 + 8 + 1 + 8 = 24
    REQUIRE(hand.CalculateHandValue() == 24);
  }
}

TEST_CASE("HasAce") {
  Hand hand;
  SECTION("Hand contains Ace") {
    hand.AddCard(Card(Card::Clubs, Card::Ace));
    REQUIRE(hand.HasAce());
  }SECTION("Hand doesn't contain Ace") {
    hand.AddCard(Card(Card::Clubs, Card::Four));
    REQUIRE_FALSE(hand.HasAce());
  }
}

TEST_CASE("HasBlackjack") {
  Hand hand;
  SECTION("First two cards contain an Ace and a ten-valued card in any order") {
    hand.AddCard(Card(Card::Diamonds, Card::Ace));
    hand.AddCard(Card(Card::Spades, Card::Ten));
    REQUIRE(hand.HasBlackjack());
  }SECTION("Hand value adds up to 21 but is not blackjack") {
    hand.AddCard(Card(Card::Diamonds, Card::Ace));
    hand.AddCard(Card(Card::Spades, Card::Six));
    hand.AddCard(Card(Card::Hearts, Card::Five));
    REQUIRE_FALSE(hand.HasBlackjack());
  }SECTION("Hand contains Ace and a ten-valued card but its not the first two cards") {
    hand.AddCard(Card(Card::Diamonds, Card::Jack));
    hand.AddCard(Card(Card::Spades, Card::Two));
    hand.AddCard(Card(Card::Hearts, Card::Ace));
    REQUIRE_FALSE(hand.HasBlackjack());
  }
}