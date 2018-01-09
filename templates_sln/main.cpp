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

int main()
{
	list<Puzzle2dPiece<5>> pieces = { { 0, 3, 2, -5 }, { 0, -2, 2, -5 } };
	Puzzle2dPiece<5> piece(1, 2, 3, 4);
	Puzzle2dPiece<5> piece2(4,3,2,1);

	cout << pieces.front();
	cout << piece;

	cout << "******" << endl;
	for(auto& c: pieces.front().getCoors())
		cout << c <<endl;

	cout << "******" << endl;
	for (auto& coor : piece)
		cout << coor << endl;


	//////DataMap
	DataMap<4,5> m = *(new DataMap<4,5>());
	m.insert(&piece);
	m.insert(&piece2);


	auto l = m.get(&piece2);

	cout << "size: " << l.size() << endl;
	cout << "parts in l: " << *l.front() << endl;

	///DataBase
	DataBase<4,5> db(pieces.begin(), pieces.end());

	auto ls= db.get(0, std::numeric_limits<int>::min(), 2, -5);
	
	cout << "DataBase: " << endl;
	for (auto& part : ls)
	{
		 cout << *part << endl;

	}

	//////////////////first Main///////////////
	     //********************************//
	//list<Puzzle2dPiece<5>> pieces = { { 0, 3, 2, -5 },{ 0, -2, 2, -5 } };
	//auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	//auto some_pieces = groups.get({ 0, 3, 2, std::numeric_limits<int>::min() });
	//for (auto piece_ptr : some_pieces) {
	//	std::cout << *piece_ptr << std::endl; // will print the first piece!

	//////////////////second Main///////////////
	//********************************//
	//list<Puzzle2dPiece<5>> pieces = { { 0, 3, 2, -5 },{ 0, -2, 2, -5 } };
	//auto groups = groupPuzzlePieces(pieces.begin(), pieces.end());
	//auto some_pieces = groups.get({ 0, std::numeric_limits<int>::min(), 2, -5 });
	//for (auto piece_ptr : some_pieces) {
	//	std::cout << *piece_ptr << std::endl; // will print both pieces!
	
    return 0;
}

