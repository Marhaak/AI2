#include "Include.h"
#include "Agent.h"
#include "Environment.h"

using namespace std;

int sleep = 300;
int xCordForEnvironment = 15;
int yCordForEnvironment = 15;

int main(int argc, char* argv[]){

	Environment* environment = nullptr;
	Agent* agent = nullptr;

	// Taking commandline parameter to set up size of environment
	if (argc == 2){
		environment = new Environment( string(argv[1]) );
	} else { 
		environment = new Environment( "File.AI" );
	}

	agent = new Agent(environment);
	
	//running.
	if(agent->Run() == 1) {
		cout << "\n\nReached the goal!" << endl;
		cin.get();
	} else {
		cout << "Cannot find the goal" << endl;
	}

	//Cleaning up
	delete environment;
	delete agent;
	environment = nullptr;
	agent = nullptr;
	return 0;
}