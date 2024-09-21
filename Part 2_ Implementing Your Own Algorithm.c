/**
 * @file reversi.c
 * @author <-Sankalp Aggarwal->
 */

#if !defined(TESTER_P1) && !defined(TESTER_P2)
#include "reversi.h"
#endif

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void printBoard(char board[][26], int n) {
  char row = 'a';
  char col = 'a';

  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < n + 1; j++) {
      if (i == 0 && j == 0) {
        printf("  ");

      } else if (i == 0) {
        printf("%c", row++);
      } else if (j == 0) {
        printf("%c ", col++);
      } else if ((i == n / 2 && j == n / 2) ||
                 (i == (n / 2) + 1 && j == (n / 2) + 1)) {
        printf("%c", board[i - 1][j - 1]);

      } else if ((i == n / 2 && j == (n / 2) + 1) ||
                 (i == (n / 2) + 1 && j == n / 2)) {
        printf("%c", board[i - 1][j - 1]);

      } else {
        printf("%c", board[i - 1][j - 1]);
      }
    }

    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col) {
  if ((0 <= row && row < n) && (0 <= col && col < n)) {
    return true;
  } else {
    return false;
  }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  if (colour == 'W') {
    bool chk = true;

    for (int x = row, y = col; positionInBounds(n, x, y);
         x += deltaRow, y += deltaCol) {
      if (x == row + deltaRow && y == col + deltaCol) {
        if (board[x][y] == 'U' || board[x][y] == 'W') {
          return false;
        }
      } else {
        if (board[x][y] == 'W') {
          if (x == row && y == col) {
            continue;
          } else {
            chk = false;
            break;
          }

        } else if (board[x][y] == 'U') {
          if (x == row && y == col) {
            continue;
          } else {
            return false;
          }
        } else {
          continue;
        }
      }
    }
    if (chk == false) {
      return true;
    } else {
      return false;
    }
  } else {
    bool chk = true;

    for (int x = row, y = col; positionInBounds(n, x, y);
         x += deltaRow, y += deltaCol) {
      if (x == row + deltaRow && y == col + deltaCol) {
        if (board[x][y] == 'U' || board[x][y] == 'B') {
          return false;
        }
      } else {
        if (board[x][y] == 'B') {
          if (x == row && y == col) {
            continue;
          } else {
            chk = false;
            break;
          }
        } else if (board[x][y] == 'U') {
          if (x == row && y == col) {
            continue;
          } else {
            return false;
          }
        } else {
          continue;
        }
      }
    }

    if (chk == false) {
      return true;
    } else {
      return false;
    }
  }
}

int checkformove(char board[][26], int n, int row, int col, char hc, char cc) {
  if (positionInBounds(n, row, col) && board[row][col] == 'U') {
    bool chk = true;
    for (int dr = -1; dr <= 1; dr++) {
      for (int dc = -1; dc <= 1; dc++) {
        if (dr != 0 || dc != 0) {
          if (checkLegalInDirection(board, n, row, col, hc, dr, dc)) {
            board[row][col] = hc;
            int i = 1;
            while (board[row + (dr * i)][col + (dc * i)] != hc) {
              board[row + (dr * i)][col + (dc * i)] = hc;
              i++;
            }
            printBoard(board, n);
            return 0;
          }
        }
      }
    }
  }
  printf("Invalid move.");
  printf("%c player wins.", cc);
  return 1;
}

int calcScore(char board[26][26], char hc, char cc, int n) {
  int score = 0, row = 0, col = 0;
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++) {
      score = score - board[row][col] == hc;
      score = score + board[row][col] == cc;
    }
  }
  return score;
}

int makeMoves(char board[26][26], int n, char turn, int row, int col) {
  int x = 0, y = 0, dr = 0, dc = 0;
  char tempboard[26][26];
  char oppturn;
  if (turn == 'W') {
    oppturn = 'B';
  } else {
    oppturn = 'W';
  }
  board[row][col] = turn;

  for (dr = -1; dr <= 1; dr++)
    for (dc = -1; dc <= 1; dc++) {
      if (row + dr < 0 || row + dr >= n || col + dc < 0 || col + dc >= n ||
          (dr == 0 && dc == 0))
        continue;

      if (board[row + dr][col + dc] == oppturn) {
        x = row + dr;
        y = col + dc;

        for (;;) {
          x += dr;
          y += dc;

          if (x < 0 || x >= n || y < 0 || y >= n) break;

          if (board[x][y] == ' ') break;

          if (board[x][y] == turn) {
            while (board[x -= dr][y -= dc] == oppturn) board[x][y] = turn;
            break;
          }
        }
      }
    }
}

