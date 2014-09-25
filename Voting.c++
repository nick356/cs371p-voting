// --------
// includes
// --------
#include <iostream> // istream, ostream
#include <utility> // pair
#include <vector>
#include <string>
#include "Voting.h"


using namespace std;
vector<string> canidates;
vector<int> numVotes;
vector<vector<int>> canidateVotes;

void readStart(istream& r,ostream& w){
	assert(!r.eof());
	int elections;
	int currentElection=0;
	r>>elections;
	while(currentElection<elections){
		int numCan;
		r>>numCam;
		assert(createElection(numCam,r));
		while(r.peek() != '\n')
			assert(assignBallot(r)>0);
		++currentElection;
	}


}

bool createElection(int numCam,istream& r){
	assert(numCam>0);
	string x;
	canidates = vector<string>(numCam);
	numVotes = vector<int>(numCam,0);
	for(int i = 0; i<numCam;++i)
	{
		r>>x;
		canidates.push_back(x);
	}
	return canidates.size()>0;
}

int assignBallot(istream& r){
	vector<int> ballot;
	int x;
	while(r.peek()!='\n'){
		r>>x;
		ballot.push_back(x);
	}
	char temp = r.get();
	canidateVotes.push_back(ballot);
	return ballot[0];
}

int dumbSolution(){
	bool winnerfound = false;
	int highestVote = 0;
	while(!winnerfound){
		for(int i = 0; i<numVotes.size();++i){
			if(highestVote<numVotes[i])
				highestVote = numVotes[i];
		}
		if(highestVote>=canidateVotes.size()/2){
			winnerfound = true;
			break;
		}

		

	}

	if(winnerfound)
		return highestVote;
	else
		return 0;
}
