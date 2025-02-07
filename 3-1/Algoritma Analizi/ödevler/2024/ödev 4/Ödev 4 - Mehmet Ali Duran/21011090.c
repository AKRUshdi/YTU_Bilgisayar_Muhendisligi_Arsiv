#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int getNumberOfRowAndColumn();
void bruteforce(int **board, int queens, int n, int *solutionCount);
void optimized_1(int** matrix, int roww, int N, int* solutionCount);
void optimized_2(int** matrix, int roww, int N, int* solutionCount);
void backtracking(int** board, int row, int n, int* solutionCount);
void allMethods(int** matrix, int N, int* solutionCount);
void printTable(int** matrix, int N);
void resetTable(int** matrix, int N);
int** createTable(int N);
void destroyTable(int** matrix, int N);
void executeAndMeasureTime(void (*function)(int**, int, int, int*), int** matrix, int row, int N, int* solutionCount);



int main(){
	
	int N, choice, i, j, solutionCount = 0;
	N = getNumberOfRowAndColumn();
	int** matrix = createTable(N);
	
	do{
		printf("1 - Solve with BRUTE FORCE\n");
		printf("2 - Solve with OPTIMIZED-1\n");
		printf("3 - Solve with OPTIMIZED-2\n");
		printf("4 - Solve with BACKTRACKING\n");
		printf("5 - Solve with ALL METHODS\n");	
		printf("6 - Enter new table size\n");
		printf("7 - Quit  ");
		resetTable(matrix, N);
		scanf("%d", &choice);
		printf("\n\n");
		//system("cls");
		switch(choice){
			case 1:
				solutionCount = 0;
				executeAndMeasureTime(bruteforce, matrix, 0, N, &solutionCount);
				printf("solutionCount for bruteForce = %d\n", solutionCount);
				break;
			case 2:
				solutionCount = 0;
				executeAndMeasureTime(optimized_1, matrix, 0, N, &solutionCount);
				printf("solutionCount for optimized_1 = %d\n", solutionCount);
				break;
			case 3:
				solutionCount = 0;
				executeAndMeasureTime(optimized_2, matrix, 0, N, &solutionCount);
				printf("solutionCount for optimized_2 = %d\n", solutionCount);
				break;
			case 4:
				solutionCount = 0;
				executeAndMeasureTime(backtracking, matrix, 0, N, &solutionCount);
				printf("solutionCount for backtracking = %d\n", solutionCount);
				break;
			case 5:
				
				allMethods(matrix, N, &solutionCount);
				break;
			case 6:
				destroyTable(matrix, N);  // Mevcut tabloyu serbest b�rak
			    N = getNumberOfRowAndColumn();
			    matrix = createTable(N); // Yeni tablo olu�tur
			    printf("New table size: %d\n", N);
				break;
		}
	}while(choice!=7);

	destroyTable(matrix, N);
	return 0;
}

/**
 * @brief Kullan�c�dan NxN satran� tahtas�n�n boyutunu al�r.
 * @return Satran� tahtas�n�n boyutu (N), minimum 4 olmal�d�r.
 */
int getNumberOfRowAndColumn(){
	int N;
	
	do{
		printf("Please enter the size of table (it should be minimum 4): ");
		scanf("%d",&N);	
	}while(N < 4);
	
	return N;
}

/**
 * @brief N vezir problemini optimize edilmi� bir y�ntemle ��zer.
 *        Sadece s�tun �ak��malar�n� kontrol eder.
 * @param matrix NxN satran� tahtas�.
 * @param execute fonksiyonun uymas� icin koydum bir etkisi yok
 * @param N Satran� tahtas�n�n boyutu.
 * @param solutionCount ��z�m say�s�n� saklayan i�aret�i.
 */
void optimized_1(int** matrix, int row, int N, int* solutionCount) {
    int col, i;
    bool safe;

    if (row == N) {
        /* T�m sat�rlar doldurulduysa, ��z�m� kontrol et */
        if (isValidForBruteForce(matrix, N)) {
            (*solutionCount)++;
            printf("Solution %d:\n", *solutionCount);
            printTable(matrix, N);
        }
        return;
    }

    /* Her sat�r i�in t�m s�tunlar� dene */
    for (col = 0; col < N; col++) {
        safe = true;
        
        /* Sadece �nceki sat�rlarda ayn� s�tunda vezir var m� kontrol et */
        for (i = 0; i < row; i++) {
            if (matrix[i][col] == 1) {
                safe = false;
                break;
            }
        }

        if (safe) {
            matrix[row][col] = 1;
            optimized_1(matrix, row + 1, N, solutionCount);
            matrix[row][col] = 0;  /* backtrack */
        }
    }
}

