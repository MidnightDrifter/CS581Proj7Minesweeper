#include "analyzer.h"
#include "field.h"
#include <set>
#include <iostream>

/*




I'll use the following notations:
for a location X:
KM(X) - number of known adjacent mines (neighbors that are marked as mines by the player)

UL(X) - set of unknown locations (neighbors that are not assigned either safe or mine)

Val(X) - if the cell was is open, then Val(X) is the number of all adjacent mines,
even those that are not discovered yet.


 0 1 2
+-----
0|m m -
1|m 5 -
2|- - -

X=(1,1)
KM(X) = 3
UL(X) = { (0,0), (1,0), (2,0), (2,1), (2,2) }
===================================================
Rule 1:
======
if some location X satisfies
Val(X) - KM(X) = | UL(X) |
where |.| is the cardinality - number of elements in the set
then all locations in UL(X) are mines

Rule 2:
======
if some location X satisfies
Val(X) = KM(X)
then all locations in UL(X) are safe

Here are some trivial mines which you can get by Rules 1 and 2:

0 1 2 3 4 5 6 7
+---------------
0|2 3 m 2 2 m 2 1
1|m m 4 - - 4 m 2
2|- - - - - - 4 m
3|m 5 - 6 - - - 2
4|2 m m - 5 5 - 2
5|1 3 4 - - - 4 m
6|0 1 m 4 - - m 3
7|0 1 2 m 2 3 m 2
===================================================

Rule 3:
======
if for 2 locations X and Y:
(Val(X) - KM(X) ) - ( Val(Y) - KM(Y) ) = | UL(X) \ UL(Y) |
where "\" is set difference
then
A) all locations in UL(X)\UL(Y) are mines
B) all locations in UL(Y)\UL(X) are safe

Example:
	0   1   2   3   4
	+---+---+---+---+---+
0	|   |   |   |   |   |
	+---+---+---+---+---+
1	|   | 2Y| 4X| 2 |   |
	+---+---+---+---+---+
2	|   |   |   |   |   |
	+---+---+---+---+---+

X=(2,1) Y=(1,1)
UL(X) = { (1,0),  (1,2), (2,0), (2,2), (3,0), (3,2) }
UL(Y) = { (0,0), (0,1), (0,2), (1,0), (1,2), (2,0), (2,2) }
UL(X) \ UL(Y) = { (3,0), (3,2) }
(Val(X) - KM(X) ) - ( Val(Y) - KM(Y) ) = | UL(X) \ UL(Y) |
( 4     -  0    ) - (  2     -  0    ) = 2
holds

So (3,0), (3,2) are mines
UL(Y) \ UL(X) = { (0,0), (0,1), (0,2) } are safe

Rule explained:
Val(X) - KM(X) is the number of unknown mines.
(Val(X) - KM(X) ) - ( Val(Y) - KM(Y) ) - unknown mines of X that should not be visible to Y
| UL(X) \ UL(Y) | - number of cells around X that are not visible to Y


Contradiction rules:

Rule 4 (too many mines):
======
Val(X) < KM(X) then assignment is impossible

Rule 5 (not enough mines):
======
Val(X) > KM(X) + | UL(X) | then assignment is impossible







*/

class Mine
{
public:

	Mine(int x, int y, bool known, bool marked) : xCoord(x), yCoord(y), isKnown(known), isMarkedMine(marked), isClicked(false), value(-1){}
	Mine(int x, int y) : xCoord(x), yCoord(y), isKnown(false), isMarkedMine(false), isClicked(false), value(-1) {}
	Mine(int x, int y, int v) : xCoord(x), yCoord(y), isKnown(true), isMarkedMine(false), isClicked(true), value(v) {}



	int GetX() const { return xCoord; }
	int GetY() const { return yCoord; }
	int GetVal() const { return value; }
	bool GetIsKnown() const { return isKnown; }
	bool GetIsMarked() const { return isMarkedMine; }
	bool GetIsClicked() const { return isClicked; }
	bool GetIsSafe() const { return isKnown && !isMarkedMine; }

	void SetVal(int v) { value = v; }
	void SetIsKnown(bool b) { isKnown = b; }
	void SetIsMarked(bool b) { isKnown = b; }
	void SetIsClicked(bool b) { isClicked = b; }

private:
	int xCoord, yCoord, value;
	bool isKnown;
	bool isMarkedMine;  //NOTE:  if it's KNOWN and NOT marked as a mine, it must be safe, clicked or otherwise
	bool isClicked;





};

std::pair<int, int> Analyzer::ApplyRule12(MSfieldPart1& f, bool open)
{
	/*
	
	Rule 1:
======
if some location X satisfies
Val(X) - KM(X) = | UL(X) |
where |.| is the cardinality - number of elements in the set
then all locations in UL(X) are mines

Rule 2:
======
if some location X satisfies
Val(X) = KM(X)
then all locations in UL(X) are safe
	
	*/


	for (int x = 0; x < f.GetMaxX(); x++)
	{
		for (int y = 0; y < f.GetMaxY(); y++)
		{

		}


	}


}


std::pair<int, int> Analyzer::ApplyRule3(MSfieldPart1& f, bool open)
{

}




////////////////////////////////////////////////////////////
Analyzer::Analyzer(MSfieldPart1 & field) : field(field),temp(field) {
}

////////////////////////////////////////////////////////////
bool Analyzer::IsMine(int x,int y) {
	temp=field;
	temp.MarkAsSafe(x,y);
    bool proved = false;

	//Assume safe, try to prove otherwise
	//For each (LEGAL) location around (x,y):
		//Apply rules 1,2,3 if possible
		//Check for contradiction with rules 4,5
		//If contradiction via rules 4,5, return true
	//If we get through all the neighbors and can't contradict anything, return false
	
	std::vector<Mine> neighbors;

	for (int i = x - 1; i < x + 1; i++)
	{
		for (int j = y - 1; j < y + 1; y++)
		{
			//Check for cell's legality
			if (temp.CheckIsInside(i,j) && !(i == x && j == y))
			{
				//Mine m(i, j);
				if (temp.IsUnknown(i, j))  //Straight-up unknown
				{
					neighbors.emplace_back(i, j, false, false);
				}

				else  //Known, but either A. safe & unclicked, B. marked as mine, or C. open and has value in it
				{
					//if(temp.)
					if (temp.IsMarkedMine(i, j))  //B
					{
						neighbors.emplace_back(i, j, true, true);
					}
					else if (temp.IsClicked(i, j))  //C
					{
						neighbors.emplace_back(i, j, temp.GetMineCount(i, j));
					}

					else //By process of elimination it MUST be A, right?
					{
						neighbors.emplace_back(i, j, true, true);
					}
				}

			}
		}
	}

	


	/*
	Rule 1:
======
if some location X satisfies
Val(X) - KM(X) = | UL(X) |
where |.| is the cardinality - number of elements in the set
then all locations in UL(X) are mines

	*/




	return proved;
}

////////////////////////////////////////////////////////////
bool Analyzer::IsSafe(int x, int y) { 
	temp=field;
	temp.MarkAsMine(x,y);
    bool proved = false;


	//Assume mine, attempt to prove otherwise


	return proved;
}

////////////////////////////////////////////////////////////
Solver::Solver(MSfieldPart2 & field) : Analyzer(field) {}

////////////////////////////////////////////////////////////
void Solver::Solve( ) {
    //part 2
}
