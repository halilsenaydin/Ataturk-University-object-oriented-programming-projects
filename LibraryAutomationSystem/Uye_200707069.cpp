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

#include "Uye_200707069.h"

bool Uye_200707069::Login(Uye_200707069 member, string userName, string password)
{
	if (Kullanici_200707069::IsValidUser(member, userName, password))
	{
		return true;
	}

	return false;
}

void Uye_200707069::SearchBook(Kitap_200707069 books[], int size, string search)
{
	int counter = 0;

	cout << endl;
	for (int i = 0; i < size; i++)
	{
		if (books[i].GetBookName() == search || books[i].GetWriterName() == search) // Aranan ifade yazar veya kitap ismi mi?
		{
			cout << books[i].GetId() << "\t" << books[i].GetBookName() << "\t" << books[i].GetWriterName() << "\t" << books[i].GetStatus() << endl;
			counter++;
		}
	}

	if (counter == 0)
	{
		cout << "\n!! Aradýðýnýz Ýsimde Kitap Veya Yazar Bulunamadý !!" << endl;
	}
}

void Uye_200707069::TakeBorrowBook(Kitap_200707069 books[], int size, int bookId, Uye_200707069 member)
{
	// Business Rules!!
	string messages[] = { "\n!! Daha Fazla Kitap Ödünç Alamazsýnýz !!"};
	bool rules[] = {
		IsMemberCanBorrowBook(books, size, member) // Member cann't borrow more books!
	};

	string message;
	bool isValidBusinessRules = Kullanici_200707069::RunBusinessRules(rules, messages, 1, message); // Ýþ kurallarý eklendikçe dizi boyutu deðiþtirilmelidir! Dinamik deðil!

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return;
	}

	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (books[i].GetId() == bookId && books[i].GetStatus() == "Unhold") // Ödünç Alýnacak kitap geçerli mi? (Id ile eþleþti mi?, userId geçerli mi?, Kitap ödünç alýnmýþ mý?)
		{
			books[i].SetUserId(member.GetId());
			books[i].SetStatus("Hold");
			cout << "\n-- Kitabý Baþarýlý Bir Þekilde Ödünç Aldýnýz --" << endl;
			counter++;
			return;
		}
	}

	cout << "\n!! Ödünç Alýnmýþ Bir Kitap Ödünç Verilemez !!" << endl;
}

void Uye_200707069::ReturnBook(Kitap_200707069 books[], int size, int bookId, int userId)
{
	for (int i = 0; i < size; i++)
	{
		if (books[i].GetId() == bookId && userId >= 0 && books[i].GetStatus() == "Hold" && books[i].GetUserId() == userId) // Ýade edilecek kitap geçerli mi?
		{
			books[i].SetUserId(-1); // Ýade edilen kitap, herhangi bir kullanýcýya ait olamaz.
			books[i].SetStatus("Unhold");
			cout << "\n-- Kitabý Baþarýlý Bir Þekilde Ýade Ettiniz --" << endl;
			return;
		}
	}

	cout << "\n!! Ödünç Almadýðýnýz Bir Kitabý Ýade Edemezsiniz !!" << endl;
}

void Uye_200707069::GetAllBook(Kitap_200707069 books[], int size)
{
	Kitap_200707069 kitap;
	kitap.GetAll(books, size);
}

void Uye_200707069::GetBookDetail(Kitap_200707069 books[], int size, int bookId)
{
	Kitap_200707069 tempBook;
	tempBook.GetBookDetail(books, size, bookId);
}

void Uye_200707069::ShowMemberInformations(Uye_200707069 members[], int numberOfMembers, int memberId)
{
	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].id == memberId && memberId != -1 && memberId != 0)
		{
			// Geliþtirilebilir, daha sonra geliþtir!
			cout << "\n\tAdýnýz: " << members[i].GetName() << "\n\tKullanýcý Adýnýz: " << members[i].GetUserName() << endl;
		}
	}
}

