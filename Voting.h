//Voting.h
#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------
#include <iostream> // istream, ostream
#include <utility> // pair


// ------------
// voting_readStart
// ------------
/**
* read the first number of the file and branch out from there
* @param r an std::istream
*/
void readStart(std::istream& r,std::ostream& w);

// ------------
// voting_solveVote
// ------------
/**
* Print out the winner of the vote
* @param r an std::istream
*/
void solveVote(std::istream& r,std::ostream& w);

// ------------
// voting_createElection
// ------------
/**
*Places all of the canidates in a vector
*@param numCam is the number of canadites
*@param r an std::istream
*returns whether the Election Vector has increased in size
*/
bool createElection(int numCam,istream& r);

// ------------
// voting_assignBallot
// ------------
/**
*Places the ballots in the ballot vector
*@param r an std::istream
*returns the preffered canidate number
*/
int assignBallot(istream& r);





#endif //Voting.h
