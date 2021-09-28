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

#include "Kitap_200707069.h"
#include<string>

Kitap_200707069 Kitap_200707069::Get(Kitap_200707069 books[], int size, int id) { // Get book by id from array (database)
	for (int i = 0; i < size; i++)
	{
		if (books[i].id == id)
		{
			return books[i];
		}
	}

	return Kitap_200707069{}; // Book not found
}

void Kitap_200707069::GetAll(Kitap_200707069 books[], int size) { // Get all book from array (database)
	int counter = 0;
	cout << endl;

	cout << setw(3) << "ID " << setw(50) << left << "Kitap Ad�" << setw(50) << left << "Yazar Ad�" << setw(20) << left << "Kitap Durumu" << "\n" << endl;
	for (int i = 0; i < size; i++)
	{
		if (books[i].id != -1)
		{
			string whoBorrowed = books[i].userId == -1 ? " " : "Kitab� �d�n� Alan Kullan�c�n�n ID'si: " + to_string(books[i].userId);
			cout << setw(3) << left << books[i].id << setw(50) << left << books[i].bookName << setw(50) << left << books[i].writerName << setw(20) << left << books[i].status << whoBorrowed << endl;
			counter++;
		}
	}

	if (counter == 0)
	{
		cout << "\n!! Hen�z Bir Kitap Eklenmemi� !!" << endl;
	}
}

void Kitap_200707069::GetByUserId(Kitap_200707069 books[], int size, int userId) // Get book by userId from array (database)
{
	int counter = 0;
	cout << endl;
	cout << setw(3) << "ID " << setw(50) << left << "Kitap Ad�" << setw(50) << left << "Yazar Ad�" << setw(25) << left << "Kitap �d�n� Al�nma Durumu" << "\n" << endl;
	for (int i = 0; i < size; i++)
	{
		if (books[i].userId == userId && userId >= 0)
		{
			cout << setw(3) << left << books[i].id << setw(50) << left << books[i].bookName << setw(50) << left << books[i].writerName << setw(25) << left << books[i].status << endl;
			counter++;
		}
	}

	if (counter == 0)
	{
		cout << "\n!! �d�n� Ald���n�z Bir Kitap Yoktur !!" << endl;
	}
}

void Kitap_200707069::GetBookDetail(Kitap_200707069 books[], int numberOfBook, int bookId)
{
	for (int i = 0; i < numberOfBook; i++)
	{
		if (books[i].id == bookId && bookId != -1 && bookId != 0)
		{
			cout << "\n\tKitap Ad�: " << books[i].bookName << "\n\tYazar Ad�: " << books[i].writerName << "\n\tA��klama: " << books[i].description << endl;
			return;
		}
	}

	cout << "\n!! Yanl�� ID De�eri Girdiniz !!" << endl;
}

void Kitap_200707069::Add(Kitap_200707069 books[], int numberOfBook, Kitap_200707069 book) // Add book
{
	// Business Rules!!
	string messages[] = {"\n!! Kitap �smi T�rk�e Karakter Ve Sembol ��eremez !!", "\n!! Yazar �smi T�rk�e Karakter Ve Sembol ��eremez !!",  "\n!! Kitap �smi En Fazla 50 Karakter Olabilir !!", "\n!! Yazar �smi En Fazla 50 Karakter Olabilir !!", "\n!! Kitap Daha �nce Eklenmi�, Bu Kitab� Tekrar Ekleyemezsin !!" };
	bool rules[] = {
		IsValidString(book.bookName),
		IsValidString(book.writerName),
		NumberOfCharacters(book.bookName) < 50,
		NumberOfCharacters(book.writerName) < 50,
		IsBookExist(books, numberOfBook, book.writerName, book.bookName)
	};

	string message;
	bool isValidBusinessRules = Kitap_200707069::RunBusinessRules(rules, messages, 5, message); // �� kurallar� eklendik�e dizi boyutu de�i�tirilmelidir! Dinamik de�il!

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is an invalid rule.
	}

	for (int i = 0; i < numberOfBook; i++)
	{
		if (books[i].id == -1)
		{
			book.id = i + 1;
			book.userId = -1;
			book.status = "Unhold";
			book.description = "A��klama Eklenmemi�";

			books[i] = book;
			cout << "\n-- Kitap Ba�ar�l� Bir �ekilde Eklendi --" << endl;
			return;
		}
	}
}

void Kitap_200707069::Delete(Kitap_200707069 books[], int numberOfBook, int bookId) // Delete book
{
	for (int i = 0; i < numberOfBook; i++)
	{
		if (books[i].id == bookId)
		{
			books[i].id = -1;
			cout << "\n-- Kitap Ba�ar�l� Bir �ekilde Silindi --" << endl;
			return;
		}
	}
	
	cout << "\n!! Yanl�� ID De�eri Girdiniz !!" << endl;

}

