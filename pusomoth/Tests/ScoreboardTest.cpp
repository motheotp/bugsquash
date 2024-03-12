/**
 * @file ScoreboardTest.cpp
 * @author Motheo Treasure Puso
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <Scoreboard.h>
#include <memory>

TEST(ScoreboardTest, Getter) {
	Scoreboard board;

	ASSERT_EQ(0, board.GetFixed());

	board.IncreaseFixed();
	ASSERT_EQ(1, board.GetFixed());

	board.IncreaseFixed();
	ASSERT_EQ(2, board.GetFixed());

	board.SetScoreToZero();
	ASSERT_EQ(0, board.GetFixed());
}