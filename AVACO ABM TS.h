#pragma once
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
	for (aa = 1; aa < 5; aa++) {
		for (bb = 1; bb < 13; bb++) {
			for (cc = 0; cc < 13; cc++) {
				fagentsi[0] = aa;		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian
				fagentsi[1] = bb;		//Time Lag: 1-12
				fagentsi[2] = cc;		//Time Series
				fagentsi[4] = 0;		//Order
				for (jjj = dd; jjj >= 1; jjj--) {
					if (fagentsi[0] == 1) fagentsi[4] = trend(iii, jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 2) fagentsi[4] = contrarien(iii, jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 3) fagentsi[4] = fundamentalistt(iii, jjj, fagentsi[1], fagentsi[2], ttt);
					if (fagentsi[0] == 4) fagentsi[4] = fundamentalistc(iii, jjj, fagentsi[1], fagentsi[2], ttt);

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
	fagentsi[0] = ftickeri[iii][0];		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian,
	fagentsi[1] = ftickeri[iii][1];		//Time Lag: 1-12
	fagentsi[2] = ftickeri[iii][2];		//Time Series
	fagentsi[4] = 0;					//Order
	jjj = 0;

	if (fagentsi[0] == 1) fagentsi[4] = trend(iii, jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 2) fagentsi[4] = contrarien(iii, jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 3) fagentsi[4] = fundamentalistt(iii, jjj, fagentsi[1], fagentsi[2], ttt);
	if (fagentsi[0] == 4) fagentsi[4] = fundamentalistc(iii, jjj, fagentsi[1], fagentsi[2], ttt);

	ofstream DOTickerFile("AVACO ABM DOTicker.csv", ios::app);
	DOTickerFile << iii << ";" << fagentsi[4] << ";" << ftickeri[iii][0] << ";" << ftickeri[iii][1] << ";" << ftickeri[iii][2] << endl;
	DOTickerFile.close();
	
	return fagentsi[4];
}

double order_calculation(int ai0, int ai1, int ai2, double ad0, double ad1, double ad2, int ii, int ttt, int nn)
{
	int ai4;
	double ad3;
	ad3 = 0;
	
	if (ai0 == 1) ai4 = trend(ii, 0, ai1, ai2);
	if (ai0 == 2) ai4 = contrarien(ii, 0, ai1, ai2);
	if (ai0 == 3) ai4 = fundamentalistt(ii, 0, ai1, ai2, ttt);
	if (ai0 == 4) ai4 = fundamentalistc(ii, 0, ai1, ai2, ttt);
	if (ai0 == 5) ai4 = doptimizer(ii, 0, ttt, nn, ai1);


	if (ad1 > 0) {
		if (ai4 == 1) {
			ad3 = ad1 * ad0 / prices[ii][ttt];
		}
	}
	if (ad2 > 0) {
		if (ai4 == -1) {
			ad3 = -ad2 * ad0;
		}
	}
	return ad3;
}
