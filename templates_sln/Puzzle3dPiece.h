#ifndef PUZZLE3DPIECE_H
#define PUZZLE3DPIECE_H

#include <vector>
#include "PuzzlePiece.h"

using namespace std;


template<int K>
class Puzzle3dPiece : public PuzzlePiece
{
public:
	static const size_t Dimension = 6;
	Puzzle3dPiece(int first, int sec, int third, int forth, int fifth, int sixth)
	{
		_coordinates.push_back(first);
		_coordinates.push_back(sec);
		_coordinates.push_back(third);
		_coordinates.push_back(forth);
		_coordinates.push_back(fifth);
		_coordinates.push_back(sixth);
	}

	friend ostream& operator<<(ostream& out, const Puzzle3dPiece<K>& piece)
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