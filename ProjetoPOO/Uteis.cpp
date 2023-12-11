#include "Uteis.h"


int Util::RandNumInt(int LimInf, int LimSup)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(LimInf, LimSup);
	return dis(gen);
}

double Util::RandNumDouble(double LimInf, double LimSup)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(LimInf, LimSup);
	return dis(gen);
}

