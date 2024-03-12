/**
 * @file Level.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "Level.h"
#include "LevelManager.h"
#include "Program.h"
#include "BugNull.h"
#include "BugNullFat.h"
#include "BugGarbage.h"
#include "BugGarbageFat.h"
#include "BugRedundancy.h"
#include "BugFeature.h"
#include "BugFatFunc.h"
#include "BugZombie.h"
#include "BugRace.h"
#include <sstream>

#include <wx/graphics.h>
#include "Game.h"
#include "LevelEndCheck.h"
using namespace std;

/// level starting time
const double StartingTime = 2;
/// The font color to use
const wxColour FontColor = wxColour(0, 200, 200);
/// start and end font size
const int FontHeightFactor = 10;

/**
 * Level Constructor
 * @param levelNumber the current level number
 * @param manager the level manager object
 * @param filename the name of the level file
 */
Level::Level(int levelNumber, LevelManager *manager, std::wstring filename): mLevelNumber(levelNumber), mManager(manager)
{
	LoadFromXml(filename);
}

/**
 * load from xml file
 * @param filename
 */
void Level::LoadFromXml(wstring filename)
{
	wxXmlDocument xmlDoc;
	if(!xmlDoc.Load(filename))
	{
		wxMessageBox(L"Unable to load level file");
		return;
	}

	// Once we know it is open, clear the existing data
	Clear();

	// Get the XML document root node
	auto root = xmlDoc.GetRoot();
	mLevelName = root->GetAttribute(L"level").ToStdWstring();

	auto game = root->GetChildren();
	mGameName = game->GetAttribute(L"name").ToStdWstring();

	//
	// Traverse the children of the root
	// node of the XML document in memory!!!!
	//
	auto node = game;
	for( ; node; node=node->GetNext())
	{
		// A pointer for the item we are loading
		shared_ptr<Program> program;

		auto name = node->GetName();
		if (name == L"program")
		{
			mNumPrograms += 1;
			wstring tempName = L"";
			program = make_shared<Program>(this, tempName);
			mItems.push_back(program);
			program->XmlLoad(node);

			shared_ptr<Item> subItem;
			auto child = node->GetChildren();
			for( ; child; child=child->GetNext())
			{
				shared_ptr<Item> childItem;
				name = child->GetName();
				if(name == L"bug")
				{
					mNumBugs += 1;
					// Find the type of the item
					auto type = child->GetAttribute(L"type");
					if (type == L"null")
					{
						mNumBugsNull += 1;
						if(child->GetChildren())
						{
							childItem = make_shared<BugNullFat>(this, program);
						}
						else
						{
							childItem = make_shared<BugNull>(this, program);
						}
					}
					if (type == L"garbage")
					{
						mNumBugsGarbage += 1;
						if(child->GetChildren())
						{
							childItem = make_shared<BugGarbageFat>(this, program);
						}
						else
						{
							childItem = make_shared<BugGarbage>(this, program);
						}
					}
					if (type == L"redundancy")
					{
						mNumBugsRedundancy += 1;
						childItem = make_shared<BugRedundancy>(this, program);
					}
					if (type == L"zombie")
					{
						childItem = make_shared<BugZombie>(this, program);
					}
					if (type == L"race")
					{
						childItem = make_shared<BugRace>(this, program);
					}
				}
				if(name == L"feature")
				{
					mNumBugs += 1; // We are counting a feature as a bug
					mNumBugsFeature += 1;
					childItem = make_shared<BugFeature>(this, program);
				}

				if (childItem != nullptr)
				{
					mItems.push_back(childItem);
					childItem->XmlLoad(child);
				}

			}
		}
	}
}

/**
 * Clear the level
 */
void Level::Clear()
{
	mState = LevelState::Starting;
	mItems.clear();
}

/**
 * Update the level
 * @param elapse
 */
void Level::Update(double elapse)
{
	if(mState == LevelState::PAUSE)
		return;
	double newElapse = elapse;
	if(mState == LevelState::Starting)
	{
		if(mTimeCount + elapse > StartingTime)
		{
			newElapse = mTimeCount + elapse - StartingTime;
			mState = LevelState::Gaming;
		}
		else {
			mTimeCount += elapse;
		}
	}
	if(mState == LevelState::Gaming) // TODO: After starting screen is done, remove this
	{
		for(const auto& item: mItems)
		{
			item->Update(newElapse);
		}
		LevelEndCheck visitor;
		Accept(&visitor);
		if (visitor.ShouldEnd())
		{
			mState = LevelState::Ended;
		}
	}

}

/**
 * Draw the Level
 * @param graphics The device context to draw on
 */
void Level::Draw(shared_ptr<wxGraphicsContext> graphics)
{

	for(const auto& item: mItems)
	{
		 item->Draw(graphics);
	}
	if(mState == LevelState::Starting)
	{
        OnBeginDraw(graphics);
	}
	if (mState == LevelState::Ended)
	{
		OnEndDraw(graphics);
	}
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the level.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
shared_ptr<Item> Level::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}
void Level::Pause(bool pause)
{
	if(pause)
	{
		mPrevState = mState;
		mState = LevelState::PAUSE;
	}
	else
	{
		mState = mPrevState;
	}
}
/**
 * Add Bug Redundancy when it clicked
 * @param bug the bug item to add
 */
void Level::AddBug(std::shared_ptr<Item> bug)
{
    mItems.push_back(bug);
}
/**
 * Remove Bug when first clicked
 * @param bug the bug item to remove
 */
void Level::RemoveBug(std::shared_ptr<Item> bug)
{
    auto it = std::find(mItems.begin(), mItems.end(), bug);
    if (it != mItems.end()) {
        mItems.erase(it);
    }
}

/**
 * Accept a visitor for the item collection
 * @param visitor The visitor for the item collection
 */
void Level::Accept(ItemVisitor* visitor)
{
	for (auto item : mItems)
	{
		item->Accept(visitor);
	}
}

/**
 * Draw the level begin message
 * @param graphics The graphics context to draw on
 */
void Level::OnBeginDraw(shared_ptr<wxGraphicsContext> graphics)
{
    ostringstream message;
    message << "Level " << mLevelNumber <<  " Begin";
    DrawMessage(graphics, message.str());
}

/**
 * Draw the level end message depending on the win state
 * @param graphics The graphics context to draw on
 */
void Level::OnEndDraw(shared_ptr<wxGraphicsContext> graphics)
{
    string message = "Level Complete!";
    DrawMessage(graphics, message);
}

/**
 * Draw a specific level message on the screen
 * @param graphics The graphics context to draw on
 * @param message The message to draw
 */
void Level::DrawMessage(shared_ptr<wxGraphicsContext> graphics, string message)
{
    double levelHeight = mManager->GetGame()->GetHeight();
    double levelwidth = mManager->GetGame()->GetWidth();

    graphics->PushState();
    wxFont bigFont(wxSize(0, levelHeight / FontHeightFactor),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);

    graphics->SetFont(bigFont, FontColor);

    // Get width and height of message to center it
    double messageWidth;
    double messageHeight;
    graphics->GetTextExtent(message, &messageWidth, &messageHeight);

    graphics->DrawText(message, levelwidth/2 - messageWidth/2, levelHeight/2 - messageHeight/2);

    graphics->PopState();
}