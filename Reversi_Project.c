//
// Author: Sankalp Aggarwal
//

// #include "reversi.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);

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

int main(void) {
  printf("Enter the board dimension: ");
  char board[26][26];
  int n = 0;

  scanf("%d", &n);
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
  printf("Enter board configuration:\n");
  char ch1, ch2, ch3;
  scanf(" %c%c%c", &ch1, &ch2, &ch3);
  while (ch1 != '!' && ch2 != '!' && ch3 != '!') {
    board[ch2 - 'a'][ch3 - 'a'] = ch1;
    scanf(" %c%c%c", &ch1, &ch2, &ch3);
  }
  printBoard(board, n);

  printf("Available moves for W:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'U') {
        bool chk = true;
        for (int dr = -1; dr <= 1; dr++) {
          for (int dc = -1; dc <= 1; dc++) {
            if (dr != 0 || dc != 0) {
              if (checkLegalInDirection(board, n, i, j, 'W', dr, dc)) {
                printf("%c%c\n", 97 + i, 97 + j);

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
  printf("Available moves for B:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'U') {
        bool chk = true;
        for (int dr = -1; dr <= 1; dr++) {
          for (int dc = -1; dc <= 1; dc++) {
            if (dr != 0 || dc != 0) {
              if (checkLegalInDirection(board, n, i, j, 'B', dr, dc)) {
                printf("%c%c\n", 97 + i, 97 + j);

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

  printf("Enter a move:\n");
  char c1, c2, c3;
  scanf(" %c%c%c", &c1, &c2, &c3);
  bool chk1 = false;
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      if ((dr != 0 || dc != 0) &&
          checkLegalInDirection(board, n, c2 - 'a', c3 - 'a', c1, dr, dc)) {
        chk1 = true;

        board[c2 - 'a'][c3 - 'a'] = c1;
        for (int row = c2 - 'a' + dr, col = c3 - 'a' + dc;
             board[row][col] != c1; row += dr, col += dc) {
          board[row][col] = c1;
        }
      }
    }
  }

  if (chk1) {
    printf("Valid move.\n");

    printBoard(board, n);
  } else {
    printf("Invalid move.\n");
    printBoard(board, n);
  }
  return 0;
}
