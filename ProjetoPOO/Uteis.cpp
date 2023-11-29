#include "Uteis.h"


int Util::RandNumInt(int LimInf, int LimSup)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(LimInf, LimSup);

	return dis(gen);
}