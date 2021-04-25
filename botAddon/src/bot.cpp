#include <string.h>
#include <iostream>
#include<algorithm>
#include <vector>
#include "bot.h"
using namespace std;

#define INF 100000

int BOT_NUMBER=2, HUMAN_NUMBER=1;

int pieceSquareTable8[8][8] = {
    {-80, -25, -20, -20, -20, -20, -25, -80},
    {-25,  10,  10,  10,  10,  10,  10,  -25},
    {-20,  10,  25,  25,  25,  25,  10,  -20},
    {-20,  10,  25,  50,  50,  25,  10,  -20},
    {-20,  10,  25,  50,  50,  25,  10,  -20},
    {-20,  10,  25,  25,  25,  25,  10,  -20},
    {-25,  10,  10,  10,  10,  10,  10,  -25},
    {-80, -25, -20, -20, -20, -20, -25, -80}
};

int pieceSquareTable6[6][6] = {
    {-80, -25, -20, -20, -25, -80},
    {-25,  10,  10,  10,  10,  -25},
    {-20,  10,  25,  25,  10,  -20},
    {-20,  10,  25,  25,  10,  -20},
    {-25,  10,  10,  10,  10,  -25},
    {-80, -25, -20, -20, -25, -80}
};

int connecednessVal1 = 0, connectednessVal2 = 0;


vector<vector<int>> findMoves (int i, int j, vector<vector<int>> &boardState, int currentPlayer) {
  // setSelectedPieceMoves([]);
  int BOARD_LENGTH = boardState.size();

	int currentPieceNumber = boardState[i][j];
	int opponentPieceNumber = (currentPlayer==1) ? 2 : 1;
	int verticalPieceCount = 0;
	int horizontalPieceCount = 0;
	int positiveDiagonalPieceCount = 0;
	int negativeDiagonalPieceCount = 0;

	vector<vector<int>> moves;

	if (currentPieceNumber == currentPlayer) {
		for (int k = 0; k < BOARD_LENGTH; k = k + 1) {
			if (boardState[k][j] != 0) verticalPieceCount += 1;
			if (boardState[i][k] != 0) horizontalPieceCount += 1;
			if (i + k < BOARD_LENGTH) {
				if (j + k < BOARD_LENGTH) {
					if (boardState[i + k][j + k] != 0) {
						negativeDiagonalPieceCount += 1;
					}
				}
				if (j - k >= 0) {
					if (boardState[i + k][j - k] != 0) {
						positiveDiagonalPieceCount += 1;
					}
				}
			}
			if (i - k >= 0 && k != 0) {
				if (j + k < BOARD_LENGTH) {
					if (boardState[i - k][j + k] != 0) {
						positiveDiagonalPieceCount += 1;
					}
				}
				if (j - k >= 0) {
					if (boardState[i - k][j - k] != 0) {
						negativeDiagonalPieceCount += 1;
					}
				}
			}
		}

		// finding moves

		if (horizontalPieceCount > 0) {
			// right
			if (j + horizontalPieceCount < BOARD_LENGTH && boardState[i][j + horizontalPieceCount] != currentPieceNumber) {
				bool flag = true;
				for (int k = j; k < j + horizontalPieceCount; k++) {
					if (boardState[i][k] == opponentPieceNumber) {
						flag = false;
					}
				}
				if(flag) {
                    vector<int> mv = { i, j, i, j+horizontalPieceCount };
                    moves.push_back(mv);
				}
			}
			if (j - horizontalPieceCount >= 0 && boardState[i][j - horizontalPieceCount] != currentPieceNumber ) {
				// left
				bool flag = true;
				for (int k = j; k > j - horizontalPieceCount; k--) {
					if (boardState[i][k] == opponentPieceNumber) {
						flag = false;
					}
				}
				if(flag) {
                    vector<int> mv = { i, j, i, j - horizontalPieceCount };
                    moves.push_back(mv);
				}
			}
		}

		if (verticalPieceCount > 0) {
			if (i + verticalPieceCount < BOARD_LENGTH && boardState[i + verticalPieceCount][j] != currentPieceNumber) {
				// down
				bool flag = true;
				for (int k = i; k < i + verticalPieceCount; k++) {
					if (boardState[k][j] == opponentPieceNumber) {
						flag = false;
					}
				}
				if(flag) {
                    vector<int> mv = { i, j, i+verticalPieceCount, j };
                    moves.push_back(mv);
				}
			}
			if (i - verticalPieceCount >= 0 && boardState[i - verticalPieceCount][j] != currentPieceNumber) {
				// up
				bool flag = true;
				for (int k = i; k > i - verticalPieceCount; k--) {
					if (boardState[k][j] == opponentPieceNumber) {
						flag = false;
					}
				}
				if(flag) {
                    vector<int> mv = { i, j, i-verticalPieceCount, j };
                    moves.push_back(mv);
				}
			}
		}

		if (positiveDiagonalPieceCount > 0) {
			// left down
			if (i + positiveDiagonalPieceCount < BOARD_LENGTH && j - positiveDiagonalPieceCount >= 0 &&
				boardState[i + positiveDiagonalPieceCount][j - positiveDiagonalPieceCount] != currentPieceNumber) {
				bool flag = true;
				for (int k = 0; k <positiveDiagonalPieceCount; k++) {
					if (boardState[i+k][j-k] == opponentPieceNumber) {
						flag = false;
					}
				}
				if(flag) {
                    vector<int> mv = { i, j, i + positiveDiagonalPieceCount,j - positiveDiagonalPieceCount };
                    moves.push_back(mv);
				}
			}
			// right up
			if (i - positiveDiagonalPieceCount >= 0 && j + positiveDiagonalPieceCount < BOARD_LENGTH &&
				boardState[i - positiveDiagonalPieceCount][j + positiveDiagonalPieceCount] != currentPieceNumber) {
				bool flag = true;
				for (int k = 0; k < positiveDiagonalPieceCount; k++) {
					if (boardState[i - k][j + k] == opponentPieceNumber) {
						flag = false;
					}
				}
				if (flag) {
                    vector<int> mv = { i, j, i - positiveDiagonalPieceCount,j + positiveDiagonalPieceCount };
                    moves.push_back(mv);
				}
			}
		}

		if (negativeDiagonalPieceCount > 0) {
			// right down
			if (i + negativeDiagonalPieceCount < BOARD_LENGTH && j + negativeDiagonalPieceCount < BOARD_LENGTH &&
				boardState[i + negativeDiagonalPieceCount][j + negativeDiagonalPieceCount] != currentPieceNumber) {
				bool flag = true;
				for (int k = 0; k < negativeDiagonalPieceCount; k++) {
					if (boardState[i + k][j + k] == opponentPieceNumber) {
						flag = false;
					}
				}
				if (flag) {
                    vector<int> mv = { i, j, i + negativeDiagonalPieceCount,j + negativeDiagonalPieceCount };
                    moves.push_back(mv);
				}
			}
			// left up
			if (i - negativeDiagonalPieceCount >= 0 && j - negativeDiagonalPieceCount >= 0 &&
				boardState[i - negativeDiagonalPieceCount][j - negativeDiagonalPieceCount] != currentPieceNumber) {
				bool flag = true;
				for (int k = 0; k < negativeDiagonalPieceCount; k++) {
					if (boardState[i - k][j - k] == opponentPieceNumber) {
						flag = false;
					}
				}
				if (flag) {
                    vector<int> mv = { i, j, i - negativeDiagonalPieceCount,j - negativeDiagonalPieceCount };
                    moves.push_back(mv);
				}
			}
		}
		// setSelectedPieceMoves(moves);
  }
  return moves;
};



