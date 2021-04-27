#include <catch2/catch.hpp>

#include <core/dealer.h>
#include <core/deck.h>

using blackjack::Dealer;
using blackjack::Deck;

TEST_CASE("Dealer Constructor") {
  REQUIRE_NOTHROW(Dealer());
}

TEST_CASE("DealerPlay") {
  Deck deck;
  Dealer dealer;
  
  SECTION("Hits until 17 or more") {
    dealer.DealerPlay(&deck);
    REQUIRE(dealer.GetHand().CalculateHandValue() >= 17);
    REQUIRE(dealer.GetHand().GetCards().size() >= 2);
  }
  
  SECTION("Hits on soft 17") {
    dealer.GetHand().AddCard(Card(Card::Hearts, Card::Ace));
    dealer.GetHand().AddCard(Card(Card::Spades, Card::Six));
    REQUIRE(dealer.GetHand().GetCards().size() == 2);
    REQUIRE_NOTHROW(dealer.DealerPlay(&deck));
    REQUIRE(dealer.GetHand().GetCards().size() > 2);
    REQUIRE(dealer.GetHand().HasAce());
    REQUIRE(dealer.GetHand().CalculateHandValue() >= 17);
  }
}