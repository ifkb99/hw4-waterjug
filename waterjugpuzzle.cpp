//I pledge my honor that I have abided by the Stevens Honor System
//Ian Baker and Alden Radoncic

#include "waterjug.h"

using namespace std;

State CtoA(State cur) {
	State nextState = State{cur.a, cur.b, cur.c};
	nextState.v.push_back(cur);
	if (cur.a < cap[0]) {
		int pour = cap[0] - cur.a;
		if (pour >= cur.c) {
			nextState.a += cur.c;
			nextState.c = 0;
		} else {
			nextState.c -= pour;
			nextState.a += pour;
		}
	}
	return nextState;
}

State BtoA(State cur) {
	State nextState = State{cur.a, cur.b, cur.c};
	nextState.v.push_back(cur);
	if (cur.a < cap[0]) {
		int pour = cap[0] - cur.a;
		if (pour >= cur.b) {
			nextState.a += cur.b;
			nextState.b = 0;
		} else {
			nextState.b -= pour;
			nextState.a += pour;
		}
	}
	return nextState;
}

State CtoB(State cur) {
	State nextState = State{cur.a, cur.b, cur.c};
	nextState.v.push_back(cur);
	if (cur.b < cap[1]) {
		int pour = cap[1] - cur.b;
		if (pour >= cur.c) {
			nextState.b += cur.c;
			nextState.c = 0;
		} else {
			nextState.c -= pour;
			nextState.b += pour;
		}
	}
	return nextState;
}

State AtoB(State cur) {
	State nextState = State{cur.a, cur.b, cur.c};
	nextState.v.push_back(cur);
	if (cur.b < cap[1]) {
		int pour = cap[1] - cur.b;
		if (pour >= cur.a) {
			nextState.b += cur.a;
			nextState.a = 0;
		} else {
			nextState.a -= pour;
			nextState.b += pour;
		}
	}
	return nextState;
}

State BtoC(State cur) {
	State nextState = State{cur.a, cur.b, cur.c};
	nextState.v.push_back(cur);
	if (cur.c < cap[2]) {
		int pour = cap[2] - cur.c;
		if (pour >= cur.b) {
			nextState.c += cur.b;
			nextState.b = 0;
		} else {
			nextState.b -= pour;
			nextState.c += pour;
		}
	}
	return nextState;
}

State AtoC(State cur) {
	State nextState = State{cur.a, cur.b, cur.c};
	nextState.v.push_back(cur);
	if (cur.c < cap[2]) {
		int pour = cap[2] - cur.c;
		if (pour >= cur.a) {
			nextState.c += cur.a;
			nextState.a = 0;
		} else {
			nextState.a -= pour;
			nextState.c += pour;
		}
	}
	return nextState;
}

void printState(State s) {
	// cout << "Pour " << s.amt << " gallon";
	// if (s.amt > 1) { cout << "s"; }
	// cout << " from " << s.op << ". " << s.to_string() << endl;
	cout << s.to_string() << endl;
}

void printGoal(State goal) {
	//TODO: add in extra string stuff
	//reverse(goal.v.begin(), goal.v.end());
	for (auto &s: goal.v) {
		cout << s.to_string() << endl;
	}
	cout << goal.to_string() << endl;
}

bool visitedState(State &cur) {
	return visitedMatrix[cur.a][cur.b] != false;
}

bool hitGoals(State cur) {
	BFTraversal.push(cur);
	while (!BFTraversal.empty()) {
		cur = BFTraversal.front();
		BFTraversal.pop();
		if (!visitedMatrix[cur.a][cur.b]) {
			visitedMatrix[cur.a][cur.b] = true;
			if (cur.a == goal[0] && cur.b == goal[1]) {
				//printState(State{0, 0, cap[2]});
				printGoal(cur);
				return true;
			}
			//push all traversals into queue
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
	visitedMatrix = new bool*[cap[0]+1];
	for (int i=0; i<cap[0]+1; i++) {
		visitedMatrix[i] = new bool[cap[1]+1];
		fill(visitedMatrix[i], visitedMatrix[i]+cap[1]+1, false);
	}

	if (!hitGoals(State{0, 0, cap[2]})) {
		cout << "No solution." << endl;
	}

	//delete visitedMatrix
	for (int i=0; i<cap[0]+1; i++) {
		//debug loop
		// for (int j=1; j<cap[1]+1; j++) {
		// 	if (visitedMatrix[i][j] != nullptr)
		// 		cout << i << ", " << j << ": " << visitedMatrix[i][j]->to_string() << endl;
		// }
		delete [] visitedMatrix[i];
	}
	delete [] visitedMatrix;

	return 0;
}