void exploreCluster (int i, int j, int pieceNumber, vector<vector<int>> &boardState, vector<vector<bool>> &visited) {
	if (i<0 || i>=boardState.size() || j<0 || j>=boardState.size() || boardState[i][j] != pieceNumber) return;
	visited[i][j] = true;
	if (i+1<boardState.size() && !visited[i + 1][j])
		exploreCluster(i + 1, j, pieceNumber, boardState, visited);
	if (i-1>=0 && !visited[i-1][j])
		exploreCluster(i - 1, j, pieceNumber, boardState, visited);
	if (j+1<boardState.size() && !visited[i][j+1])
		exploreCluster(i, j + 1, pieceNumber, boardState, visited);
	if (j-1>=0 && !visited[i][j-1])
		exploreCluster(i, j - 1, pieceNumber, boardState, visited);
	if (i+1<boardState.size() && j+1<boardState.size() && !visited[i+1][j+1])
		exploreCluster(i + 1, j + 1, pieceNumber, boardState, visited);
	if (i - 1 >= 0 && j - 1 >= 0 && !visited[i - 1][j - 1])
		exploreCluster(i - 1, j - 1, pieceNumber, boardState, visited);
	if (i + 1 < boardState.size() && j - 1 >= 0 && !visited[i + 1][j - 1])
		exploreCluster(i + 1, j - 1, pieceNumber, boardState, visited);
	if (j + 1 < boardState.size() && i - 1 >= 0 && !visited[i - 1][j + 1])
		exploreCluster(i - 1, j + 1, pieceNumber, boardState, visited);
}

