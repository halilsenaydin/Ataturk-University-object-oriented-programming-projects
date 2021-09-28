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

#include "Admin_200707069.h"

Admin_200707069::Admin_200707069()
{
	Admin_200707069::SetUserName("admin");
	Admin_200707069::SetPassword("1234");
}

bool Admin_200707069::Login(Admin_200707069 admin, string userName, string password) // user must input valid username and password
{
	if (Kullanici_200707069::IsValidUser(admin, userName, password))
	{
		return true;
	}

	return false;
}

void Admin_200707069::AddMember(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member) // Add Member To Array
{
	member.SetPassword("temp"); // Default password

	Uye_200707069 tempMember;
	Kullanici_200707069 tempUser = tempMember.GetByUserName(members, numberOfMembers, member.GetUserName());

	// Business Rules!!
	string messages[] = { "\n!! Kullan�c�n�n �smi T�rk�e Karakter Ve Sembol ��eremez !!",  "\n!! Kullan�c� Ad� T�rk�e Karakter ve Sembol ��eremez !!", "\n!! Kullan�c� Ad� Bo�luk Karakteri ��eremez !!", "\n!! Kullan�c�n�n �smi En Fazla 50 Karakter ��erebilir !!", "\n!! Kullan�c� Ad� En Fazla 30 Karakter ��erebilir !!" , "\n!! Kullan�c� Daha �nce Eklenmi�, Tekrar Eklenemez !!"};
	bool rules[] = {
		Kullanici_200707069::IsValidString(member.GetName()),
		Kullanici_200707069::IsValidString(member.GetUserName()),
		Kullanici_200707069::IsValidUserName(member.GetUserName()),
		Kullanici_200707069::NumberOfCharacters(member.GetName()) < 50, // name must have not greater 50 character
		Kullanici_200707069::NumberOfCharacters(member.GetUserName()) < 30, // userName must have not greater 30 character
		IsExistUser(members, numberOfMembers, tempUser.GetId())
	};

	string message;
	bool isValidBusinessRules = Kullanici_200707069::RunBusinessRules(rules, messages, 6, message);

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // Do not in add array! There is a invalid rule.
	}

	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() == -1)
		{
			member.SetId(i + 1);
			members[i] = member;
			cout << "\n-- Kullan�c� Ba�ar�l� Bir �ekilde Eklendi --" << endl;
			return;
		}
	}
}

void Admin_200707069::DeleteMember(Uye_200707069 members[], int numberOfMembers, int memberId) // Delete Member To Array
{
	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() == memberId)
		{
			members[i].SetId(-1);
			cout << "\n-- �ye Ba�ar�l� Bir �ekilde Silindi --" << endl;
			return;
		}
	}

	cout << "\n!! Yanl�� ID De�eri Girdiniz" << endl;
}

void Admin_200707069::GetAllMember(Uye_200707069 members[], int numberOfMembers)
{
	int counter = 0;
	cout << endl;
	cout << setw(3) << left << "ID" << setw(50) << left << "�sim" << setw(30) << left << "Kullan�c� Ad�" << setw(15) << left << "Uye Tipi" << endl;
	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() != -1)
		{
			cout << setw(3) << left << members[i].GetId() << setw(50) << left << members[i].GetName() << setw(30) << left << members[i].GetUserName() << setw(15) << left << members[i].GetMemberType() << endl;
			counter++;
		}
	}

	if (counter == 0)
	{
		cout << "\n!! Hen�z Bir Kullan�c� Yoktur !!" << endl;
	}
}
 
void Admin_200707069::AddBook(Kitap_200707069 books[], int numberOfBook, Kitap_200707069 book) // Add Book To Array
{
	Kitap_200707069 tempBook;
	tempBook.Add(books, numberOfBook, book);
}

void Admin_200707069::DeleteBook(Kitap_200707069 books[], int numberOfBook, int bookId) // Delete Book To Array
{
	Kitap_200707069 tempBook;
	tempBook.Delete(books, numberOfBook, bookId);
}

void Admin_200707069::GetAllBook(Kitap_200707069 books[], int size)
{
	Kitap_200707069 tempBook;
	tempBook.GetAll(books, size);
}

void Admin_200707069::EditBookName(Kitap_200707069 books[], int numberOfBook, int bookId, string bookName)
{
	Kitap_200707069 tempBook;
	tempBook.EditBookName(books, numberOfBook, bookId, bookName);
}

void Admin_200707069::EditWriterName(Kitap_200707069 books[], int numberOfBook, int bookId, string writerName)
{
	Kitap_200707069 tempBook;
	tempBook.EditWriterName(books, numberOfBook, bookId, writerName);
}

void Admin_200707069::EditDescription(Kitap_200707069 books[], int numberOfBook, int bookId, string description)
{
	Kitap_200707069 tempBook;
	tempBook.EditDescription(books, numberOfBook, bookId, description);
}

// Helper Methods
bool Admin_200707069::IsExistUser(Uye_200707069 members[], int numberOfMembers, int id) // User must be registered!
{
	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() == id && id != -1)
		{
			return false; // Exist user
		}
	}

	return true; // Not exist user
}