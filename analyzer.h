#ifndef ANALYZER_H
#define ANALYZER_H
#include "field.h"
#include <iostream>
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////
class Analyzer {
	protected:
        //returns a pair of counts - (new safe cells,new mines);
        std::pair<int,int> ApplyRule12( MSfieldPart1 & f, bool open );
        //returns a pair of counts - (new safe cells,new mines);
		std::pair<int,int> ApplyRule3 ( MSfieldPart1 & f, bool open );
		MSfieldPart1 & field;           //actual field
		MSfieldPart1 temp;              //temporary field for proof by contradiction
	public:
		Analyzer(MSfieldPart1 & field);
		virtual ~Analyzer() {}
		bool IsMine(int x,int y);  //resolution proof by contradiction
		bool IsSafe(int x, int y); //resolution proof by contradiction
};

////////////////////////////////////////////////////////////////////////////////
class Solver : public Analyzer {
	private:
	public:
		Solver(MSfieldPart2 & field);
        void Solve( );
};
#endif
