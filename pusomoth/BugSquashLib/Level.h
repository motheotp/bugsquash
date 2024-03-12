/**
 * @file Level.h
 * @author ShuWei Chen, Will Feddern，Ziqi Liu
 */

#ifndef PROJECT1_BUGSQUASHLIB_LEVEL_H
#define PROJECT1_BUGSQUASHLIB_LEVEL_H

#include <wx/dcbuffer.h>
#include "ItemVisitor.h"

class LevelManager;
class Item;
class Program;
/**
 *  this is a level class, contain every thing that a level knows
 */
class Level
{
private:
	/**
	 * Enum class of state of level
	 */
	enum class LevelState {
		Starting,
		Gaming,
		PAUSE,
		Ended
	};

	/// level state
	LevelState mState = LevelState::Starting;

	/// prev state
	LevelState mPrevState = LevelState::Starting;

	/// name of level
	std::wstring mLevelName = L"";

	/// name of level
	std::wstring mGameName = L"";
	/// manager
	LevelManager *mManager = nullptr;

	/// current level number
	int mLevelNumber = -1;

	/// items of level
	std::vector<std::shared_ptr<Item>> mItems;

	/// count time for starting and end
	double mTimeCount = 0;

	/// program for bug to use
	std::shared_ptr<Program> mProgram = nullptr;

	/// clear this level
	void Clear();

	/// Number of programs in loaded level
	int mNumPrograms = 0;

	/// Number of bugs in loaded level
	int mNumBugs = 0;

	/// Number of Null bugs in loaded level
	int mNumBugsNull = 0;

	/// Number of Garbage bugs in loaded level
	int mNumBugsGarbage = 0;

	/// Number of Redundancy bugs in loaded level
	int mNumBugsRedundancy = 0;

	/// Number of Feature bugs in loaded level
	int mNumBugsFeature = 0;

	/// Bugs in the level
    std::vector<std::shared_ptr<Item>> mBugs;
public:
	/// Default constructor (disabled)
	Level() = delete;

	/// Copy constructor (disabled)
	Level(const Level &) = delete;

	/// Assignment operator
	void operator=(const Level &) = delete;

	Level(int levelNumber, LevelManager *manager, std::wstring filename);

	void LoadFromXml(std::wstring filename);

	void Update(double elapse);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	/**
	 * Get manager
	 * @return level manager
	 */
	auto GetManager() { return mManager; }

	std::shared_ptr<Item> HitTest(int x, int y);

	/// @return the number of programs in the level
	int GetNumPrograms() { return mNumPrograms; }
	/// @return the number of bugs in the level (includes features)
	int GetNumBugs() { return mNumBugs; }
	/// @return the number of null bugs in the level
	int GetNumBugsNull() { return mNumBugsNull; }
	/// @return the number of garbage bugs in the level
	int GetNumBugsGarbage() { return mNumBugsGarbage; }
	/// @return the number of redundancy bugs in the level
	int GetNumBugsRedundancy() { return mNumBugsRedundancy; }
	/// @return the number of feature "bugs" in the level
	int GetNumBugsFeature() { return mNumBugsFeature; }

	/**
	 * Pause the game
	 * @param pause is pause
	 */
	void Pause(bool pause);
    /// Add Redundancy Bug
    void AddBug(std::shared_ptr<Item> bug);
    /// Remove Redundancy Bug
    void RemoveBug(std::shared_ptr<Item> bug);

	void Accept(ItemVisitor* visitor);

    void OnBeginDraw(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawMessage(std::shared_ptr<wxGraphicsContext> graphics, std::string message);
    void OnEndDraw(std::shared_ptr<wxGraphicsContext> graphics);

};

#endif //PROJECT1_BUGSQUASHLIB_LEVEL_H
