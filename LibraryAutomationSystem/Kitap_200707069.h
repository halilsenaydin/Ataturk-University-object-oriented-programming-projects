#ifndef KITAP_200707069
#define KITAP_200707069

/*
	Adým --> Halil Ýbrahim
	Soyadým --> Þenaydýn
	Öðrenci Numaram --> 200707069
	Bölümüm --> C Grubu - Bilgisayar Mühendisliði
	Dersin Adý Ve Kodu --> Nesneye Yönelik Programlama / BIM-104-50-50-C
	Dersin Verildði Akademik Dönem --> 2020 - 2021 Eðitim Öðretim Yýlý / Bahar Dönemi
	Projenin Numarasý --> 2
	Dersi Veren Öðretim Üyesinin Adý --> Deniz DAL
*/

#include<string> // string
#include<iostream> // cin, cout
#include<iomanip> // setw(), left

using namespace std;

class Kitap_200707069
{
public:
	Kitap_200707069 Get(Kitap_200707069 books[], int size, int id); // Get book by id
	void GetAll(Kitap_200707069 books[], int size); // Get all (from the array)
	void GetByUserId(Kitap_200707069 books[], int size, int userId); // Get the books the user has borrowed. 

	void GetBookDetail(Kitap_200707069 books[], int numberOfBook, int bookId); // Get book detail from book array with book id (Db)

	void Add(Kitap_200707069 books[], int numberOfBook, Kitap_200707069 book);
	void Delete(Kitap_200707069 books[], int numberOfBook, int bookId);

	// Update
	void EditBookName(Kitap_200707069 books[], int numberOfBook, int bookId, string bookName);
	void EditWriterName(Kitap_200707069 books[], int numberOfBook, int bookId, string writerName);
	void EditDescription(Kitap_200707069 books[], int numberOfBook, int bookId, string description);

	// Set Methods
	void SetId(int id);
	void SetUserId(int userId);
	void SetBookName(string bookName);
	void SetWriterName(string writerName);
	void SetStatus(string status);

	void SetDescription(string description);

	// Get Methods
	int GetId();
	int GetUserId();
	string GetBookName();
	string GetWriterName();
	string GetStatus();

	string GetDescription();

private:
	int id;
	int userId; // O kitabý alan kullanýcýnýn id'si. Null olabilir.
	string bookName;
	string writerName;
	string status; // Hold or Unhold

	string description;

	// Helper Functions
	bool IsBookExist(Kitap_200707069 books[], int size, string writerName, string bookName);
	bool IsValidString(string stringData); // Bu fonksiyon bazý class'larda da kullanýlabilir. Daha sonra static bir class içine method olarak yaz! (Projede izin yoktu)
	int NumberOfCharacters(string stringData);

	// Ýþ kuralý arttýkça dizi boyutu artýrýlmalýdýr!
	// Kurallara karþýlýk gelen mesajlar ayný sýrayla yazýlmalýdýr! (Bu sorunu kendi class'ýmý yazarak çözebilirdim, izin yoktu maalesef..)
	bool RunBusinessRules(bool rules[], string messages[], int size, string& message); // Bu fonksiyon bazý class'larda da kullanýlabilir. Daha sonra static bir class içine method olarak yaz!(Projede izin yoktu)
};

#endif // KITAP_200707069