int isMatchOver (vector<vector<int>> &boardState) {
	int BOARD_LENGTH = boardState.size();
	int playerOneClusterCount = 0, playerTwoClusterCount = 0;
	vector<vector<bool>> visited;

	for (int i=0; i<BOARD_LENGTH; i++) {
        vector<bool> temp;
        for (int j=0; j<BOARD_LENGTH; j++) {
            if (boardState[i][j] != 0) temp.push_back(false);
            else temp.push_back(true);
        }
		visited.push_back(temp);
	}

	for (int i=0; i<BOARD_LENGTH; i++) {
		for (int j=0; j<BOARD_LENGTH; j++) {
			if (!visited[i][j]) {
				if (boardState[i][j]==HUMAN_NUMBER && playerOneClusterCount<2) {
                    exploreCluster(i, j, boardState[i][j], boardState, visited);
                    playerOneClusterCount++;
				}
				else if (boardState[i][j]==BOT_NUMBER && playerTwoClusterCount<2) {
                    exploreCluster(i, j, boardState[i][j], boardState, visited);
                    playerTwoClusterCount++;
				}
			}
		}
	}
	if (playerOneClusterCount==1 && playerTwoClusterCount==1) return 0;
	if (playerOneClusterCount==1) return HUMAN_NUMBER;
	if (playerTwoClusterCount==1) return BOT_NUMBER;
	return -1;
}


// heuristics

int connectedComponents (vector<vector<int>> &boardState) {
    int BOARD_LENGTH = boardState.size();
	int playerOneClusterCount = 0, playerTwoClusterCount = 0;
	vector<vector<bool>> visited;

	for (int k=0; k<BOARD_LENGTH; k++) {
        vector<bool> temp;
        for (int i=0; i<BOARD_LENGTH; i++) {
            temp.push_back(false);
        }
		visited.push_back(temp);
	}

	for (int i = 0; i < BOARD_LENGTH; i++) {
		for (int j = 0; j < BOARD_LENGTH; j++) {
			if (boardState[i][j] == 0) {
				visited[i][j] = true;
			}
		}
	}

	for (int i=0; i<BOARD_LENGTH; i++) {
		for (int j=0; j<BOARD_LENGTH; j++) {
			if (!visited[i][j]) {
				exploreCluster(i, j, boardState[i][j], boardState, visited);
				if (boardState[i][j]==HUMAN_NUMBER) playerOneClusterCount += 1;
				else if (boardState[i][j]==BOT_NUMBER) playerTwoClusterCount += 1;
			}
		}
	}
	//cout << "p1: " << playerOneClusterCount << " p2: " << playerTwoClusterCount << endl;
	return (100/playerTwoClusterCount) - (100/playerOneClusterCount);
}

int pieceSquareValue (vector<vector<int>> &boardState) {
    int p1=0, p2=0;
    for (int i=0; i<boardState.size(); i++) {
		for (int j=0; j<boardState.size(); j++) {
            if(boardState[i][j]==HUMAN_NUMBER) {
                if(boardState.size()==6) {
                    p1 += pieceSquareTable6[i][j];
                } else {
                    p1 += pieceSquareTable8[i][j];
                }
            }
			if(boardState[i][j]==BOT_NUMBER) {
                if(boardState.size()==6) {
                    p2 += pieceSquareTable6[i][j];
                } else {
                    p2 += pieceSquareTable8[i][j];
                }
            }
		}
	}

	return p2-p1;
}

int connectedness (vector<vector<int>> &boardState) {
    int p1=0, p2=0;

    for (int i=0; i<boardState.size(); i++) {
		for (int j=0; j<boardState.size(); j++) {
            if (boardState[i][j]==1) {
                if (i+1<boardState.size() && boardState[i+1][j]==1) p1++;
                if (i-1>=0 && boardState[i-1][j]==1) p1++;
                if (j+1<boardState.size() && boardState[i][j+1]==1) p1++;
                if (j-1>=0 && boardState[i][j-1]==2) p1++;
                if (i+1<boardState.size() && j+1<boardState.size() && boardState[i+1][j+1]==1) p1++;
                if (i - 1 >= 0 && j - 1 >= 0 && boardState[i - 1][j - 1]==1) p1++;
                if (i + 1 < boardState.size() && j - 1 >= 0 && boardState[i + 1][j - 1]==1) p1++;
                if (j + 1 < boardState.size() && i - 1 >= 0 && boardState[i - 1][j + 1]==1) p1++;
            } else if (boardState[i][j]==2) {
                if (i+1<boardState.size() && boardState[i+1][j]==2) p2++;
                if (i-1>=0 && boardState[i-1][j]==2) p2++;
                if (j+1<boardState.size() && boardState[i][j+1]==2) p2++;
                if (j-1>=0 && boardState[i][j-1]==2) p2++;
                if (i+1<boardState.size() && j+1<boardState.size() && boardState[i+1][j+1]==2) p2++;
                if (i - 1 >= 0 && j - 1 >= 0 && boardState[i - 1][j - 1]==2) p2++;
                if (i + 1 < boardState.size() && j - 1 >= 0 && boardState[i + 1][j - 1]==2) p2++;
                if (j + 1 < boardState.size() && i - 1 >= 0 && boardState[i - 1][j + 1]==2) p2++;
            }
		}
    }
    return p2-p1;
}

