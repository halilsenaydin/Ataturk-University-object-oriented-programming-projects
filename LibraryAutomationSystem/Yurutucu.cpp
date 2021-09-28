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

#include<clocale>

#include "Kitap_200707069.h"
#include "Admin_200707069.h"
#include "Uye_200707069.h"

using namespace std;

void AdminMenu(Kitap_200707069[], Uye_200707069[], int, string, string);
void MemberMenu(Kitap_200707069[], Uye_200707069[], int, string, string);
void MemberOperations(Uye_200707069[], int, Uye_200707069);
void EditBook(Kitap_200707069[], int);
void CreateDefaultBook(Kitap_200707069[], int);
void CreateDefaultMembers(Uye_200707069[], int);
void ForgotPassword();

int main() {
	setlocale(LC_ALL, "turkish");

	cout << "\n\t\t-- Abuziddin Kütüphanesinin Otomasyon Sistemi --\n" << endl;

	// Varsayýlan kitap tanýmlarý. (Bunlar db'de var gibi düþünülebilir.) [Fonksiyonda Tanýmlý!]
	Kitap_200707069 books[100];
	CreateDefaultBook(books, 100);

	// Varsayýlan kullanýcý tanýmlarý.
	Uye_200707069 members[100];
	CreateDefaultMembers(members, 100);

	bool loop = true;
	do
	{
		string userName;
		string password;

		// menu
		int selection;
		cout << "\n 1- Admin Giriþi \n 2- Üye Giriþi \n 3- Çýkýþ" << endl;
		cout << " Menüden Bir Ýþlem Seçin Ve Devam Edin: "; cin >> selection;

		switch (selection)
		{
		case 1:
			cout << "\nAdmin Kullanýcý Adýný Girin: "; getline(cin, userName);
			getline(cin, userName);
			cout << "Admin Þifresini Girin: "; getline(cin, password);
			AdminMenu(books, members, 100, userName, password);
			break;

		case 2:
			cout << "\nKullanýcý Adýnýzý Girin: "; getline(cin, userName);
			getline(cin, userName);
			cout << "Kullanýcý Þifrenizi Girin: "; getline(cin, password);
			MemberMenu(books, members, 100, userName, password);
			break;

		case 3:
			loop = false;
			break;

		default:
			cout << "\nSen Robot Musun? Menüden Bir Ýþlem Seç !!" << endl;
			break;
		}
	} while (loop);

	return 0;
}

