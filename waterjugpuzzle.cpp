//I pledge my honor that I have abided by the Stevens Honor System
//Ian Baker and Alden Radoncic

#include "waterjug.h"

using namespace std;

int min(int a, int b) {
	return a > b ? b : a;
}

bool notVisited(State* cur) {
	return visitedMatrix[cur->a][cur->b] == nullptr;
}

void stateCheck(State *cur, int a, int b) {
	if (visitedMatrix[a][b] == nullptr) {
		visitedMatrix[a][b] = cur;
	} else {
		delete cur;
		cur = nullptr;
	}
}

State* CtoA(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->c, cap[0] - cur->a);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c);
		nextState->a += pour;
		nextState->c -= pour;
		stateCheck(nextState, cur->a, cur->b);
	}
	return nextState;
}

State* BtoA(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->b, cap[0] - cur->a);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c);
		nextState->a += pour;
		nextState->b -= pour;
		stateCheck(nextState, cur->a, cur->b);
	}
	return nextState;
}

State* CtoB(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->c, cap[1] - cur->b);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c);
		nextState->b += pour;
		nextState->c -= pour;
		stateCheck(nextState, cur->a, cur->b);
	}
	return nextState;
}

State* AtoB(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->a, cap[1] - cur->b);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c);
		nextState->b += pour;
		nextState->a -= pour;
		stateCheck(nextState, cur->a, cur->b);
	}
	return nextState;
}

State* BtoC(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->b, cap[2] - cur->c);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c);
		nextState->c += pour;
		nextState->b -= pour;
		stateCheck(nextState, cur->a, cur->b);
	}
	return nextState;
}

State* AtoC(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->a, cap[2] - cur->c);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c);
		nextState->c += pour;
		nextState->a -= pour;
		stateCheck(nextState, cur->a, cur->b);
	}
	return nextState;
}

void printState(State* s) {
	// cout << "Pour " << s.amt << " gallon";
	// if (s.amt > 1) { cout << "s"; }
	// cout << " from " << s.op << ". " << s.to_string() << endl;
	cout << s->to_string() << endl;
}

void printGoal(State* goal) {
	//TODO: add in extra string stuff
	// cout << goal->a << ", " << goal->b << endl;
	// if (goal->a != 0 && goal->b != 0) {
	// 	printGoal(visitedMatrix[goal->a][goal->b]);
	// }
	// printState(goal);
	while (goal->a != 0 && goal->b != 0) {
		printState(goal);
		goal = visitedMatrix[goal->a][goal->b];
	}
	printState(goal);
}

bool hitGoals(State *cur) {
	BFTraversal.push(cur);
	while (!BFTraversal.empty()) {
		//cur = BFTraversal.front();
		if (BFTraversal.front() != nullptr && notVisited(BFTraversal.front())) {
			if (BFTraversal.front()->a == goal[0] && BFTraversal.front()->b == goal[1]) {
				//printGoal(cur);
				cout << BFTraversal.front()->to_string() << endl;
				return true;
			}
			//push all traversals into queue
			BFTraversal.push(CtoA(BFTraversal.front()));
			BFTraversal.push(BtoA(BFTraversal.front()));
			BFTraversal.push(CtoB(BFTraversal.front()));
			BFTraversal.push(AtoB(BFTraversal.front()));
			BFTraversal.push(BtoC(BFTraversal.front()));
			BFTraversal.push(AtoC(BFTraversal.front()));
		}
		BFTraversal.pop();
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
	visitedMatrix = new State**[cap[0]+1];
	for (int i=0; i<cap[0]+1; i++) {
		visitedMatrix[i] = new State*[cap[1]+1];
		fill(visitedMatrix[i], visitedMatrix[i]+cap[1]+1, nullptr);
	}

	State *startState = new State{0, 0, cap[2]};
	if (!hitGoals(startState)) {
		cout << "No solution." << endl;
	}

	//delete visitedMatrix
	for (int i=0; i<cap[0]+1; i++) {
		//debug loop
		for (int j=0; j<cap[1]+1; j++) {
			if (visitedMatrix[i][j] != nullptr)
				cout << i << ", " << j << ": " << visitedMatrix[i][j]->to_string() << endl;
		}
		delete [] visitedMatrix[i];
	}
	delete [] visitedMatrix;

	return 0;
}
