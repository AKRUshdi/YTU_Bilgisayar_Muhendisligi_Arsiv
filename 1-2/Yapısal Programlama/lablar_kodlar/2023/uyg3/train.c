#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//struct car{
//	int a;
//	char name[20];
//};
//
//
//
//normalde struct i�inde char dizisi varsa ona mainde structname.dizi = "araba" �eklinde atama yapam�yorsun ama 
//struct structname varname = {5, "araba"}; �eklinde olunca atama yap�labiliyor bunu da anca bu �ekilde yap�yor
// declaration yap�p sonra initializon yap�nca kabul etmiyor

struct car{
	int a;
	char name[20];
};

int main() {
	
	//struct car c1 = {1, "araba"};
	struct car c1 = {.name = "madem", .a = 5}; // b�yle de alternatif bir yol varm�s 
	//c1.name = "madem"; // olmuyor
	printf("%d %s",c1.a, c1.name);
	
	
	return 0;
}
