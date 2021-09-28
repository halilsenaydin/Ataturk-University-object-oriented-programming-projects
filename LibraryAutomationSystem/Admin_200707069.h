#ifndef ADMIN_200707069
#define ADMIN_200707069

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