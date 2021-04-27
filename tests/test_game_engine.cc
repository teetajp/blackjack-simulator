#include <catch2/catch.hpp>
#include <core/game_engine.h>

using blackjack::GameEngine;

TEST_CASE("Constructor") {
  REQUIRE_NOTHROW(GameEngine());
}

//TEST_CASE("AddPlayer");

//TEST_CASE("StartRound");
//
//TEST_CASE("RequestBets"); // todo: need to implement from GUI
//
//TEST_CASE("DealCards");
//
//TEST_CASE("CheckBlackjack");
//
//TEST_CASE("PlayerPlays");
//
//TEST_CASE("DealerPlays");
//
//TEST_CASE("SettleBets");
//
//TEST_CASE("ResetHands");