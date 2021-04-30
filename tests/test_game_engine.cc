#include <catch2/catch.hpp>
#include <core/game_engine.h>
#include <sstream>

using blackjack::GameEngine;
using std::stringstream;

TEST_CASE("Constructor") {
  REQUIRE_NOTHROW(GameEngine());
}

//TEST_CASE("AddPlayer");

//TEST_CASE("StartRound");
//
// todo: need to implement from GUI
//TEST_CASE("RequestBets") {
//  GameEngine engine;
//  engine.AddPlayer("TJ", 100);
//  stringstream ss("10");
//  engine.RequestBets(ss);
//  REQUIRE(engine.GetPlayer("TJ").GetBet() == 10);
//}

//TEST_CASE("DealCards");
//
//TEST_CASE("PayBlackjacks");
//
//TEST_CASE("PlayerPlays");
//
//TEST_CASE("DealerPlays");
//
//TEST_CASE("SettleBets");
//
//TEST_CASE("ResetHands");