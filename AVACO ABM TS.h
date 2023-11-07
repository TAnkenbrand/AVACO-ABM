int trend(int aai0, int aai1, int aai3)
{
	if (prices[t - 1][aai1] > prices[t - 1 - aai3][aai1]) return 1;
	if (prices[t - 1][aai1] < prices[t - 1 - aai3][aai1]) return -1;
	else return 0;
}
int fundamentalist(int aai0, int aai1, int aai3)
{
	if (((prices[t - 1][aai0] - prices[t - 1 - aai3][aai0]) / prices[t - 1 - aai3][aai0]) > ((prices[t - 1][aai1] - prices[t - 1 - aai3][aai1]) / prices[t - 1 - aai3][aai1])) return 1;
	if (((prices[t - 1][aai0] - prices[t - 1 - aai3][aai0]) / prices[t - 1 - aai3][aai0]) < ((prices[t - 1][aai1] - prices[t - 1 - aai3][aai1]) / prices[t - 1 - aai3][aai1])) return -1;
	else return 0;
}
