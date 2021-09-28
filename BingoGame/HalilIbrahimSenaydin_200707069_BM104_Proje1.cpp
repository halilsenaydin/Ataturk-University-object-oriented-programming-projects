// Kullandýðum kütüphaneler:
#include<iostream> // cin ve cout.
#include<cstdlib> // srand, rand. rasgele sayý üretmek için.
#include<ctime> // time(0). srand çekirdeði için, her defasýnda farklý rastgele sayýlarý elde etmek için zamaný kullanýrýz.
#include<clocale> // setlocale(). Konsol uygulamasýnda türkçe karakter kullanabilmek için.
#include<iomanip> // setw(). Yazdýrýlacak ifadeyi manipüle etmek için.

// Çalýþtýðým isim uzayý
using namespace std; // Standart isim uzayýnda çalýþýyorum.


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
	setlocale(LC_ALL, "Turkish"); // Konsol içinde türkçe karakter kullanýlabilir hale getirdik.

	// Tombala kartlarý, oyuncu sayýsý, oyuncularý, tombala torbasýný, oyuncularýn puanlarýný ve oyuncularýn kartlarýný tutan dizi ve deðiþkenler.
	int tombalaCards[10][15];
	int playerCards[10][15];
	int luckyBag[90];
	int numberOfPlayer;

	// Oyuncu sayýsý max 5 olabilir.
	int players[5]; // Oyuncu indislerini tutabilmek için.


	bool choice = true; // Kullanýcý çýkmak istiyor mu? Deðeri fonksiyon içinde deðiþtirilir. (Referans olarak parametre verilir.)
	int setNumber;

	WelcomeScreenForPlayers(choice);
	srand((unsigned int)time(0)); // Fonksiyon içinde üretilen rastgele sayýlarýn, her çalýþtýrýldýðýnda ayný olmamasý için srand kullandýk, zamanýn bir fonksiyonu olarak kullanarak seed'i de deðiþtirmiþ oluruz.
	while (choice) // Kullanýcý seçimine göre döngüye girer!
	{
		// Oyuncu puanlarý ve sonuç tablosu ilk deðer olarak sýfýr ayarlanýr.
		int result[5][3] = { 0 };
		int pointsOfPlayer[5] = { 0 };


		// Tombala kartlarýný oluþtur ve tombala kartlarýný ekrana yaz.
		TombalaKartlariniOlustur(tombalaCards, 10);
		WriteTombalaCards(tombalaCards, 10);


		// Oyuncu sayýsýný al, geçerliliðini kontrol et.
		cout << "\nOyuncu Sayýsýný Girin: "; cin >> numberOfPlayer;
		bool valid = IsPlayerNumberValid(numberOfPlayer);
		while (!valid)
		{
			cout << "\nOyuncu Sayýsý En Az 2 En Fazla 5 Olabilir.\nLütfen Tekrar Girin: "; cin >> numberOfPlayer;
			valid = IsPlayerNumberValid(numberOfPlayer);
		}

		// 3 set oynanacak oyun için döngü oluþtur, her set baþýnda oyuncu kartlarý deðiþir, tombala torbasýndaki rastgele çekilen sayýlar da deðiþir.
		setNumber = 1;

		while (setNumber <= 3)
		{
			if (setNumber != 1)
			{
				cout << "\n" << setNumber - 1 << ". Set Bitti Yeni Set Baþlýyor! Yeni Setin Oynanmasý Ýçin Lütfen Herhangi Bir Tuþa Basýn! --> ";
			}

			string isContinue;
			if (setNumber >= 2)
			{
				cin >> isContinue;
			}

			cout << "\n\t********** " << setNumber << ". Set Oynanýyor **********\n" << endl;

			// Oyuncu kartlarýný oluþtur ve yazdýr, tombala torbasýný oluþtur ve yazdýr.
			MatchPlayersWithCards(players, numberOfPlayer);
			CreatePlayerCards(tombalaCards, players, playerCards, numberOfPlayer);

			WritePlayerCards(playerCards, numberOfPlayer);

			CreateLuckyBag(luckyBag, 90);
			WriteLuckyBag(luckyBag, 90);

			// Çekilen numaralara göre oyuncu kartlarýný kontrol et, puan verme iþlemini yap.
			MarkNumbersOnPlayerCardsAndGivePoint(luckyBag, 90, playerCards, pointsOfPlayer, numberOfPlayer, result);

			WritePointOfPlayers(pointsOfPlayer, numberOfPlayer); // Her set için son durumu ekrana yazdýr.
			setNumber++;
		}


		// 3 setin sonunda en yüksek puaný alan oyuncuyu bul ve ekrana tebrik mesajý ver, sonuç tablosunu yazdýr ve kullanýcý seçim ekranýný yazdýr.
		WriteLuckyPlayer(pointsOfPlayer, numberOfPlayer);
		WriteResultTable(result, numberOfPlayer);
		WelcomeScreenForPlayers(choice);
	}
}


