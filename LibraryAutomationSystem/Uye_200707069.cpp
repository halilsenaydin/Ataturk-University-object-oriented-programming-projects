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
		cout << "\n!! Arad���n�z �simde Kitap Veya Yazar Bulunamad� !!" << endl;
	}
}

void Uye_200707069::TakeBorrowBook(Kitap_200707069 books[], int size, int bookId, Uye_200707069 member)
{
	// Business Rules!!
	string messages[] = { "\n!! Daha Fazla Kitap �d�n� Alamazs�n�z !!"};
	bool rules[] = {
		IsMemberCanBorrowBook(books, size, member) // Member cann't borrow more books!
	};

	string message;
	bool isValidBusinessRules = Kullanici_200707069::RunBusinessRules(rules, messages, 1, message); // �� kurallar� eklendik�e dizi boyutu de�i�tirilmelidir! Dinamik de�il!

	if (!isValidBusinessRules)
	{
		cout << message << endl;
		return;
	}

	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (books[i].GetId() == bookId && books[i].GetStatus() == "Unhold") // �d�n� Al�nacak kitap ge�erli mi? (Id ile e�le�ti mi?, userId ge�erli mi?, Kitap �d�n� al�nm�� m�?)
		{
			books[i].SetUserId(member.GetId());
			books[i].SetStatus("Hold");
			cout << "\n-- Kitab� Ba�ar�l� Bir �ekilde �d�n� Ald�n�z --" << endl;
			counter++;
			return;
		}
	}

	cout << "\n!! �d�n� Al�nm�� Bir Kitap �d�n� Verilemez !!" << endl;
}

void Uye_200707069::ReturnBook(Kitap_200707069 books[], int size, int bookId, int userId)
{
	for (int i = 0; i < size; i++)
	{
		if (books[i].GetId() == bookId && userId >= 0 && books[i].GetStatus() == "Hold" && books[i].GetUserId() == userId) // �ade edilecek kitap ge�erli mi?
		{
			books[i].SetUserId(-1); // �ade edilen kitap, herhangi bir kullan�c�ya ait olamaz.
			books[i].SetStatus("Unhold");
			cout << "\n-- Kitab� Ba�ar�l� Bir �ekilde �ade Ettiniz --" << endl;
			return;
		}
	}

	cout << "\n!! �d�n� Almad���n�z Bir Kitab� �ade Edemezsiniz !!" << endl;
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
			// Geli�tirilebilir, daha sonra geli�tir!
			cout << "\n\tAd�n�z: " << members[i].GetName() << "\n\tKullan�c� Ad�n�z: " << members[i].GetUserName() << endl;
		}
	}
}

void Uye_200707069::ChangeName(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string name)
{
	// Business Rules!!
	string messages[] = {"\n!! Kullan�c�n�n �smi T�rk�e Karakter Ve Sembol ��eremez !!", "\n!! Kullan�c�n�n �smi En Fazla 50 Karakter ��erebilir !!" };
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
			cout << "\n-- Kullan�c�n�n �smi Ba�ar�l� Bir �ekilde G�ncellendi --" << endl;
			return;
		}
	}
}

void Uye_200707069::ChangeUserName(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string userName)
{
	Uye_200707069 tempMember;
	Uye_200707069 tempUser = tempMember.GetByUserName(members, numberOfMembers, userName);

	// Business Rules!!
	string messages[] = {"\n!! Kullan�c� Ad� Bo�luk Karakteri ��eremez !!", "\n!! Kullan�c� Ad� T�rk�e Karakter Ve Sembol ��eremez !!", "\n!! Kullan�c� Ad� En Fazla 30 Karakter ��erebilir !!", "\n!! Kullan�c� Ad� Daha �nce Al�nm�� !!" };
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
			cout << "\n-- Kullan�c� Ad� Ba�ar�l� Bir �ekilde G�ncellendi --" << endl;
			return;
		}
	}
}

void Uye_200707069::ChangePassword(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string password)
{
	// Business Rules!!
	string messages[] = {"\n!! Parola T�rk�e Karakter Ve Sembol ��eremez !!", "\n!! Parola En Az 14 Karakterli Ve Bo�luk ��ermemelidir !!" };
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
			cout << "\n-- Kullan�c� Parolas� Ba�ar�l� Bir �ekilde G�ncellendi --" << endl;
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
Uye_200707069 Uye_200707069::GetByUserName(Uye_200707069 members[], int numberOfMembers, string userName) // Kullan�c� ad�na g�re Uye getir.
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