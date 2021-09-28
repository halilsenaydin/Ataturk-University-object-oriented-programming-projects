#ifndef ADMIN_200707069
#define ADMIN_200707069

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

#include "Kullanici_200707069.h"
#include "Kitap_200707069.h"
#include "Uye_200707069.h"

class Admin_200707069 :
    public Kullanici_200707069
{
public:
	Admin_200707069();
	bool Login(Admin_200707069 admin, string userName, string password);

	void AddMember(Uye_200707069 members[], int numberOfMembers, Uye_200707069 member);
	void DeleteMember(Uye_200707069 members[], int numberOfMembers, int memberId);
	void GetAllMember(Uye_200707069 members[], int numberOfMembers);

	void AddBook(Kitap_200707069 books[], int numberOfBook, Kitap_200707069 book);
	void DeleteBook(Kitap_200707069 books[], int numberOfBook, int bookId);
	void GetAllBook(Kitap_200707069 books[], int size);

	void EditBookName(Kitap_200707069 books[], int numberOfBook, int bookId, string bookName);
	void EditWriterName(Kitap_200707069 books[], int numberOfBook, int bookId, string writerName);
	void EditDescription(Kitap_200707069 books[], int numberOfBook, int bookId, string description);

private:
	// Helper Methods
	bool IsExistUser(Uye_200707069 members[], int size, int id);
};

#endif // ADMIN_200707069