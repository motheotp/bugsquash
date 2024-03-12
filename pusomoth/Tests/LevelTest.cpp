/**
 * @file LevelTest.cpp
 * @author Motheo Treasure Puso
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Scoreboard.h>
#include <LevelManager.h>

using namespace std;

TEST(LevelTest, Constructor) {
    shared_ptr<Scoreboard> board;
    LevelManager manager(L".");
}

TEST(LevelTest, LoadLevelZero)
{
	// Creates board and level manager
    shared_ptr<Scoreboard> board;
    LevelManager manager (L".");

	// Sets level to 0
    manager.ToLevel(0);

	// Ensures that level zero has the correct number of programs and bugs (includes features)
	ASSERT_EQ(1, manager.GetNumPrograms());
	ASSERT_EQ(7, manager.GetNumBugs());
}

TEST(LevelTest, LoadLevelOne)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 1
	manager.ToLevel(1);

	// Ensures that level one has the correct number of programs and bugs (includes features)
	ASSERT_EQ(1, manager.GetNumPrograms());
	ASSERT_EQ(12, manager.GetNumBugs());
}

TEST(LevelTest, LoadLevelTwo)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 2
	manager.ToLevel(2);

	// Ensures that level two has the correct number of programs and bugs (includes features)
	ASSERT_EQ(3, manager.GetNumPrograms());
	ASSERT_EQ(24, manager.GetNumBugs());
}

TEST(LevelTest, LoadLevelThree)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 3
	manager.ToLevel(3);

	// Ensures that level three has the correct number of programs and bugs (includes features)
	ASSERT_EQ(2, manager.GetNumPrograms());
	ASSERT_EQ(20, manager.GetNumBugs());
}