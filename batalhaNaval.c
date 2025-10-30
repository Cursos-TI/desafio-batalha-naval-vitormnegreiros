#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 10


void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("Tabuleiro (valores):\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0=Água, 3=Navio, 5=Área afetada\n\n");
}


void build_cone(int size, int mat[][size]) {
    int center = size / 2;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            mat[r][c] = 0;
        }
    }
    for (int r = 0; r < size; r++) {
        int left = center - r;
        int right = center + r;
        for (int c = 0; c < size; c++) {
            if (c >= 0 && c < size && left >= 0 && right < size) {
                if (c >= left && c <= right) mat[r][c] = 1;
            } else {
                if (c >= 0 && c < size && c >= (left < 0 ? 0 : left) && c <= (right >= size ? size - 1 : right)) {
                    mat[r][c] = 1;
                }
            }
        }
    }
}


void build_cross(int size, int mat[][size]) {
    int center = size / 2;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            mat[r][c] = 0;
        }
    }
    for (int i = 0; i < size; i++) {
        mat[center][i] = 1; 
        mat[i][center] = 1;
    }
}


void build_octahedron(int size, int mat[][size]) {
    int center = size / 2;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            int dist = (r > center ? r - center : center - r) + (c > center ? c - center : center - c);
            if (dist <= center)
                mat[r][c] = 1;
            else
                mat[r][c] = 0;
        }
    }
}


void overlay_skill(int board[BOARD_SIZE][BOARD_SIZE], int skill_size, int skill[][skill_size],
                   int origin_row, int origin_col, int anchor) {
    int center = skill_size / 2;
    for (int r = 0; r < skill_size; r++) {
        for (int c = 0; c < skill_size; c++) {
            if (skill[r][c] != 1) continue;

            int board_r, board_c;
            if (anchor == 0) {
                
                board_r = origin_row + r;
                board_c = origin_col + (c - center);
            } else {
               
                board_r = origin_row + (r - center);
                board_c = origin_col + (c - center);
            }

            if (board_r >= 0 && board_r < BOARD_SIZE && board_c >= 0 && board_c < BOARD_SIZE) {
                if (board[board_r][board_c] != 3) { 
                    board[board_r][board_c] = 5;
                }
            }
        }
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 0;

  
    board[2][3] = 3;
    board[2][4] = 3;
    board[2][5] = 3;
    board[6][1] = 3;
    board[7][1] = 3;
    board[4][8] = 3;

  
    const int cone_size = 7;        
    const int cross_size = 5;      
    const int octa_size = 7;     

    int cone[cone_size][cone_size];
    int cross[cross_size][cross_size];
    int octa[octa_size][octa_size];

    build_cone(cone_size, cone);         
    build_cross(cross_size, cross);       
    build_octahedron(octa_size, octa); 

    int cone_origin_r = 0, cone_origin_c = 5;     
    int cross_origin_r = 5, cross_origin_c = 5; 
    int octa_origin_r = 8, octa_origin_c = 2;   

    overlay_skill(board, cone_size, cone, cone_origin_r, cone_origin_c, 0);
    overlay_skill(board, cross_size, cross, cross_origin_r, cross_origin_c, 1);
    overlay_skill(board, octa_size, octa, octa_origin_r, octa_origin_c, 1); 

    print_board(board);

    
    printf("Matriz Cone (1=afetado):\n");
    for (int r = 0; r < cone_size; r++) {
        for (int c = 0; c < cone_size; c++) printf("%d ", cone[r][c]);
        printf("\n");
    }

    printf("\nMatriz Cruz (1=afetado):\n");
    for (int r = 0; r < cross_size; r++) {
        for (int c = 0; c < cross_size; c++) printf("%d ", cross[r][c]);
        printf("\n");
    }

    printf("\nMatriz Octaedro (1=afetado):\n");
    for (int r = 0; r < octa_size; r++) {
        for (int c = 0; c < octa_size; c++) printf("%d ", octa[r][c]);
        printf("\n");
    }

    return 0;
}