// Tombala kartlarýný oluþturan fonksiyon, herhangi bir kartta bulunan 15 sayýnýn tamamý da eþsiz ve 1 - 90 aralýðýnda rastgele sýralanmýþtýr.
void TombalaKartlariniOlustur(int tombalaCards[][15], int row) {

	for (int i = 0; i < row; i++)
	{
		int randomNumbers[15];
		for (int j = 0; j < 15; j++)
		{
			while (true) { // Döngünün amacý, eðer üretilen rastgele sayýdan daha önce üreilmiþse tekrar üretilmesi saðlanýr ve bu iþlem rastgele sayýlar birbirinden farklý oluncaya dek devam eder.

				int randomNumber = rand() % 90 + 1;
				randomNumbers[j] = randomNumber;

				int unique = IsUnique(randomNumbers, j + 1, randomNumber); // Üretilen sayý, dizi içinde birden fazla var mi? Alt fonksiyon çaðrýlýr.

				if (unique)
				{
					tombalaCards[i][j] = randomNumber; // Aranan kan bulundu :)
					break; // While döngüsünü kýr.
				}
			}
		}
	}
}

void WriteTombalaCards(int tombalaCards[][15], int row) { // Tombala kartlarýný ekrana yazdýran fonksiyon.
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

void MatchPlayersWithCards(int players[], int numberOfPlayer) { // Oyuncular için rastgele kartlarý seçen fonksiyon.
	cout << "\nOyuncular Ýçin Seçilen Kart Numaralarý --> ";

	for (int i = 0; i < numberOfPlayer; i++)
	{
		int randomNumbers[5];
		while (true) {
			int randIndis = rand() % 10; // 0-9 aralýðýnda rastgele kart indisi bulur.
			randomNumbers[i] = randIndis;

			int unique = IsUnique(randomNumbers, i + 1, randIndis); // Üretilen indis, dizi içinde birden fazla var mi? Alt fonksiyon çaðrýlýr.

			if (unique)
			{
				players[i] = randIndis;
				break; // While döngüsünü kýr.
			}
		}
		cout << setw(2) << players[i] + 1 << " ";

	}
	cout << "\n" << endl;
}

void CreatePlayerCards(int tombalaCards[][15], int players[], int playerCards[][15], int numberOfPlayer) {  // Oyuncularýn kartlarýný bir diziye aktarmak için gerekli fonksiyondur. Tombala kartlarýnda iþlem yapýlýrsa diðer setlerde tombala kartlarý da deðiþiyor, hatalý oyuna sebep oluyor.
	for (int i = 0; i < numberOfPlayer; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			playerCards[i][j] = tombalaCards[players[i]][j];
		}
	}
}

