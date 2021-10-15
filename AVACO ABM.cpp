#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//#include <omp.h> openmp

using namespace std;

double prices[8050][13];

#include "AVACO ABM TS.h"

int main()
{
	int i, j, a, c, e, f, g, h, n, tt, agentsi[3][5];
	double agentsd[3][4], ticker[8050][4];
	string line, value;
	double orders, volume, maxperformance, maxdrawdown, efficency, b, d;

	n = 230;	//number of datasets 460 / 8045 / 321 in sample 276 / 5219 / 230
	tt = 1;	//Dependent/target time series

	
	ifstream PriceFile("AVACO Price.csv");
	for (i = 0; i < n; i++) {
		getline(PriceFile, line);
		stringstream ss(line);
		for (j = 0; j < 3; j++) { //13
			getline(ss, value, ',');
			prices[i][j] = stod(value);
		}
	}
	PriceFile.close();

//	ofstream TickerFile("AVACO ABM Ticker.csv");
	ofstream SolutionFile("AVACO ABM Solution.csv");
	
	for (a = 1; a < 13; a++) {
		for (b = 0; b <= 0.1; b += 0.01) {
			for (c = 1; c < 13; c++) {
				for (d = 0; d <= 0.1; d += 0.01) {
					for (e = 1; e < 5; e++) {
						for (f = e; f < 5; f++) { //1
							for (g = 0; g < 3; g++) { //13
								for (h = 0; h < 3; h++) { //13
									//Initialisation Agent1
									agentsi[0][0] = e; //e;			//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:Dynamic Optimizer
									agentsi[0][1] = a; // a;		//Time Lag: 1-12, Time Lag Optimizer: 1 - 25
									agentsi[0][2] = g; // g;		//Time Series
									agentsd[0][0] = b; // b;		//Trading Ratio
									agentsd[0][1] = 1;		//Cash
									agentsd[0][2] = 0.01;	//Asset
									agentsd[0][3] = 0;		//Order
//Initialisation Agent2
									agentsi[1][0] = f; //f 		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:Dynamic Optimizer
									agentsi[1][1] = c;	//c		//Time Lag: 1-12
									agentsi[1][2] = h;	//h		//Time Series
									agentsd[1][0] = d;	//d		//Trading Ratio
									agentsd[1][1] = 1;		//Cash
									agentsd[1][2] = 0.01;	//Asset
									agentsd[1][3] = 0;		//Order

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
											if (agentsi[j][0] == 1) agentsi[j][4] = trend(i, 0, agentsi[j][1], agentsi[j][2]);
											if (agentsi[j][0] == 2) agentsi[j][4] = contrarien(i, 0, agentsi[j][1], agentsi[j][2]);
											if (agentsi[j][0] == 3) agentsi[j][4] = fundamentalistt(i, 0, agentsi[j][1], agentsi[j][2], tt);
											if (agentsi[j][0] == 4) agentsi[j][4] = fundamentalistc(i, 0, agentsi[j][1], agentsi[j][2], tt);
											if (agentsi[j][0] == 5) agentsi[j][4] = doptimizer(i, 0, tt, n, agentsi[j][1]);


											if (agentsd[j][1] > 0) {
												if (agentsi[j][4] == 1) {
													agentsd[j][3] = agentsd[j][1] * agentsd[j][0] / prices[i][tt];
												}
											}
											if (agentsd[j][2] > 0) {
												if (agentsi[j][4] == -1) {
													agentsd[j][3] = -agentsd[j][2] * agentsd[j][0];
												}
											}
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
//										TickerFile << ticker[i][0] << ";" << ticker[i][1] << ";" << ticker[i][2] << ";" << maxdrawdown << ";" << efficency << ";" << agentsd[0][1] << ";" << agentsd[1][1] << endl;
									}
									efficency = ticker[n - 1][2] / (efficency - abs((prices[36][tt] - prices[35][tt]) / prices[35][tt]));
//									TickerFile.close();
									if (efficency > 0.29) {
										if (maxdrawdown < 0.64) {
											SolutionFile << efficency << ";" << maxdrawdown << ";" << a << ";" << b << ";" << c << ";" << d << ";" << e << ";" << f << ";" << g << ";" << h << endl;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	SolutionFile.close();
}