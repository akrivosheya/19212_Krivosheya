#pragma once
#include <string>
#include "Strategy.h"


#define OPTIONALSTEPS 100

bool IsDigit(std::string str);

bool IsMode(char* str);

void SetModeOptional(const int& size, std::string& mode);

bool SetOptions(const int& size, std::string& mode, int& steps, int& i, const int& argc, char* argv[]);

std::string Moves(bool& moveS1, bool& moveS2, bool& moveS3);

void GetMoves(bool& moveS1, bool& moveS2, bool& moveS3, Strategy* S1, Strategy* S2, Strategy* S3);

void GetGets(bool& moveS1, bool& moveS2, bool& moveS3, int& getS1, int& getS2, int& getS3);

void GetPoints(int& pointS1, int& pointS2, int& pointS3, int& getS1, int& getS2, int& getS3);

void PutRes(bool& moveS1, bool& moveS2, bool& moveS3, Strategy* S1, Strategy* S2, Strategy* S3);

void PrintRes(int& pointS1, int& pointS2, int& pointS3, Strategy* S1, Strategy* S2, Strategy* S3);

void Reload(Strategy* S1, Strategy* S2, Strategy* S3);

void SetWinners(int& pointS1, int& pointS2, int& pointS3, int& S1, int& S2, int& S3);
