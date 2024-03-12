/**
 * @file Scoreboard.h
 * @author Treasure Puso
 */

#ifndef JIMINY_PROJECT1_BUGSQUASHLIB_SCOREBOARD_H
#define JIMINY_PROJECT1_BUGSQUASHLIB_SCOREBOARD_H

#include<memory>

/**
 * Scoreboard Class
 */
class Scoreboard
{
private:
	///Bug squashed score number
	int mFixed = 0;

	///Bug missed score number
	int mMissed = 0;

	///oops (wrong feature)
	int mOops = 0;


public:
	Scoreboard();
	void OnDrawLabel(std::shared_ptr<wxGraphicsContext> graphics, double x, double y);
	void Display(std::shared_ptr<wxGraphicsContext> graphics, double x, double y);

	/** Setter to increase score
	 *
	 */
	void IncreaseFixed(){mFixed += 1;}

	/** Setter to increase score
	*
	*/
	void IncreaseMissed(){mMissed += 1;}

	/** Setter to increase score
	*
	*/
	void IncreaseOops(){mOops += 1;}


	 /**
	  * Sets score to back to zero
	  */
	  void SetScoreToZero(){
		  mFixed = 0;
		  mMissed = 0;
		  mOops = 0;
	  }

	  /**
	   * Getter for the current score in the Scoreboard
	   * @return int mFixed
	   */
	  int  GetFixed() const {return mFixed;}

};

#endif //JIMINY_PROJECT1_BUGSQUASHLIB_SCOREBOARD_H