void AdminMenu(Kitap_200707069 books[], Uye_200707069 members[], int size, string userName, string password)
{
	bool loopForAdminMenu = true;

	Admin_200707069 admin;
	if (admin.Login(admin, userName, password))
	{
		cout << "\nAdmin Kullanýcýsý Olarak Giriþ Yaptýnýz!" << endl;

		int selection;

		do
		{
			// Admin Menu
			cout << "\n\t 1- Kitap Ekle \n\t 2- Kitap Sil \n\t 3- Kitaplarý Listele \n\t 4- Kitap Bilgilerini Düzenle \n\t 5- Üye Ekle \n\t 6- Üyeleri Listele \n\t 7- Üyeleri Sil \n\t 8- Çýkýþ" << endl;
			cout << "Menüden Bir Ýþlem Seçin Ve Devam Edin: "; cin >> selection;

			// Bu case'lerin her biri bir buton aslýnda!!
			switch (selection)
			{
			case  1:
				{
					Kitap_200707069 book; // Create a instance

					string bookName, writerName;
					cout << "Kitabýn Ýsmini Girin: "; getline(cin, bookName);
					getline(cin, bookName);
					cout << "Kitabýn Yazarýnýn Ýsmini Girin: "; getline(cin, writerName);

					book.SetBookName(bookName);
					book.SetWriterName(writerName);
					admin.AddBook(books, size, book);

					break;
				}
			case 2:
				{
					Kitap_200707069 book; // Create a instance
					int bookId;

					book.GetAll(books, size);
					cout << "Yukarýdaki Kitaplardan Silmek Ýstediðiniz Bir Kitabýn ID Deðerini Girin: "; cin >> bookId;

					admin.DeleteBook(books, size, bookId);

					break;
				}
			case 3:
				{
					admin.GetAllBook(books, size);
					break;
				}
			case 4:
				{
					EditBook(books, size);
					break;
				}
			case 5:
				{
					Uye_200707069 user; // Create a instance, Uye eklemek için uye instance'i oluþturmak gerek!

					string name;
					string userName;
					int memberType;

					cout << "Kullanýcý Ýsmini Girin: "; getline(cin, name);
					getline(cin, name);
					cout << "Kullanýcýnýn Kullanýcý Adýný Girin: "; getline(cin, userName);

					bool boolForMemberType = true;
					do
					{
						cout << "\n 1- Öðrenci\n 2- Personel\n 3- Öðretim Elemaný" << endl;
						cout << "Üye Tipini Seçin: "; cin >> memberType;

						if (memberType == 1)
						{
							user.SetMemberType("Ogrenci");
							boolForMemberType = false;
						}
						else if (memberType == 2)
						{
							user.SetMemberType("Personel");
							boolForMemberType = false;
						}
						else if (memberType == 3)
						{
							user.SetMemberType("Ogretim Elemani");
							boolForMemberType = false;
						}
						else
						{
							cout << "\n!! Geçerli Bir Üye Tipi Girin !!" << endl;
						}

					} while (boolForMemberType);

					user.SetName(name);
					user.SetUserName(userName);

					admin.AddMember(members, 100, user);

					break;
				}
			case 6:
				{
					admin.GetAllMember(members, 100);
					break;
				}
			case 7:
				{
					int userId;

					admin.GetAllMember(members, 100);
					cout << "Yukarýdaki Kullanýcýlardan Silmek Ýstediðiniz Bir Kullanýcýnýn ID Deðerini Girin: "; cin >> userId;

					admin.DeleteMember(members, 100, userId);

					break;
				}
			case 8:
				{
					loopForAdminMenu = false; // Çýkýþ, ana menüye dön.
					break;
				}
			default:
				{
					cout << "\n!! Sadece Menüdeki Ýþlemleri Seçebilirsiniz !!" << endl;
					break;
				}
			}
		} while (loopForAdminMenu);
	}
	else
	{
		cout << "\n!! Kullanýcý Adýnýz Veya Þifreniz Yanlýþ !!" << endl;
		ForgotPassword();
		return;
	}
}

