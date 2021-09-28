#ifndef UYE_200707069
#define UYE_200707069

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
#include "Kullanici_200707069.h"

using namespace std;

class Uye_200707069 :
    public Kullanici_200707069
{
public:
	bool Login(Uye_200707069 member, string userName, string password);

	void SearchBook(Kitap_200707069 books[], int size, string search);
	void TakeBorrowBook(Kitap_200707069 books[], int size, int bookId, Uye_200707069 member); // member: Hangi kullan�c� i�lem yap�yor?
	void ReturnBook(Kitap_200707069 books[], int size, int bookId, int userId); // userId: Hangi kullan�c� i�lem yap�yor?
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