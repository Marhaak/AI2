#include "Include.h"
#include "Agent.h"
#include "Environment.h"
#include <ctime>

using namespace std;

int sleep = 0;
int xCordForEnvironment = 10;
int yCordForEnvironment = 10;
int numOfDirt = 20;	
int numOfObstacles = 10;
bool reinsertDirt = true;
int numOfStepsBeforeNewDirt = 15;
int runtime = 10;


int main(int argc, char* argv[]){

	Environment* environment = nullptr;
	Agent* agent = nullptr;
	Node* startNode = nullptr;

	// Taking commandline parameter to set up size of environment
	if (argc == 2){
		environment = new Environment( string(argv[1]) );
	} else if (argc == 3){
		environment = new Environment( atoi(argv[1]), atoi(argv[2]) );
	} else if (argc == 5){
		environment = new Environment( atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]) );
	} else { 
		environment = new Environment( "File.AI" );
		//environment = new Environment(xCordForEnvironment, yCordForEnvironment, numOfDirt, numOfObstacles); 
	}
	clock_t start = clock();

	agent = new Agent(environment);
	
	//running.
	if(agent->Run() == 1) {
		cout << "It is very clean now!" << endl;
		environment->GetScore();
		clock_t end = clock();
		int time_elapsed = int(end - start);

		cout << "Tid(ms): " << time_elapsed;
		cin.get();
	} else {
		cout << "Can not clean everything!" << endl;
	}

	//Cleaning up
	delete environment;
	delete agent;
	delete startNode;
	environment = nullptr;
	agent = nullptr;
	startNode = nullptr;
	return 0;
}