void MemberMenu(Kitap_200707069 books[], Uye_200707069 members[], int size, string userName, string password)
{
	Uye_200707069 member;

	Uye_200707069 tempMember = member.GetByUserName(members, size, userName); // Local storage..
	if (!member.Login(tempMember, userName, password))
	{
		cout << "\n!! Kullanýcý Adýnýz Veya Þifreniz Yanlýþ !!" << endl;
		ForgotPassword();
		return; // wrong userName, or password
	}

	cout << "\n" << userName << " Kullanýcý Adý Ýle Giriþ Yaptýnýz!" << endl;

	int selection;

	bool loopForMemberMenu = true;
	do
	{
		// Member Menu
		cout << "\n\t 1- Kitap Ara \n\t 2- Kitap Ödünç Al \n\t 3- Kitaplarý Ýade Et \n\t 4- Kitaplarý Listele \n\t 5- Kitap Detayýna Git \n\t 6- Üyelik Ýþlemleri \n\t 7- Üyelik Bilgileri \n\t 8- Çýkýþ" << endl;
		cout << "Menüden Bir Ýþlem Seçin Ve Devam Edin: "; cin >> selection;

		// Bu case'lerin her biri bir buton aslýnda!!
		switch (selection)
		{
		case 1:
			{
				string search;

				cout << "Kitabýn Ýsmini Girin Veya Yazarýn Ýsmini Girin: "; getline(cin, search);
				getline(cin, search);

				member.SearchBook(books, size, search);
				break;
			}
		case 2:
			{
				int bookId;
				member.GetAllBook(books, size);
				cout << "Yukarýdaki Kitaplardan Ödünç Almak Ýstediðiniz Bir Kitabýn ID Deðerini Girin: "; cin >> bookId;

				member.TakeBorrowBook(books, size, bookId, tempMember);
				break;
			}

		case 3:
			{
				int bookId;
				member.GetAllBookOfUser(books, size, tempMember.GetId());

				cout << "Yukarýdaki Kitaplardan Ýade Etmek Ýstediðiniz Bir Kitabýn ID Deðerini Girin: "; cin >> bookId;
				member.ReturnBook(books, size, bookId, tempMember.GetId());
				break;
			}

		case 4:
			{
				member.GetAllBook(books, size);
				break;
			}

		case 5:
			{
				int bookId;
				member.GetAllBook(books, size);
				cout << "Yukarýdaki Kitaplardan Detaylarýný Ýstediðiniz Bir Kitabýn ID Deðerini Girin: "; cin >> bookId;

				member.GetBookDetail(books, size, bookId);
				break;
			}

		case 6:
			{

				MemberOperations(members, size, tempMember);
				break;
			}

		case 7:
			{
				member.ShowMemberInformations(members, size, tempMember.GetId());
				break;
			}

		case 8:
			{
				loopForMemberMenu = false;
				break;
			}

		default:
			{
				cout << "\n 'Bir seçim yapmanýz gerektiðinde,seçmemek de bir seçimdir.\n !! Sadece Menüdeki Ýþlemleri Seçebilirsiniz !!" << endl;
				break;
			}
		}
	} while (loopForMemberMenu);
}

void MemberOperations(Uye_200707069 members[], int size, Uye_200707069 user) // Change name, change userName, change password!
{
	int selection;
	Uye_200707069 tempMember;

	bool loop = true;
	do
	{
		cout << "\n 1- Ýsmini Güncelle\n 2- Kullanýcý Adýný Güncelle\n 3- Þifreni Güncelle\n 4- Kullanýcý Menüsüne Dön" << endl;
		cout << "Yukarýdaki Menüden Bir Ýþlem Seçin: "; cin >> selection;

		switch (selection)
		{
		case 1:
			{
				string name;
				cout << "Yeni Ýsminizi Girin: "; getline(cin, name);
				getline(cin, name);
				tempMember.ChangeName(members, size, user, name);
				break;
			}

		case 2:
			{
				string userName;
				cout << "Yeni Kullanýcý Adýnýzý Girin: "; getline(cin, userName);
				getline(cin, userName);
				tempMember.ChangeUserName(members, size, user, userName);
				break;
			}

		case 3:
			{
				string newPassword,
					tempPassword;

				cout << "Yeni Þifrenizi Girin: "; getline(cin, newPassword);
				getline(cin, newPassword);
				cout << "Þifrenizi Tekrar Girin: "; getline(cin, tempPassword);

				if (newPassword == tempPassword)
				{
					tempMember.ChangePassword(members, size, user, newPassword);
				}
				else
				{
					cout << "\n 'Eðer,ileride bir gün keþke demek istemiyorsan,2 þeyi doðru yaz! yeni þifre, yeni þifre tekrarý.' \n !! Girdiðiniz Parolalar Eþleþmiyor !!" << endl;
				}
				break;
			}

		case 4:
			{
				loop = false;
				break;
			}

		default:
			{
				cout << "\n 'Ne yapmayacaðýna karar vermek, ne yapacaðýna karar vermek kadar önemlidir.' \n !! Geçerli Bir Seçim Yapmadýnýz !!" << endl;
				break;
			}
		}

	} while (loop);
}

