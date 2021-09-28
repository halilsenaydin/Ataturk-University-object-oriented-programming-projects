#ifndef KULLANICI_200707069
#define KULLANICI_200707069

/*
	Ad�m --> Halil �brahim
	Soyad�m --> �enayd�n
	��renci Numaram --> 200707069
	B�l�m�m --> C Grubu - Bilgisayar M�hendisli�i
	Dersin Ad� Ve Kodu --> Nesneye Y�nelik Programlama / BIM-104-50-50-C
	Dersin Verild�i Akademik D�nem --> 2020 - 2021 E�itim ��retim Y�l� / Bahar D�nemi
	Projenin Numaras� --> 2
	Dersi Veren ��retim �yesinin Ad� --> Deniz DAL
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
	int id; // id, �yeler i�in otomatik artand�r, miras al�nan class'da tan�mlan�r.

	// Helper Methods
	bool IsValidUserName(string userName);
	bool IsValidPassword(string userName);
	bool IsValidString(string stringData);
	int NumberOfCharacters(string stringData);

	// �� kural� artt�k�a dizi boyutu art�r�lmal�d�r!
	// Kurallara kar��l�k gelen mesajlar ayn� s�rayla yaz�lmal�d�r! (Bu sorunu kendi class'�m� yazarak ��zebilirdim, izin yoktu maalesef..)
	bool RunBusinessRules(bool rules[], string messages[], int size, string &message);

private:
	string name;
	string userName;
	string password;
};

#endif // KULLANICI_200707069