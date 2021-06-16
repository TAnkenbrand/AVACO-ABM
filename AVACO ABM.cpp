#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <omp.h> openmp

using namespace std;

double prices[8050][13];

int trend(int ii, int jj, int a1, int a2)
{
	if (prices[ii - jj][a2] > prices[ii - jj - a1][a2]) return 1;
	if (prices[ii - jj][a2] < prices[ii - jj - a1][a2]) return -1;
	else return 0;
}
int contrarien(int ii, int jj, int a1, int a2)
{
	if (prices[ii - jj][a2] < prices[ii - jj - a1][a2]) return 1;
	if (prices[ii - jj][a2] > prices[ii - jj - a1][a2]) return -1;
	else return 0;
}
int fundamentalistt(int ii, int jj, int a1, int a2, int ttt)
{
	if (((prices[ii - jj][ttt] - prices[ii - jj - a1][ttt]) / prices[ii - jj - a1][ttt]) > ((prices[ii - jj][a2] - prices[ii - jj - a1][a2]) / prices[ii - jj - a1][a2])) return 1;
	if (((prices[ii - jj][ttt] - prices[ii - jj - a1][ttt]) / prices[ii - jj - a1][ttt]) < ((prices[ii - jj][a2] - prices[ii - jj - a1][a2]) / prices[ii - jj - a1][a2])) return -1;
	else return 0;
}
int fundamentalistc(int ii, int jj, int a1, int a2, int ttt)
{
	if (((prices[ii - jj][ttt] - prices[ii - jj - a1][ttt]) / prices[ii - jj - a1][ttt]) < ((prices[ii - jj][a2] - prices[ii - jj - a1][a2]) / prices[ii - jj - a1][a2])) return 1;
	if (((prices[ii - jj][ttt] - prices[ii - jj - a1][ttt]) / prices[ii - jj - a1][ttt]) > ((prices[ii - jj][a2] - prices[ii - jj - a1][a2]) / prices[ii - jj - a1][a2])) return -1;
	else return 0;
}
int matrend(int ii, int jj, int a1, int a2)
{
	int kk;
	double ma = 0;
	for (kk = 0; kk < a1; kk++) {
		ma = ma + prices[ii - jj - kk][a2];
	}
	ma = ma / kk;
	if (ma < prices[ii - jj][a2]) return 1;
	if (ma > prices[ii - jj][a2]) return -1;
	else return 0;
}
int macontrarien(int ii, int jj, int a1, int a2)
{
	int kk;
	double ma = 0;
	for (kk = 0; kk < a1; kk++) {
		ma = ma + prices[ii - jj - kk][a2];
	}
	ma = ma / kk;
	if (ma > prices[ii - jj][a2]) return 1;
	if (ma < prices[ii - jj][a2]) return -1;
	else return 0;
}
int doptimizer(int iii, int jjj, int ttt, int nn, int dd)
{
	int ftickeri[8050][3], aa, bb, cc, fagentsi[5];
	double ftickerd[8050][3], fmaxperformance, fmaxdrawdown, fdynamic_maxperformance, fdynamic_maxdrawdown, fprofit[8050];
//	int dd = 20;		//Time Lag Optimizer: 1 - 25

	for (aa = 0; aa < nn; aa++) {
		for (jjj = 0; jjj < 3; jjj++) {
			ftickeri[aa][jjj] = 0;
		}
	}
	for (aa = 0; aa < nn; aa++) {
		for (jjj = 0; jjj < 3; jjj++) {
			ftickerd[aa][jjj] = 0;
		}
	}
	fmaxperformance = 0;
	fmaxdrawdown = 0;
	// Dynamic Optimizer			
	for (jjj = 1; jjj < 25; jjj++) {
		fprofit[jjj] = 0;
	}
	fdynamic_maxperformance = 0;
	fdynamic_maxdrawdown = 0;
	for (aa = 1; aa < 7; aa++) {
		for (bb = 1; bb < 13; bb++) {
			for (cc = 0; cc < 13; cc++) {
				fagentsi[0] = aa;		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:MA Trend, 6:MA Contrarian, 7:Rebalancer
				fagentsi[1] = bb;		//Time Lag: 1-12
				fagentsi[2] = cc;		//Time Series
				fagentsi[4] = 0;		//Order
				for (jjj = dd; jjj >= 1; jjj--) {
					if (fagentsi[0] == 1) fagentsi[4] = trend(iii, jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 2) fagentsi[4] = contrarien(iii, jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 3) fagentsi[4] = fundamentalistt(iii, jjj, fagentsi[1], fagentsi[2], ttt);
					if (fagentsi[0] == 4) fagentsi[4] = fundamentalistc(iii, jjj, fagentsi[1], fagentsi[2], ttt);
					if (fagentsi[0] == 5) fagentsi[4] = matrend(iii, jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 6) fagentsi[4] = macontrarien(iii, jjj, fagentsi[1], fagentsi[2]);

					//Dynamic Performance
					fprofit[jjj - 1] = fprofit[jjj] + fagentsi[4] * (prices[iii - jjj + 1][ttt] - prices[iii - jjj][ttt]) / prices[iii - jjj][ttt];
					if (fdynamic_maxperformance < fprofit[jjj]) {
						fdynamic_maxperformance = fprofit[jjj];
					}
					if (fdynamic_maxdrawdown < fdynamic_maxperformance - fprofit[jjj]) {
						fdynamic_maxdrawdown = fdynamic_maxperformance - fprofit[jjj];
					}
					if (fprofit[1] / fdynamic_maxdrawdown > ftickerd[iii][0]) {
						ftickerd[iii][0] = fprofit[1] / fdynamic_maxdrawdown;
						ftickerd[iii][1] = fprofit[1];
						ftickerd[iii][2] = fdynamic_maxdrawdown;
						ftickeri[iii][0] = aa;
						ftickeri[iii][1] = bb;
						ftickeri[iii][2] = cc;
					}
				}
			}
		}
	}
	// Forecast
	fagentsi[0] = ftickeri[iii][0];		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:MA Trend, 6:MA Contrarian
	fagentsi[1] = ftickeri[iii][1];		//Time Lag: 1-12
	fagentsi[2] = ftickeri[iii][2];		//Time Series
	fagentsi[4] = 0;					//Order
	jjj = 0;

	if (fagentsi[0] == 1) fagentsi[4] = trend(iii, jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 2) fagentsi[4] = contrarien(iii, jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 3) fagentsi[4] = fundamentalistt(iii, jjj, fagentsi[1], fagentsi[2], ttt);
	if (fagentsi[0] == 4) fagentsi[4] = fundamentalistc(iii, jjj, fagentsi[1], fagentsi[2], ttt);
	if (fagentsi[0] == 5) fagentsi[4] = matrend(iii, jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 6) fagentsi[4] = macontrarien(iii, jjj, fagentsi[1], fagentsi[2]);
	
	ofstream DOTickerFile("AVACO ABM DOTicker.csv", ios::app);
	DOTickerFile << iii << ";" << fagentsi[4] << ";" << ftickeri[iii][0] << ";" << ftickeri[iii][1] << ";" << ftickeri[iii][2] << endl;
	DOTickerFile.close();
	
	return fagentsi[4];
}

