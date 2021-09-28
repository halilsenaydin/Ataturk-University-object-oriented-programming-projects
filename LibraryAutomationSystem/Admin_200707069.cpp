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
	string messages[] = { "\n!! Kullanýcýnýn Ýsmi Türkçe Karakter Ve Sembol Ýçeremez !!",  "\n!! Kullanýcý Adý Türkçe Karakter ve Sembol Ýçeremez !!", "\n!! Kullanýcý Adý Boþluk Karakteri Ýçeremez !!", "\n!! Kullanýcýnýn Ýsmi En Fazla 50 Karakter Ýçerebilir !!", "\n!! Kullanýcý Adý En Fazla 30 Karakter Ýçerebilir !!" , "\n!! Kullanýcý Daha Önce Eklenmiþ, Tekrar Eklenemez !!"};
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
			cout << "\n-- Kullanýcý Baþarýlý Bir Þekilde Eklendi --" << endl;
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
			cout << "\n-- Üye Baþarýlý Bir Þekilde Silindi --" << endl;
			return;
		}
	}

	cout << "\n!! Yanlýþ ID Deðeri Girdiniz" << endl;
}

void Admin_200707069::GetAllMember(Uye_200707069 members[], int numberOfMembers)
{
	int counter = 0;
	cout << endl;
	cout << setw(3) << left << "ID" << setw(50) << left << "Ýsim" << setw(30) << left << "Kullanýcý Adý" << setw(15) << left << "Uye Tipi" << endl;
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
		cout << "\n!! Henüz Bir Kullanýcý Yoktur !!" << endl;
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