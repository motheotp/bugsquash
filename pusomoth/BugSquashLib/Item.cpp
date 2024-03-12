/**
 * @file Item.cpp
 * @author Motheo Treasure Puso
 */

#include "pch.h"
#include "Item.h"
#include <memory>
#include <wx/xml/xml.h>
#include <wx/graphics.h>

using namespace std;

/**
 * Constructor
 * @param level The level this item belongs to
 * @param filename The filename of the picture for this item
 */
Item::Item(Level* level, const std::wstring &filename)
{
	mLevel = level;
    mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = std::make_shared<wxBitmap>(*mItemImage);
}

/**
 * Destructor
 */
Item::~Item()
{
}


/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
}

/**
 * Draw this bug
 * @param graphics graphics to draw on
 */
void Item::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
	graphics->DrawBitmap(*mItemBitmap,
                   int(GetX() - wid / 2),
                   int(GetY() - hit / 2),
				   wid,
				   hit);
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(double x, double y)
{
	double wid = mItemBitmap->GetWidth();
	double hit = mItemBitmap->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to the image top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	// If the location is transparent, we are not in the drawn
	// part of the image
	return !mItemImage->IsTransparent((int)testX, (int)testY);
}

int Item::GetWidth()
{
	return mItemBitmap->GetWidth();
}

int Item::GetHeight()
{
	return mItemBitmap->GetHeight();
}
