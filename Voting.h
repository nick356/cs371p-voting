//Voting.h
#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------
#include <iostream> // istream, ostream
#include <utility> // pair

using namespace std;

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
int assignBallot(string line);

// ------------
// voting_destroyCanidates
// ------------
/**
*Goes through and destroys any canidate with the same number of votes as x
*@param x should be the lowest number of votes an individual has
*returns true
*/
bool destroyCanidates(int& x);


// ------------
// voting_isThereLowest
// ------------
/**
*Finds both the highest and lowest number of votes.
*returns a pair of int where the first value is the lowest and the second is the highest
*/
pair<int, int> isThereLowest();


// ------------
// voting_transferBallots
// ------------
/**
*Will go through and transfer all of the ballots that belong to the canidate given.
*@param canNum is the canidates number.
*returns true when completed, false if the canidate has no ballots to give.
*/
bool transferBallots(unsigned int canNum);

// ------------
// voting_printWinner
// ------------
/**
*Will print out a winner, this will solve the problem for a given election
*@param w is the outstream.
*/
void printWinner(ostream& w);


#endif //Voting.h