/**
 * @brief N vezir problemini optimize edilmi� bir y�ntemle ��zer.
 *        Sadece s�tun �ak��malar�n� kontrol eder.
 * @param matrix NxN satran� tahtas�.
 * @param execute fonksiyonun uymas� icin koydum bir etkisi yok
 * @param N Satran� tahtas�n�n boyutu.
 * @param solutionCount ��z�m say�s�n� saklayan i�aret�i.
 */
void optimized_2(int** matrix, int row, int N, int* solutionCount) {
    int i, j, k, col;
    bool isValid, safe;

    if (row == N) {
        /* Sadece �apraz kontrolleri yap ��nk� sat�r ve s�tun kontrolleri zaten yap�ld� */
        isValid = true;
        for (i = 0; i < N && isValid; i++) {
            for (j = 0; j < N; j++) {
                if (matrix[i][j] == 1) {
                    /* �apraz kontroller */
                    for (k = 1; k < N; k++) {
                        /* Sol �st �apraz */
                        if (i-k >= 0 && j-k >= 0 && matrix[i-k][j-k] == 1) {
                            isValid = false;
                            break;
                        }
                        /* Sa� �st �apraz */
                        if (i-k >= 0 && j+k < N && matrix[i-k][j+k] == 1) {
                            isValid = false;
                            break;
                        }
                    }
                }
            }
        }
        
        if (isValid) {
            (*solutionCount)++;
            printf("Solution %d:\n", *solutionCount);
            printTable(matrix, N);
        }
        return;
    }

    /* Her sat�r i�in t�m s�tunlar� dene */
    for (col = 0; col < N; col++) {
        safe = true;
        
        /* Sat�r ve s�tun kontrol� */
        for (i = 0; i < row; i++) {
            if (matrix[i][col] == 1) {  /* S�tun kontrol� */
                safe = false;
                break;
            }
        }

        if (safe) {
            matrix[row][col] = 1;
            optimized_2(matrix, row + 1, N, solutionCount);
            matrix[row][col] = 0;  /* backtrack */
        }
    }
}

/**
 * @brief Backtracking y�ntemiyle vezir yerle�tirmenin g�venli olup olmad���n� kontrol eder.
 * @param board NxN satran� tahtas�.
 * @param row Vezir yerle�tirilecek sat�r.
 * @param col Vezir yerle�tirilecek s�tun.
 * @param N Satran� tahtas�n�n boyutu.
 * @return G�venli ise true, de�ilse false d�ner.
 */
bool isSafeBacktracking(int** board, int row, int col, int N) {
	int i, j;
    for (i = 0; i < row; i++) {
        if (board[i][col] == 1) return false; // Ayn� s�tun
    }
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false; // Sol �st �apraz
    }
    for (i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) return false; // Sa� �st �apraz
    }
    return true;
}

/**
 * @brief Backtracking y�ntemiyle N vezir problemine ��z�m arar.
 * @param board NxN satran� tahtas�.
 * @param row Vezir yerle�tirilecek sat�r.
 * @param N Satran� tahtas�n�n boyutu.
 * @param solutionCount ��z�m say�s�n� saklayan i�aret�i.
 */
void backtracking(int** board, int row, int N, int* solutionCount) {
	int col;
    if (row == N) {
        (*solutionCount)++;
        printf("Solution %d:\n", *solutionCount);
        printTable(board, N);
        return;
    }
    for (col = 0; col < N; col++) {
        if (isSafeBacktracking(board, row, col, N)) {
            board[row][col] = 1; // Veziri yerle�tir
            backtracking(board, row + 1, N, solutionCount);
            board[row][col] = 0; // Backtracking
        }
    }
}

/**
 * @brief Brute force y�ntemiyle tahtan�n ge�erli olup olmad���n� kontrol eder.
 * @param board NxN satran� tahtas�.
 * @param n Satran� tahtas�n�n boyutu.
 * @return Ge�erli ise 1, de�ilse 0 d�ner.
 */
int isValidForBruteForce(int **board, int n) {
    int row, col, i, j, k;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (board[row][col] == 1) {
                // Ayn� sat�rda ba�ka bir vezir var m�?
                for (k = 0; k < n; k++) {
                    if (k != col && board[row][k] == 1)
                        return 0;
                }
                // Ayn� s�tunda ba�ka bir vezir var m�?
                for (k = 0; k < n; k++) {
                    if (k != row && board[k][col] == 1)
                        return 0;
                }
                // Sol �st �apraz
                for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
                    if (board[i][j] == 1)
                        return 0;
                }
                // Sa� �st �apraz
                for (i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
                    if (board[i][j] == 1)
                        return 0;
                }
                // Sol alt �apraz
                for (i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
                    if (board[i][j] == 1)
                        return 0;
                }
                // Sa� alt �apraz
                for (i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
                    if (board[i][j] == 1)
                        return 0;
                }
            }
        }
    }
    return 1;
}

