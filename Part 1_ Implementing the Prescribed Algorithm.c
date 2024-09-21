/**
 * @file reversi.c
 * @author Sankalp Aggarwal
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
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
  printf("Invalid move.\n");
  printf("%c player wins.", cc);
  return 1;
}

int Humanmoves(char board[26][26], int n, char cc, char hc) {
  char row, col;
  printf("Enter move for colour %c (RowCol): ", hc);
  scanf(" %c%c", &row, &col);
  return checkformove(board, n, row - 'a', col - 'a', hc, cc);
}

void computerMoves(char board[26][26], int n, char cc) {
  int dr, dc;
  int count = 0;
  int imax = 0;
  int jmax = 0;
  int scoremax = 0;

  int tempboard[26][26];

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U') {
        for (dr = -1; dr <= 1; dr++) {
          for (dc = -1; dc <= 1; dc++) {
            if ((dr != 0 || dc != 0) &&
                checkLegalInDirection(board, n, row, col, cc, dr, dc)) {
              int i = 1;
              int max = 0;
              while ((positionInBounds(n, row + (dr * i), col + (dc * i))) &&
                     board[row + (dr * i)][col + (dc * i)] != cc) {
                i++;
                max++;
              }
              count += max;
            }
          }
        }
      }
      tempboard[row][col] = count;
      count = 0;
    }
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (tempboard[row][col] > scoremax) {
        scoremax = tempboard[row][col];
        imax = row;
        jmax = col;
      }
    }
  }

  for (dr = -1; dr <= 1; dr++) {
    for (dc = -1; dc <= 1; dc++) {
      if (checkLegalInDirection(board, n, imax, jmax, cc, dr, dc)) {
        board[imax][jmax] = cc;
        int i = 1;
        while (board[imax + (dr * i)][jmax + (dc * i)] != cc) {
          board[imax + (dr * i)][jmax + (dc * i)] = cc;
          i++;
        }
      }
    }
  }

  printf("Computer places %c at %c%c.\n", cc, imax + 97, jmax + 97);

  printBoard(board, n);
}

#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

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
          printf("%c player has no valid move.\n", hc);
        }
      } else if (nextmove == z) {
        nextmove = hc;
        if (validMovesCount != 0) {
          computerMoves(board, n, z);
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
          printf("%c player has no valid move.\n", z);
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

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************
