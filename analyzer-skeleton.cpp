#include "analyzer.h"
#include "field.h"
#include <set>
#include <iostream>

////////////////////////////////////////////////////////////
Analyzer::Analyzer(MSfieldPart1 & field) : field(field),temp(field) {
}

////////////////////////////////////////////////////////////
bool Analyzer::IsMine(int x,int y) {
	temp=field;
	temp.MarkAsSafe(x,y);
    bool proved = false;




	return proved;
}

////////////////////////////////////////////////////////////
bool Analyzer::IsSafe(int x, int y) { 
	temp=field;
	temp.MarkAsMine(x,y);
    bool proved = false;





	return proved;
}

////////////////////////////////////////////////////////////
Solver::Solver(MSfieldPart2 & field) : Analyzer(field) {}

////////////////////////////////////////////////////////////
void Solver::Solve( ) {
    //part 2
}
