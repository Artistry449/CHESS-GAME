#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 8
// declaring main board
char mainBoard[BOARD_SIZE][BOARD_SIZE];
// declaring white and dark board
char whiteBoard[BOARD_SIZE][BOARD_SIZE];
char darkBoard[BOARD_SIZE][BOARD_SIZE];
// variables
unsigned short moveCounterWhite = 0, moveCounterDark = 0;
char light_square = ' ';
char dark_square = ' ';
char wPawn = 'p';
char wKnight = 'k';
char dPawn = 'P';
char dKnight = 'K';
char possibleMove = 'X';
char drawKey = 'D';
int whitePiece = 10;
int darkPiece = 10;
// declaring functions:

void primeBoard();  // sets prime locations of pieces
int makeMove(char x, int y, char piece, char new_x_axis, int new_y_axis, int side); // makes a move by using user's x,y inputs
void DrawBoard(char data1[BOARD_SIZE][BOARD_SIZE]); // Draws board by changes
int showPossibleMoves(char piece, char x, int y); // show possible moves of user's input
void clearX(); // clears every 'X' after showPossibleMoves()

int main(){
    // 4 - white, 5-dark
    char piece, old_x_axis, new_x_axis, drawAnswer;
    int old_y_axis, new_y_axis, result;
    printf("\n\t ~~~CHESS GAME~~~\n");

    printf("\nk - WHITE KNIGHT   p - WHITE PAWN\nK - DARK KNIGHT    P - DARK PAWN\nX - possible moves\n\n");
    printf("insert D key to piece in order to DRAW request\n");
    printf("\t     WHITE SIDE\n");
    primeBoard();
    DrawBoard(mainBoard);
    printf("\t     DARK SIDE\n\n\n");

    while (darkPiece > 0 && whitePiece > 0)
    {
    whiteGO:
        // WHITE TURN
        printf("\n\t\t  ---WHITE TURN---\n");
        printf("Please input what piece you want to move(for example p e 2)\n");
        printf("piece: ");
        scanf(" %c", &piece);
        if (piece == drawKey){
            printf("\nWHITE SIDE WANTS TO DRAW. IF YOU WANT TO DRAW, PRESS D, IF NOT, PRESS N\n");
            scanf(" %c", &drawAnswer);
            if (drawAnswer == drawKey){
                printf("\nGAME HAS ENDED BY DRAW");
                break;
            }
            else if (drawAnswer == 'N'){
                goto whiteGO;
            }
        }
        printf("key: ");
        scanf(" %c", &old_x_axis);
        printf("key: ");
        scanf(" %d", &old_y_axis);

        if (showPossibleMoves(piece, old_x_axis, old_y_axis) == 1){
            DrawBoard(mainBoard);
            clearX();
        }
        else if (showPossibleMoves(piece, old_x_axis, old_y_axis) == 0){
            clearX();
            goto whiteGO;
        }
        printf("Please input where to move(for example e 4)\n");
        printf("key: ");
        scanf(" %c", &new_x_axis);
        printf("key: ");
        scanf(" %d", &new_y_axis);
        if (makeMove(new_x_axis, new_y_axis - 1, piece, old_x_axis, old_y_axis - 1, 4) == 1){
            DrawBoard(mainBoard);
        }
        else{
            goto whiteGO;
        }
        moveCounterWhite += 1;
        if (darkPiece == 0){
            printf("\n\nWHITE WINS!");
            break;
        }
        system("clear");
        DrawBoard(mainBoard);
    darkGO:
        // DARK TURN

        printf("\n\t\t  ---DARK TURN---\n");
        printf("Please input what piece you want to move(for example P e 7)\n");
        printf("piece: ");
        scanf(" %c", &piece);
        if (piece == drawKey){
            printf("\nDARK SIDE WANTS TO DRAW. IF YOU WANT TO DRAW, PRESS D, IF NOT, PRESS N\n");
            scanf(" %c", &drawAnswer);
            if (drawAnswer == drawKey)
            {
                printf("\nGAME HAS ENDED BY DRAW");
                break;
            }
            else if (drawAnswer == 'N')
            {
                goto darkGO;
            }
        }
        printf("key: ");
        scanf(" %c", &old_x_axis);
        printf("key: ");
        scanf(" %d", &old_y_axis);
        if (showPossibleMoves(piece, old_x_axis, old_y_axis) == 1){
            DrawBoard(mainBoard);
            clearX();
        }
        else if (showPossibleMoves(piece, old_x_axis, old_y_axis) == 0){
            goto darkGO;
        }
        printf("Please input where to move(for example e 5)\n");
        printf("key: ");
        scanf(" %c", &new_x_axis);
        printf("key: ");
        scanf(" %d", &new_y_axis);
        if (makeMove(new_x_axis, new_y_axis - 1, piece, old_x_axis, old_y_axis - 1, 5) == 1){
            DrawBoard(mainBoard);
        }
        else{
            goto darkGO;
        }
        moveCounterDark += 1;

        if (whitePiece == 0){
            printf("\n\nDARK WINS!");
            break;
        }
        system("clear");
        DrawBoard(mainBoard);
    }

    printf("\n\nTOTAL MOVES: %d", moveCounterWhite + moveCounterDark);
    printf("\n\nWHITE TOTAL MOVES: %d", moveCounterWhite);
    printf("\n\nDARK TOTAL MOVES: %d", moveCounterDark);
}
void primeBoard()
{
    // Board prime position
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if ((i + j) % 2 == 0)
                mainBoard[i][j] = dark_square;
            else
                mainBoard[i][j] = light_square;
            if (i == 1)
                mainBoard[i][j] = wPawn;
            whiteBoard[i][j] = wPawn;
            if (i == 6)
                mainBoard[i][j] = dPawn;
            darkBoard[i][j] = dPawn;
        }
    }
    // Knight prime position
    mainBoard[0][1] = wKnight;
    mainBoard[0][6] = wKnight;
    mainBoard[7][1] = dKnight;
    mainBoard[7][6] = dKnight;

    whiteBoard[0][1] = wKnight;
    whiteBoard[0][6] = wKnight;
    darkBoard[7][1] = dKnight;
    darkBoard[7][6] = dKnight;
}
void DrawBoard(char data1[BOARD_SIZE][BOARD_SIZE]){
    int i, iX, iY;
    for (i = 0; i < BOARD_SIZE; i++){
        if (i == 0)
            printf("    %c  ", 97 + i);
        else
            printf(" %c  ", 97 + i);
    }
    printf("\n");
    for (i = 0; i < BOARD_SIZE; i++){
        if (i == 0)
            printf("  +---+");
        else
            printf("---+");
    }
    printf("\n");
    for (iY = 0; iY < BOARD_SIZE; iY++){
        for (iX = 0; iX < BOARD_SIZE; iX++){
            if (iX == 0)
                printf(" %d| %c |", iY + 1, data1[iY][iX]);
            else if (iX > 0 && iX < 20)
                printf(" %c |", data1[iY][iX]);
        }
        printf("\n");
        for (i = 0; i < BOARD_SIZE; i++){
            if (i == 0)
                printf("  +---+");
            else
                printf("---+");
        }
        printf("\n");
    }
}
int makeMove(char new_x_axis, int new_y_axis, char piece, char x, int y, int side)
{
    char temp;
    // Convert characters to integer coordinates
    x = x - 'a';
    new_x_axis = new_x_axis - 'a';

    //  Update the board
    if (x < BOARD_SIZE && y < BOARD_SIZE && x >= 0 && y >= 0 &&
        new_x_axis < BOARD_SIZE && new_y_axis < BOARD_SIZE && new_x_axis >= 0 && new_y_axis >= 0)
    {
        // Checking if it is turn of WHITE
        if (side == 4){
            // for Pawn
            if (piece == wPawn && mainBoard[y][x] == wPawn){
                // Checking if it is first move and can move pawn more than 2 blocks
                if (mainBoard[1][x] == wPawn && new_y_axis - y == 2){
                    whiteBoard[new_y_axis][new_x_axis] = mainBoard[y][x];
                    mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                }
                // Checking if moveCounter!=0 and check if pawn can move 1 block
                else if (new_x_axis == x && new_y_axis - y == 1){
                    if (mainBoard[new_y_axis][new_x_axis] != dPawn && mainBoard[new_y_axis][new_x_axis] != dKnight)
                    {
                        if (new_y_axis == 7){
                            whiteBoard[new_y_axis][new_x_axis] = wKnight;
                            mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                        }
                        else{
                            whiteBoard[new_y_axis][new_x_axis] = mainBoard[y][x];
                            mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                        }
                    }
                    else{
                        printf("\nInvalid input!\n");
                        return 0;
                    }
                }
                // Checking if a pawn can eat any other enemy piece
                else if ((new_x_axis == x + 1 || new_x_axis == x - 1) && (new_y_axis == y + 1) && (mainBoard[new_y_axis][new_x_axis] == dKnight || mainBoard[new_y_axis][new_x_axis] == dPawn)){
                    if (new_y_axis == 7){
                        darkPiece -= 1;
                        whiteBoard[new_y_axis][new_x_axis] = wKnight;
                        mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                    }
                    else{
                        darkPiece -= 1;
                        whiteBoard[new_y_axis][new_x_axis] = whiteBoard[y][x];
                        mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                    }
                }
                else{
                    printf("Invalid move!");
                    return 0;
                }
            }
            // for Knight
            else if (piece == wKnight && mainBoard[y][x] == wKnight)
            {
                // printf("\n\nAAAA");
                // Checking if it is a valid move of Knight
                if ((((new_x_axis == (x - 1)) || (new_x_axis == (x + 1))) && ((new_y_axis == (y - 2)) || (new_y_axis == (y + 2)))) || (((new_x_axis == (x - 2)) || (new_x_axis == (x + 2))) && ((new_y_axis == (y - 1)) || (new_y_axis == (y + 1))))){
                    // Checking if a knight can eat any other enemy pieces
                    if ((mainBoard[new_y_axis][new_x_axis] == dPawn || mainBoard[new_y_axis][new_x_axis] == dKnight)){
                        whiteBoard[new_y_axis][new_x_axis] = whiteBoard[y][x];
                        mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                        darkPiece = darkPiece - 1;
                        // printf("\n\nAAAA");
                    }
                    // Checking if the knight can move to new x,y
                    else if ((mainBoard[new_y_axis][new_y_axis] == light_square) || (mainBoard[new_y_axis][new_x_axis] == dark_square)){
                        whiteBoard[new_y_axis][new_x_axis] = wKnight;
                        mainBoard[new_y_axis][new_x_axis] = whiteBoard[new_y_axis][new_x_axis];
                    }
                    else if ((mainBoard[new_y_axis][new_x_axis] == wPawn || mainBoard[new_y_axis][new_x_axis] == wKnight)){
                        printf("\nInvalid move!\n");
                        return 0;
                    }
                }
                else{
                    printf("\nInvalid move!\n");
                    return 0;
                }
            }
            else{
                printf("Invalid piece! Please choose what piece you want to move");
                return 0;
            }
        }

        // Checking if it is turn of black
        else if (side == 5){
            // for Pawn
            if (piece == dPawn && mainBoard[y][x] == dPawn){
                // Checking if it is first move and can move pawn more than 2 blocks
                if (moveCounterDark == 0 && y - new_y_axis == 2){
                    darkBoard[new_y_axis][new_x_axis] = mainBoard[y][x];
                    mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                }
                // Checking if moveCounter!=0 and check if pawn can move 1 block
                else if (new_x_axis == x && y - new_y_axis == 1){
                    if (mainBoard[new_y_axis][new_x_axis] != dPawn && mainBoard[new_y_axis][new_x_axis] != dKnight && mainBoard[new_y_axis][new_x_axis] != wPawn && mainBoard[new_y_axis][new_x_axis] != wKnight){
                        if (new_y_axis == 7){
                            darkBoard[new_y_axis][new_x_axis] = dKnight;
                            mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                        }
                        else{
                            darkBoard[new_y_axis][new_x_axis] = mainBoard[y][x];
                            mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                        }
                    }
                    else{
                        printf("\nInvalid input!\n");
                        return 0;
                    }
                }
                // Checking if a pawn can eat any other enemy piece
                else if ((new_x_axis == x + 1 || new_x_axis == x - 1) && new_y_axis == y - 1 && (mainBoard[new_y_axis][new_x_axis] == wKnight || mainBoard[new_y_axis][new_x_axis] == wPawn)){
                    if (new_y_axis == 0){
                        whitePiece -= 1;
                        darkBoard[new_y_axis][new_x_axis] = dKnight;
                        mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                    }
                    else{
                        whitePiece -= 1;
                        darkBoard[new_y_axis][new_x_axis] = darkBoard[y][x];
                        mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                    }
                }
                else{
                    printf("Invalid move!");
                    return 0;
                }
            }
            // for Knight
            else if (piece == dKnight && mainBoard[y][x] == dKnight){
                // Checking if it is a valid move of Knight
                if ((((new_x_axis == (x - 1)) || (new_x_axis == (x + 1))) && ((new_y_axis == (y - 2)) || (new_y_axis == (y + 2)))) || (((new_x_axis == (x - 2)) || (new_x_axis == (x + 2))) && ((new_y_axis == (y - 1)) || (new_y_axis == (y + 1))))){
                    // Checking if a knight can eat any other enemy pieces
                    if ((mainBoard[new_y_axis][new_x_axis] == wPawn || mainBoard[new_y_axis][new_x_axis] == wKnight)){
                        darkBoard[new_y_axis][new_x_axis] = darkBoard[y][x];
                        mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                        darkPiece = darkPiece - 1;
                    }
                    // Checking if the knight can move to new x,y
                    else if ((mainBoard[new_y_axis][new_y_axis] == light_square) || (mainBoard[new_y_axis][new_x_axis] == dark_square)){
                        darkBoard[new_y_axis][new_x_axis] = dKnight;
                        mainBoard[new_y_axis][new_x_axis] = darkBoard[new_y_axis][new_x_axis];
                    }
                    else if ((mainBoard[new_y_axis][new_x_axis] == dPawn || mainBoard[new_y_axis][new_x_axis] == dKnight)){
                        printf("\nInvalid move!\n");
                        return 0;
                    }
                }
                else{
                    printf("\nInvalid move!\n");
                    return 0;
                }
            }
            else{
                printf("Invalid piece! Please choose what piece you want to move\n");
                return 0;
            }
        }
        if ((x + y) % 2 == 0)
            mainBoard[y][x] = dark_square;
        else
            mainBoard[y][x] = light_square;
        whiteBoard[y][x] = mainBoard[y][x];
        darkBoard[y][x] = mainBoard[y][x];
    }
    else{
        printf("\nInvalid coordinates!\n");
        return 0;
    }
    return 1;
}
int showPossibleMoves(char piece, char x, int y){
    x = x - 'a';
    y = y - 1;
    // FOR WHITE PAWN
    if (piece == wPawn && mainBoard[y][x] == wPawn){
        // [1 block] showing possible moves of pawn
        if ((mainBoard[y + 1][x] == light_square) || (mainBoard[y + 1][x] == dark_square)){
            mainBoard[y + 1][x] = possibleMove;
            // [2 block]
            if ((y == 1 && ((mainBoard[y + 2][x] == light_square) || (mainBoard[y + 2][x] == dark_square)))){
                mainBoard[y + 2][x] = possibleMove;
            }
        }
    }
    // FOR DARK PAWN
    else if (piece == dPawn && mainBoard[y][x] == dPawn){
        // [1 block] showing possible moves of pawn
        if ((mainBoard[y - 1][x] == light_square) || (mainBoard[y - 1][x] == dark_square)){
            mainBoard[y - 1][x] = possibleMove;
            // [2 block]
            if ((y == 6 && ((mainBoard[y - 2][x] == light_square) || (mainBoard[y - 2][x] == dark_square)))){
                mainBoard[y - 2][x] = possibleMove;
            }
        }
    }
    // FOR BOTH KNIGHT
    else if (piece == wKnight || piece == dKnight){
        if (mainBoard[y][x] == wKnight || mainBoard[y][x] == dKnight){
            // first 4 type
            if ((mainBoard[y + 2][x + 1] == light_square || mainBoard[y + 2][x + 1] == dark_square) && y + 2 < BOARD_SIZE && x + 1 < BOARD_SIZE)
                mainBoard[y + 2][x + 1] = possibleMove;
            if ((mainBoard[y - 2][x + 1] == light_square || mainBoard[y + 2][x - 1] == dark_square) &&
                y - 2 >= 0 && x + 1 < BOARD_SIZE)
                mainBoard[y - 2][x + 1] = possibleMove;
            if ((mainBoard[y + 2][x - 1] == light_square || mainBoard[y + 2][x - 1] == dark_square) && y + 2 < BOARD_SIZE && x - 1 >= 0)
                mainBoard[y + 2][x - 1] = possibleMove;
            if ((mainBoard[y - 2][x - 1] == light_square || mainBoard[y - 2][x - 1] == dark_square) && y - 2 >= 0 && x - 1 >= 0)
                mainBoard[y - 2][x - 1] = possibleMove;
            // Second 4 type
            if ((mainBoard[y + 1][x - 2] == light_square || mainBoard[y + 1][x - 2] == dark_square) && y + 1 < BOARD_SIZE && x - 2 >= 0)
                mainBoard[y + 1][x - 2] = possibleMove;
            if ((mainBoard[y + 1][x + 2] == light_square || mainBoard[y + 1][x + 2] == dark_square) && y + 1 < BOARD_SIZE && x + 2 < BOARD_SIZE)
                mainBoard[y + 1][x + 2] = possibleMove;
            if ((mainBoard[y - 1][x - 2] == light_square || mainBoard[y - 1][x - 2] == dark_square) && y - 1 >= 0 && x - 2 >= 0)
                mainBoard[y - 1][x - 2] = possibleMove;
            if ((mainBoard[y - 1][x + 2] == light_square || mainBoard[y - 1][x + 2] == dark_square) && y - 1 >= 0 && x + 2 < BOARD_SIZE)
                mainBoard[y - 1][x + 2] = possibleMove;
        }
    }
    else{
        return 0;
    }
    return 1;
}
void clearX()
{
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++)
            if (mainBoard[i][j] == possibleMove){
                if ((i + j) % 2 == 0)
                    mainBoard[i][j] = light_square;
                else
                    mainBoard[i][j] = dark_square;
            }
    }
}
