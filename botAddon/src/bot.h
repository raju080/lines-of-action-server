#include <string>
#include <vector>

//std::string findMove (std::vector<std::vector<int>> board, int botNumber);
std::vector<std::vector<int>> findMoves (int i, int j, std::vector<std::vector<int>> &boardState, int currentPlayer);

void exploreCluster (int i, int j, int pieceNumber, std::vector<std::vector<int>> &boardState, std::vector<std::vector<bool>> &visited);

int isMatchOver (std::vector<std::vector<int>> &boardState);

int connectedness(std::vector<std::vector<int>> &boardState);

int heuristic(std::vector<std::vector<int>> &boardState);

std::vector<int> minimax(std::vector<std::vector<int>> &boardState, int depth, bool maxplayer);

std::vector<int> moveBot (std::vector<std::vector<int>> &boardState, int botPieceNumber);


