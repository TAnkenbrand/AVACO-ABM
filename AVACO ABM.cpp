#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

double prices[8305][13];

#include "AVACO ABM TS.h"
#include "AVACO ABM O.h"

int main()
{
	int i, j, k, n, nts;
	double profit[8305][13];
	double agent[2][8];
	string line, value;
	double orders[13], volume[13], maxperformance[13], maxdrawdown[13], efficency[13];

	n = 8304;	//number of datasets 8305
	nts = 13;	//number of time series
		
	//Read prices
	ifstream PriceFile("AVACO ABM Price.csv");
	for (i = 0; i < n; i++) {
		getline(PriceFile, line);
		stringstream ss(line);
		for (j = 0; j < nts; j++) {
			getline(ss, value, ',');
			prices[i][j] = stod(value);
		}
	}
	PriceFile.close();

//Initialization Agents
	ifstream AgentFile("AVACO ABM Agents.csv");
	for (i = 0; i < 2; i++) {
		getline(AgentFile, line);
		stringstream ss(line);
		for (j = 0; j < 8; j++) {
			getline(ss, value, ',');
			agent[i][j] = stod(value);
		}
	}
	AgentFile.close();
		
	for (i = 0; i < n; i++) {
		for (j = 0; j < nts; j++) {
			profit[i][j] = 0;
		}
	}
	for (j = 0; j < nts; j++) {
		maxperformance[j] = 0;
		maxdrawdown[j] = 0;
		efficency[j] = 0;
	}
	
	for (i = 36; i < n; i++) {
		for (j = 0; j < nts; j++) {
			for (k = 0; k < 2; k++) {
				if (agent[k][0] == j) agent[k][7] = order_calculation(agent[k][2], agent[k][3], agent[k][1], agent[k][4], agent[k][5], agent[k][6], i, j, n);
			}

//Price Calculation
			orders[j] = 0;
			volume[j] = 0.0001;
			for (k = 0; k < 2; k++) {
				if (agent[k][0] == j) {
					orders[j] = orders[j] + agent[k][7];
					volume[j] = volume[j] + abs(agent[k][7]);
				}
			}
			if (orders[j] == 0) {
				profit[i + 1][j] = profit[i][j];
			}
			if (orders[j] != 0) {
				profit[i + 1][j] = profit[i][j] + (orders[j] / abs(orders[j])) * (prices[i + 1][j] - prices[i][j]) / prices[i][j];
			}

//Clearing and Settlement of the Orders
			for (k = 0; k < 2; k++) {
				if (agent[k][0] == j) {
					agent[k][5] = agent[k][5] - agent[k][7] * prices[i + 1][j];
					agent[k][6] = agent[k][6] + agent[k][7];
					agent[k][7] = 0;
				}
			}

//Calculation of the Performance Indicators
			if (maxperformance[j] < profit[i][j]) {
				maxperformance[j] = profit[i][j];
			}
			if (maxdrawdown[j] < maxperformance[j] - profit[i][j]) {
				maxdrawdown[j] = maxperformance[j] - profit[i][j];
			}
			efficency[j] = efficency[j] + abs((prices[i][j] - prices[i - 1][j]) / prices[i - 1][j]);
		}
//		efficency[j] = profit[n - 1][j] / (efficency[j] - abs((prices[36][j] - prices[35][j]) / prices[35][j]));
	}
	
	ofstream PerformanceFile("AVACO ABM Performance.csv");
	for (j = 0; j < nts; j++) {
		efficency[j] = profit[n - 1][j] / (efficency[j] - abs((prices[36][j] - prices[35][j]) / prices[35][j]));
		PerformanceFile << profit[n-1][j] << ";" << efficency[j] << ";" << maxdrawdown[j] << endl;
	}
	PerformanceFile.close();
}