int bestMove(char board[26][26], int moves[26][26], char hc, int n) {
  int row = 0, col = 0, i = 0, j = 0;
  char cc;
  if (hc == 'W') {
    cc = 'B';
  } else {
    cc = 'W';
  }
  char tempboard[26][26];
  int score = 0;
  int newScore = 0;
  for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++) {
      if (!moves[row][col]) continue;
      for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
          tempboard[i][j] = board[i][j];
        }
      }
      makeMoves(tempboard, n, hc, row, col);
      newScore = calcScore(tempboard, hc, cc, n);
      if (score < newScore) {
        score = newScore;
      }
    }
  }
  return score;
}

void computerMoves1(char board[26][26], int n, char cc, char hc, int *row,
                    int *col) {
  int dr, dc;
  int count = 0;
  int bestRow = 0;
  int bestCol = 0;
  int score = 600;
  int newScore = 0;
  int i, j;
  char tempboard[26][26];
  int validMovesComputer[26][26];
  int validMovesHuman[26][26];

  for (int z = 0; z < n; z++) {
    for (int y = 0; y < n; y++) {
      validMovesComputer[z][y] = 0;
      validMovesHuman[z][y] = 0;
    }
  }

  for (int row1 = 0; row1 < n; row1++) {
    for (int col1 = 0; col1 < n; col1++) {
      if (board[row1][col1] == 'U') {
        for (dr = -1; dr <= 1; dr++) {
          for (dc = -1; dc <= 1; dc++) {
            if ((dr != 0 || dc != 0) &&
                checkLegalInDirection(board, n, row1, col1, cc, dr, dc)) {
              validMovesComputer[row1][col1] = 1;
            }
          }
        }
      }
    }
  }

  for (int row1 = 0; row1 < n; row1++) {
    for (int col1 = 0; col1 < n; col1++) {
      if (validMovesComputer[row1][col1] == 0) continue;
      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) tempboard[i][j] = board[i][j];
      makeMoves(tempboard, n, cc, row1, col1);
      for (int row1 = 0; row1 < n; row1++) {
        for (int col1 = 0; col1 < n; col1++) {
          if (board[row1][col1] == 'U') {
            for (dr = -1; dr <= 1; dr++) {
              for (dc = -1; dc <= 1; dc++) {
                if ((dr != 0 || dc != 0) &&
                    checkLegalInDirection(board, n, row1, col1, hc, dr, dc)) {
                  validMovesHuman[row1][col1] = 1;
                }
              }
            }
          }
        }
      }
      newScore = bestMove(tempboard, validMovesHuman, hc, n);
      if (newScore < score) {
        score = newScore;
        bestRow = row1;
        bestCol = col1;
      }
    }
  }
  *row = bestRow;
  *col = bestCol;
}
int makeMove(char board[26][26], int n, char turn, int *row, int *col) {
  char oppturn;
  if (turn == 'W') {
    oppturn = 'B';
  } else {
    oppturn = 'W';
  }
  computerMoves1(board, n, turn, oppturn, row, col);

  return 0;
}

int Humanmoves(char board[26][26], int n, char cc, char hc) {
  char row, col;
  printf("Enter move for colour %c (RowCol): ", hc);
  scanf(" %c%c", &row, &col);
  return checkformove(board, n, row - 'a', col - 'a', hc, cc);
}

void computerMoves(char board[26][26], int n, char cc, char hc) {
  int dr, dc;
  int count = 0;
  int bestRow = 0;
  int bestCol = 0;
  int score = 600;
  int newScore = 0;
  int i, j;
  char tempboard[26][26];
  int validMovesComputer[26][26];
  int validMovesHuman[26][26];

  for (int z = 0; z < n; z++) {
    for (int y = 0; y < n; y++) {
      validMovesComputer[z][y] = 0;
      validMovesHuman[z][y] = 0;
    }
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U') {
        for (dr = -1; dr <= 1; dr++) {
          for (dc = -1; dc <= 1; dc++) {
            if ((dr != 0 || dc != 0) &&
                checkLegalInDirection(board, n, row, col, cc, dr, dc)) {
              validMovesComputer[row][col] = 1;
            }
          }
        }
      }
    }
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (validMovesComputer[row][col] == 0) continue;
      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) tempboard[i][j] = board[i][j];
      makeMoves(tempboard, n, cc, row, col);
      for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
          if (board[row][col] == 'U') {
            for (dr = -1; dr <= 1; dr++) {
              for (dc = -1; dc <= 1; dc++) {
                if ((dr != 0 || dc != 0) &&
                    checkLegalInDirection(board, n, row, col, hc, dr, dc)) {
                  validMovesHuman[row][col] = 1;
                }
              }
            }
          }
        }
      }
      newScore = bestMove(tempboard, validMovesHuman, hc, n);
      if (newScore < score) {
        score = newScore;
        bestRow = row;
        bestCol = col;
      }
    }
  }

  for (dr = -1; dr <= 1; dr++) {
    for (dc = -1; dc <= 1; dc++) {
      if (checkLegalInDirection(board, n, bestRow, bestCol, cc, dr, dc)) {
        board[bestRow][bestCol] = cc;
        int i = 1;
        while (board[bestRow + (dr * i)][bestCol + (dc * i)] != cc) {
          board[bestRow + (dr * i)][bestCol + (dc * i)] = cc;
          i++;
        }
      }
    }
  }

  printf("Computer places %c at %c%c.\n", cc, bestRow + 97, bestCol + 97);

  printBoard(board, n);
}

