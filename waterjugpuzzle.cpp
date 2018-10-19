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

void stateCheck(State *cur, State *last) {
	if (visitedMatrix[cur->a][cur->b] == nullptr) {
		visitedMatrix[cur->a][cur->b] = last;
	} else {
		delete cur;
		cur = nullptr;
	}
}

State* CtoA(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->c, cap[0] - cur->a);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c, "C to A", pour);
		nextState->a += pour;
		nextState->c -= pour;
		stateCheck(nextState, cur);
	}
	return nextState;
}

State* BtoA(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->b, cap[0] - cur->a);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c, "B to A", pour);
		nextState->a += pour;
		nextState->b -= pour;
		stateCheck(nextState, cur);
	}
	return nextState;
}

State* CtoB(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->c, cap[1] - cur->b);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c, "C to B", pour);
		nextState->b += pour;
		nextState->c -= pour;
		stateCheck(nextState, cur);
	}
	return nextState;
}

State* AtoB(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->a, cap[1] - cur->b);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c, "A to B", pour);
		nextState->b += pour;
		nextState->a -= pour;
		stateCheck(nextState, cur);
	}
	return nextState;
}

State* BtoC(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->b, cap[2] - cur->c);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c, "B to C", pour);
		nextState->c += pour;
		nextState->b -= pour;
		stateCheck(nextState, cur);
	}
	return nextState;
}

State* AtoC(State *cur) {
	State *nextState = nullptr;
	int pour = min(cur->a, cap[2] - cur->c);
	if (pour > 0) {
		nextState = new State(cur->a, cur->b, cur->c, "A to C", pour);
		nextState->c += pour;
		nextState->a -= pour;
		stateCheck(nextState, cur);
	}
	return nextState;
}

void printState(State* s) {
	cout << "Pour " << s->amt << " gallon";
	if (s->amt > 1) { cout << "s"; }
	cout << " from " << s->op << ". " << s->to_string() << endl;
}

void printGoal(State* goal) {
	if (goal->a != 0 || goal->b != 0) {
		printGoal(visitedMatrix[goal->a][goal->b]);
		printState(goal);
	}	
}

bool hitGoals(State *cur) {
	BFTraversal.push(cur);
	while (!BFTraversal.empty()) {
		cur = BFTraversal.front();
		if (cur != nullptr) {
			if (cur->a == goal[0] && cur->b == goal[1]) {
				cout << "Initial state. " << startState->to_string() << endl;
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
	visitedMatrix = new bool*[cap[0]+1];
	for (int i=0; i<cap[0]+1; i++) {
		visitedMatrix[i] = new bool[cap[1]+1];
		fill(visitedMatrix[i], visitedMatrix[i]+cap[1]+1, false);
	}

	startState = new State{0, 0, cap[2], "", -1};
	if (!hitGoals(startState)) {
		cout << "No solution." << endl;
	}

	//delete visitedMatrix
	for (int i=0; i<cap[0]+1; i++) {
		delete [] visitedMatrix[i];
	}
	delete [] visitedMatrix;

	return 0;
}
