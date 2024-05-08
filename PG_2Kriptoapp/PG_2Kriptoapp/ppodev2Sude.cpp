#include <iostream>//Giriş/çıkış işlemleri
#include <time.h>//Zamanı değiştirmeye yönelik işlemler.
#include <vector>//Vektör kapsayıcısını sağlar
#include <conio.h>//Konsol giriş/çıkış işlevleri
#include <sstream>//Dize akışı işleme

using namespace std;


int GetInput()//Kullanıcıdan bir tamsayı okur ve döndürür.
{
    int secim;
    cin >> secim;
    return secim;
}

double GetDoubleInput()//Kullanıcıdan  bir double okur ve döndürür.
{
    double x;
    cin >> x;
    return x;
}

void kullaniciyiBekle() { //Bir mesaj yazdırır ve bir tuşa basılmasını bekler.
    cout << "\n\nAna menuye donmek icin herhangi bir tusa basiniz.";
    _getch();
}

void getAnaMenu() {//Ana Menü seçeneklerini görüntüler
    cout << "Ana Menu\n\n";
    cout << "Lutfen menuden seciminizi yapiniz\n\n";
    cout << "1 - Genel Hesap Acma\n";
    cout << "2 - Ozel Hesap Acma\n";
    cout << "3 - Hesaba Para Ekleme\n";
    cout << "4 - Hesaptan Para Cekme\n";
    cout << "5 - Tarihi Duzenleme\n";
    cout << "6 - Hesaplari Listeleme \n";
    cout << "7 - Cikis\n";
    cout << "\nSecim: ";
}

int rdn(int y, int m, int d) { /* Rata Die birinci gün 0001-01-01 */ //R.D. gün sayısını atar.
    if (m < 3)
        y--, m += 12;
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

class Hesap { 
    int hesapNo;
    string hesapTipi;
    double bakiye;
    double kriptoDeger;
public:
    Hesap(int a, string b, double c) { 
        hesapNo = 1000 + a;
        hesapTipi = b;
        bakiye = c;
        kriptoDeger = 1;
        cout << hesapNo << " nolu " << hesapTipi << " hesap acilmistir.Bakiye : " << bakiye;
        kullaniciyiBekle();

    };
    void Al(double miktar);// miktar alma fonksiyonu
    void Sat(double miktar);//miktar satma fonksiyonu
    void Bakiye();//bakiye fonksiyon
    void Kar(int sistemTarihi[3], int guncelTarih[3]);//Sistem tarihinden geçen süreye kadar olan zaman dilimindeki karı hesaplayan fonksiyon
    int getHesapNo() { return hesapNo; };
};

void Hesap::Al(double miktar) { //Hesaba para ekleyen fonksiyon
    bakiye += kriptoDeger * miktar;
    cout << miktar << " eklenmistir. Yeni bakiye : " << bakiye;
    kullaniciyiBekle();
};

void Hesap::Sat(double miktar) { //Hesaptan parayı satan fonksiyon
    bakiye -= kriptoDeger * miktar;
    cout << miktar << " satilmistir. Yeni bakiye : " << bakiye;
    kullaniciyiBekle();
};

void Hesap::Bakiye() {
    cout << "Hesap No : " << hesapNo << " Turu: " << hesapTipi << " Bakiye: " << bakiye;
};

// fonksiyon toplam gün sayısını döndürücek
int getNumberOfDays(int month, int year)
{
    // Artık yıl koşulu
    if (month == 2) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    // 31 güne sahiip günler
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
        || month == 10 || month == 12)
        return 31;
    else
        return 30;
}

void Hesap::Kar(int sistemTarihi[3], int guncelTarih[3]) {
   
    int gunFarki = rdn(sistemTarihi[2], sistemTarihi[1], sistemTarihi[0]) - rdn(guncelTarih[2], guncelTarih[1], guncelTarih[0]);
    int totalKazanc = 0;
    cout << "\nGun farki : " << gunFarki;
    if (hesapTipi == "GENEL") {
        for (int i = 0; i < gunFarki; i++) {
            if ((i + 1) % 15 == 0)
                totalKazanc -= totalKazanc * 0.05;
            else
                totalKazanc += totalKazanc * 0.01;
        }
    }
    else
    {
        int arr[3];
        int hesap_ay;
        int hesap_gun;
        int anlik_ay;
        if (sistemTarihi[1] < guncelTarih[1]) {
            hesap_ay = sistemTarihi[1] - guncelTarih[1] + 12;
        }
        for (int yil = 0; yil < sistemTarihi[2] - guncelTarih[2]; yil++) {

            anlik_ay = guncelTarih[1];
            cout << "\nhesap ay : " << hesap_ay;
            //cout << "\nanlik ay : " << anlik_ay;
            while (hesap_ay >= 0) { // aradaki fark kadar don
                hesap_ay--;
                cout << "Anlik ay : " << anlik_ay;
                anlik_ay++;
                if (anlik_ay > 12) anlik_ay = 1;
            }
        }
    }
};

