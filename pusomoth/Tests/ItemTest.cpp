/**
 * @file ItemTest.cpp
 * @author Motheo Treasure Puso
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>

/// Laptop filename
const std::wstring LaptopImageName = L"images/laptop.png";

/** Mock class for testing the class Item */
class ItemMock : public Item
{
public:
    ItemMock(Level* level) : Item(level, LaptopImageName) {}
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}

	void Accept(ItemVisitor* visitor) override {}
};

TEST(ItemTest, HitTest) {
	ItemMock item(nullptr);

	// Test initial values
	ASSERT_NEAR(0, item.GetX(), 0.0001);
	ASSERT_NEAR(0, item.GetY(), 0.0001);

	// Test SetX and SetY
	item.SetX(25.5);
	item.SetY(30.5);
	ASSERT_NEAR(25.5, item.GetX(), 0.0001);
	ASSERT_NEAR(30.5, item.GetY(), 0.0001);

	// Move for HitTest
	item.SetX(500);
	item.SetY(500);

	// Center of the item should be a true
	ASSERT_TRUE(item.HitTest(500, 500));

	// Left of the item
	ASSERT_FALSE(item.HitTest(0, 500));

	// Right of the item
	ASSERT_FALSE(item.HitTest(1000, 500));

	// Above the item
	ASSERT_FALSE(item.HitTest(500, 0));

	// Below the item
	ASSERT_FALSE(item.HitTest(1000, 500));

	// On a item transparent pixel (Laptop Image)
	ASSERT_FALSE(item.HitTest(500 - 75, 500));
}


