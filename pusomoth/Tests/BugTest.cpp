/**
 * @file BugTest.cpp
 * @author Motheo Treasure Puso
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <LevelManager.h>
#include <Item.h>
#include <Scoreboard.h>

using namespace std;

TEST(BugTest, Constructor) {
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");
}

TEST(BugTest, LevelZeroBugs)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 0
	manager.ToLevel(0);

	// Ensures that level zero has the correct number of each bug
	ASSERT_EQ(1, manager.GetNumBugsNull());
	ASSERT_EQ(1, manager.GetNumBugsRedundancy());
	ASSERT_EQ(3, manager.GetNumBugsGarbage());
	ASSERT_EQ(2, manager.GetNumBugsFeature());
}

TEST(BugTest, LevelOneBugs)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 1
	manager.ToLevel(1);

	// Ensures that level one has the correct number of each bug
	ASSERT_EQ(3, manager.GetNumBugsNull());
	ASSERT_EQ(2, manager.GetNumBugsRedundancy());
	ASSERT_EQ(5, manager.GetNumBugsGarbage());
	ASSERT_EQ(2, manager.GetNumBugsFeature());
}

TEST(BugTest, LevelTwoBugs)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 2
	manager.ToLevel(2);

	// Ensures that level two has the correct number of each bug
	ASSERT_EQ(7, manager.GetNumBugsNull());
	ASSERT_EQ(2, manager.GetNumBugsRedundancy());
	ASSERT_EQ(8, manager.GetNumBugsGarbage());
	ASSERT_EQ(7, manager.GetNumBugsFeature());
}

TEST(BugTest, LevelThreeBugs)
{
	// Creates board and level manager
	shared_ptr<Scoreboard> board;
	LevelManager manager(L".");

	// Sets level to 3
	manager.ToLevel(3);

	// Ensures that level three has the correct number of each bug
	ASSERT_EQ(6, manager.GetNumBugsNull());
	ASSERT_EQ(1, manager.GetNumBugsRedundancy());
	ASSERT_EQ(4, manager.GetNumBugsGarbage());
	ASSERT_EQ(2, manager.GetNumBugsFeature());
}