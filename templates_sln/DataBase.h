#ifndef DATABASE_H
#define DATABASE_H

#include "DataMap.h"
#include "Puzzle2dPiece.h"
#include <iostream>

using namespace std;


template<int DIM, int K>
class DataBase 
{
	DataMap<DIM,K> _map;

public:
	DataBase(typename list<Puzzle2dPiece<K>>::iterator _begin, typename list<Puzzle2dPiece<K>>::iterator _end)
	{
		for (auto& it = _begin; it != _end; it++)
		{
			_map.insert(&(*it));
		}
	}

	const list<Puzzle2dPiece<K>*>* get(int first, int sec, int third, int forth)
	{
		Puzzle2dPiece<K> p(first, sec, third, forth);
		return _map.get(&p);
	}

	const list<Puzzle3dPiece<K>*>* get(int first, int sec, int third, int forth, int fifth, int sixth)
	{
		Puzzle3dPiece<K> p(first, sec, third, forth, fifth, sixth);
		return _map.get(&p);
	}
};

#endif