void EditBook(Kitap_200707069 books[], int size) {
	Admin_200707069 admin;
	int selection;

	bool loop = true;
	do
	{
		cout << "\n\t 1- Kitap Adýný Düzenle \n\t 2- Kitabýn Yazarýnýn Adýný Düzenle \n\t 3- Kitabýn Açýklamasýný Düzenle \n\t 4- Admin Menüsüne Dön" << endl;
		cout << "\t--> Yukarýdan Bir Ýþlem Seçin: "; cin >> selection;

		switch (selection)
		{
		case 1:
			{
				int bookId;
				string bookName;
				admin.GetAllBook(books, size);
				cout << "Yukarýdaki Kitaplardan Ýsmini Düzenlemek Ýstediðiniz Kitabýn ID'sini Girin: "; cin >> bookId;

				cout << "Yeni Kitap Adýný Girin: "; getline(cin, bookName);
				getline(cin, bookName);

				admin.EditBookName(books, size, bookId, bookName);
				break;
			}
		case 2:
			{
				int bookId;
				string writerName;
				admin.GetAllBook(books, size);
				cout << "Yukarýdaki Kitaplardan Yazar Ýsmini Düzenlemek Ýstediðiniz Kitabýn ID'sini Girin: "; cin >> bookId;

				cout << "Kitabýn Yeni Yazarýnýn Ýsmini Girin: "; getline(cin, writerName);
				getline(cin, writerName);

				admin.EditWriterName(books, size, bookId, writerName);
				break;
			}
		case 3:
			{
				int bookId;
				string description;
				admin.GetAllBook(books, size);
				cout << "Yukarýdaki Kitaplardan Açýklamasýný Düzenlemek Ýstediðiniz Kitabýn ID'sini Girin: "; cin >> bookId;

				cout << "Kitabýn Yeni Açýklamasýný Girin: "; getline(cin, description);
				getline(cin, description);

				admin.EditDescription(books, size, bookId, description);
				break;
			}
		case 4:
			{
				loop = false;
				break;
			}
		default:
			{
				cout << "\n!! Sadece Menüdeki Ýþlemler Seçilebilir !!" << endl;
				break;
			}
		}

	} while (loop);
}

void CreateDefaultBook(Kitap_200707069 books[], int size) {
	for (int i = 0; i < size; i++)
	{
		books[i].SetId(-1);
	}

	Kitap_200707069 matlab;
	matlab.SetId(1);
	matlab.SetWriterName("Deniz Dal");
	matlab.SetStatus("Unhold");
	matlab.SetBookName("Matlab Ile Programlamaya Giris");
	matlab.SetUserId(-1);
	matlab.SetDescription("Kitap sayesinde algoritma temellerini atabilir, programlama icin en iyi bilgiyi edinebilirsiniz. Admin'in tavsiyesidir.");

	Kitap_200707069 myFavoriteBook;
	myFavoriteBook.SetId(2);
	myFavoriteBook.SetWriterName("Erdal Demirkiran");
	myFavoriteBook.SetStatus("Unhold");
	myFavoriteBook.SetBookName("Sadece Aptallar 8 Saat Uyur");
	myFavoriteBook.SetUserId(-1);
	myFavoriteBook.SetDescription("Insan daha az uyuyup daha fazla sey yapabilecekken neden kendimizi kisitliyoruz? Admin'in en sevdiði kitapdýr.");

	Kitap_200707069 utopia;
	utopia.SetId(3);
	utopia.SetWriterName("Thomas More");
	utopia.SetStatus("Unhold");
	utopia.SetBookName("Utopya");
	utopia.SetUserId(-1);
	utopia.SetDescription("Dusler Ulkesi Mi? Kabuslar Ulkesi Mi?");

	Kitap_200707069 notesfromUnderground;
	notesfromUnderground.SetId(4);
	notesfromUnderground.SetWriterName("Fyodor Dostoevsky");
	notesfromUnderground.SetStatus("Unhold");
	notesfromUnderground.SetBookName("Yeraltindan Notlar");
	notesfromUnderground.SetUserId(-1);
	notesfromUnderground.SetDescription("Dostoevsky'yi anlamak icin okumak gereken en önemli sah eserlerdendir..");


	Kitap_200707069 prideAndPrejudice;
	prideAndPrejudice.SetId(5);
	prideAndPrejudice.SetWriterName("Jane Austen");
	prideAndPrejudice.SetStatus("Unhold");
	prideAndPrejudice.SetBookName("Ask Ve Gurur");
	prideAndPrejudice.SetUserId(-1);
	prideAndPrejudice.SetDescription("Abuziddin'in ve lilaH'in en sevdigi kitap.. Aciklamasi yok, cunku yazacak tek kelime bulamadim. Muhtesem otesi bir kitap..");

	Kitap_200707069 inferno;
	inferno.SetId(6);
	inferno.SetWriterName("Dan Brown");
	inferno.SetStatus("Unhold");
	inferno.SetBookName("Cehennem");
	inferno.SetUserId(-1);
	inferno.SetDescription("Avrupa’dan Turkiye’ye uzanan soluksuz bir maceraya atilmaya hazir misiniz?");

	books[0] = matlab;
	books[1] = myFavoriteBook;
	books[2] = utopia;
	books[3] = notesfromUnderground;
	books[4] = prideAndPrejudice;
	books[5] = inferno;
}

