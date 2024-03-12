/**
 * @file LevelManagerTest.cpp
 * @author Motheo Treasure Puso
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <LevelManager.h>
#include <Level.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>


TEST(LevelManagerTest, XmlLevelLoading) {
	// Generate dummy app so I can actually access the wxStandardPaths
	wxApp::SetInstance(new wxApp());
	wxInitAllImageHandlers();

	// Grab directory
	wxStandardPaths& standardPaths = wxStandardPaths::Get();

	std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
	wxFileName filename(resourcesDir);

//#ifdef __WXMAC__
	//filename.RemoveLastDir();
	//filename.RemoveLastDir();
	// TODO: Untested, I don't use a mac, Just tested and when not commented out it fails the test, so I commmented it out.
//#endif

	resourcesDir = filename.GetPath();
	LevelManager levelManager(resourcesDir);

	// Load first level
	levelManager.ToLevel(0);

	// Verify that the first level loads
	std::shared_ptr<Level> firstLevel = levelManager.GetLevel();
	ASSERT_NE(firstLevel, nullptr);

	// Check if the program is in the right position
	ASSERT_NE(firstLevel->HitTest(1000, 500), nullptr);

	// Check if the Null Bug is in the right position
	ASSERT_NE(firstLevel->HitTest(-100, 400), nullptr);

	// TODO: Check future bugs as they are added
}
