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