void WritePlayerCards(int playerCards[][15], int numberOfPlayer) { // Oyuncular için rastgele seçilen kartlarý ekrana yazdýran fonksiyon.

	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << setw(2) << i + 1 << ". Oyuncunu Kartý --> ";
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

void CreateLuckyBag(int luckyBag[], int numberSizeInBag) { // Tombala torbasýný oluþturan fonksiyon.
	int randomNumbers[90];
	int randomNumber;
	bool unique;

	for (int i = 0; i < numberSizeInBag; i++)
	{
		while (true) {
			randomNumber = rand() % 90 + 1;
			randomNumbers[i] = randomNumber;

			unique = IsUnique(randomNumbers, i + 1, randomNumber); // Üretilen sayý, dizi içinde birden fazla var mi? Alt fonksiyon çaðrýlýr.

			if (unique)
			{
				luckyBag[i] = randomNumber; // Eþsiz!, torbaya üretilen sayýyý ekle.
				break; // While döngüsünü kýr.
			}
		}
	}
}

void WriteLuckyBag(int luckyBag[], int numberSizeInBag) { // Tombala torbasýný yazdýran fonksiyon.
	cout << "\nÇEKÝLEN NUMARALAR: " << endl;
	for (int i = 0; i < numberSizeInBag; i++)
	{
		cout << setw(2) << "\t" << luckyBag[i] << " ";
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}
}

void MarkNumbersOnPlayerCardsAndGivePoint(int luckyBag[], int numberSizeInBag, int playerCards[][15], int pointsOfPlayer[], int numberOfPlayer, int result[][3]) {// Tombala torbasýndan çýkan sayýlarýn oyuncu kartlarýnda ki varlýðýný kontrol eder ve iþaretler. Çinko veya tombala yapan oyunculara da puan veren fonksiyondur.
	cout << endl;

	int firstZincCounter = 0, secondZincCounter = 0;
	int tombala = 0;
	int counter;

	for (int i = 0; i < numberSizeInBag; i++) // Tombala torbasýndaki sayýlar.
	{
		for (int j = 0; j < numberOfPlayer; j++) // Oyuncu kartý.
		{
			counter = 0;
			for (int k = 0; k < 15; k++) // Oyuncu kartýndaki sayýlar.
			{
				if (luckyBag[i] == playerCards[j][k]) // Torbadaki i.elemaný oyuncularýn kartlarý ile karþýlaþtýrýp ayný ise o andaki elemaný iþaretleyip bildireceðiz.
				{
					playerCards[j][k] = -1; // Ýþaretle.
				}

				playerCards[j][k] == -1 ? counter++ : NULL; // Ýþartlenen sayýlarý sayaç yardýmýyla say!

			}

			// Çinko yapan oyuncu veya oyuncular var mý? Varsa her biri için puan ver. Tüm oyuncular çinko veya tombala yapmak için tek pula bakýyor olabilir.
			if (counter == 5 && firstZincCounter != -1)
			{
				pointsOfPlayer[j] += 5;
				cout << "!!!! 1.Çinko Kazanan " << j + 1 << " Numaralý Oyuncu !!!!" << endl;
				WritePlayerCards(playerCards, numberOfPlayer);
				firstZincCounter++;
				result[j][0]++;
			}

			else if (counter == 10 && secondZincCounter != -1)
			{
				pointsOfPlayer[j] += 10;
				cout << "!!!! 2.Çinko Kazanan " << j + 1 << " Numaralý Oyuncu !!!!" << endl;
				WritePlayerCards(playerCards, numberOfPlayer);
				secondZincCounter++;
				result[j][1]++;
			}

			else if (counter == 15)
			{
				pointsOfPlayer[j] += 15;
				cout << "!!!! Tombala Yapan " << j + 1 << " Numaralý Oyuncu !!!!" << endl;
				WritePlayerCards(playerCards, numberOfPlayer);
				tombala++;
				result[j][2]++;
			}
		}

		// Ayný pul ile birkaç oyuncu ayný anda çinko veya tombala yapabilir.
		if (tombala != 0)
		{
			return; // Tombala yapmýþ bir oyuncu veya oyuncular var!
		}

		if (firstZincCounter != 0)
		{
			firstZincCounter = -1; // Birinci çinkoyu oyuncu veya oyuncular yapmýþ. Diðer pullar çekilirken artýk birinci çinko yapýlamaz.
		}

		if (secondZincCounter != 0)
		{
			secondZincCounter = -1; // Ýkinci çinkoyu oyuncu veya oyuncular yapmýþ. Diðer pullar çekilirken artýk ikinci çinko yapýlamaz.
		}
	}
}

void WritePointOfPlayers(int pointOfPlayers[], int numberOfPlayers) { // Oyuncularýn puan tablosunu ekrana yazdýran fonksiyon.
	cout << endl;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		cout << i + 1 << ". Oyuncunun Puan Durumu -->";
		cout << setw(3) << pointOfPlayers[i] << endl;
	}
}

