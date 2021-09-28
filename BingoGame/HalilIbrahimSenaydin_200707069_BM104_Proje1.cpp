// Kulland��um k�t�phaneler:
#include<iostream> // cin ve cout.
#include<cstdlib> // srand, rand. rasgele say� �retmek i�in.
#include<ctime> // time(0). srand �ekirde�i i�in, her defas�nda farkl� rastgele say�lar� elde etmek i�in zaman� kullan�r�z.
#include<clocale> // setlocale(). Konsol uygulamas�nda t�rk�e karakter kullanabilmek i�in.
#include<iomanip> // setw(). Yazd�r�lacak ifadeyi manip�le etmek i�in.

// �al��t���m isim uzay�
using namespace std; // Standart isim uzay�nda �al���yorum.


// Fonksiyon prototipleri:
void WelcomeScreenForPlayers(bool&); // referans tip parametre alan fonksiyon prototipi
void TombalaKartlariniOlustur(int[][15], int);
void WriteTombalaCards(int[][15], int);
bool IsPlayerNumberValid(int);
bool IsUnique(int array[], int, int);
void MatchPlayersWithCards(int[], int);
void CreatePlayerCards(int[][15], int[], int[][15], int);
void WritePlayerCards(int[][15], int);
void CreateLuckyBag(int[], int);
void WriteLuckyBag(int[], int);
void MarkNumbersOnPlayerCardsAndGivePoint(int[], int, int[][15], int[], int, int[][3]);
void WritePointOfPlayers(int[], int);
void WriteLuckyPlayer(int[], int);
void WriteResultTable(int[][3], int);

// Generik bir fonksiyonun prototipi!!
template <class T, class H>
T FindBiggestNumberInArray(T[], H);


int main() {
	setlocale(LC_ALL, "Turkish"); // Konsol i�inde t�rk�e karakter kullan�labilir hale getirdik.

	// Tombala kartlar�, oyuncu say�s�, oyuncular�, tombala torbas�n�, oyuncular�n puanlar�n� ve oyuncular�n kartlar�n� tutan dizi ve de�i�kenler.
	int tombalaCards[10][15];
	int playerCards[10][15];
	int luckyBag[90];
	int numberOfPlayer;

	// Oyuncu say�s� max 5 olabilir.
	int players[5]; // Oyuncu indislerini tutabilmek i�in.


	bool choice = true; // Kullan�c� ��kmak istiyor mu? De�eri fonksiyon i�inde de�i�tirilir. (Referans olarak parametre verilir.)
	int setNumber;

	WelcomeScreenForPlayers(choice);
	srand((unsigned int)time(0)); // Fonksiyon i�inde �retilen rastgele say�lar�n, her �al��t�r�ld���nda ayn� olmamas� i�in srand kulland�k, zaman�n bir fonksiyonu olarak kullanarak seed'i de de�i�tirmi� oluruz.
	while (choice) // Kullan�c� se�imine g�re d�ng�ye girer!
	{
		// Oyuncu puanlar� ve sonu� tablosu ilk de�er olarak s�f�r ayarlan�r.
		int result[5][3] = { 0 };
		int pointsOfPlayer[5] = { 0 };


		// Tombala kartlar�n� olu�tur ve tombala kartlar�n� ekrana yaz.
		TombalaKartlariniOlustur(tombalaCards, 10);
		WriteTombalaCards(tombalaCards, 10);


		// Oyuncu say�s�n� al, ge�erlili�ini kontrol et.
		cout << "\nOyuncu Say�s�n� Girin: "; cin >> numberOfPlayer;
		bool valid = IsPlayerNumberValid(numberOfPlayer);
		while (!valid)
		{
			cout << "\nOyuncu Say�s� En Az 2 En Fazla 5 Olabilir.\nL�tfen Tekrar Girin: "; cin >> numberOfPlayer;
			valid = IsPlayerNumberValid(numberOfPlayer);
		}

		// 3 set oynanacak oyun i�in d�ng� olu�tur, her set ba��nda oyuncu kartlar� de�i�ir, tombala torbas�ndaki rastgele �ekilen say�lar da de�i�ir.
		setNumber = 1;

		while (setNumber <= 3)
		{
			if (setNumber != 1)
			{
				cout << "\n" << setNumber - 1 << ". Set Bitti Yeni Set Ba�l�yor! Yeni Setin Oynanmas� ��in L�tfen Herhangi Bir Tu�a Bas�n! --> ";
			}

			string isContinue;
			if (setNumber >= 2)
			{
				cin >> isContinue;
			}

			cout << "\n\t********** " << setNumber << ". Set Oynan�yor **********\n" << endl;

			// Oyuncu kartlar�n� olu�tur ve yazd�r, tombala torbas�n� olu�tur ve yazd�r.
			MatchPlayersWithCards(players, numberOfPlayer);
			CreatePlayerCards(tombalaCards, players, playerCards, numberOfPlayer);

			WritePlayerCards(playerCards, numberOfPlayer);

			CreateLuckyBag(luckyBag, 90);
			WriteLuckyBag(luckyBag, 90);

			// �ekilen numaralara g�re oyuncu kartlar�n� kontrol et, puan verme i�lemini yap.
			MarkNumbersOnPlayerCardsAndGivePoint(luckyBag, 90, playerCards, pointsOfPlayer, numberOfPlayer, result);

			WritePointOfPlayers(pointsOfPlayer, numberOfPlayer); // Her set i�in son durumu ekrana yazd�r.
			setNumber++;
		}


		// 3 setin sonunda en y�ksek puan� alan oyuncuyu bul ve ekrana tebrik mesaj� ver, sonu� tablosunu yazd�r ve kullan�c� se�im ekran�n� yazd�r.
		WriteLuckyPlayer(pointsOfPlayer, numberOfPlayer);
		WriteResultTable(result, numberOfPlayer);
		WelcomeScreenForPlayers(choice);
	}
}


