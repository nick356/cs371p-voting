// --------
// includes
// --------
#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <utility> // pair
#include "gtest/gtest.h"
#include "Voting.h"



// -----------
// TestVoting
// -----------

// Read

TEST(Voting, Canidites_1) {
	std::istringstream r("\n\nJohn\nJim\n");
	int x = 2;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_2) {
	std::istringstream r("\n\nJohn\nJim\nDick\nGreyson\nJason\nTodd\nTim\nDrake\n");
	int x = 8;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_3) {
	std::istringstream r("\n\nBatman\n");
	int x = 1;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_4) {
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_5) {
	std::istringstream r("\n\nThomas Taylor\nSusan Anderson\nWilliam Brown\nMaria Jones\nPatricia Davis\nBarbara Brown\nMary Thomas\nDorothy Wilson\nJennifer Johnson\nLinda Smith\nDavid Johnson\nSusan Johnson\nThomas Johnson\nRobert Thomas\nDavid Miller\nMargaret Wilson");
	int x = 16;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_6) {
	std::istringstream r("\n\nThomas Taylor\nSusan Anderson\nWilliam Brown\nMaria Jones\nPatricia Davis\nBarbara Brown\nMary Thomas");
	int x = 7;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_7) {
	std::istringstream r("\n\nThomas Taylor\nSusan Anderson\nWilliam Brown");
	int x = 3;
	ASSERT_EQ(true,createElection(x,r));
}

TEST(Voting, Canidites_8) {
	std::istringstream r("\n\nNancy Anderson\nThomas Jones\nLisa Thomas\nDaniel Williams\nElizabeth Taylor\nBarbara Jones\nThomas Johnson\nLisa Davis\nNancy Williams\nSusan Jones\nPatricia Wilson\nLinda Smith\nLisa Davis\nBarbara Miller\nLinda Taylor\nThomas Miller");
	int x = 16;
	ASSERT_EQ(true,createElection(x,r));
}



//Adding a ballot to some canidate's list.
TEST(Voting, Ballots_1){
	std::istringstream r("\n\nJohn\nJim\n");
	int x = 2;
	createElection(x,r);
	ASSERT_EQ(0,assignBallot("1 2\n"));
}

TEST(Voting, Ballots_2){
	std::istringstream r("\n\nJohn\nJim\n");
	int x = 2;
	createElection(x,r);
	ASSERT_EQ(1,assignBallot("2 1\n"));
}
TEST(Voting, Ballots_3){
	std::istringstream r("\n\nJohn\nJim\nDick\nGreyson\nJason\nTodd\nTim\nDrake\n");
	int x = 8;
	createElection(x,r);
	ASSERT_EQ(7,assignBallot("8 4 5 6 7 3 1 2\n"));
}

TEST(Voting, Ballots_4){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	ASSERT_EQ(2,assignBallot("3 4 2 1\n"));
}

TEST(Voting, Ballots_5){
	std::istringstream r("\n\nThomas Taylor\nSusan Anderson\nWilliam Brown\nMaria Jones\nPatricia Davis\nBarbara Brown\nMary Thomas\nDorothy Wilson\nJennifer Johnson\nLinda Smith\nDavid Johnson\nSusan Johnson\nThomas Johnson\nRobert Thomas\nDavid Miller\nMargaret Wilson");
	int x = 16;
	createElection(x,r);
	ASSERT_EQ(9,assignBallot("10 8 7 15 4 12 6 14 5 1 3 16 13 11 2 9\n")); 
	ASSERT_EQ(9,assignBallot("10 13 7 14 6 3 15 2 9 4 12 8 1 11 5 16\n")); 
	ASSERT_EQ(7,assignBallot("8 2 3 12 11 10 15 1 7 13 9 16 14 6 5 4\n"));
}

TEST(Voting, Ballots_6){
	std::istringstream r("\n\nBatman");
	int x = 1;
	createElection(x,r);
	ASSERT_EQ(0,assignBallot("1\n"));
}

TEST(Voting, Ballots_7){
	std::istringstream r("\n\nJohn\nJim\nDick\nGreyson\nJason\nTodd\nTim\nDrake\n");
	int x = 8;
	createElection(x,r);
	ASSERT_EQ(7,assignBallot("8 4 5 6 7 3 1 2\n"));
	ASSERT_EQ(3,assignBallot("4 5 6 7 3 8 1 2\n"));
}
TEST(Voting, Ballots_8){
	std::istringstream r("\n\nThomas Taylor\nSusan Anderson\nWilliam Brown\nMaria Jones\nPatricia Davis\nBarbara Brown\nMary Thomas\nDorothy Wilson\nJennifer Johnson\nLinda Smith\nDavid Johnson\nSusan Johnson\nThomas Johnson\nRobert Thomas\nDavid Miller\nMargaret Wilson");
	int x = 16;
	createElection(x,r);
	ASSERT_EQ(9,assignBallot("10 8 7 15 4 12 6 14 5 1 3 16 13 11 2 9\n")); 
	ASSERT_EQ(9,assignBallot("10 13 7 14 6 3 15 2 9 4 12 8 1 11 5 16\n")); 
	ASSERT_EQ(7,assignBallot("8 2 3 12 11 10 15 1 7 13 9 16 14 6 5 4\n"));
	ASSERT_EQ(11,assignBallot("12 13 9 10 15 14 5 4 7 2 6 8 16 11 1 3\n"));
}


