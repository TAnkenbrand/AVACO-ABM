#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

//Configuartion
const int nd = 979;		//number of datasets
const int nm = 8;		//number of markets/time series
const int na = 2;		//number of agents

double prices[nd][nm];	//time series
int t;					//time

struct agents 
{
	int agenti[4];						//Dependent, Independent, Strategy, Time Lag
	double agentd[1];					//Order Ratio
	double agenta[nm + 1], agento[nm];	//Assets (USD, Prices), Orders (Prices)
};


#include "AVACO ABM TS.h"
#include "AVACO ABM O.h"

int main()
{
	agents agent[na];

	int i, j;
	double profit[nd][nm];
	string line, value;
	double orders[nm], volume[nm], maxperformance[nm], maxdrawdown[nm], efficency[nm], trend[nm];

	//Read prices
	ifstream PriceFile("AVACO ABM Price.csv");
	for (i = 0; i < nd; i++) {
		getline(PriceFile, line);
		stringstream ss(line);
		for (j = 0; j < nm; j++) {
			getline(ss, value, ',');
			prices[i][j] = stod(value);
		}
	}
	PriceFile.close();

	//Initialization Agents
	ifstream AgentFile("AVACO ABM Agents.csv");
	for (i = 0; i < na; i++) {
		getline(AgentFile, line);
		stringstream ss(line);
		for (j = 0; j < 4; j++) {
			getline(ss, value, ',');
			agent[i].agenti[j] = stoi(value);
		}
		for (j = 0; j < 1; j++) {
			getline(ss, value, ',');
			agent[i].agentd[j] = stod(value);
		}
		for (j = 0; j < 9; j++) {
			getline(ss, value, ',');
			agent[i].agenta[j] = stod(value);
		}
	}
	AgentFile.close();
	
	for (i = 0; i < nd; i++) {
		for (j = 0; j < nm; j++) {
			profit[i][j] = 0;
		}
	}
	for (j = 0; j < nm; j++) {
		maxperformance[j] = 0;
		maxdrawdown[j] = 0;

		efficency[j] = 0;
		trend[j] = 0;
	}

	for (t = 36; t < nd; t++) {

		//Calculation Trading Strategy and Order		
		for (i = 0; i < na; i++) {
			for (j = 0; j < nm; j++) {
				agent[i].agento[j] = 0;

				if (agent[i].agenti[0] == j) {
					agent[i].agento[j] = trade_calculation(agent[i].agenti[0], agent[i].agenti[1], agent[i].agenti[2], agent[i].agenti[3]);
				}				
				agent[i].agento[j] = order_calculation(agent[i], j);
			}
		}
				
		//Price Calculation
		for (j = 0; j < nm; j++) {
			orders[j] = 0;
			volume[j] = 0.0001;
			for (i = 0; i < na; i++) {
				orders[j] = orders[j] + agent[i].agento[j];
//				volume[j] = volume[j] + abs(agent[i].agento[j]);
			}

		//Calculation of the Performance Indicators
			if (orders[j] == 0) {
				profit[t][j] = profit[t - 1][j];
			}
			if (orders[j] != 0) {
				profit[t][j] = profit[t - 1][j] + (orders[j] / abs(orders[j])) * (prices[t][j] - prices[t - 1][j]) / prices[t - 1][j];
			}

			if (orders[j] * (prices[t][j] - prices[t - 1][j]) > 0) trend[j] = trend[j] + 1;

			if (maxperformance[j] < profit[t][j]) {
				maxperformance[j] = profit[t][j];
			}
			if (maxdrawdown[j] < maxperformance[j] - profit[t][j]) {
				maxdrawdown[j] = maxperformance[j] - profit[t][j];
			}
			efficency[j] = efficency[j] + abs((prices[t][j] - prices[t - 1][j]) / prices[t - 1][j]);
		}
		
		//Clearing and Settlement of the Orders
		for (i = 0; i < na; i++) {
			agent[i] = clearing_settlement(agent[i]);
		}

		ofstream TickerFile("AVACO ABM Ticker.csv", ios::app);
		TickerFile << t << ";" << prices[t][1] << ";" << profit[t][1] << ";" << maxdrawdown[1] << ";" << trend[1] << ";" << efficency[1] << ";" << orders[1] << endl;
		TickerFile.close();

		//Learning / adaptation of the agents configuration
	}

	ofstream PerformanceFile("AVACO ABM Performance.csv");
	for (j = 0; j < nm; j++) {
		efficency[j] = profit[nd - 1][j] / efficency[j];
		trend[j] = trend[j] / (nd - 36);
		PerformanceFile << trend[j] << ";" << profit[nd - 1][j] << ";" << efficency[j] << ";" << maxdrawdown[j] << endl;
	}
	PerformanceFile.close();
}