int minArea (vector<vector<int>> &boardState) {
    int p1=0, p2=0;
    int top1=10, bottom1=-1, left1=10, right1=-1, top2=10, bottom2=-1, left2=10, right2=-1;
    for (int i=0; i<boardState.size(); i++) {
		for (int j=0; j<boardState.size(); j++) {
            if (boardState[i][j]==1) {
                if (i<top1) top1=i;
                if (i>bottom1) bottom1=i;
                if (j<left1) left1=j;
                if (j>right1) right1=j;
            } else if (boardState[i][j]==2) {
                if (i<top2) top2=i;
                if (i>bottom2) bottom2=i;
                if (j<left2) left2=j;
                if (j>right2) right2=j;
            }
		}
    }
    p1 = (bottom1-top1)*(right1-left1);
    p2 = (bottom2-top2)*(right2-left2);
    return p1-p2;
}

void printBoard(vector<vector<int>> &boardState) {
    for (int i=0; i<boardState.size(); i++) {
		for (int j=0; j<boardState.size(); j++) {
            cout << boardState[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


int heuristic(vector<vector<int>> &boardState) {
    //int connectednessVal = connectedness(boardState);
    int pieceSquareVal = pieceSquareValue(boardState);
    //int areaVal = minArea(boardState);
    //return pieceSquareVal+connectednessVal*2+areaVal;
    return pieceSquareVal;
}

bool sortcol( const vector<int>& v1, const vector<int>& v2 ) {
    return v1[0] > v2[0];
}


vector<int> minimax(vector<vector<int>> &boardState, int depth, bool maxplayer, int alpha, int beta) {
    int win = isMatchOver(boardState);
    if (win >= 0) {
        if (win == BOT_NUMBER) {
            vector<int> vect = {INF-depth, -1, -1, -1, -1};
            return vect;
        }
        if (win == HUMAN_NUMBER) {
            vector<int> vect = {-INF+depth, -1, -1, -1, -1};
            return vect;
        }
        if (win == 0) {
            vector<int> vect = {0, -1, -1, -1, -1};
            return vect;
        }
        vector<int> vect = {0, -1, -1, -1, -1};
        return vect;
    }
    if (depth==0) {
        int val = heuristic(boardState);
        vector<int> vect = {val, -1, -1, -1, -1};
        return vect;
    }

    int BOARD_LENGTH = boardState.size();

    if(maxplayer) {
        //cout << "Max player " << endl << endl;
        vector<int> max_val = {-INF, -1, -1, -1, -1};
        for (int i=0; i<BOARD_LENGTH; i++) {
            for (int j=0; j<BOARD_LENGTH; j++) {
                if (boardState[i][j] == BOT_NUMBER) {
                    vector<vector<int>> moves = findMoves(i, j, boardState, BOT_NUMBER);
                    for (int k=0; k<moves.size(); k++) {
                        int prev_piece = boardState[moves[k][2]][moves[k][3]];
                        boardState[moves[k][2]][moves[k][3]] = BOT_NUMBER;
                        boardState[moves[k][0]][moves[k][1]] = 0;
                        //printBoard(boardState);
                        vector<int> child_val = minimax(boardState, depth-1, false, alpha, beta);
                        boardState[moves[k][2]][moves[k][3]] = prev_piece;
                        boardState[moves[k][0]][moves[k][1]] = BOT_NUMBER;
                        if (child_val[0] > max_val[0]) {
                            max_val[0] = child_val[0];
                            max_val[1] = moves[k][0];
                            max_val[2] = moves[k][1];
                            max_val[3] = moves[k][2];
                            max_val[4] = moves[k][3];
                        }
                        alpha = max(alpha, child_val[0]);
                        if (beta <= alpha) break;
                    }
                }
            }
        }
        return max_val;
    } else {
        //cout << "Max player " << endl << endl;
        vector<int> min_val = {INF, -1, -1, -1, -1};
        for (int i=0; i<BOARD_LENGTH; i++) {
            for (int j=0; j<BOARD_LENGTH; j++) {
                if (boardState[i][j] == HUMAN_NUMBER) {
                    vector<vector<int>> moves = findMoves(i, j, boardState, HUMAN_NUMBER);
                    for (int k=0; k<moves.size(); k++) {
                        int prev_piece = boardState[moves[k][2]][moves[k][3]];
                        boardState[moves[k][2]][moves[k][3]] = HUMAN_NUMBER;
                        boardState[moves[k][0]][moves[k][1]] = 0;
                        //printBoard(boardState);
                        vector<int> child_val = minimax(boardState, depth-1, true, alpha, beta);
                        boardState[moves[k][2]][moves[k][3]] = prev_piece;
                        boardState[moves[k][0]][moves[k][1]] = HUMAN_NUMBER;
                        if (child_val[0] < min_val[0]) {
                            min_val[0] = child_val[0];
                            min_val[1] = moves[k][0];
                            min_val[2] = moves[k][1];
                            min_val[3] = moves[k][2];
                            min_val[4] = moves[k][3];
                        }
                        beta = min(beta, child_val[0]);
                        if (beta <= alpha) break;
                    }
                }
            }
        }
        return min_val;
    }
}



vector<vector<int>> findAllMoves(vector<vector<int>> &boardState, int pieceNumber) {
    vector<vector<int>> allMoves;
    for (int i=0; i<boardState.size(); i++) {
        for (int j=0; j<boardState.size(); j++) {
            if (boardState[i][j] == pieceNumber) {
                vector<vector<int>> moves = findMoves(i, j, boardState, pieceNumber);
                for (int k=0; k<moves.size(); k++) {
                    int prev_piece = boardState[moves[k][2]][moves[k][3]];
                    boardState[moves[k][2]][moves[k][3]] = pieceNumber;
                    boardState[moves[k][0]][moves[k][1]] = 0;
                    allMoves.push_back({heuristic(boardState), moves[k][0], moves[k][1], moves[k][2], moves[k][3]});
                    boardState[moves[k][2]][moves[k][3]] = prev_piece;
                    boardState[moves[k][0]][moves[k][1]] = pieceNumber;
                }
            }
        }
    }
    return allMoves;
}

vector<int> minimaxParent (vector<vector<int>> &boardState, int depth, bool maxplayer, int alpha, int beta) {
    vector<int> max_val = {-INF, -1, -1, -1, -1};
    vector<vector<int>> allMoves = findAllMoves(boardState, BOT_NUMBER);
    sort(allMoves.begin(), allMoves.end(),sortcol);
    for (int k=0; k<allMoves.size(); k++) {
        int prev_piece = boardState[allMoves[k][3]][allMoves[k][4]];
        boardState[allMoves[k][3]][allMoves[k][4]] = BOT_NUMBER;
        boardState[allMoves[k][1]][allMoves[k][2]] = 0;
        vector<int> child_val = minimax(boardState, depth-1, false, alpha, beta);
        boardState[allMoves[k][3]][allMoves[k][4]] = prev_piece;
        boardState[allMoves[k][1]][allMoves[k][2]] = BOT_NUMBER;
        if (child_val[0] > max_val[0]) {
            max_val[0] = child_val[0];
            max_val[1] = allMoves[k][1];
            max_val[2] = allMoves[k][2];
            max_val[3] = allMoves[k][3];
            max_val[4] = allMoves[k][4];
        }
        alpha = max(alpha, child_val[0]);
        if (beta <= alpha) break;
    }

    if(max_val[0]==-INF) return allMoves[0];
    return max_val;
}

vector<int> moveBot (vector<vector<int>> &boardState, int botPieceNumber) {
    int depth = 4;
    if (boardState.size()==6) depth = 6;
    else if (boardState.size()==8) depth = 5;

    vector<int> bestMove = minimaxParent(boardState, depth, true, -INF, +INF);
    cout << "best move: " << bestMove[1] << " " << bestMove[2] << " -> " << bestMove[3] << " " << bestMove[4] << " = " << bestMove[0] << endl;
    return bestMove;
}



int main () {
  vector<vector<int>> vec = {
	{0, 1, 1, 1, 1, 0},
	{0, 0, 2, 0, 0, 2},
	{2, 0, 0, 0, 0, 2},
	{2, 1, 0, 0, 0, 2},
	{2, 0, 0, 0, 0, 2},
	{0, 0, 1, 1, 1, 0},
  };

  moveBot(vec, 2);

  return 0;
}

