// Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>

#define STRONG_TAKEN 3
#define WEAK_TAKEN 2
#define WEAK_NOT_TAKEN 1
#define STRONG_NOT_TAKEN 0

using namespace std;

void printReport(int M, int N, long total, long miss);


int main(int argc, char* argv[])
{
	ifstream memoryAccesses;		//Trace File

	string	
		fileURL,
		fileLine;

	unsigned long long	
		address,
		index,
		globalPredictionHistory = 0,
		counter = 0,
		upperBits, 
		mBits;

	long
		totalTraceCounter = 0,
		missedPredictions = 0;

	int
		M,
		N;

	char 
		actualPrediction,
		prediction;	// T for Taken N for Not Taken

	vector<int> predictionTable;

	
	/*
	parse the arguments and initialize cache_size, associativity, replacement, writeback policy, and file location
	*/
	M = stoi(argv[2]);
		
	N = stoi(argv[3]);
		
	fileURL = argv[4];
	
	for (int i = 0; i < (long long)pow(2, M); i++)
		predictionTable.push_back( WEAK_TAKEN);
	
	
	memoryAccesses.open(fileURL);
	
	/*
	if file not found exit the program
	remeber to use \\ when entering file location
	fileURL string takes into account escape characters
	*/
	if (!memoryAccesses)
	{

		cerr << fileURL << " Unable to open file datafile.txt" << endl;
		exit(1);   // call system to stop
	}

	/*
	parse the string
	*/
	while (memoryAccesses >> fileLine)
	{
		counter++;

		//every odd string is the access type Read or Write
		if (counter % 2 == 1)
			address = (unsigned long long)strtoll(fileLine.c_str(), 0, 16);
			

		//for every even string get the address
		if (counter % 2 == 0)
		{
			actualPrediction = fileLine[0];

			address = address >> 2;
			
			mBits = address & ((1 << M) - 1);

			//upperBits = upperBits >> (M - N);

			index = (globalPredictionHistory<<(M-N)) ^ mBits;

			
			int bitCounter = predictionTable[index];

			if (bitCounter >= WEAK_TAKEN)
			{
				prediction = 't';
				//globalPredictionHistory = ((globalPredictionHistory >> 1) + (int)pow(2,N-1)) % (int)pow(2, N);
			}
			else
			{
				prediction = 'n';
				//globalPredictionHistory = (globalPredictionHistory >> 1) % (int)pow(2, N);
			}

			if (actualPrediction == 't')
			{
				if (bitCounter != STRONG_TAKEN)
					predictionTable[index] += 1;
			}
			else 
			{
				if (bitCounter != STRONG_NOT_TAKEN)
					predictionTable[index] -= 1;
			}

			if (prediction != actualPrediction)
			{
				missedPredictions++;
			}
			
			if(actualPrediction =='t')
				globalPredictionHistory = ((globalPredictionHistory >> 1) + (int)pow(2, N - 1)) % (int)pow(2, N);
			else
				globalPredictionHistory = ((globalPredictionHistory >> 1)) % (int)pow(2, N);

			totalTraceCounter++;
		}

	}

	printReport(M, N, totalTraceCounter, missedPredictions);

	system("pause");
	return 0;
}



void printReport(int M, int N, long total, long misses)
{
	double missPercentage = (double)misses / (double)total;
	
	cout << M << " " << N << " " << missPercentage << endl;
}