void WelcomeScreenForPlayers(bool& choice) { // Oyun karþýlama fonksiyonu, parametre olarak aldýðý seçim deðerini koþula göre deðiþtirerek çaðrýldýðý yerde deðiþken deðeri deðiþtirilir.
	while (true)
	{
		int selection;
		cout << "\n 1- Oyun Kurallarý Ýçin 1'i Seçin \n 2- Oyuna Baþlamak Ýçin 2'yi Seçin \n 3- Oyundan Çýkmak Ýçin 3'ü Seçin \n Seçim Yap: "; cin >> selection;
		if (selection == 1)
		{
			cout << "\n\t****************************** Tombala Oyunu Kurallarý: ******************************\n\n 1- Oyun en fazla 5 en az 2 kiþiyle oynanýr. \n\n 2- Oyuncularýn kartlarýný bilgisayar rastgele olarak seçer. " << endl;
			cout << "\n 3- Rastgele çekilen her pul oyuncu kartlarýndaki varlýðý kontrol edilir, oyuncunun kartýnda varsa iþaretler, o iþaret - 1'dir. \n\n 4- Çekilen pullardan 5 tanesi oyuncunun kartýnda çýkmýþsa oyuncu birinci çinkoyu yapmýþtýr ve  5 puan, 10 tanesi çýkmýþsa oyuncu ikinci çinkoyu yapmýþtýr ve 10 puan, 15 tanesi de çýkmýþsa oyuncu tombala yapmýþtýr ve 15 puan alýr. \n\n 5- Pullarda çekilen sýra önemli olduðu için ilk tombala yapan kiþi o seti kazanýr. \n\n 6- Ýlk birinci çinkoyu yapan oyuncu 5 puan alýr, ilk ikinci çinkoyu yapan oyuncu 10 puaný alýr. \n\n 7- Birden fazla oyuncu tombala veya çinko yapmak için ayný pulu bekliyorsa, oyuncular ayný anda çinko veya tombala yapmýþ kabul edilir. \n\n 8- Set sayýsý 3'tür.Ve toplam 3 set içinde oyuncularýn toplam puaný hesaplanýr ve en yüksek puana sahip oyuncu oyunu kazanýr. \n\n 9- Oyunu baþlatan her oyuncu kurallarý okumuþ ve kabul etmiþ sayýlacaktýr. \n\n 10- Bol þanslar :)";
		}
		else if (selection == 2) {
			cout << "\n\t*********************** TOMBALA OYUNU BAÞLIYOR, ÝYÝ EÐLENCELER :) ***********************\n\n";
			choice = true;
			break;
		}
		else if (selection == 3) {
			choice = false; // Seçimi false yap, çaðrýldýðý yerde bu seçim kontrol ediliyor.
			cout << "\nOyundan Çýkýþ Yaptýnýz :)" << endl;
			break;
		}
		else
		{
			cout << "\n!! Oyuna geçmek için 2'yi tuþlayýn, Kurallarý okumak için 1'i tuþlayýn !!" << endl;
		}
		cout << endl;
		cout << endl;
	}
}

void WriteLuckyPlayer(int pointsOfPlayer[], int numberOfPlayer) {  // Kazanan oyuncuyu ekrana yazdýran fonksiyon. Birden fazla kazanan oyuncu olabilir.

	int highScore = FindBiggestNumberInArray<int, int>(pointsOfPlayer, numberOfPlayer); // Oyuncu puanlarýndaki en yüksek puaný bul ve deðiþkene ata.

	cout << endl;

	for (int i = 0; i < numberOfPlayer; i++)
	{
		if (pointsOfPlayer[i] == highScore) // Kazanan oyuncularý dizi içinde tarayarak bul!
		{
			cout << "\n\t ********** Kazanan Oyuncu " << highScore << " Puan Ýle " << i + 1 << " Numaralý Oyuncu **********" << endl;
			cout << "\t ********** Tebrikler " << i + 1 << " Numaralý Oyuncu Þanslý Günündesin :) **********" << endl;
		}
	}
}

void WriteResultTable(int result[][3], int numberOfPlayer) { // Oyuncularýn Toplam Set Sonunda Yapmýþ Olduklarý Tombala ve Çinko Sayýlarýný Yazdýran Fonksiyon!
	cout << "\n------------------------------------------------------------------------------------" << endl;
	cout << "\n\t\t\t !!!! Oyuncularýn Sonuç Tablosu !!!!" << endl;

	cout << "\n\t\t1. Çinko Sayýsý  2. Çinko Sayýsý  Tombala Sayýsý" << endl;;
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

bool IsPlayerNumberValid(int numberOfPlayer) { // Oyuncu sayýsý geçerliliðini kontrol eden fonksiyon.
	if (numberOfPlayer < 2 || numberOfPlayer > 5)
	{
		return false;
	}
	return true;
}

bool IsUnique(int array[], int arraySize, int number) { // Parametre olarak verilen sayý, dizi içinde birden fazla var mý? Birden fazla varsa false ver.
	int unique = 0;
	for (int k = 0; k < arraySize; k++)
	{
		if (number == array[k])
		{
			unique += 1;
			if (unique >= 2)
			{
				return false; // Aranan kan bulunamadý :( Eþsiz deðil!
			}
		}
	}

	return true; // Aranan kan bulundý :) Eþsiz!
}

template <class T, class H> // Ýki tipli çalýþýlýr.
T FindBiggestNumberInArray(T array[], H size) // Parametre olarak aldýðý dizinin içindeki en büyük sayýyý döndürür.
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