void CreateDefaultMembers(Uye_200707069 members[], int size) {
	for (int i = 0; i < size; i++)
	{
		members[i].SetId(-1);
	}

	Uye_200707069 hallbo;
	hallbo.SetId(1);
	hallbo.SetName("Halil Senaydin");
	hallbo.SetPassword("123456");
	hallbo.SetUserName("snydnhll"); // GitHub, you can visit my account and you can give star my repository (github.com/snydnhll)
	hallbo.SetMemberType("Ogrenci");

	Uye_200707069 abuziddin;
	abuziddin.SetId(2);
	abuziddin.SetName("Abuziddin Hasimulkerim");
	abuziddin.SetPassword("123456");
	abuziddin.SetUserName("hasimulkerimAbuziddin");
	abuziddin.SetMemberType("Ogretim Elemani");

	members[0] = hallbo;
	members[1] = abuziddin;
}

void ForgotPassword()
{
	int forgotPassword;
	bool loop = true;
	do
	{
		cout << "\nÞifreni Mi Unuttun? \n\t 1- Evet\n\t 2- Hayýr \n\t --> Seçiminizi Girin: "; cin >> forgotPassword;

		if (forgotPassword == 1)
		{
			cout << "\nÞifrenizi Yenileyebilmem Ýçin Devlet Bankasýna Þifre Unutma Ücretini Ödemeniz Gerekiyor.\nGerekli bilgilendirmeler için; www.abuziddinkutuphaneleri.com\\sifreunuttumneyapmaliyim Sayfasýna Gitmelisiniz \nÖdeme Yaptýktan Sonra Abuziddin Kütüphanelerinden Makbuzunuzu Göstererek Yeni Þifre Alabilirsiniz.." << endl;
			cout << "Böyle Bir Þey Olsaydý Kimse Þifresini Unutmazdý nsdjkbnkfvbhkdsb" << endl;
			cout << "Sayýn Kullanýcýmýz Ödeme Tabi ki Yoktur, Bu Özelliði Henüz Yayýnlayamadýk, Yakýnda Þifrelerinizi De Tek Tuþla Yenileyebileceksiniz." << endl;
			cout << "Abuziddin Kütüphaneleri Olarak Ýyi Ve Saðlýklý Günler Dileriz, Okumaya Ara Vermeyin Takipde Kalýn ;)" << endl;
			loop = false;
		}
		else if (forgotPassword == 2)
		{
			loop = false;
		}
		else
		{
			cout << " 'Hayatta öyle seçimler yap ki, kazandýðýn þeyler kaybettiklerine deðsin.' \n !! Menüden Geçerli Bir Seçim Yapýn Lütfen !! " << endl;
		}
	} while (loop);
}