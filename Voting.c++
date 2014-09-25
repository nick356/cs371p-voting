// --------
// includes
// --------
#include <iostream> // istream, ostream
#include <utility> // pair
#include <vector>
#include <string>
#include "Voting.h"


using namespace std;

struct canidate{

	string canidates;
	bool isOut;
	int numVotes;

}
vector<canidate> canidates;
vector<vector<int>> canidateVotes;


//This just starts reading the file.
void readStart(istream& r,ostream& w){
	//Checked to make sure it is not end of file
	assert(!r.eof());
	int elections;
	int currentElection=0;
	//The first number from the file will be the number of elections.
	//Thus we store it in elections.
	r>>elections;
	while(currentElection<elections){
		int numCan;
		r>>numCam;
		//We are making sure that there have been canidates added to the vector
		assert(createElection(numCam,r));
		while(r.peek() != '\n')
			assert(assignBallot(r)>0);
		++currentElection;
	}


}

//We store the canidates name in their appropriate vector.
bool createElection(int numCam,istream& r){
	//Makeing sure there are canidates
	assert(numCam>0);
	string x;
	canidates = vector<canidate>(numCam);
	for(int i = 0; i<numCam;++i)
	{
		r>>x;
		canidates[i].canidates = x;
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

int destroyCanidates(){
	int lowest = -1;
	for(int i = 0; i<numVotes.size();++i){
		if(numVotes[i] != -1 && lowest != -1)
			lowest = numVotes[i];
		if(numVotes[i]<lowest && numVotes[i] != -1)
			lowest = numVotes[i];
	}

	for(int i = 0; i<numVotes.size();++i)
		if(numVotes[i] == lowest)
			numVotes[i] = -1;

	return lowest;
}



int dumbSolution(){
	bool winnerfound = false;
	for(int i = 0; i< canidateVotes.size(); ++i)
		++numVotes[canidateVotes[i][0]];
	while(!winnerfound){
		for(int i = 0; i< numVotes.size(); ++i)
			if(numVotes[i]>=canidateVotes.size()/2)
				return numVotes[i];
		assert(destroyCanidates()>-1);

		for(int i = 0; i<canidateVotes.size();++i)
			while(numVotes[canidateVotes[i][0]] == -1){
				int j = 1;
				canidateVotes[i][0] = canidateVotes[i][j];
				++j;
			}
		for(int i = 0; i<canidateVotes.size();++i)
			if(numVotes[canidateVotes[i][0]] == -1)
				
	}
		return 0;
}
