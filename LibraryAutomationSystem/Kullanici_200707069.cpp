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

#include "Kullanici_200707069.h"

bool Kullanici_200707069::IsValidUser(Kullanici_200707069 user, string userName, string password)
{
	if (user.userName == userName && user.password == password)
	{
		return true;
	}

	return false;
}

void Kullanici_200707069::GetAllBookOfUser(Kitap_200707069 books[], int size, int userId)
{
	cout << "�d�n� Ald���n�z Kitaplar (Ge�erli Bir Id De�eri Girin!)" << endl;
	Kitap_200707069 book;
	book.GetByUserId(books, size, userId);
}

// Getter Methods
int Kullanici_200707069::GetId()
{
	return Kullanici_200707069::id;
}

string Kullanici_200707069::GetName()
{
	return Kullanici_200707069::name;
}

string Kullanici_200707069::GetUserName()
{
	return Kullanici_200707069::userName;
}

string Kullanici_200707069::GetPassword()
{
	return Kullanici_200707069::password;
}

// Setter Methods
void Kullanici_200707069::SetId(int id)
{
	Kullanici_200707069::id = id;
}

void Kullanici_200707069::SetName(string name)
{
	Kullanici_200707069::name = name;
}

void Kullanici_200707069::SetUserName(string userName)
{
	Kullanici_200707069::userName = userName;
}

void Kullanici_200707069::SetPassword(string password)
{
	Kullanici_200707069::password = password;
}

// Helper Methods
bool Kullanici_200707069::IsValidUserName(string userName) // userName must have not contain empty character!
{
	for (int i = 0; userName[i] != '\0'; i++)
	{
		if (userName[i] == ' ')
		{
			return false;
		}
	}

	return true;
}

bool Kullanici_200707069::IsValidPassword(string password) // password must have not contain empty character and password length must have min 14 character!
{
	int counter = 0;
	for (int i = 0; password[i] != '\0'; i++)
	{
		if (password[i] == ' ')
		{
			return false;
		}
		counter++;
	}

	if (counter < 14)
	{
		return false;
	}

	return true;
}

bool Kullanici_200707069::IsValidString(string stringData) // String must have not contain turkish character and symbol!
{
	char validCharacters[] = { 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '-', '.', '\0' };

	int arraySize = 0;
	int counter = 0;
	for (int i = 0; stringData[i] != '\0'; i++)
	{
		arraySize++;
		for (int j = 0; validCharacters[j] != '\0'; j++)
		{
			if (stringData[i] == validCharacters[j])
			{
				counter++;
			}
		}
	}

	if (counter != arraySize)
	{
		return false;
	}

	return true;
}

int Kullanici_200707069::NumberOfCharacters(string stringData)
{
	int counter = 0;
	for (int i = 0; stringData[i] != '\0'; i++)
	{
		counter++;
	}

	return counter;
}


// �� kurallar�n� �al��t�rmak i�in haz�rlad���m helper method. Parametre olarak ald��� i� kurallar� dizisini kontrol eder, belirledi�im kurallara uymuyorsa false d�nderir. Mesaj olarak da hangi kurala uymuyorsa referans olarak gelen de�i�kene o kural�n mesaj�n� atar!
bool Kullanici_200707069::RunBusinessRules(bool rules[], string messages[], int size, string& message)
{
	for (int i = 0; i < size; i++)
	{
		if (!rules[i])
		{
			message = messages[i];
			return false;
		}
	}

	return true;
}
