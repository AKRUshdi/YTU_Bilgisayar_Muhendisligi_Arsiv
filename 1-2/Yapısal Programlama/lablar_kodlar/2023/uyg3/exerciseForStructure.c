#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#pragma pack(1)
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
	int age;
	char name[20];
};

struct test{
	char a;
	int c;
	char b;
	
};

struct ogrenciler{
	char ad[20];
	char bolum[30];
	int sinif;
	float orta;
	
}ogr[3]={
	{
		"Ali", "Kamu Yonetimi", 3, 3.15
	},
	{
		"Mahmut", "�ktisat", 1, 2.50
	},
	{
		"Ayse", "Isletme", 4, 4.0
	}

};//farkl� bir kullan�m
int main() {
	
	//struct car c1 = {1, "araba"};
	struct car c1 = {.name = "madem", .age = 5}; // b�yle de alternatif bir yol varm�s 
	//c1.name = "madem"; // olmuyor
	
	struct car c2 = {6, "mazda"};
	struct car *ptr = &c2;
	
	//c2 = c1; //bu sekilde birbirine esitleyebiliyorsun
	printf("%d %s\n",c1.age, c1.name);
	printf("%d %s\n", (*ptr).age, (*ptr).name); // -> = *(var.field)  (*ptr).age
	printf("%d",sizeof(struct test));  // structure padding structure tan�mlarken fieldlar�n s�ralar� haf�zada tutulan alan�
	//direkt olarak etkiliyor ��nk� i�lemci tek seferde 4 byte yani bir word okuyor bu sebeple dizilim �nemli s�ra de�i�irse
	// kaplad��� alan de�i�iyor dene de g�r
	//#pragma pack(1) diye �zel bir �ey var bunu yaz�nca ba�a o zaman waste memory �nleniyor
	printf("\n%s",ogr[0].ad);
	
	// ayr�ca struct i�inde unionlar kullanarak ya da tersi �ekilde uygun �ekilde dizayn edilince haf�za tasarrufu
	// sa�lanabilir
	return 0;
}
