#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>

#include "Puzzle2dPiece.h"
#include "Puzzle3dPiece.h"
#include "PuzzlePiece.h"

#include "DataMap.h"
#include "DataBase.h"

using namespace std;

template<typename Iter, typename IterType = std::iterator_traits<Iter>::iterator_category()>
DataBase<Iter> groupPuzzlePieces(Iter first, Iter last)
{
	return DataBase<Iter>(first, last);
}

int main()
{
	cout << "2D Main:" << endl;
	list<Puzzle2dPiece<5>> pieces4 = { { 0, 3, 2, -5 },{ 0, -2, 2, -5 } };
	auto groups4 = groupPuzzlePieces(pieces4.begin(), pieces4.end());
	// note that there is no & on the auto below (was in previous version)
	auto some_pieces4 = groups4.get({ 0, std::numeric_limits<int>::min(), 2, -5 });
	for (auto piece_ptr4 : some_pieces4) {
		std::cout << *piece_ptr4 << std::endl; // will print both pieces!
	}

	cout << endl;

	cout << "3D Main:" << endl;
	list<Puzzle3dPiece<1>> pieces6 = { { 0, 1, 1, 1, -1, -1 },{ 0, -1, 1, 1, 1, 1 } };
	auto groups6 = groupPuzzlePieces(pieces6.begin(), pieces6.end());
	// note that there is no & on the auto below (was in previous version)
	auto some_pieces6 = groups6.get({ 0, 1, 1, 1, 1, 1 });
	for (auto piece_ptr6 : some_pieces6) {
		std::cout << *piece_ptr6 << std::endl; // will print nothing!
	}

	cout << endl;

	return 0;
}

