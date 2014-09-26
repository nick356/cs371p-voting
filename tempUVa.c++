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
vector<canidate> canidates(20);

vector<canidate*> winners;
int canidatesInRunning;
int ballots;


bool transferBallots(unsigned int canNum){
	//We go through each ballot the canidate has
	//cout<<"Person is loosing: "<<(*winners[canNum]).name<<endl;
	for(unsigned int i = 0; i<(*winners[canNum]).canidateVotes.size();++i)
	{
		//We check to make sure that the ballot the canidate has is not empty (which it should not be), then we check
		//to see if the canidate at the front of the ballot is out.
		while(canidates[(*winners[canNum]).canidateVotes[i].front()-1].isOut){
			//If the canidate is out then we pop that canidate from the ballot.
			(*winners[canNum]).canidateVotes[i].pop();
		}
		//We make sure that the ballot is not empty
		assert(!(*winners[canNum]).canidateVotes[i].empty());
		//Then we transfer the ballot to it's next prefered canidate.
		canidates[(*winners[canNum]).canidateVotes[i].front()-1].canidateVotes.push_back((*winners[canNum]).canidateVotes[i]);
		//Increment the number of votes the new canidate has.
		++canidates[(*winners[canNum]).canidateVotes[i].front()-1].numVotes;
	}
	//Destroy the old canidates ballots, we don't need copies.	
	return true;
}

//We store the canidates name in their appropriate vector.
bool createElection(int numCam,istream& r){
	//Makeing sure there are canidates
	assert(numCam>0);
	string x;
	getline(r,x);
	winners = vector<canidate*>(numCam);
	for(int i = 0; i<numCam;++i)
	{
		getline(r,x);
		canidates[i].name = x;
		canidates[i].isOut = false;
		canidates[i].numVotes = 0;
		winners[i]=&canidates[i];
		//cout<<x<<endl;
	}
	return numCam>0;
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
	vector<int> temp;
	vector<canidate*> tempwin;
	for(unsigned int i = 0; i<winners.size();++i){
		if((*winners[i]).numVotes == x){
			temp.push_back(i);
			(*winners[i]).isOut = true;
			--canidatesInRunning;
		}else{
			//cout<<"Item being added to tempwin: "<<(*winners[i]).name<<endl;
			tempwin.push_back(winners[i]);
		}
	}
	//We then transfer their ballots.
	//cout<<"The size of the temp array is: "<<temp.size()<<endl;
	for(unsigned int i = 0; i<temp.size();++i){
		assert(transferBallots(temp[i]));
	}

	winners = tempwin;
	//cout<<"Current size of winners: "<<winners.size()<<endl;
	//Return the lowest number of votes;

	return true;
}

pair<int, int> isThereLowest(){
	int lowest = 20000;
	int highest = -1;
	for(unsigned int i = 0; i<winners.size();++i){
		//If the canidate is not already out and if the lowest is -1 or if the canidates number
		//of votes is less than the lowest.
		if((*winners[i]).numVotes < lowest)
			lowest = (*winners[i]).numVotes;
		if((*winners[i]).numVotes > highest)
			highest = (*winners[i]).numVotes;
		//cout<<"Bad Code!!!"<<endl;
	}
	/*for(unsigned int i = 0; i<winners.size();++i)
		if((*winners[i]).numVotes == lowest)
			cout<<(*winners[i]).name<<": "<<(*winners[i]).numVotes<<endl;*/
	return make_pair(lowest,highest);
}

void printWinner(ostream& w){
	bool winnerfound = false;
	pair<int, int> temp = isThereLowest();
	assert(temp.first != -1 && temp.second != -1);
	while(!winnerfound){
		temp=isThereLowest();
		if(temp.first == temp.second || temp.second > ballots/2){
			for(unsigned int i = 0; i<winners.size();++i)
				if(temp.second == (*winners[i]).numVotes)
					w<<(*winners[i]).name<<endl;	
			winnerfound = true;
		}else
			destroyCanidates(temp.first);
	}
}

//This just starts reading the file.
void readStart(istream& r,ostream& w){
	//Checked to make sure it is not end of file
	assert(!r.eof());
	int elections;
	int currentElection=0;
	int numCam;
	//The first number from the file will be the number of elections.
	//Thus we store it in elections.
	r>>elections;
	assert(elections > 0 );;
	while(currentElection<elections){
		r>>numCam;
		ballots = 0;
		if(numCam != 0){
			canidatesInRunning = numCam;
			//We are making sure that there have been canidates added to the vector
			assert(createElection(numCam,r));
			string temp;
			getline(r,temp);
		
			if(!temp.empty()){
				while(!temp.empty()){
					assert(assignBallot(temp)>=0);
					getline(r,temp);
				}
			}
			printWinner(w);
			winners.clear();	
		}
		++currentElection;
		if(currentElection != elections){
			w<<endl;
		}
	}
}
int main () {
	using namespace std;
	readStart(cin, cout);
	return 0;
}
