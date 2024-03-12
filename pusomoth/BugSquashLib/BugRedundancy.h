/**
 * @file BugRedundancy.h
 * @author Thomas Sheehy, Will Feddern
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUGREDUNDANCY_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUGREDUNDANCY_H

#include "Bug.h"

/**
 * Class for the Redundancy Bug
 */
class BugRedundancy : public Bug
{
private:
	/// Top Image
	std::unique_ptr<wxImage> mTopImage = nullptr;
	/// Top Image bitmap
	std::unique_ptr<wxBitmap> mTopBitmap = nullptr;

	/// Left Wing Image
	std::unique_ptr<wxImage> mLeftWingImage = nullptr;
	/// Left Wing Bitmap
	std::unique_ptr<wxBitmap> mLeftWingBitmap = nullptr;

	/// Right Wing Image
	std::unique_ptr<wxImage> mRightWingImage = nullptr;
	/// Right Wing Bitmap
	std::unique_ptr<wxBitmap> mRightWingBitmap = nullptr;

	/// Total elapsed time (for animation)
	double mTotalElapsed = 0.0;
    /// new member variable to track if bug has been clicked before
    bool mHasBeenClicked = false;
	/// The redundancy bugs that split off from the original
    std::vector<std::shared_ptr<BugRedundancy>> mSplitBugs;


public:
	explicit BugRedundancy(Level* level, std::shared_ptr<Program> program);

	void UpdateSprite(double elapsed) override;
    /// called when Redundancy Bug clicked
    void OnClick() override;

	/**
	 * Accept a visitor
	 * @param visitor The visitor we accept
	 */
	void Accept(ItemVisitor* visitor) override { visitor->VisitRedundancyBug(this); }

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUGREDUNDANCY_H