void Uye_200707069::ChangeName(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string name)
{
	// Business Rules!!
	string messages[] = {"\n!! Kullanýcýnýn Ýsmi Türkçe Karakter Ve Sembol Ýçeremez !!", "\n!! Kullanýcýnýn Ýsmi En Fazla 50 Karakter Ýçerebilir !!" };
	bool rules[] = {
		Kullanici_200707069::IsValidString(name),
		Kullanici_200707069::NumberOfCharacters(name) < 50
	};

	string message;
	bool isValidBusinessRules = Kullanici_200707069::RunBusinessRules(rules, messages, 2, message);

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is a invalid rule. Do not update name in array
	}

	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() == member.GetId())
		{
			member.SetName(name); // Updated name
			members[i] = member;
			cout << "\n-- Kullanýcýnýn Ýsmi Baþarýlý Bir Þekilde Güncellendi --" << endl;
			return;
		}
	}
}

void Uye_200707069::ChangeUserName(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string userName)
{
	Uye_200707069 tempMember;
	Uye_200707069 tempUser = tempMember.GetByUserName(members, numberOfMembers, userName);

	// Business Rules!!
	string messages[] = {"\n!! Kullanýcý Adý Boþluk Karakteri Ýçeremez !!", "\n!! Kullanýcý Adý Türkçe Karakter Ve Sembol Ýçeremez !!", "\n!! Kullanýcý Adý En Fazla 30 Karakter Ýçerebilir !!", "\n!! Kullanýcý Adý Daha Önce Alýnmýþ !!" };
	bool rules[] = {
		Kullanici_200707069::IsValidUserName(userName),
		Kullanici_200707069::IsValidString(userName),
		Kullanici_200707069::NumberOfCharacters(userName) < 30,
		IsExistUser(members, numberOfMembers, tempUser.GetId())
	};

	string message;
	bool isValidBusinessRules = Kullanici_200707069::RunBusinessRules(rules, messages, 4, message);

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is a invalid rule. Do not update userName in array
	}

	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() == member.GetId())
		{
			member.SetUserName(userName); // Updated userName
			members[i] = member;
			cout << "\n-- Kullanýcý Adý Baþarýlý Bir Þekilde Güncellendi --" << endl;
			return;
		}
	}
}

void Uye_200707069::ChangePassword(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string password)
{
	// Business Rules!!
	string messages[] = {"\n!! Parola Türkçe Karakter Ve Sembol Ýçeremez !!", "\n!! Parola En Az 14 Karakterli Ve Boþluk Ýçermemelidir !!" };
	bool rules[] = {
		Kullanici_200707069::IsValidString(password),
		IsValidPassword(password)
	};

	string message;
	bool isValidBusinessRules = Kullanici_200707069::RunBusinessRules(rules, messages, 2, message);

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return; // There is a invalid rule. Do not update password in array
	}

	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetId() == member.GetId())
		{
			member.SetPassword(password); // Updated password
			members[i] = member;
			cout << "\n-- Kullanýcý Parolasý Baþarýlý Bir Þekilde Güncellendi --" << endl;
			return;
		}
	}
}

// Getter Methods
string Uye_200707069::GetMemberType()
{
	return Uye_200707069::memberType;
}

// Setter Methods
void Uye_200707069::SetMemberType(string memberType)
{
	Uye_200707069::memberType = memberType;
}

// Helper Methods - public -
Uye_200707069 Uye_200707069::GetByUserName(Uye_200707069 members[], int numberOfMembers, string userName) // Kullanýcý adýna göre Uye getir.
{
	for (int i = 0; i < numberOfMembers; i++)
	{
		if (members[i].GetUserName() == userName)
		{
			return members[i];
		}
	}

	return Uye_200707069();
}

// Helper Methods - private -
bool Uye_200707069::IsExistUser(Uye_200707069 members[], int numberOfMembers, int id) // User must be registered!
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

bool Uye_200707069::IsMemberCanBorrowBook(Kitap_200707069 books[], int size, Uye_200707069 member) // Member cann't borrow more books!
{
	int counter = 1;
	for (int i = 0; i < size; i++)
	{
		if (books[i].GetUserId() == member.GetId())
		{
			counter++;
		}
	}

	if (member.memberType == "Ogrenci" && counter <= 5)
	{
		return true;
	}
	else if (member.memberType == "Ogretim Elemani" && counter <= 10)
	{
		return true;
	}
	else if (member.memberType == "Personel" && counter <= 3)
	{
		return true;
	}

	return false;
}