#ifndef WATERJUG_H
#define WATERJUG_H

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

//represents state of water in jugs
struct State {
	int a, b, c;
	std::vector<State> v;

	//used for printing
	std::string operation;

	State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}

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

//state mod funcs
State CtoA(State cur);
State BtoA(State cur);
State CtoB(State cur);
State AtoB(State cur);
State BtoC(State cur);
State AtoC(State cur);

//functions
void printState(State s);
void printGoal(State goal);
bool hitGoals(State cur);

//a capA by capB matrix
bool **visitedMatrix;

//traversal queue
std::queue<State> BFTraversal;

#endif
