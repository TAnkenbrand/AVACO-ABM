double trade_calculation(int ai0, int ai1, int ai3)
{
	int ai4 = 0;
	
	if (ai0 == 1) ai4 = trend(ai0, ai3);
	if (ai0 == 2) ai4 = -1 * trend(ai0, ai3);
	if (ai0 == 3) ai4 = fundamentalist(ai0, ai1, ai3);
	if (ai0 == 4) ai4 = - 1 * fundamentalist(ai0, ai1, ai3);
//	if (ai0 == 5) ai4 = doptimizer(0, ttt, nn, ai1);

	return ai4;
}

double order_calculation(agents agenttemp, int jj)
{
	if (jj == 0) {
		if (agenttemp.agenta[0] > 0) {
			if (agenttemp.agento[0] == 1) {
				agenttemp.agento[0] = agenttemp.agenta[0] * agenttemp.agentd[0] / prices[t][0];
			}
		}
		if (agenttemp.agenta[1] > 0) {
			if (agenttemp.agento[0] == -1) {
				agenttemp.agento[0] = -agenttemp.agenta[1] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 1) {
		if (agenttemp.agenta[0] > 0) {
			if (agenttemp.agento[1] == -1) {
				agenttemp.agento[1] = agenttemp.agenta[0] * agenttemp.agentd[0] * prices[t][1];
			}
		}
		if (agenttemp.agenta[2] > 0) {
			if (agenttemp.agento[1] == 1) {
				agenttemp.agento[1] = -agenttemp.agenta[2] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 2) {
		if (agenttemp.agenta[0] > 0) {
			if (agenttemp.agento[2] == 1) {
				agenttemp.agento[2] = agenttemp.agenta[0] * agenttemp.agentd[0] / prices[t][2];
			}
		}
		if (agenttemp.agenta[3] > 0) {
			if (agenttemp.agento[2] == -1) {
				agenttemp.agento[2] = -agenttemp.agenta[3] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 3) {
		if (agenttemp.agenta[1] > 0) {
			if (agenttemp.agento[3] == 1) {
				agenttemp.agento[3] = agenttemp.agenta[1] * agenttemp.agentd[0] / prices[t][3];
			}
		}
		if (agenttemp.agenta[4] > 0) {
			if (agenttemp.agento[2] == -1) {
				agenttemp.agento[2] = -agenttemp.agenta[4] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 4) {
		if (agenttemp.agenta[2] > 0) {
			if (agenttemp.agento[4] == 1) {
				agenttemp.agento[4] = agenttemp.agenta[2] * agenttemp.agentd[0] / prices[t][4];
			}
		}
		if (agenttemp.agenta[5] > 0) {
			if (agenttemp.agento[4] == -1) {
				agenttemp.agento[4] = -agenttemp.agenta[5] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 5) {
		if (agenttemp.agenta[0] > 0) {
			if (agenttemp.agento[5] == 1) {
				agenttemp.agento[5] = agenttemp.agenta[0] * agenttemp.agentd[0] / prices[t][5];
			}
		}
		if (agenttemp.agenta[6] > 0) {
			if (agenttemp.agento[5] == -1) {
				agenttemp.agento[5] = -agenttemp.agenta[6] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 6) {
		if (agenttemp.agenta[1] > 0) {
			if (agenttemp.agento[6] == 1) {
				agenttemp.agento[6] = agenttemp.agenta[1] * agenttemp.agentd[0] / prices[t][6];
			}
		}
		if (agenttemp.agenta[7] > 0) {
			if (agenttemp.agento[6] == -1) {
				agenttemp.agento[6] = -agenttemp.agenta[7] * agenttemp.agentd[0];
			}
		}
	}
	if (jj == 7) {
		if (agenttemp.agenta[2] > 0) {
			if (agenttemp.agento[7] == 1) {
				agenttemp.agento[7] = agenttemp.agenta[2] * agenttemp.agentd[0] / prices[t][7];
			}
		}
		if (agenttemp.agenta[8] > 0) {
			if (agenttemp.agento[7] == -1) {
				agenttemp.agento[7] = -agenttemp.agenta[8] * agenttemp.agentd[0];
			}
		}
	}

	return agenttemp.agento[jj];
}