// Tombala kartlar�n� olu�turan fonksiyon, herhangi bir kartta bulunan 15 say�n�n tamam� da e�siz ve 1 - 90 aral���nda rastgele s�ralanm��t�r.
void TombalaKartlariniOlustur(int tombalaCards[][15], int row) {

	for (int i = 0; i < row; i++)
	{
		int randomNumbers[15];
		for (int j = 0; j < 15; j++)
		{
			while (true) { // D�ng�n�n amac�, e�er �retilen rastgele say�dan daha �nce �reilmi�se tekrar �retilmesi sa�lan�r ve bu i�lem rastgele say�lar birbirinden farkl� oluncaya dek devam eder.

				int randomNumber = rand() % 90 + 1;
				randomNumbers[j] = randomNumber;

				int unique = IsUnique(randomNumbers, j + 1, randomNumber); // �retilen say�, dizi i�inde birden fazla var mi? Alt fonksiyon �a�r�l�r.

				if (unique)
				{
					tombalaCards[i][j] = randomNumber; // Aranan kan bulundu :)
					break; // While d�ng�s�n� k�r.
				}
			}
		}
	}
}

void WriteTombalaCards(int tombalaCards[][15], int row) { // Tombala kartlar�n� ekrana yazd�ran fonksiyon.
	for (int i = 0; i < row; i++)
	{
		cout << setw(2) << i + 1 << ". Kart -->  ";
		for (int j = 0; j < 15; j++)
		{
			cout << setw(2) << tombalaCards[i][j] << "   ";
			if ((j + 1) % 5 == 0)
			{
				cout << endl;
				for (int k = 0; k < 14; k++)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void MatchPlayersWithCards(int players[], int numberOfPlayer) { // Oyuncular i�in rastgele kartlar� se�en fonksiyon.
	cout << "\nOyuncular ��in Se�ilen Kart Numaralar� --> ";

	for (int i = 0; i < numberOfPlayer; i++)
	{
		int randomNumbers[5];
		while (true) {
			int randIndis = rand() % 10; // 0-9 aral���nda rastgele kart indisi bulur.
			randomNumbers[i] = randIndis;

			int unique = IsUnique(randomNumbers, i + 1, randIndis); // �retilen indis, dizi i�inde birden fazla var mi? Alt fonksiyon �a�r�l�r.

			if (unique)
			{
				players[i] = randIndis;
				break; // While d�ng�s�n� k�r.
			}
		}
		cout << setw(2) << players[i] + 1 << " ";

	}
	cout << "\n" << endl;
}

void CreatePlayerCards(int tombalaCards[][15], int players[], int playerCards[][15], int numberOfPlayer) {  // Oyuncular�n kartlar�n� bir diziye aktarmak i�in gerekli fonksiyondur. Tombala kartlar�nda i�lem yap�l�rsa di�er setlerde tombala kartlar� da de�i�iyor, hatal� oyuna sebep oluyor.
	for (int i = 0; i < numberOfPlayer; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			playerCards[i][j] = tombalaCards[players[i]][j];
		}
	}
}

void WritePlayerCards(int playerCards[][15], int numberOfPlayer) { // Oyuncular i�in rastgele se�ilen kartlar� ekrana yazd�ran fonksiyon.

	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << setw(2) << i + 1 << ". Oyuncunu Kart� --> ";
		for (int j = 0; j < 15; j++)
		{
			cout << setw(2) << playerCards[i][j] << " ";
			if ((j + 1) % 5 == 0)
			{
				cout << endl;
				for (int k = 0; k < 23; k++)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

void CreateLuckyBag(int luckyBag[], int numberSizeInBag) { // Tombala torbas�n� olu�turan fonksiyon.
	int randomNumbers[90];
	int randomNumber;
	bool unique;

	for (int i = 0; i < numberSizeInBag; i++)
	{
		while (true) {
			randomNumber = rand() % 90 + 1;
			randomNumbers[i] = randomNumber;

			unique = IsUnique(randomNumbers, i + 1, randomNumber); // �retilen say�, dizi i�inde birden fazla var mi? Alt fonksiyon �a�r�l�r.

			if (unique)
			{
				luckyBag[i] = randomNumber; // E�siz!, torbaya �retilen say�y� ekle.
				break; // While d�ng�s�n� k�r.
			}
		}
	}
}

void WriteLuckyBag(int luckyBag[], int numberSizeInBag) { // Tombala torbas�n� yazd�ran fonksiyon.
	cout << "\n�EK�LEN NUMARALAR: " << endl;
	for (int i = 0; i < numberSizeInBag; i++)
	{
		cout << setw(2) << "\t" << luckyBag[i] << " ";
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}
}

void MarkNumbersOnPlayerCardsAndGivePoint(int luckyBag[], int numberSizeInBag, int playerCards[][15], int pointsOfPlayer[], int numberOfPlayer, int result[][3]) {// Tombala torbas�ndan ��kan say�lar�n oyuncu kartlar�nda ki varl���n� kontrol eder ve i�aretler. �inko veya tombala yapan oyunculara da puan veren fonksiyondur.
	cout << endl;

	int firstZincCounter = 0, secondZincCounter = 0;
	int tombala = 0;
	int counter;

	for (int i = 0; i < numberSizeInBag; i++) // Tombala torbas�ndaki say�lar.
	{
		for (int j = 0; j < numberOfPlayer; j++) // Oyuncu kart�.
		{
			counter = 0;
			for (int k = 0; k < 15; k++) // Oyuncu kart�ndaki say�lar.
			{
				if (luckyBag[i] == playerCards[j][k]) // Torbadaki i.eleman� oyuncular�n kartlar� ile kar��la�t�r�p ayn� ise o andaki eleman� i�aretleyip bildirece�iz.
				{
					playerCards[j][k] = -1; // ��aretle.
				}

				playerCards[j][k] == -1 ? counter++ : NULL; // ��artlenen say�lar� saya� yard�m�yla say!

			}

			// �inko yapan oyuncu veya oyuncular var m�? Varsa her biri i�in puan ver. T�m oyuncular �inko veya tombala yapmak i�in tek pula bak�yor olabilir.
			if (counter == 5 && firstZincCounter != -1)
			{
				pointsOfPlayer[j] += 5;
				cout << "!!!! 1.�inko Kazanan " << j + 1 << " Numaral� Oyuncu !!!!" << endl;
				WritePlayerCards(playerCards, numberOfPlayer);
				firstZincCounter++;
				result[j][0]++;
			}

			else if (counter == 10 && secondZincCounter != -1)
			{
				pointsOfPlayer[j] += 10;
				cout << "!!!! 2.�inko Kazanan " << j + 1 << " Numaral� Oyuncu !!!!" << endl;
				WritePlayerCards(playerCards, numberOfPlayer);
				secondZincCounter++;
				result[j][1]++;
			}

			else if (counter == 15)
			{
				pointsOfPlayer[j] += 15;
				cout << "!!!! Tombala Yapan " << j + 1 << " Numaral� Oyuncu !!!!" << endl;
				WritePlayerCards(playerCards, numberOfPlayer);
				tombala++;
				result[j][2]++;
			}
		}

		// Ayn� pul ile birka� oyuncu ayn� anda �inko veya tombala yapabilir.
		if (tombala != 0)
		{
			return; // Tombala yapm�� bir oyuncu veya oyuncular var!
		}

		if (firstZincCounter != 0)
		{
			firstZincCounter = -1; // Birinci �inkoyu oyuncu veya oyuncular yapm��. Di�er pullar �ekilirken art�k birinci �inko yap�lamaz.
		}

		if (secondZincCounter != 0)
		{
			secondZincCounter = -1; // �kinci �inkoyu oyuncu veya oyuncular yapm��. Di�er pullar �ekilirken art�k ikinci �inko yap�lamaz.
		}
	}
}

void WritePointOfPlayers(int pointOfPlayers[], int numberOfPlayers) { // Oyuncular�n puan tablosunu ekrana yazd�ran fonksiyon.
	cout << endl;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		cout << i + 1 << ". Oyuncunun Puan Durumu -->";
		cout << setw(3) << pointOfPlayers[i] << endl;
	}
}

void WelcomeScreenForPlayers(bool& choice) { // Oyun kar��lama fonksiyonu, parametre olarak ald��� se�im de�erini ko�ula g�re de�i�tirerek �a�r�ld��� yerde de�i�ken de�eri de�i�tirilir.
	while (true)
	{
		int selection;
		cout << "\n 1- Oyun Kurallar� ��in 1'i Se�in \n 2- Oyuna Ba�lamak ��in 2'yi Se�in \n 3- Oyundan ��kmak ��in 3'� Se�in \n Se�im Yap: "; cin >> selection;
		if (selection == 1)
		{
			cout << "\n\t****************************** Tombala Oyunu Kurallar�: ******************************\n\n 1- Oyun en fazla 5 en az 2 ki�iyle oynan�r. \n\n 2- Oyuncular�n kartlar�n� bilgisayar rastgele olarak se�er. " << endl;
			cout << "\n 3- Rastgele �ekilen her pul oyuncu kartlar�ndaki varl��� kontrol edilir, oyuncunun kart�nda varsa i�aretler, o i�aret - 1'dir. \n\n 4- �ekilen pullardan 5 tanesi oyuncunun kart�nda ��km��sa oyuncu birinci �inkoyu yapm��t�r ve  5 puan, 10 tanesi ��km��sa oyuncu ikinci �inkoyu yapm��t�r ve 10 puan, 15 tanesi de ��km��sa oyuncu tombala yapm��t�r ve 15 puan al�r. \n\n 5- Pullarda �ekilen s�ra �nemli oldu�u i�in ilk tombala yapan ki�i o seti kazan�r. \n\n 6- �lk birinci �inkoyu yapan oyuncu 5 puan al�r, ilk ikinci �inkoyu yapan oyuncu 10 puan� al�r. \n\n 7- Birden fazla oyuncu tombala veya �inko yapmak i�in ayn� pulu bekliyorsa, oyuncular ayn� anda �inko veya tombala yapm�� kabul edilir. \n\n 8- Set say�s� 3't�r.Ve toplam 3 set i�inde oyuncular�n toplam puan� hesaplan�r ve en y�ksek puana sahip oyuncu oyunu kazan�r. \n\n 9- Oyunu ba�latan her oyuncu kurallar� okumu� ve kabul etmi� say�lacakt�r. \n\n 10- Bol �anslar :)";
		}
		else if (selection == 2) {
			cout << "\n\t*********************** TOMBALA OYUNU BA�LIYOR, �Y� E�LENCELER :) ***********************\n\n";
			choice = true;
			break;
		}
		else if (selection == 3) {
			choice = false; // Se�imi false yap, �a�r�ld��� yerde bu se�im kontrol ediliyor.
			cout << "\nOyundan ��k�� Yapt�n�z :)" << endl;
			break;
		}
		else
		{
			cout << "\n!! Oyuna ge�mek i�in 2'yi tu�lay�n, Kurallar� okumak i�in 1'i tu�lay�n !!" << endl;
		}
		cout << endl;
		cout << endl;
	}
}

void WriteLuckyPlayer(int pointsOfPlayer[], int numberOfPlayer) {  // Kazanan oyuncuyu ekrana yazd�ran fonksiyon. Birden fazla kazanan oyuncu olabilir.

	int highScore = FindBiggestNumberInArray<int, int>(pointsOfPlayer, numberOfPlayer); // Oyuncu puanlar�ndaki en y�ksek puan� bul ve de�i�kene ata.

	cout << endl;

	for (int i = 0; i < numberOfPlayer; i++)
	{
		if (pointsOfPlayer[i] == highScore) // Kazanan oyuncular� dizi i�inde tarayarak bul!
		{
			cout << "\n\t ********** Kazanan Oyuncu " << highScore << " Puan �le " << i + 1 << " Numaral� Oyuncu **********" << endl;
			cout << "\t ********** Tebrikler " << i + 1 << " Numaral� Oyuncu �ansl� G�n�ndesin :) **********" << endl;
		}
	}
}

void WriteResultTable(int result[][3], int numberOfPlayer) { // Oyuncular�n Toplam Set Sonunda Yapm�� Olduklar� Tombala ve �inko Say�lar�n� Yazd�ran Fonksiyon!
	cout << "\n------------------------------------------------------------------------------------" << endl;
	cout << "\n\t\t\t !!!! Oyuncular�n Sonu� Tablosu !!!!" << endl;

	cout << "\n\t\t1. �inko Say�s�  2. �inko Say�s�  Tombala Say�s�" << endl;;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << i + 1 << ". Oyuncunun ->";
		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				cout << setw(10) << result[i][j];
			}
			else
			{
				cout << setw(16) << result[i][j];
			}

		}
		cout << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
	}
}

bool IsPlayerNumberValid(int numberOfPlayer) { // Oyuncu say�s� ge�erlili�ini kontrol eden fonksiyon.
	if (numberOfPlayer < 2 || numberOfPlayer > 5)
	{
		return false;
	}
	return true;
}

bool IsUnique(int array[], int arraySize, int number) { // Parametre olarak verilen say�, dizi i�inde birden fazla var m�? Birden fazla varsa false ver.
	int unique = 0;
	for (int k = 0; k < arraySize; k++)
	{
		if (number == array[k])
		{
			unique += 1;
			if (unique >= 2)
			{
				return false; // Aranan kan bulunamad� :( E�siz de�il!
			}
		}
	}

	return true; // Aranan kan bulund� :) E�siz!
}

template <class T, class H> // �ki tipli �al���l�r.
T FindBiggestNumberInArray(T array[], H size) // Parametre olarak ald��� dizinin i�indeki en b�y�k say�y� d�nd�r�r.
{
	T biggestNumber = array[0];
	for (int i = 1; i < size; i++)
	{
		if (array[i] > biggestNumber)
		{
			biggestNumber = array[i];
		}
	}
	return biggestNumber;
}