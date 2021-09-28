#ifndef UYE_200707069
#define UYE_200707069

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

#include "Kitap_200707069.h"
#include "Kullanici_200707069.h"

using namespace std;

class Uye_200707069 :
    public Kullanici_200707069
{
public:
	bool Login(Uye_200707069 member, string userName, string password);

	void SearchBook(Kitap_200707069 books[], int size, string search);
	void TakeBorrowBook(Kitap_200707069 books[], int size, int bookId, Uye_200707069 member); // member: Hangi kullanýcý iþlem yapýyor?
	void ReturnBook(Kitap_200707069 books[], int size, int bookId, int userId); // userId: Hangi kullanýcý iþlem yapýyor?
	void GetAllBook(Kitap_200707069 books[], int size);

	void GetBookDetail(Kitap_200707069 books[], int size, int bookId);
	void ShowMemberInformations(Uye_200707069 members[], int numberOfMembers, int memberId);

	// Member Operations
	void ChangeName(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string name);
	void ChangeUserName(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string userName);
	void ChangePassword(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member, string password);

	// Helper Methods
	Uye_200707069 GetByUserName(Uye_200707069 members[], int numberOfMembers, string userName);

	// Getter Methods
	string GetMemberType();

	// Setter Methods
	void SetMemberType(string memberType); 

private:
	string memberType;

	// Helper Methods
	bool IsExistUser(Uye_200707069 members[], int size, int id);
	bool IsMemberCanBorrowBook(Kitap_200707069 books[], int size, Uye_200707069 member);
};

#endif // UYE_200707069