//Is Lowest
TEST(Voting, lowest_1){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(0,y.first);
	ASSERT_EQ(1,y.second);
}
TEST(Voting, lowest_2){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(1,y.first);
	ASSERT_EQ(2,y.second);
}
TEST(Voting, lowest_3){
	std::istringstream r("\n\nBatman\n");
	int x = 1;
	createElection(x,r);
	assignBallot("1\n");
	assignBallot("1\n");
	assignBallot("1\n");
	assignBallot("1\n");
	assignBallot("1\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(5,y.first);
	ASSERT_EQ(5,y.second);
}
TEST(Voting, lowest_4){
	std::istringstream r("\n\nJohn\nJim\nDick\nGreyson\nJason\nTodd\nTim\nDrake\n");
	int x = 8;
	createElection(x,r);
	assignBallot("8 7 6 5 4 3 2 1\n");
	assignBallot("7 8 6 5 4 3 2 1\n");
	assignBallot("6 7 8 5 4 3 2 1\n");
	assignBallot("5 6 7 8 4 3 2 1\n");
	assignBallot("4 5 6 7 8 3 2 1\n");
	assignBallot("3 4 5 6 7 8 2 1\n");
	assignBallot("2 3 4 5 6 7 8 1\n");
	assignBallot("1 2 3 4 5 6 7 8\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(1,y.first);
	ASSERT_EQ(1,y.second);
}

TEST(Voting, lowest_5){
	std::istringstream r("\n\nBatman\n");
	int x = 1;
	createElection(x,r);
	assignBallot("1\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(1,y.first);
	ASSERT_EQ(1,y.second);
}

TEST(Voting, lowest_6){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(2,y.first);
	ASSERT_EQ(4,y.second);
}

TEST(Voting, lowest_7){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("3 4 2 1\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(0,y.first);
	ASSERT_EQ(6,y.second);
}

TEST(Voting, lowest_8){
	std::istringstream r("\n\nJohn\nJim\nDick\nGreyson\nJason\nTodd\nTim\nDrake\n");
	int x = 8;
	createElection(x,r);
	assignBallot("8 7 6 5 4 3 2 1\n");
	assignBallot("7 8 6 5 4 3 2 1\n");
	assignBallot("6 7 8 5 4 3 2 1\n");
	assignBallot("5 6 7 8 4 3 2 1\n");
	assignBallot("4 5 6 7 8 3 2 1\n");
	assignBallot("3 4 5 6 7 8 2 1\n");
	assignBallot("2 3 4 5 6 7 8 1\n");
	assignBallot("1 2 3 4 5 6 7 8\n");
	assignBallot("8 7 6 5 4 3 2 1\n");
	assignBallot("7 8 6 5 4 3 2 1\n");
	assignBallot("6 7 8 5 4 3 2 1\n");
	assignBallot("5 6 7 8 4 3 2 1\n");
	assignBallot("4 5 6 7 8 3 2 1\n");
	assignBallot("3 4 5 6 7 8 2 1\n");
	assignBallot("2 3 4 5 6 7 8 1\n");
	assignBallot("1 2 3 4 5 6 7 8\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(2,y.first);
	ASSERT_EQ(2,y.second);
}

//Destroy
TEST(Voting, destroy_1){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(true,destroyCanidates(y.first));
}

TEST(Voting, destroy_2){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(true,destroyCanidates(y.first));
}

TEST(Voting, destroy_3){
	std::istringstream r("\n\nJohn\nJim\n");
	int x = 2;
	createElection(x,r);
	assignBallot("1 2\n");
	assignBallot("2 1\n");
	assignBallot("2 1\n");
	assignBallot("2 1\n");
	assignBallot("1 2\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(true,destroyCanidates(y.first));
}

TEST(Voting, destroy_4){
	std::istringstream r("\n\nJohn\nJim\n");
	int x = 2;
	createElection(x,r);
	assignBallot("1 2\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(true,destroyCanidates(y.first));
}

TEST(Voting, destroy_5){
	std::istringstream r("\n\nBarbra\nGordon\nHarley\nQuinn\n");
	int x = 4;
	createElection(x,r);
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	assignBallot("3 4 2 1\n");
	assignBallot("4 3 2 1\n");
	assignBallot("2 4 3 1\n");
	assignBallot("3 4 2 1\n");
	assignBallot("1 4 2 3\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(true,destroyCanidates(y.first));
}
TEST(Voting, destroy_6){
	std::istringstream r("\n\nBatman\n \n");
	int x = 2;
	createElection(x,r);
	assignBallot("1 2\n");
	pair<int, int> y=isThereLowest();
	ASSERT_EQ(true,destroyCanidates(y.first));
}

