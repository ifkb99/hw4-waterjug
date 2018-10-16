//I pledge my honor that I have abided by the Stevens Honor System
//Ian Baker and Alden Radoncic

#include "waterjug.h"

using namespace std;

State CtoA(State &cur) {
	if (cur.a < cap[0]) {
		int pour = cap[0] - cur.a;
		if (pour >= cur.c) {
			cur.a += cur.c;
		} else {
			cur.c -= pour;
			cur.a += pour;
		}
	}
	return cur;
}

State BtoA(State &cur) {
	if (cur.a < cap[0]) {
		int pour = cap[0] - cur.a;
		if (pour >= cur.b) {
			cur.a += cur.b;
		} else {
			cur.b -= pour;
			cur.a += pour;
		}
	}
	return cur;
}

State CtoB(State &cur) {
	if (cur.b < cap[1]) {
		int pour = cap[1] - cur.b;
		if (pour >= cur.c) {
			cur.b += cur.c;
		} else {
			cur.c -= pour;
			cur.b += pour;
		}
	}
	return cur;
}

State AtoB(State &cur) {
	if (cur.b < cap[1]) {
		int pour = cap[1] - cur.b;
		if (pour >= cur.a) {
			cur.b += cur.a;
		} else {
			cur.a -= pour;
			cur.b += pour;
		}
	}
	return cur;
}

State BtoC(State &cur) {
	if (cur.c < cap[2]) {
		int pour = cap[2] - cur.c;
		if (pour >= cur.b) {
			cur.c += cur.b;
		} else {
			cur.b -= pour;
			cur.c += pour;
		}
	}
	return cur;
}

State AtoC(State &cur) {
	if (cur.c < cap[2]) {
		int pour = cap[2] - cur.c;
		if (pour >= cur.a) {
			cur.c += cur.a;
		} else {
			cur.a -= pour;
			cur.c += pour;
		}
	}
	return cur;
}

void printGoal(State goal) {
	//TODO: make this recursive with base case nullptr
	cout << goal.string() << endl;
}

bool hitGoals(State cur) {
	BFTraversal.push(cur);
	while (!BFTraversal.empty()) {
		cur = BFTraversal.front();
		BFTraversal.pop();
		if (!(cur.a > cap[0] || cur.b > cap[1] || visitedMatrix[cur.a][cur.b])) {
			visitedMatrix[cur.a][cur.b] = true;
			if (cur.a == goal[0] && cur.b == goal[1]) {
				printGoal(cur);
				return true;
			}
			//push all traversals into queue
			//some math may still need to be checked
			BFTraversal.push(CtoA(cur));
			BFTraversal.push(BtoA(cur));
			BFTraversal.push(CtoB(cur));
			BFTraversal.push(AtoB(cur));
			BFTraversal.push(BtoC(cur));
			BFTraversal.push(AtoC(cur));
		}
	}
	return false;
}

int main(int argc, const char * argv[]) {
	if (argc != 7) {
		cout << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return -1;
	}

	istringstream iss;
	for (int i=1; i<=3; i++) {
		iss.str(argv[i]);
		if (!(iss >> cap[i-1])) {
			cout << "Error: Invalid capacity '" << argv[i] << "' for jug " << errArr[i-1] << "." << endl;
			return -1;
		}
		//add 3 to i in order to set the goal value
		iss.clear();
		iss.str(argv[i+3]);
		if (!(iss >> goal[i-1]) || goal[i-1] < 0) {
			cout << "Error: Invalid goal '" << argv[i+3] << "' for jug " << errArr[i-1] << "." << endl;
			return -1;
		}
		if (goal[i-1] > cap[i-1]) {
			cout << "Error: Goal cannot exceed capacity of jug " << errArr[i-1] << "." << endl;
			return -1;
		}
		iss.clear();
	}
	if (goal[0]+goal[1]+goal[2] != cap[2]) {
		cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return -1;
	}

	//define and populate trial matrix
	visitedMatrix = new bool*[cap[0]];
	for (int i=0; i<cap[0]; i++) {
		visitedMatrix[i] = new bool[cap[1]];
		fill(visitedMatrix[i], visitedMatrix[i]+cap[1], false);
	}

	cout << hitGoals(State{0, 0, cap[2], nullptr}) << endl;

	//make all calls here

	//delete visitedMatrix
	for (int i=0; i<cap[0]; i++) {
		delete [] visitedMatrix[i];
	}
	delete [] visitedMatrix;

	return 0;
}
