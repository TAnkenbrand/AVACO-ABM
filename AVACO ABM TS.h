int trend(int aai0, int aai1, int aai3)
{
	if (prices[t][aai1] > prices[t - aai3][aai1]) return 1;
	if (prices[t][aai1] < prices[t - aai3][aai1]) return -1;
	else return 0;
}
int fundamentalist(int aai0, int aai1, int aai3)
{
	if (((prices[t][aai0] - prices[t - aai3][aai0]) / prices[t - aai3][aai0]) > ((prices[t][aai1] - prices[t - aai3][aai1]) / prices[t - aai3][aai1])) return 1;
	if (((prices[t][aai0] - prices[t - aai3][aai0]) / prices[t - aai3][aai0]) < ((prices[t][aai1] - prices[t - aai3][aai1]) / prices[t - aai3][aai1])) return -1;
	else return 0;
}
/*int doptimizer(int iii, int jjj, int ttt, int nn, int dd)
{
	int ftickeri[nd+1][3], aa, bb, cc, fagentsi[5];
	double ftickerd[nd+1][3], fmaxperformance, fmaxdrawdown, fdynamic_maxperformance, fdynamic_maxdrawdown, fprofit[nd+1];
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
			for (cc = 0; cc < nm; cc++) {
				fagentsi[0] = aa;		//Typ: 1:Trend, 2:Contrarian, 3:Fundamentalist Trend, 4:Fundamentalist Contrarian
				fagentsi[1] = bb;		//Time Lag: 1-12
				fagentsi[2] = cc;		//Time Series
				fagentsi[4] = 0;		//Order
				for (jjj = dd; jjj >= 1; jjj--) {
					if (fagentsi[0] == 1) fagentsi[4] = trend(t - jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 2) fagentsi[4] = contrarien(t - jjj, fagentsi[1], fagentsi[2]);
					if (fagentsi[0] == 3) fagentsi[4] = fundamentalistt(t - jjj, fagentsi[1], fagentsi[2], ttt);
					if (fagentsi[0] == 4) fagentsi[4] = fundamentalistc(t - jjj, fagentsi[1], fagentsi[2], ttt);

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

	if (fagentsi[0] == 1) fagentsi[4] = trend(iii - jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 2) fagentsi[4] = contrarien(iii - jjj, fagentsi[1], fagentsi[2]);
	if (fagentsi[0] == 3) fagentsi[4] = fundamentalistt(iii - jjj, fagentsi[1], fagentsi[2], ttt);
	if (fagentsi[0] == 4) fagentsi[4] = fundamentalistc(iii - jjj, fagentsi[1], fagentsi[2], ttt);

	ofstream DOTickerFile("AVACO ABM DOTicker.csv", ios::app);
	DOTickerFile << iii << ";" << fagentsi[4] << ";" << ftickeri[iii][0] << ";" << ftickeri[iii][1] << ";" << ftickeri[iii][2] << endl;
	DOTickerFile.close();
	
	return fagentsi[4];
}
*/

