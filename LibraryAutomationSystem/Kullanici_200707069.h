#ifndef KULLANICI_200707069
#define KULLANICI_200707069

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

#include <string> // getline(), string
#include<iostream> // cout, cin
#include<iomanip> // setw(), left
#include "Kitap_200707069.h"

using namespace std;

class Kullanici_200707069
{
public:
	bool IsValidUser(Kullanici_200707069 user, string userName, string password);
	void GetAllBookOfUser(Kitap_200707069 books[], int size, int userId);

	// Getter Methods
	int GetId();
	string GetName();
	string GetUserName();
	string GetPassword();

	// Setter Methods
	void SetId(int id);
	void SetName(string name);
	void SetUserName(string userName);
	void SetPassword(string password);

protected:
	int id; // id, üyeler için otomatik artandýr, miras alýnan class'da tanýmlanýr.

	// Helper Methods
	bool IsValidUserName(string userName);
	bool IsValidPassword(string userName);
	bool IsValidString(string stringData);
	int NumberOfCharacters(string stringData);

	// Ýþ kuralý arttýkça dizi boyutu artýrýlmalýdýr!
	// Kurallara karþýlýk gelen mesajlar ayný sýrayla yazýlmalýdýr! (Bu sorunu kendi class'ýmý yazarak çözebilirdim, izin yoktu maalesef..)
	bool RunBusinessRules(bool rules[], string messages[], int size, string &message);

private:
	string name;
	string userName;
	string password;
};

#endif // KULLANICI_200707069