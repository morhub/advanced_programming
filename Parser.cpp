#include "Parser.h"


using namespace std;

Parser::Parser(int argc, char* argv[]):
	rotate(false),
	threads(0)
{
	const string Rotate  = "-rotate";
	const string Threads = "-threads";

	bool threadFlag  = false;
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
			threadFlag = true;
			std::istringstream iss;
			iss.str(argv[i+1]);
			iss >> threads;
			if (threads <= 0) //no number after this flag
			{
				threads = ILLEGAL_THREADS;
				break;
			}
			else
			{
				threads--; //1 thread is the main thread
				continue;
			}			
		}
		if (!parsedInput)
		{
			inputFile = argv[i];
			parsedInput = true;
			continue;
		}
		outputFile = argv[i];
	}
	
	if (!threadFlag)
		threads = 3; //the default is 4 threads, 1 is the main thread
}