void Kitap_200707069::EditBookName(Kitap_200707069 books[], int numberOfBook, int bookId, string bookName)
{
	// Business Rules!!
	string messages[] = { "\n!! Kitap �smi T�rk�e Karakter Ve Sembol ��eremez !!",  "\n!! Kitap �smi En Fazla 50 Karakter Olabilir !!" };
	bool rules[] = {
		IsValidString(bookName),
		NumberOfCharacters(bookName) < 50
	};

	string message;
	bool isValidBusinessRules = Kitap_200707069::RunBusinessRules(rules, messages, 2, message); // �� kurallar� eklendik�e dizi boyutu de�i�tirilmelidir! Dinamik de�il!

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is an invalid rule.
	}

	for (int i = 0; i < numberOfBook; i++)
	{
		if (books[i].GetId() == bookId && bookId != 0 && bookId != -1)
		{
			books[i].SetBookName(bookName);
			cout << "\n--Kitap �smi Ba�ar�l� Bir �ekilde G�ncellenmi�tir --" << endl;
			return;
		}
	}

	cout << "\n!! Yanl�� ID De�eri Girdiniz, Kitap �smi G�ncellenemedi !!" << endl;
}

void Kitap_200707069::EditWriterName(Kitap_200707069 books[], int numberOfBook, int bookId, string writerName)
{
	// Business Rules!!
	string messages[] = { "\n!! Yazar �smi T�rk�e Karakter Ve Sembol ��eremez !!",  "\n!! Yazar �smi En Fazla 30 Karakter Olabilir !!" };
	bool rules[] = {
		IsValidString(writerName),
		NumberOfCharacters(writerName) < 30
	};

	string message;
	bool isValidBusinessRules = Kitap_200707069::RunBusinessRules(rules, messages, 2, message); // �� kurallar� eklendik�e dizi boyutu de�i�tirilmelidir! Dinamik de�il!

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is an invalid rule.
	}

	for (int i = 0; i < numberOfBook; i++)
	{
		if (books[i].GetId() == bookId && bookId != 0 && bookId != -1)
		{
			books[i].SetWriterName(writerName);
			cout << "\n--Yazar �smi Ba�ar�l� Bir �ekilde G�ncellenmi�tir --" << endl;
			return;
		}
	}

	cout << "\n!! Yanl�� ID De�eri Girdiniz, Yazar �smi G�ncellenemedi !!" << endl;
}

void Kitap_200707069::EditDescription(Kitap_200707069 books[], int numberOfBook, int bookId, string description)
{
	// Business Rules!!
	string messages[] = { "\n!! A��klama T�rk�e Karakter Ve Sembol ��eremez !!",  "\n!! A��klama En Fazla 100 Karakter Olabilir !!" };
	bool rules[] = {
		IsValidString(description),
		NumberOfCharacters(description) < 100
	};

	string message;
	bool isValidBusinessRules = Kitap_200707069::RunBusinessRules(rules, messages, 2, message); // �� kurallar� eklendik�e dizi boyutu de�i�tirilmelidir! Dinamik de�il!

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is an invalid rule.
	}

	for (int i = 0; i < numberOfBook; i++)
	{
		if (books[i].GetId() == bookId && bookId != 0 && bookId != -1)
		{
			books[i].SetDescription(description);
			cout << "\n--A��klama Ba�ar�l� Bir �ekilde G�ncellenmi�tir --" << endl;
			return;
		}
	}

	cout << "\n!! Yanl�� ID De�eri Girdiniz, Kitab�n A��klamas� G�ncellenemedi !!" << endl;
}

// Setter Methods
void Kitap_200707069::SetId(int id)
{
	Kitap_200707069::id = id;
}

void Kitap_200707069::SetUserId(int userId)
{
	Kitap_200707069::userId = userId;
}

void Kitap_200707069::SetBookName(string bookName)
{
	Kitap_200707069::bookName = bookName;
}

void Kitap_200707069::SetWriterName(string writerName)
{
	Kitap_200707069::writerName = writerName;
}

void Kitap_200707069::SetStatus(string status)
{
	Kitap_200707069::status = status;
}

void Kitap_200707069::SetDescription(string description)
{
	Kitap_200707069::description = description;
}

// Getter Methods
int Kitap_200707069::GetId()
{
	return Kitap_200707069::id;
}

int Kitap_200707069::GetUserId()
{
	return Kitap_200707069::userId;
}

string Kitap_200707069::GetBookName()
{
	return Kitap_200707069::bookName;
}

string Kitap_200707069::GetWriterName()
{
	return Kitap_200707069::writerName;
}

string Kitap_200707069::GetStatus()
{
	return Kitap_200707069::status;
}

string Kitap_200707069::GetDescription()
{
	return Kitap_200707069::description;
}

// Helper Methods
bool Kitap_200707069::IsBookExist(Kitap_200707069 books[], int size, string writerName, string bookName) // Book must have contained on my array (database)
{
	for (int i = 0; i < size; i++)
	{
		if (books[i].bookName == bookName && books[i].writerName == writerName)
		{
			return false; // Book exist!
		}
	}
	return true; // Book not exist!
}

bool Kitap_200707069::IsValidString(string stringData) // String must have not contain turkish character and number!
{
	char validCharacters[] = { 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' };

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

int Kitap_200707069::NumberOfCharacters(string stringData)
{
	int counter = 0;
	for (int i = 0; stringData[i] != '\0'; i++)
	{
		counter++;
	}

	return counter;
}

// �� kurallar�n� �al��t�rmak i�in haz�rlad���m helper method. Parametre olarak ald��� i� kurallar� dizisini kontrol eder, belirledi�im kurallara uymuyorsa false d�nderir. Mesaj olarak da hangi kurala uymuyorsa referans olarak gelen de�i�kene o kural�n mesaj�n� atar!
bool Kitap_200707069::RunBusinessRules(bool rules[], string messages[], int size, string& message)
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
