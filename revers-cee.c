/*
Lab 8 further develops the code from Lab 7 for the Reversi Game
In part 1 I will be implementing a program that plays the Reversi game against a
human opponent using a specified algorithm for computer moves.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const char BLACK = '#';
const char WHITE = 'O';
const char BLANK = ' ';

// The following function statically initializes the 2-D game board for the up
// to 26 columns and rows
void initializeBoard(char board[][26], int n) {
  int i, j;

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= n - 1; j++) {
      board[i][j] = BLANK;
      board[n / 2 - 1][n / 2 - 1] = WHITE;
      board[n / 2][n / 2 - 1] = BLACK;
      board[n / 2 - 1][n / 2] = BLACK;
      board[n / 2][n / 2] = WHITE;
    }
  }
}

// The following function prints the game board along with the axis labeled a-z
// depending on the size of the of the dimensions
void printBoard(char board[][26], int n) {
  // Print the column labels
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("  %c ", 'a' + i);
  }
  printf("\n  ");
  for (int j = 0; j < n; j++) {
    printf("+---");
  }
  printf("+\n");

  // Print the rows of the board
  for (int i = 0; i < n; i++) {
    printf("%c ", 'a' + i);
    for (int j = 0; j < n; j++) {
      printf("| %c ", board[i][j]);
    }
    printf("|\n");
    printf("  ");
    for (int j = 0; j < n; j++) {
      printf("+---");
    }
    printf("+\n");
  }
}

void printBoards(char board1[][26], char board2[][26], int n) {
  // Print the column labels for board1
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("  %c ", 'a' + i);
  }

  // Add spacing between the two boards
  printf("      ");

  // Print the column labels for board2
  for (int i = 0; i < n; i++) {
    printf("  %c ", 'a' + i);
  }
  printf("\n");

  // Print the separator line between the column labels and board cells
  printf("  ");
  for (int j = 0; j < n; j++) {
    printf("+---");
  }

  // Add spacing between the two boards
  printf("      ");

  for (int j = 0; j < n; j++) {
    printf("+---");
  }
  printf("+\n");

  // Print the rows of the two boards side by side
  for (int i = 0; i < n; i++) {
    printf("%c ", 'a' + i);
    for (int j = 0; j < n; j++) {
      printf("| %c ", board1[i][j]);
    }

    // Add spacing between the two boards
    printf("|   %c ", 'a' + i);

    for (int j = 0; j < n; j++) {
      printf("| %c ", board2[i][j]);
    }
    printf("|\n");

    // Print the separator line between each row of the boards
    printf("  ");
    for (int j = 0; j < n; j++) {
      printf("+---");
    }

    // Add spacing between the two boards
    printf("|     ");

    for (int j = 0; j < n; j++) {
      printf("+---");
    }
    printf("+\n");
  }
}

// This function checks if all positions have been filled
bool gameOver(char board[][26], int n, bool *humanMadeInvalid) {
  int row, col;

  if (*humanMadeInvalid == true) {
    return true;
  }

  for (row = 0; row <= n - 1; row++) {
    for (col = 0; col <= n - 1; col++) {
      if (board[row][col] == BLANK) {
        return false;
      }
    }
  }
  return true;
}

// This boolean functions checks whether the specified row and col lie within
// the board dimensions
bool positionInBounds(int n, int row, int col) {
  return (((row >= 0) && (row <= n - 1)) && ((col >= 0) && (col <= n - 1)));
}

// This boolean function checks whether the row and col are in a legal position
// for a tile of colour by searching in the direction specified by deltaRow and
// deltaCol
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  int i = 1;
  char opponentColor;

  if (colour == WHITE) {
    opponentColor = BLACK;
  }

  else {
    opponentColor = WHITE;
  }

  // immediate surroundings
  while ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) &&
         ((board[row + (deltaRow * i)][col + (deltaCol * i)]) != (colour)) &&
         ((board[row + (deltaRow * i)][col + (deltaCol * i)]) != (BLANK))) {
    i++;
    if ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) &&
        (board[row + (deltaRow * i)][col + (deltaCol * i)] == colour)) {
      return true;
    }

    else {
      if ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) &&
          (board[row + (deltaRow * i)][col + (deltaCol * i)] ==
           opponentColor)) {
        continue;
      }

      else {
        if ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i)) ==
             false)) {
          return false;
        }

        else {
          if (board[row + (deltaRow * i)][col + (deltaCol * i)] == colour) {
            return true;
          }

          else {
            return false;
          }
        }
      }
    }
  }
  return false;
}

// This function is responsible for flipping the tiles for the game
void flipTiles(char board[][26], int n, int row, int col, char colour,
               int deltaRow, int deltaCol) {
  board[row][col] = colour;
  int i = 1;
  while (board[row + (deltaRow * i)][col + (deltaCol * i)] != colour) {
    board[row + (deltaRow * i)][col + (deltaCol * i)] = colour;
    i++;
  }
}

bool movesPossibleForPlayer(char board[][26], int n, char currentPlayer) {
  int row, col, deltaRow, deltaCol;

  for (row = 0; row <= n - 1; row++) {
    for (col = 0; col <= n - 1; col++) {
      if (board[row][col] == BLANK) {
        for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) {
            }

            else {
              if (checkLegalInDirection(board, n, row, col, currentPlayer,
                                        deltaRow, deltaCol)) {
                return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}

// This functions checks for valid input
bool checkForValidInput(char board[][26], int n, char colour,
                        char computerColour, int row, int col,
                        bool *humanMadeInvalid) {
  int deltaRow, deltaCol;

  if ((positionInBounds(n, row, col)) && (board[row][col] == BLANK)) {
    for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
      for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
        if ((deltaRow != 0 || deltaCol != 0) &&
            checkLegalInDirection(board, n, row, col, colour, deltaRow,
                                  deltaCol)) {
          flipTiles(board, n, row, col, colour, deltaRow, deltaCol);
          // printBoard(board, n);
          return true;
        }
      }
    }
  }

  printf("Invalid move.\n");
//   printf("%c player wins.", computerColour);
//  *humanMadeInvalid = true;
//   gameOver(board, n, humanMadeInvalid);
  return false;
}

int numberOfFlippedTiles(char board[][26], int n, int row, int col, char colour,
                         int deltaRow, int deltaCol) {
  int i = 1;
  int max = 0;
  while ((positionInBounds(n, row + (deltaRow * i), col + (deltaCol * i))) &&
         board[row + (deltaRow * i)][col + (deltaCol * i)] != colour) {
    i++;
    max++;
  }
  return max;
}

void copyBoard(char board1[][26], char board2[][26], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board2[i][j] = board1[i][j];
    }
  }
}

void makeBestMove(char board[][26], int n, char computerColour) {
  int deltaRow, deltaCol;
  int imax = 0;
  int jmax = 0;
  int scoremax = 0;

  int cellScore[26][26];

  // Store orignal board for printing later
  char originalBoard[26][26];
  copyBoard(board, originalBoard, 26);

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      int count = 0;
      if ((positionInBounds(n, row, col)) && (board[row][col] == BLANK)) {
        for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if ((deltaRow != 0 || deltaCol != 0) &&
                checkLegalInDirection(board, n, row, col, computerColour,
                                      deltaRow, deltaCol)) {
              count += numberOfFlippedTiles(board, n, row, col, computerColour,
                                            deltaRow, deltaCol);
            }
          }
        }
      }
      cellScore[row][col] = count;
    }
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (cellScore[row][col] > scoremax) {
        scoremax = cellScore[row][col];
        imax = row;
        jmax = col;
      }
    }
  }

  for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (checkLegalInDirection(board, n, imax, jmax, computerColour, deltaRow,
                                deltaCol)) {
        flipTiles(board, n, imax, jmax, computerColour, deltaRow, deltaCol);
      }
    }
  }

  printf("Computer places %c at %c%c.\n", computerColour, imax + 97, jmax + 97);

  printBoards(originalBoard, board, n);
}

void playHumanPlayer(char board[][26], int n, char currentPlayer,
                     char computerColour, char humanColour,
                     bool *humanMadeInvalid) {
  char row, col;

  if (movesPossibleForPlayer(board, n, humanColour)) {

    bool validInput=false;
    do {
        printf("Enter move for colour %c (RowCol): ", humanColour);
        scanf(" %c%c", &row, &col);
        validInput=checkForValidInput(board, n, currentPlayer, computerColour, row - 'a',
                        col - 'a', humanMadeInvalid);
        printf("\n\n");
    } while(validInput==false);
    return;
  }

  else {
    printf("%c player has no valid move.\n", humanColour);
    return;
  }
}

void playComputerPlayer(char board[][26], int n, char currentPlayer,
                        char computerColour, char humanColour) {
  if (movesPossibleForPlayer(board, n, computerColour)) {
    makeBestMove(board, n, computerColour);
  }

  else {
    printf("%c player has no valid move.\n", computerColour);
  }
}

// This function determines who's turn it is and plays the game accordingly
char takeTurn(char board[][26], int n, char currentPlayer,
                     char computerColour, char humanColour,
                     bool *humanMadeInvalid) {
  if (currentPlayer == humanColour) {
    playHumanPlayer(board, n, currentPlayer, computerColour, humanColour,
                    humanMadeInvalid);
    currentPlayer = computerColour;
  }

  else if (currentPlayer == computerColour) {
    playComputerPlayer(board, n, currentPlayer, computerColour, humanColour);
    currentPlayer = humanColour;
  }
  return currentPlayer;
}

int main(void) {
  int n;
  char board[26][26];
  char currentPlayer = BLACK;
  char computerColour, humanColour, inputColour;
  bool humanMadeInvalid = false;

  printf("Enter the board dimension: ");
  scanf(" %d", &n);

  printf("Computer plays (B/W): ");
  scanf(" %c", &inputColour);

  initializeBoard(board, n);
  printBoard(board, n);

  if (inputColour == 'w' || inputColour == 'W') {
    computerColour = WHITE;
    humanColour = BLACK;
  } else {
    computerColour = BLACK;
    humanColour = WHITE;
  }

  while (gameOver(board, n, &humanMadeInvalid) == false) {
    currentPlayer = takeTurn(board, n, currentPlayer, computerColour,
                                    humanColour, &humanMadeInvalid);
  }

  if (humanMadeInvalid == false) {
    int row, col;
    int compCount = 0;
    int humanCount = 0;
    for (row = 0; row <= n - 1; row++) {
      for (col = 0; col <= n - 1; col++) {
        if (board[row][col] == computerColour) {
          compCount++;
        }

        else if (board[row][col] == humanColour) {
          humanCount++;
        }
      }
    }

    if (compCount > humanCount) {
      printf("%c player wins.", computerColour);
      return 0;
    }

    else if (humanCount > compCount) {
      printf("%c player wins.", humanColour);
      return 0;
    }

    else {
      printf("Draw!");
      return 0;
    }
  }
  return 0;
}
