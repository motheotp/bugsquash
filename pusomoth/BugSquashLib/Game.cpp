/**
 * @file Game.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include<memory>
#include "Game.h"
#include "Item.h"
#include <wx/graphics.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

using namespace std;

/// Game area in virtual pixels
const static int Width = 1250;

/// Game area height in virtual pixels
const static int Height = 1000;

/// Scale to shrink to when in shrink mode
const double ShrinkScale = 0.75;

/**
 * Game Constructor
 */
Game::Game()
{
}

/**
 * Initialize the game class.
 */
void Game::Initialize()
{

	wstring resourcesDir = L"../resources";
	wxFileName filename(resourcesDir);

	mLevelManager = make_shared<LevelManager>(resourcesDir);
}

/**
 * Draw the Game
 * @param graphics The device context to draw on
 * @param width The window width (int)
 * @param height The window height (int)
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(Width);
    auto scaleY = double(height) / double(Height);
    mScale = std::min(scaleX, scaleY);

    if(mShrinked)
    {
        mScale *= ShrinkScale;
    }

    mXOffset = (width - Width * mScale) / 2;
    mYOffset = (height - Height * mScale) / 2;

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    // From here on you are drawing virtual pixels
	if (!mShrinked)
	{
		graphics->Clip(0, 0, Width, Height);
	}

	// Background
	wxBrush brush(wxColour(255, 255, 255)); // white color brush
	graphics->SetBrush(brush);
	graphics->DrawRectangle(0, 0, Width, Height);
	// Level
	mLevelManager->Draw(graphics, Width, Height);

	graphics->PopState();
}

/**
 * Handle updates for movement & animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
	mLevelManager->Update(elapsed);
	//mScoreboard->Update(elapsed);
}
/**
 * Process left mouse button press
 * @param x Raw X location in pixels
 * @param y Raw Y location in pixels
 */
void Game::OnLeftDown(int x, int y)
{
	// Translate to VirtualPixels
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;

	shared_ptr<Level> currentLevel =  mLevelManager->GetLevel();
	shared_ptr<Item> clickedItem;

	if (currentLevel != nullptr)
	{
		clickedItem = currentLevel->HitTest(oX, oY);
	}

	if (clickedItem != nullptr)
	{
		clickedItem->OnClick();
	}
}
/**
 * Process left mouse button press double
 * @param x Raw X location in pixels
 * @param y Raw Y location in pixels
 */
void Game::OnLeftDDown(int x, int y)
{
	// Translate to VirtualPixels
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;

	shared_ptr<Level> currentLevel =  mLevelManager->GetLevel();
	shared_ptr<Item> clickedItem;

	if (currentLevel != nullptr)
	{
		clickedItem = currentLevel->HitTest(oX, oY);
	}

	if (clickedItem != nullptr)
	{
		clickedItem->OnDClick();
	}
}
/**
 * Get game width
 * @return
 */
double Game::GetWidth()
{
	return Width;
}

/**
 * Get game height
 * @return
 */
double Game::GetHeight()
{
	return Height;
}

/**
 * Switch to different level
 * @param levelNum: int carrying level number to go to
 */
 void Game::ToLevel(int levelNum)
 {
	 mLevelManager->ToLevel(levelNum);
 }