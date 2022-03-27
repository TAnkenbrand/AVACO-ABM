#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

double prices[8050][16];

#include "AVACO ABM TS.h"
#include "AVACO ABM O.h"

int main()
{
	int i, j, n, nts, tt, agentsi[3][5];
	double agentsd[3][4], ticker[8050][4];
	string line, value;
	double orders, volume, maxperformance, maxdrawdown, efficency;

	n = 230;	//number of datasets
	nts = 16;	//number of time series
	tt = 15;	//Dependent/target time series
		
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

	
// Initialisation Agenten
	agentsi[0][0] = 1; // e		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:Dynamic Optimizer
	agentsi[0][1] = 2; // a		//Time Lag: 1-12, Time Lag Optimizer: 1 - 25
	agentsi[0][2] = 2; // g		//Time Series 0-16
	agentsd[0][0] = 0.1; // b		//Trading Ratio 0 - 0.1
	agentsd[0][1] = 1;			//Cash
	agentsd[0][2] = 0.01;		//Asset
	agentsd[0][3] = 0;			//Order
								
	agentsi[1][0] = 3;  // f 	//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:Dynamic Optimizer
	agentsi[1][1] = 4;	// c	//Time Lag: 1-12
	agentsi[1][2] = 1;	// h	//Time Series
	agentsd[1][0] = 0.02;	// d	//Trading Ratio
	agentsd[1][1] = 1;			//Cash
	agentsd[1][2] = 0.01;		//Asset
	agentsd[1][3] = 0;			//Order

	for (i = 0; i < n; i++) {
		for (j = 0; j < 4; j++) {
			ticker[i][j] = 0.0;
		}
	}
	maxperformance = 0;
	maxdrawdown = 0;
	efficency = 0;
	for (i = 36; i < n; i++) {
		for (j = 0; j < 3; j++) {
			agentsd[j][3] = order_calculation(agentsi[j][0], agentsi[j][1], agentsi[j][2], agentsd[j][0], agentsd[j][1], agentsd[j][2], i, tt, n);
		}

		//Clearing
		orders = 0;
		volume = 0.0001;
		for (j = 0; j < 3; j++) {
			orders = orders + agentsd[j][3];
			volume = volume + abs(agentsd[j][3]);
		}
		ticker[i + 1][1] = orders;
		ticker[i + 1][0] = prices[i][tt] * (1 + (orders / (50 * volume)));
		if (orders == 0) {
			ticker[i + 1][2] = ticker[i][2];
		}
		if (orders != 0) {
			ticker[i + 1][2] = ticker[i][2] + (orders / abs(orders)) * (prices[i + 1][tt] - prices[i][tt]) / prices[i][tt];
		}
		if (maxperformance < ticker[i][2]) {
			maxperformance = ticker[i][2];
		}
		if (maxdrawdown < maxperformance - ticker[i][2]) {
			maxdrawdown = maxperformance - ticker[i][2];
		}
		efficency = efficency + abs((prices[i][tt] - prices[i - 1][tt]) / prices[i - 1][tt]);
		for (j = 0; j < 3; j++) {
			agentsd[j][1] = agentsd[j][1] - agentsd[j][3] * prices[i + 1][tt];
			agentsd[j][2] = agentsd[j][2] + agentsd[j][3];
			agentsd[j][3] = 0;
		}
	}
	efficency = ticker[n - 1][2] / (efficency - abs((prices[36][tt] - prices[35][tt]) / prices[35][tt]));
	
	ofstream PerformanceFile("AVACO ABM Performance.csv");
	PerformanceFile << efficency << ";" << maxdrawdown << endl;
	PerformanceFile.close();
}