// --------
// includes
// --------
#include <iostream> // istream, ostream
#include <utility> // pair
#include <vector>
#include <string>
#include <queue>
#include <cassert> // assert
#include <sstream>


using namespace std;

struct canidate{

	string name;
	bool isOut;
	int numVotes;
	vector<queue<int>> canidateVotes;
};
vector<canidate> canidates;
int canidatesInRunning;
int ballots;


//This just starts reading the file.
void readStart(istream& r,ostream& w){
	//Checked to make sure it is not end of file
	assert(!r.eof());
	int elections;
	int currentElection=0;
	//The first number from the file will be the number of elections.
	//Thus we store it in elections.
	r>>elections;
	assert(elections > 0 );;
	while(currentElection<elections){
		int numCam;
		r>>numCam;
		ballots = 0;
		canidatesInRunning = numCam;
		//We are making sure that there have been canidates added to the vector
		assert(createElection(numCam,r));
		string temp;
		getline(r,temp);
		while(!temp.empty()){
			assert(assignBallot(temp)>=0);
			getline(r,temp);
		}
		printWinner(w);
		++currentElection;
		canidates.clear();
		if(currentElection != elections){
			w<<endl;
			w<<endl;
		}
	}


}

//We store the canidates name in their appropriate vector.
bool createElection(int numCam,istream& r){
	//Makeing sure there are canidates
	assert(numCam>0);
	string x;
	getline(r,x);
	canidates = vector<canidate>(numCam);
	for(int i = 0; i<numCam;++i)
	{
		getline(r,x);
		canidates[i].name = x;
		canidates[i].isOut = false;
		//cout<<x<<endl;
	}
	return canidates.size()>0;
}

//We will store the ballots in a queue
int assignBallot(string line){
	queue<int> ballot;
	int x;
	stringstream parse(line);
	//Store each number on the ballot in the queue

	while(parse >> x){
		ballot.push(x);
	}
	//Store the ballot in the canidatesList of ballots.
	//cout<<ballot.front()<<endl;
	canidates[ballot.front()-1].canidateVotes.push_back(ballot);
	//Incremint the number of votes the canidate has recieved.
	++ballots;
	++canidates[ballot.front()-1].numVotes;
	return ballot.front()-1;
}

//We essentialy remove any canidate who shouldn't be in the running
bool destroyCanidates(int& x){
	//We go through all canidates who have the lowest and remove them from the running
	//We then transfer their ballots.
	for(unsigned int i = 0; i<canidates.size();++i)
		if(canidates[i].numVotes == x){
			canidates[i].isOut = true;
			--canidatesInRunning;
			assert(transferBallots(i));
		}
	//Return the lowest number of votes;

	return true;
}

pair<int, int> isThereLowest(){
	int lowest = -1;
	int highest = -1;
	for(unsigned int i = 0; i<canidates.size();++i){
		//If the canidate is not already out and if the lowest is -1 or if the canidates number
		//of votes is less than the lowest.
		if(!canidates[i].isOut && (lowest == -1 || canidates[i].numVotes < lowest))
			lowest = canidates[i].numVotes;
		if(!canidates[i].isOut && (highest == -1 || canidates[i].numVotes > highest))
			highest = canidates[i].numVotes;
	}



	return make_pair(lowest,highest);
}

bool transferBallots(unsigned int canNum){
	if(canidates[canNum].canidateVotes.empty())
		return false;
	//We go through each ballot the canidate has
	for(unsigned int i = 0; i<canidates[canNum].canidateVotes.size();++i)
	{
		//We check to make sure that the ballot the canidate has is not empty (which it should not be), then we check
		//to see if the canidate at the front of the ballot is out.
		while(canidates[canidates[canNum].canidateVotes[i].front()-1].isOut){
			//If the canidate is out then we pop that canidate from the ballot.
			canidates[canNum].canidateVotes[i].pop();
		}
		//We make sure that the ballot is not empty
		assert(!canidates[canNum].canidateVotes[i].empty());
		int index = canidates[canNum].canidateVotes[i].front()-1;
		//Then we transfer the ballot to it's next prefered canidate.
		canidates[canidates[canNum].canidateVotes[i].front()-1].canidateVotes.push_back(canidates[canNum].canidateVotes[i]);
		//Increment the number of votes the new canidate has.
		++canidates[canidates[canNum].canidateVotes[i].front()-1].numVotes;
	}
	//Destroy the old canidates ballots, we don't need copies.	
	return true;
}

void printWinner(ostream& w){
	bool winnerfound = false;
	pair<int, int> temp = isThereLowest();
	assert(temp.first != -1 && temp.second != -1);
	while(!winnerfound){
		temp=isThereLowest();
		if(temp.first == temp.second){
			for(unsigned int i = 0; i<canidates.size();i++)
				if(!canidates[i].isOut){
					w<<canidates[i].name<<" ";	
				}
			winnerfound = true;
		}else if(temp.second > ballots/2){
			for(unsigned int i = 0; i<canidates.size();i++)
				if(temp.second == canidates[i].numVotes)
					w<<canidates[i].name;
			winnerfound = true;
		}else{
			destroyCanidates(temp.first);
		}
	}
}

int main () {
	using namespace std;
	readStart(cin, cout);
	return 0;
}
