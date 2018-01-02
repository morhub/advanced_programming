#include "Parser.h"


using namespace std;


Parser::Parser(int argc, char* argv[]):
	rotate(false),
	threads(0)
{
	const string Rotate  = "-rotate";
	const string Threads = "-threads";
	
	bool parsedInput = false;

	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == Rotate)
		{
			rotate = true;
			continue;
		}
		if (argv[i] == Threads)
		{
			std::istringstream iss;
			iss.str(argv[++i]);
			iss >> threads;
			threads--; //1 thread is the main thread
			continue;
		}
		if (!parsedInput)
		{
			inputFile = argv[i];
			parsedInput = true;
			continue;
		}
		outputFile = argv[i];
	}
}
