/*
	Muhammad Subhan
	20I-0873
	CS D
	Question No 1
	Design and Analysis Of Algorithim Project
*/
#include<iostream>
#include<fstream>
#include<ctime>
#include"graph.h"

using namespace std;

const char* arg[] = { "OR1" , "OR2" , "OR3" , "OR4" , "OR5" };
int stats[1041][2] = { 0 };
int clauses = 0;		// number of clauses 
int last_count = 0;		// Satisfied Clauses
int satisfied = 0;		// Current Satisfied Clauses
//Function to Write variables to file provided by user
void writevariables(const char* filename, bool* variables)
{
	ofstream variablefile;
	variablefile.open(filename);
	if (variablefile.is_open())
	{
		for (int i = 0; i < 1041; i++)
		{
			variablefile << variables[i] << endl;
		}
	}
	variablefile.close();
}
// Function to Return variable value
bool getvalue(bool* variable, int N)
{
	if (N < 0)
	{
		return (!variable[N * -1]);
	}
	else
		return variable[N];
}
// Function to Change Value of Given Variables
bool changeval(bool * variable, int N)
{
	if (N < 0)
	{
		variable[N * -1] = 1 - variable[N * -1];
	}
	else
	{
		variable[N] = 1 - variable[N];
	}
	return variable[N];
}
// Function to Create Graph 
void creategraph(Graph<int> &g , int * N , int index , bool* variable)
{
	cout << "Inserting Nodes and Edges...\n";
	for (int i = 0; i < index; i++)
	{
		g.insertnode(N[i]);
	}
	int num = 1041;
	// inserting OR nodes in graph
	for (int i = 1; i <= 5; i++)
	{
		g.insertnode(num++);
	}

	// inserting edges in graph between nodes and OR
	num = 1041;
	g.insertedge(N[0], num, 0);
	for (int i = 1; i < index; i++)
	{
		g.insertedge(N[i], num++, 0);
	}

	// inserting edges in graph between ORs
	num = 1041;
	for (int i = 0; i < 4; i++)
	{
		g.insertedge(num, num+1, 0);
		num++;
	}
	return;
}
// Function to Traverse Graph and return Output
int traversegraph(Graph<int>& g, int* N, int index, bool* variables)
{
	bool output = false;
	graphnode<int>* head = g.gethead();
	graphnode<int>* ptr = g.returnvertex2(index);
	variables[ptr->vertexname] = getvalue(variables , head->vertexname);
	if (index == 1)
	{
		cout << "OUTPUT: " << variables[ptr->vertexname] << endl;
		if (variables[ptr->vertexname] == 1)
		{
			cout << "Clause Satisfied...\n";
		}
		else
			cout << "Clause Dissatisfied...\n";

		stats[(head->vertexname < 0 ? (head->vertexname * -1) : head->vertexname)][variables[ptr->vertexname]]++;
		return variables[ptr->vertexname];
	}
	head = head->next;
	stats[(N[0] < 0 ? (N[0] * -1) : N[0])][variables[ptr->vertexname]]++;
	cout << "Result: \n";
	for (int i = 1; i < index && ptr != NULL && head!= NULL ; i++)
	{
		cout << ptr->vertexname <<"   " << arg[ptr->vertexname - 1041] << "   " << head->vertexname << "\t";
		variables[ptr->vertexname] = (variables[ptr->vertexname] || getvalue(variables, head->vertexname));
		cout << variables[ptr->vertexname]<<"\n";
		if (output == 0 && variables[ptr->vertexname] == 1 )
		{
			output = variables[ptr->vertexname];
			stats[(N[i] < 0 ? (N[i] * -1) : N[i])][output]++;
		}
		else if (variables[ptr->vertexname] == 0)
		{
			stats[(N[i] < 0 ? (N[i] * -1) : N[i])][0]++;
		}
		/*
		if (output == 1 && getvalue(variables, N[i]) == 1)
		{
			stats[(N[i] < 0 ? (N[i] * -1) : N[i])][output]++;
		}
		if (output == 0)
		{
			stats[(N[i] < 0 ? (N[i] * -1) : N[i])][output]++;
		}
		*/
		output = variables[ptr->vertexname];
		
		if (ptr->next != NULL )
		{
			variables[ptr->next->vertexname] = variables[ptr->vertexname];
			ptr = ptr->next;
			head = head->next;
		}
		
	}
	cout << "OUTPUT: " << output << endl;
	
	if (output == 1)
	{
		cout << "Clause Satisfied!\n";
		satisfied++;
		//system("PAUSE");
		return 1;
	}
	else
	{
		cout << "Clause Dissatisfied!\n";
		//system("PAUSE");
		return 0;
	}
}
// Main Driver Function
int main()
{
	int N[13] = { 0 };
	int count = 0;
	int flips = 0;
	cout << "Generating Random Values...\n";
	bool variables[1046] = { 0 };

	// generating 1040 variables randomly 
	srand(time(0));
	for (int i = 1; i <= 1040; i++)
	{
		variables[i] = rand() % 2;
	}
	writevariables("TRandom.txt", variables);


Label:
	ifstream inputfile;
	inputfile.open("dataset.txt");
	while (!inputfile.eof() && !inputfile.fail())
	{
		Graph<int> g;
		int index = 0;
		cout << "Reading Files dataset.txt ....\n";
		while (1)
		{
			inputfile >> N[index];
			if (N[index] == 0)
			{
				break;
			}
			index++;
		}
		cout << "Input Values: ";
		for (int i = 0; i < index; i++)
		{
			if (N[i] < 0)
			{
				cout << N[i] << " , " << variables[N[i] * -1] << "\t";
			}
			else
			{
				cout << N[i] << " , " << variables[N[i]] << "\t";
			}
		}
		cout << endl;
		creategraph(g, N, index, variables);
		count = 0;
		cout << "INDEX : " << index << endl;
		traversegraph(g, N, index, variables);
//		if (traversegraph(g, N, index, variables) == 0) { system("PAUSE"); }
		cout << "\n********************************************************************************************\n";
		clauses++;
	}
	cout << "Total Number of Clauses Solved: " << clauses << endl;
	cout << "Total Number of Clauses Satisfied: " << satisfied << endl;
	writevariables("TDash.txt", variables);
	ofstream statfile;
	statfile.open("statfile.txt" , ios::trunc);
	for (int i = 1; i < 1041; i++)
	{
		statfile << i << "      Value: "<<variables[i] << "      Satisfied: " << stats[i][1] << "     Dissatisfied: " << stats[i][0] << endl;
		if (stats[i][1] - stats[i][0] <= 0 )//stats[i][1] < stats[i][0] )
		{
			if (stats[i][1] != 0 && stats[i][0] != 0)
			{
				variables[i] = 1 - variables[i];
				flips++;
			}
		}
		stats[i][0] = stats[i][1] = 0;
	}
	cout << endl;
	//system("PAUSE");
	//Sleep(1000);
	statfile.close();
	inputfile.close();


	if (satisfied > last_count)
	{
		last_count = satisfied;
		satisfied = 0;
		clauses = 0;
		goto Label;
	}
	cout << "Max Number Of Clauses Satisfied: " << last_count << endl;
	cout << "Flips: " << flips << endl;
}


