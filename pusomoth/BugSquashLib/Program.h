/**
 * @file Program.h
 * @author Will Feddern
 *
 * Class for the Program item
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_PROGRAM_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_PROGRAM_H

#include "Item.h"

/**
 * Class for the Program item
 */
class Program : public Item
{
private:
	/// Program Name
	std::wstring mName = L"";

public:
	void XmlLoad(wxXmlNode* node) override;
	explicit Program(Level* level, std::wstring& programName);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	/**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
	void Accept(ItemVisitor* visitor) override { visitor->VisitProgram(this); }

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_PROGRAM_H
