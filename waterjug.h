#ifndef WATERJUG_H
#define WATERJUG_H

#include <iostream>
#include <sstream>
#include <queue>

//represents state of water in jugs
struct State {
	int a, b, c;
	State *parent;
	//set one to true according to which operation has been done
	//ex CtoA is idx 0, BtoA is idx 1...
	//used for printing
	bool operation[6];

	State(int _a, int _b, int _c, State* _parent) : a(_a), b(_b), c(_c), parent(_parent) {}

	//returns string of jug state
	std::string to_string() {
		std::ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

const std::string errArr[3] = {"A", "B", "C"};

//capacity for jug a b and c
int cap[3];
//goal values for jug a b and c
int goal[3];

//functions
bool hitGoals(State cur);
void printGoal(State goal);

//a capA by capB matrix
bool **visitedMatrix;

//traversal queue
std::queue<State> BFTraversal;

#endif