#ifndef TESTER_P2

int main(void) {
  printf("Enter the board dimension: ");
  char board[26][26];
  int n = 0;

  scanf("%d", &n);

  printf("Computer plays (B/W): ");
  char z;
  scanf(" %c", &z);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i == (n / 2) - 1 && j == (n / 2) - 1) ||
          (i == (n / 2) && j == (n / 2))) {
        board[i][j] = 'W';
      } else if ((i == (n / 2) - 1 && j == (n / 2)) ||
                 (i == (n / 2) && j == (n / 2) - 1)) {
        board[i][j] = 'B';
      } else {
        board[i][j] = 'U';
      }
    }
  }
  printBoard(board, n);

  char nextmove;

  char hc;
  if (z == 'W') {
    hc = 'B';
    nextmove = hc;
  } else {
    hc = 'W';
    nextmove = z;
  }

  int invalidMove = 0;
  while (true) {
    bool continuegame = false;
    int row, col;
    for (row = 0; row <= n - 1; row++) {
      for (col = 0; col <= n - 1; col++) {
        if (board[row][col] == 'U') {
          continuegame = true;
          break;
        }
      }
    }
    if (continuegame) {
      int validMovesCount = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (board[i][j] == 'U') {
            bool chk = true;
            for (int dr = -1; dr <= 1; dr++) {
              for (int dc = -1; dc <= 1; dc++) {
                if (dr != 0 || dc != 0) {
                  if (checkLegalInDirection(board, n, i, j, nextmove, dr, dc)) {
                    validMovesCount += 1;

                    chk = false;
                    break;
                  }
                }
              }
              if (chk == false) {
                break;
              }
            }
          }
        }
      }
      if (nextmove == hc) {
        nextmove = z;
        if (validMovesCount != 0) {
          invalidMove = Humanmoves(board, n, z, hc);
          if (invalidMove == 1) {
            break;
          }
        } else {
          int validMovesCount = 0;
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
              if (board[i][j] == 'U') {
                bool chk = true;
                for (int dr = -1; dr <= 1; dr++) {
                  for (int dc = -1; dc <= 1; dc++) {
                    if (dr != 0 || dc != 0) {
                      if (checkLegalInDirection(board, n, i, j, nextmove, dr,
                                                dc)) {
                        validMovesCount += 1;

                        chk = false;
                        break;
                      }
                    }
                  }
                  if (chk == false) {
                    break;
                  }
                }
              }
            }
          }
          if (validMovesCount == 0) {
            break;
          }
          printf("%c player has no valid move.", hc);
        }
      } else if (nextmove == z) {
        nextmove = hc;
        if (validMovesCount != 0) {
          computerMoves(board, n, z, hc);
        } else {
          int validMovesCount = 0;
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
              if (board[i][j] == 'U') {
                bool chk = true;
                for (int dr = -1; dr <= 1; dr++) {
                  for (int dc = -1; dc <= 1; dc++) {
                    if (dr != 0 || dc != 0) {
                      if (checkLegalInDirection(board, n, i, j, nextmove, dr,
                                                dc)) {
                        validMovesCount += 1;

                        chk = false;
                        break;
                      }
                    }
                  }
                  if (chk == false) {
                    break;
                  }
                }
              }
            }
          }
          if (validMovesCount == 0) {
            break;
          }
          printf("%c player has no valid move.", z);
        }
      }
    } else {
      break;
    }
  }
  if (invalidMove == 0) {
    int cCount = 0;
    int hCount = 0;
    int row, col;
    for (row = 0; row <= n - 1; row++) {
      for (col = 0; col <= n - 1; col++) {
        if (board[row][col] == z) {
          cCount++;
        }

        else if (board[row][col] == hc) {
          hCount++;
        }
      }
    }

    if (cCount > hCount) {
      printf("%c player wins.", z);
    } else if (hCount > cCount) {
      printf("%c player wins.", hc);

    }

    else {
      printf("Draw!");
    }
  }
  return 0;
}

#endif
