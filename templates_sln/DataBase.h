#ifndef DATABASE_H
#define DATABASE_H

#include "DataMap.h"
#include <iostream>

using namespace std;

/*
 * Class Database - A wrapper for DataMap data structure, which 
 * holds a mapping for the puzzle pieces by their coordinates.
 * In addition, it defines the main interface for the Data structure
 * (which support insert at constuction time only, and query)
 */
template<typename Iter>
class DataBase
{
	using DataType = typename std::iterator_traits<Iter>::value_type;
	DataMap<DataType, DataType::Dimension> _map;

public:
	DataBase(Iter _begin, Iter _end)
	{
		for (auto& it = _begin; it != _end; it++)
		{
			_map.insert(&(*it));
		}
	}

	const list<DataType*>& get(DataType p)
	{
		auto ret = _map.get(&p);
		return (ret == nullptr) ? *(new list<DataType*>()) : *(ret);
	}
};

template<typename Iter, typename IterType = std::iterator_traits<Iter>::iterator_category()>
DataBase<Iter> groupPuzzlePieces(Iter first, Iter last)
{
	return DataBase<Iter>(first, last);
}
#endif