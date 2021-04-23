#include <catch2/catch.hpp>
#include <core/hand.h>

using blackjack::Card;
using blackjack::Hand;

TEST_CASE("Hand Constructor") {
  Hand hand;
  REQUIRE(hand.GetCards().empty());
  REQUIRE(hand.GetHandValue() == 0);
}

TEST_CASE("Add Card") {
  Hand hand;
  Card card(Card::Clubs, Card::Seven);
  hand.AddCard(card);
  REQUIRE(hand.GetCards().size() == 1);
  REQUIRE(hand.GetCards().at(0).GetSuit() == Card::Clubs);
  REQUIRE(hand.GetCards().at(0).GetRank() == Card::Seven);  
}

TEST_CASE("Reset Hand") {
  Hand hand;
  Card card(Card::Hearts, Card::Queen);
  hand.AddCard(card);
  
}