void bruteforce(int **board, int queens, int n, int *solutionCount) {
    int totalCells = n * n; // Toplam h�cre say�s�
    int totalCombinations = 1 << totalCells; // 2^(n*n) kombinasyon
	int comb, i, j, cell, row, col;
    for (comb = 0; comb < totalCombinations; comb++) {
        // Matris s�f�rla
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                board[i][j] = 0;
            }
        }

        // Kombinasyonu tahtaya yerle�tir
        int queensPlaced = 0;
        for (cell = 0; cell < totalCells; cell++) {
            if (comb & (1 << cell)) { // Bu h�creye vezir yerle�tir
                row = cell / n;
                col = cell % n;
                board[row][col] = 1;
                queensPlaced++;
            }
        }

        // E�er tam olarak n vezir yerle�tirildiyse, ge�erli mi kontrol et
        if (queensPlaced == n && isValidForBruteForce(board, n)) {
            (*solutionCount)++;
			printf("Solution %d:\n", *solutionCount);
			printTable(board, n);
        }
    }
}

/**
 * @brief Verilen t�m y�ntemleri s�rayla �al��t�r�r.
 * @param matrix NxN satran� tahtas�.
 * @param N Satran� tahtas�n�n boyutu.
 */
void allMethods(int** matrix, int N, int* solutionCount){
	
	*solutionCount = 0;
	executeAndMeasureTime(bruteforce, matrix, 0, N, solutionCount);
	printf("solutionCount for bruteForce = %d\n\n***********\n\n", *solutionCount);
	
	*solutionCount = 0;
	executeAndMeasureTime(optimized_1, matrix, 0, N, solutionCount);
	printf("solutionCount for optimized_1 = %d\n\n***********\n\n", *solutionCount);
	
	*solutionCount = 0;
	executeAndMeasureTime(optimized_2, matrix, 0, N, solutionCount);
	printf("solutionCount for optimized_2 = %d\n\n***********\n\n", *solutionCount);
	
	*solutionCount = 0;
	executeAndMeasureTime(backtracking, matrix, 0, N, solutionCount);
	printf("solutionCount for backtracking = %d\n\n***********\n\n", *solutionCount);
}

/**
 * @brief NxN satran� tahtas�n� ekrana basar.
  * @param matrix NxN satran� tahtas�.
 * @param N Satran� tahtas�n�n boyutu.
 */
void printTable(int** matrix, int N){
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%2d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}

/**
 * @brief NxN satran� tahtas�n� olu�turur.
 * @param N Satran� tahtas�n�n boyutu.
 * @return Olu�turulan satran� tahtas�na i�aret�i d�ner.
 */
int** createTable(int N){
	int i;
	int** matrix = (int**) malloc(N * sizeof(int*));
	 
	for(i=0;i<N;i++)
		matrix[i] = (int*) malloc(N * sizeof(int));
	return matrix;
}

/**
 * @brief Satran� tahtas�n� s�f�rlar.
 * @param matrix NxN satran� tahtas�.
 * @param N Satran� tahtas�n�n boyutu.
 */
void resetTable(int** matrix, int N){
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			matrix[i][j] = 0;
		}
	}
}	

/**
 * @brief NxN satran� tahtas�n� bellekten siler.
 * @param matrix NxN satran� tahtas�.
 * @param N Satran� tahtas�n�n boyutu.
 */
void destroyTable(int** matrix, int N){
	int i;
	for(i=0;i<N;i++)
		free(matrix[i]);
	free(matrix);
}

/**
 * @brief Belirtilen fonksiyonun �al��ma s�resini �l�er ve sonu�lar� yazd�r�r.
 * @param function �al��t�r�lacak fonksiyon.
 * @param matrix NxN satran� tahtas�.
 * @param row Vezir yerle�tirilecek sat�r.
 * @param N Satran� tahtas�n�n boyutu.
 * @param solutionCount ��z�m say�s�n� saklayan i�aret�i.
 */
void executeAndMeasureTime(void (*function)(int**, int, int, int*), int** matrix, int row, int N, int* solutionCount) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    function(matrix, row, N, solutionCount);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time elapsed %.2f sn\n", cpu_time_used);
}
