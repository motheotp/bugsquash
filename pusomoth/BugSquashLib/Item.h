/**
 * @file Item.h
 * @author Ziqi Liu, Thomas Sheehy, Will Feddern
 */


#ifndef JIMINY_PROJECT1_ITEM_H
#define JIMINY_PROJECT1_ITEM_H

#include "Level.h"
#include "ItemVisitor.h"

/**
 * Item base class
 */
class Item {
private:
    /// Loaded in X value of the item
    double mX = 0;
    /// Loaded in Y value of the item
    double mY = 0;
	/// The underlying item image
	std::unique_ptr<wxImage> mItemImage = nullptr;
	/// The bitmap we can display for this item
	std::shared_ptr<wxBitmap> mItemBitmap = nullptr;

protected:
	/// Constructor
	Item(Level* level, const std::wstring &filename);

	/// The Level this item belongs to
	Level* mLevel = nullptr;

	/**
     * The Bitmap for the bug
     * @returns Bug Bitmap
     */
	std::shared_ptr<wxBitmap> GetBitmap() { return mItemBitmap; }

public:

    ~Item();

    virtual void XmlLoad(wxXmlNode *node);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	virtual bool HitTest(double x, double y);

    /**
     * The X location of the item
     * @returns X location in pixels
     */
    double GetX() const { return mX; }

	/**
	 * Set the X location of the item
	 * @param x The X location to set
	 */
	void SetX(double x) { mX = x; }

    /**
     * The Y location of the item
     * @returns Y location in pixels
     */
    double GetY() const { return mY; }

	/**
	 * Set the Y location of the item
	 * @param y The Y location to set
	 */
	void SetY(double y) { mY = y; }

    /**
     * Update the item
     * @param elapsed elapsed time
     */
    virtual void Update(double elapsed) {}

	/// Called when the item is clicked
	virtual void OnClick() {}

	/**
	 * Returns the width of the item in pixels
	 * @return the width of the item in pixels
	 */
	virtual int GetWidth();

	/**
	 * Returns the height of the item in pixels
	 * @return the height of the item in pixels
	 */
	virtual int GetHeight();
	/**
	 * When double clicked
	 */
	virtual void OnDClick(){};

	/**
     * Accept a visitor
	 * @param visitor The visitor we accept
	*/
	virtual void Accept(ItemVisitor* visitor) = 0;
};


#endif //JIMINY_PROJECT1_ITEM_H
