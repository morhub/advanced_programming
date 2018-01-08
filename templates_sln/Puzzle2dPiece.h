#ifndef PUZZLE2DPIECE_H
#define PUZZLE2DPIECE_H

#include <vector>
using namespace std;


template<int K>
class Puzzle2dPiece {
	vector<int> _coordinates;
	int getRange() { return K; }

public:
	Puzzle2dPiece(int first, int sec, int third, int forth) 
	{
		_coordinates.push_back(first);
		_coordinates.push_back(sec);
		_coordinates.push_back(third);
		_coordinates.push_back(forth);
	}

	vector<int>::iterator begin() { return _coordinates.begin();  }
	vector<int>::iterator end()	{ return _coordinates.end();	}

	const vector<int>& getCoors()const { return _coordinates; }

	friend ostream& operator<<(ostream& out, const Puzzle2dPiece<K>& piece)
	{
		int dimension = piece.getCoors().size();
		for (int i = 0; i < dimension; i++)
		{
			string deli = (i == dimension - 1) ? "" : ", ";
			out << piece.getCoors().at(i) << deli;
		}
		out << endl;
		
		return out;
	}

	int getCoorAt(int t) { return _coordinates.at(t); }
	int getDimension()	 { return _coordinates.size(); }
};



#endif