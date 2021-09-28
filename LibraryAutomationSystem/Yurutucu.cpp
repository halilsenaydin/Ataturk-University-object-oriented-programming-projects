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

	cout << "\n\t\t-- Abuziddin K�t�phanesinin Otomasyon Sistemi --\n" << endl;

	// Varsay�lan kitap tan�mlar�. (Bunlar db'de var gibi d���n�lebilir.) [Fonksiyonda Tan�ml�!]
	Kitap_200707069 books[100];
	CreateDefaultBook(books, 100);

	// Varsay�lan kullan�c� tan�mlar�.
	Uye_200707069 members[100];
	CreateDefaultMembers(members, 100);

	bool loop = true;
	do
	{
		string userName;
		string password;

		// menu
		int selection;
		cout << "\n 1- Admin Giri�i \n 2- �ye Giri�i \n 3- ��k��" << endl;
		cout << " Men�den Bir ��lem Se�in Ve Devam Edin: "; cin >> selection;

		switch (selection)
		{
		case 1:
			cout << "\nAdmin Kullan�c� Ad�n� Girin: "; getline(cin, userName);
			getline(cin, userName);
			cout << "Admin �ifresini Girin: "; getline(cin, password);
			AdminMenu(books, members, 100, userName, password);
			break;

		case 2:
			cout << "\nKullan�c� Ad�n�z� Girin: "; getline(cin, userName);
			getline(cin, userName);
			cout << "Kullan�c� �ifrenizi Girin: "; getline(cin, password);
			MemberMenu(books, members, 100, userName, password);
			break;

		case 3:
			loop = false;
			break;

		default:
			cout << "\nSen Robot Musun? Men�den Bir ��lem Se� !!" << endl;
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
		cout << "\nAdmin Kullan�c�s� Olarak Giri� Yapt�n�z!" << endl;

		int selection;

		do
		{
			// Admin Menu
			cout << "\n\t 1- Kitap Ekle \n\t 2- Kitap Sil \n\t 3- Kitaplar� Listele \n\t 4- Kitap Bilgilerini D�zenle \n\t 5- �ye Ekle \n\t 6- �yeleri Listele \n\t 7- �yeleri Sil \n\t 8- ��k��" << endl;
			cout << "Men�den Bir ��lem Se�in Ve Devam Edin: "; cin >> selection;

			// Bu case'lerin her biri bir buton asl�nda!!
			switch (selection)
			{
			case  1:
				{
					Kitap_200707069 book; // Create a instance

					string bookName, writerName;
					cout << "Kitab�n �smini Girin: "; getline(cin, bookName);
					getline(cin, bookName);
					cout << "Kitab�n Yazar�n�n �smini Girin: "; getline(cin, writerName);

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
					cout << "Yukar�daki Kitaplardan Silmek �stedi�iniz Bir Kitab�n ID De�erini Girin: "; cin >> bookId;

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
					Uye_200707069 user; // Create a instance, Uye eklemek i�in uye instance'i olu�turmak gerek!

					string name;
					string userName;
					int memberType;

					cout << "Kullan�c� �smini Girin: "; getline(cin, name);
					getline(cin, name);
					cout << "Kullan�c�n�n Kullan�c� Ad�n� Girin: "; getline(cin, userName);

					bool boolForMemberType = true;
					do
					{
						cout << "\n 1- ��renci\n 2- Personel\n 3- ��retim Eleman�" << endl;
						cout << "�ye Tipini Se�in: "; cin >> memberType;

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
							cout << "\n!! Ge�erli Bir �ye Tipi Girin !!" << endl;
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
					cout << "Yukar�daki Kullan�c�lardan Silmek �stedi�iniz Bir Kullan�c�n�n ID De�erini Girin: "; cin >> userId;

					admin.DeleteMember(members, 100, userId);

					break;
				}
			case 8:
				{
					loopForAdminMenu = false; // ��k��, ana men�ye d�n.
					break;
				}
			default:
				{
					cout << "\n!! Sadece Men�deki ��lemleri Se�ebilirsiniz !!" << endl;
					break;
				}
			}
		} while (loopForAdminMenu);
	}
	else
	{
		cout << "\n!! Kullan�c� Ad�n�z Veya �ifreniz Yanl�� !!" << endl;
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
		cout << "\n!! Kullan�c� Ad�n�z Veya �ifreniz Yanl�� !!" << endl;
		ForgotPassword();
		return; // wrong userName, or password
	}

	cout << "\n" << userName << " Kullan�c� Ad� �le Giri� Yapt�n�z!" << endl;

	int selection;

	bool loopForMemberMenu = true;
	do
	{
		// Member Menu
		cout << "\n\t 1- Kitap Ara \n\t 2- Kitap �d�n� Al \n\t 3- Kitaplar� �ade Et \n\t 4- Kitaplar� Listele \n\t 5- Kitap Detay�na Git \n\t 6- �yelik ��lemleri \n\t 7- �yelik Bilgileri \n\t 8- ��k��" << endl;
		cout << "Men�den Bir ��lem Se�in Ve Devam Edin: "; cin >> selection;

		// Bu case'lerin her biri bir buton asl�nda!!
		switch (selection)
		{
		case 1:
			{
				string search;

				cout << "Kitab�n �smini Girin Veya Yazar�n �smini Girin: "; getline(cin, search);
				getline(cin, search);

				member.SearchBook(books, size, search);
				break;
			}
		case 2:
			{
				int bookId;
				member.GetAllBook(books, size);
				cout << "Yukar�daki Kitaplardan �d�n� Almak �stedi�iniz Bir Kitab�n ID De�erini Girin: "; cin >> bookId;

				member.TakeBorrowBook(books, size, bookId, tempMember);
				break;
			}

		case 3:
			{
				int bookId;
				member.GetAllBookOfUser(books, size, tempMember.GetId());

				cout << "Yukar�daki Kitaplardan �ade Etmek �stedi�iniz Bir Kitab�n ID De�erini Girin: "; cin >> bookId;
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
				cout << "Yukar�daki Kitaplardan Detaylar�n� �stedi�iniz Bir Kitab�n ID De�erini Girin: "; cin >> bookId;

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
				cout << "\n 'Bir se�im yapman�z gerekti�inde,se�memek de bir se�imdir.\n !! Sadece Men�deki ��lemleri Se�ebilirsiniz !!" << endl;
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
		cout << "\n 1- �smini G�ncelle\n 2- Kullan�c� Ad�n� G�ncelle\n 3- �ifreni G�ncelle\n 4- Kullan�c� Men�s�ne D�n" << endl;
		cout << "Yukar�daki Men�den Bir ��lem Se�in: "; cin >> selection;

		switch (selection)
		{
		case 1:
			{
				string name;
				cout << "Yeni �sminizi Girin: "; getline(cin, name);
				getline(cin, name);
				tempMember.ChangeName(members, size, user, name);
				break;
			}

		case 2:
			{
				string userName;
				cout << "Yeni Kullan�c� Ad�n�z� Girin: "; getline(cin, userName);
				getline(cin, userName);
				tempMember.ChangeUserName(members, size, user, userName);
				break;
			}

		case 3:
			{
				string newPassword,
					tempPassword;

				cout << "Yeni �ifrenizi Girin: "; getline(cin, newPassword);
				getline(cin, newPassword);
				cout << "�ifrenizi Tekrar Girin: "; getline(cin, tempPassword);

				if (newPassword == tempPassword)
				{
					tempMember.ChangePassword(members, size, user, newPassword);
				}
				else
				{
					cout << "\n 'E�er,ileride bir g�n ke�ke demek istemiyorsan,2 �eyi do�ru yaz! yeni �ifre, yeni �ifre tekrar�.' \n !! Girdi�iniz Parolalar E�le�miyor !!" << endl;
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
				cout << "\n 'Ne yapmayaca��na karar vermek, ne yapaca��na karar vermek kadar �nemlidir.' \n !! Ge�erli Bir Se�im Yapmad�n�z !!" << endl;
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
		cout << "\n\t 1- Kitap Ad�n� D�zenle \n\t 2- Kitab�n Yazar�n�n Ad�n� D�zenle \n\t 3- Kitab�n A��klamas�n� D�zenle \n\t 4- Admin Men�s�ne D�n" << endl;
		cout << "\t--> Yukar�dan Bir ��lem Se�in: "; cin >> selection;

		switch (selection)
		{
		case 1:
			{
				int bookId;
				string bookName;
				admin.GetAllBook(books, size);
				cout << "Yukar�daki Kitaplardan �smini D�zenlemek �stedi�iniz Kitab�n ID'sini Girin: "; cin >> bookId;

				cout << "Yeni Kitap Ad�n� Girin: "; getline(cin, bookName);
				getline(cin, bookName);

				admin.EditBookName(books, size, bookId, bookName);
				break;
			}
		case 2:
			{
				int bookId;
				string writerName;
				admin.GetAllBook(books, size);
				cout << "Yukar�daki Kitaplardan Yazar �smini D�zenlemek �stedi�iniz Kitab�n ID'sini Girin: "; cin >> bookId;

				cout << "Kitab�n Yeni Yazar�n�n �smini Girin: "; getline(cin, writerName);
				getline(cin, writerName);

				admin.EditWriterName(books, size, bookId, writerName);
				break;
			}
		case 3:
			{
				int bookId;
				string description;
				admin.GetAllBook(books, size);
				cout << "Yukar�daki Kitaplardan A��klamas�n� D�zenlemek �stedi�iniz Kitab�n ID'sini Girin: "; cin >> bookId;

				cout << "Kitab�n Yeni A��klamas�n� Girin: "; getline(cin, description);
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
				cout << "\n!! Sadece Men�deki ��lemler Se�ilebilir !!" << endl;
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
	myFavoriteBook.SetDescription("Insan daha az uyuyup daha fazla sey yapabilecekken neden kendimizi kisitliyoruz? Admin'in en sevdi�i kitapd�r.");

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
	notesfromUnderground.SetDescription("Dostoevsky'yi anlamak icin okumak gereken en �nemli sah eserlerdendir..");


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
	inferno.SetDescription("Avrupa�dan Turkiye�ye uzanan soluksuz bir maceraya atilmaya hazir misiniz?");

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
		cout << "\n�ifreni Mi Unuttun? \n\t 1- Evet\n\t 2- Hay�r \n\t --> Se�iminizi Girin: "; cin >> forgotPassword;

		if (forgotPassword == 1)
		{
			cout << "\n�ifrenizi Yenileyebilmem ��in Devlet Bankas�na �ifre Unutma �cretini �demeniz Gerekiyor.\nGerekli bilgilendirmeler i�in; www.abuziddinkutuphaneleri.com\\sifreunuttumneyapmaliyim Sayfas�na Gitmelisiniz \n�deme Yapt�ktan Sonra Abuziddin K�t�phanelerinden Makbuzunuzu G�stererek Yeni �ifre Alabilirsiniz.." << endl;
			cout << "B�yle Bir �ey Olsayd� Kimse �ifresini Unutmazd� nsdjkbnkfvbhkdsb" << endl;
			cout << "Say�n Kullan�c�m�z �deme Tabi ki Yoktur, Bu �zelli�i Hen�z Yay�nlayamad�k, Yak�nda �ifrelerinizi De Tek Tu�la Yenileyebileceksiniz." << endl;
			cout << "Abuziddin K�t�phaneleri Olarak �yi Ve Sa�l�kl� G�nler Dileriz, Okumaya Ara Vermeyin Takipde Kal�n ;)" << endl;
			loop = false;
		}
		else if (forgotPassword == 2)
		{
			loop = false;
		}
		else
		{
			cout << " 'Hayatta �yle se�imler yap ki, kazand���n �eyler kaybettiklerine de�sin.' \n !! Men�den Ge�erli Bir Se�im Yap�n L�tfen !! " << endl;
		}
	} while (loop);
}