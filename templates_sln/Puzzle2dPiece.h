#ifndef PUZZLE2DPIECE_H
#define PUZZLE2DPIECE_H

#include <vector>
#include "PuzzlePiece.h"

using namespace std;


template<int K>
class Puzzle2dPiece : public PuzzlePiece
{
public:
	static const size_t Dimension = 4;
	Puzzle2dPiece(int first, int sec, int third, int forth)
	{
		_coordinates.push_back(first);
		_coordinates.push_back(sec);
		_coordinates.push_back(third);
		_coordinates.push_back(forth);
	}

	friend ostream& operator<<(ostream& out, const Puzzle2dPiece<K>& piece)
	{
		int dimension = piece.Dimension;
		for (int i = 0; i < dimension; i++)
		{
			string deli = (i == dimension - 1) ? "" : ", ";
			out << piece.getCoorAt(i) << deli;
		}

		return out;
	}
};

#endif