int hesapIndexiBul(vector<Hesap> v, int hesapNo) {//Hesapları depolamak için bir vektör (hesapListesi) dahil olmak üzere değişkenleri tanımlar.
    int size = v.size();
    int index = -1;
    for (unsigned i = 0; i < size; i++) {
        if (hesapNo == v[i].getHesapNo()) {
            return i;
        };
    };
}


int main()
{
    int secim = 0;
    int toplamHesapSayisi = 0;
    vector<Hesap> hesapListesi;
    int i, size;
    string line;
    char dummy;

    time_t current_time;
    struct tm local_time;

    time(&current_time);
    localtime_s(&local_time, &current_time);

    int sistemTarihi[3];
    int guncelTarih[3];

    sistemTarihi[0] = local_time.tm_mday;
    sistemTarihi[1] = local_time.tm_mon + 1;
    sistemTarihi[2] = local_time.tm_year - 100;



    do
    {
        system("cls");

        getAnaMenu();
        secim = GetInput();//klavyeden girilen değerleri okumak için kullandık

        switch (secim) {

        case 1:/* Genel Hesap Ac */ {
            toplamHesapSayisi += 1;
            cout << "Tutar: ";
            Hesap hesap(toplamHesapSayisi, "GENEL", GetDoubleInput());
            hesapListesi.push_back(hesap);
            break;
        }
        case 2: /* Ozel Hesap Ac */ {
            toplamHesapSayisi += 1;
            cout << "Tutar: ";
            Hesap hesap(toplamHesapSayisi, "OZEL", GetDoubleInput());
            hesapListesi.push_back(hesap);
            break;
        }
        case 3: /* Bakiye Ekle */ {
            cout << "\nHesap No giriniz: ";
            i = hesapIndexiBul(hesapListesi, GetInput());
            cout << "\nNe kadar almak istediginizi giriniz: ";
            hesapListesi[i].Al(GetDoubleInput());
            break;
        }
        case 4: /* Bakiye �ek */ {
            cout << "\nHesap No giriniz: ";
            i = hesapIndexiBul(hesapListesi, GetInput());
            cout << "\nNe kadar satmak istediginizi giriniz: ";
            hesapListesi[i].Sat(GetDoubleInput());
            break;
        }
        case 5: /* Tarih */ {

            guncelTarih[0] = sistemTarihi[0];
            guncelTarih[1] = sistemTarihi[1];
            guncelTarih[2] = sistemTarihi[2];

            cout << "Tarih : " << guncelTarih[0] << "-" << guncelTarih[1] << "-" << guncelTarih[02];
            cout << "\nYeni tarihi giriniz (dd-mm-yy): ";
            cin >> line;

            stringstream lineStream(line, '-');
            lineStream >> sistemTarihi[0] >> dummy >> sistemTarihi[1] >> dummy >> sistemTarihi[2];

            cout << sistemTarihi[0] << '-' << sistemTarihi[1] << '-' << sistemTarihi[2];

            size = hesapListesi.size();
            for (unsigned i = 0; i < size; i++) {
                hesapListesi[i].Kar(sistemTarihi, guncelTarih);
            };

            kullaniciyiBekle();
            break;
        }
        case 6: /* Listele */ {
            size = hesapListesi.size();
            for (unsigned i = 0; i < size; i++) {
                hesapListesi[i].Bakiye();
            };
            kullaniciyiBekle();
            break;
        }
        case 7:
            cout << "\nIyi gunler!";
            break;

        default:
            break;
        }
    } while (secim != 7);
    system("PAUSE");
    return EXIT_SUCCESS;
}