int main()
{
	int i, j, k, a, c, e, f, g, h, n, tt, agentsi[3][5];
	double agentsd[3][4], ticker[8050][4];
	string line, value;
	double orders, volume, maxperformance, maxdrawdown, efficency, b, d, ma, r, s;

	n = 5219;	//number of datasets 460 / 8045 in sample 276 / 5219
	tt = 12;	//Dependent/target time series

	
	ifstream PriceFile("AVACO Price.csv");
	for (i = 0; i < n; i++) {
		getline(PriceFile, line);
		stringstream ss(line);
		for (j = 0; j < 13; j++) {
			getline(ss, value, ',');
			prices[i][j] = stod(value);
		}
	}
	PriceFile.close();

	ofstream TickerFile("AVACO ABM Ticker.csv");
	ofstream SolutionFile("AVACO ABM Solution.csv");
	
	for (a = 1; a < 2; a++) { //13
/*		for (b = 0; b <= 0.1; b += 0.01) {
			for (c = 1; c < 13; c++) {
				for (d = 0; d <= 0.1; d += 0.01) {
					for (e = 1; e < 8; e++) {
						for (f = 1; f < 8; f++) {
							for (g = 0; g < 13; g++) {
								for (h = 0; h < 13; h++) {
									for (r = 0; r <= 0.1; r += 0.01) {
										for (s = 0; s <= 0.01; s += 0.005) {*/
//Initialisation Agent1
											agentsi[0][0] = 7; //e;			//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:MA Trend, 6:MA Contrarian, 7:Dynamic Optimizer
											agentsi[0][1] = 20; // a;		//Time Lag: 1-12, Time Lag Optimizer: 1 - 25
											agentsi[0][2] = 1; // g;		//Time Series
											agentsd[0][0] = 0.01; // b;		//Trading Ratio
											agentsd[0][1] = 1;		//Cash
											agentsd[0][2] = 0.01;	//Asset
											agentsd[0][3] = 0;		//Order
//Initialisation Agent2
											agentsi[1][0] = 1; //f 		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:MA Trend, 6:MA Contrarian, 7:Dynamic Optimizer
											agentsi[1][1] = 1;	//c		//Time Lag: 1-12
											agentsi[1][2] = 1;	//g		//Time Series
											agentsd[1][0] = 0;	//d		//Trading Ratio
											agentsd[1][1] = 1;		//Cash
											agentsd[1][2] = 0.01;	//Asset
											agentsd[1][3] = 0;		//Order
//Initialisation Agent3
											agentsi[2][0] = 1;		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian, 5:MA Trend, 6:MA Contrarian, 7:Dynamic Optimizer
											agentsi[2][1] = 6;		//Time Lag: 1-12
											agentsi[2][2] = 7;		//Time Series
											agentsd[2][0] = 0; // r	//Trading Ratio
											agentsd[2][1] = 1;		//Cash
											agentsd[2][2] = 0.01;	//Asset
											agentsd[2][3] = 0;		//Order
								
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
													if (agentsi[j][0] == 5) agentsi[j][4] = matrend(i, 0, agentsi[j][1], agentsi[j][2]);
													if (agentsi[j][0] == 6) agentsi[j][4] = macontrarien(i, 0, agentsi[j][1], agentsi[j][2]);
													if (agentsi[j][0] == 7) agentsi[j][4] = doptimizer(i, 0, tt, n, agentsi[j][1]);


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
												TickerFile << ticker[i][0] << ";" << ticker[i][1] << ";" << ticker[i][2] << ";" << maxdrawdown << ";" << efficency << ";" << agentsd[0][1] << ";" << agentsd[1][1] << endl;
											}
											efficency = ticker[n-1][2] / (efficency - abs((prices[36][tt] - prices[35][tt]) / prices[35][tt]));
											TickerFile.close();
											if (efficency > 0.20) {
												if (maxdrawdown < 0.66) {
													SolutionFile << efficency << ";" << maxdrawdown /* << ";" << b << ";" << c << ";" << d << ";" << f << ";" << g */ << endl;
												}
											}
										}
/*									}
								}
							}
						}
					}
				}
			}
		}
	}
*/	SolutionFile.close();
}