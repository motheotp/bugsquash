/**
 * @file Bug.h
 * @author Thomas Sheehy, Will Feddern, Shuwei Chen
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_BUG_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_BUG_H

#include "Item.h"
#include "Program.h"

/**
 * Bug base class
 */
class Bug : public Item, public std::enable_shared_from_this<Bug>
{
private:
	/// Bug speed in pixels per second
	double mSpeed = 0;
	/// How long into the level play the bug starts moving, in seconds
	double mStart = 0;
	/// How long into the level it has been
	double mElapsedDelayTime = 0.0;
	/// Bug Rotation
	double mRotation = 0;
	/// Program to move towards
	std::shared_ptr<Program> mProgram = nullptr;
	/// Animation Frame
	int mAnimation = 0;
	/// Total animation time
	double mAnimationChange = 0;
	/// Total number of animation sprites
	int mSpriteCount = 1;
	/// The Generated animation sprite for this bug
	std::shared_ptr<wxBitmap> mBugSprite = nullptr;
	/// Whether or not bug has been splat
	bool mSplat = false;
	/// Whether or not the user has missed the bug (it reached program)
	bool mMissed = false;

	/// The underlying item image
	std::unique_ptr<wxImage> mItemImageSplat = nullptr;
	/// The bitmap we can display for this item
	std::shared_ptr<wxBitmap> mItemBitmapSplat = nullptr;

protected:
	void SetSpeed(double speedX);

	/**
     * The Bitmap for the bug
     * @returns Bug Bitmap
     */
	std::shared_ptr<wxBitmap> GetBitmapSplat() { return mItemBitmapSplat; }

	/**
     * The Program this bug moves towards
     * @returns Pointer to program object
     */
	std::shared_ptr<Program> GetProgram() const { return mProgram; }

	/**
	 * Sets the splat state of the bug
	 * @param splat Bool to set the spat state to
	 */
	 void SetSplat(bool splat) { mSplat = splat; }

	/**
     * Set the generated bug Sprite
     * @param sprite The new bug sprite
     */
	void SetBugSprite(std::shared_ptr<wxBitmap> sprite) { mBugSprite = sprite; }

	virtual void UpdateSprite(double elapsed);

	/**
	 * Get the animation sprite that should be shown
	 * @return int Animation sprite id
	 */
	int GetAnimation() { return mAnimation; }

	/**
	 * Get the rotation of the bug (in radians)
	 * @return double angle of the bug
	 */
	double GetRotation() { return mRotation; }


public:
	/// Constructor
	Bug(Level* level, std::shared_ptr<Program> program, int sprites, const std::wstring &filename, const std::wstring& filenameSplat);

	/// Default constructor (disabled)
	Bug() = delete;

	/// Copy constructor (disabled)
	Bug(const Bug &) = delete;

	/// Assignment operator
	void operator=(const Bug &) = delete;

	void XmlLoad(wxXmlNode *node) override;

	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	void Update(double elapsed) override;

	virtual void OnClick() override;

	virtual void AddScore();

	virtual bool HitTest(double x, double y) override;

	virtual void OnReachProgram();

	/**
	 * Get level
	 * @return level
	 */
	Level* GetLevel() {return mLevel;}

	/**
	 * Get if the bug was missed
	 * @returns boolean indicating if the bug was already missed
	 */
	bool IsMissed() const { return mMissed; }

	/**
	 * Get the generated bug Sprite
	 * @returns Bug Sprite
	 */
	std::shared_ptr<wxBitmap> GetBugSprite() { return mBugSprite; }

	/**
     * Get if the bug was squished
     * @returns boolean indicating if the bug was already squished
     */
	bool IsSplat() const { return mSplat; }
};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_BUG_H
