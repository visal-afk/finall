#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include <ctime>
using namespace std;

class Ingredient {
    string ad;
    double kiloQiymeti;
    double miqdarKg;

public:
    Ingredient() = default;
    Ingredient(const string& ad, double kiloQiymeti, double miqdarKg) {
        setAd(ad);
        setKiloQiymeti(kiloQiymeti);
        setMiqdarKg(miqdarKg);
    }

    string getAd()const noexcept { return ad; }
    double getKiloQiymeti()const noexcept { return kiloQiymeti; }
    double getMiqdarKg()const noexcept { return miqdarKg; }

    void setAd(string ad)throw(string) {
        if (ad.length() < 2) {
            throw string("2 herifli yada 2 herifden balaca inqridient yoxdu");
        }
        this->ad = ad;
    }

    void setKiloQiymeti(double kiloQiymeti)throw(string) {
        if (kiloQiymeti <= 0) {
            throw string("qiymeti 0 dan boyuk olmalidi");
        }
        this->kiloQiymeti = kiloQiymeti;
    }

    void setMiqdarKg(double miqdarKg) throw(string) {
        if (miqdarKg < 0) {
            throw string("ceki menfi ola bilmez");
        }
        this->miqdarKg = miqdarKg;
    }

    void MiqdarKqArtir(double miqdarKg)throw(string) {
        if (miqdarKg <= 0) {
            throw string("menfi eded artirmaq olmaz");
        }
        this->miqdarKg += miqdarKg;
    }

    void MiqdarKqCix(double miqdarKg)throw(string) {
        if (miqdarKg > this->miqdarKg) {
            throw string("o qeder inqridient yoxdu ");
        }
        this->miqdarKg -= miqdarKg;
    }
};

class Anbar {

    vector<Ingredient> inqrediyentler;
public:
    Anbar() {
        try
        {
            loadData();
        }
        catch (string ex)
        {
            Ingredient ing("flour", 1.0, 2.5);
            inqrediyentler.push_back(ing);

        }
    }

    void saveData() {
        string filepath = "sklad.txt";
        ofstream fs(filepath, ios::out);
        if (fs.is_open()) {
            for (size_t i = 0; i < inqrediyentler.size(); i++)
            {
                if (i == inqrediyentler.size() - 1) {
                    fs << inqrediyentler[i].getAd() << "#" << inqrediyentler[i].getMiqdarKg() << "#" << inqrediyentler[i].getKiloQiymeti();
                    continue;
                }
                fs << inqrediyentler[i].getAd() << "#" << inqrediyentler[i].getMiqdarKg() << "#" << inqrediyentler[i].getKiloQiymeti() << "\n";
            }
        }
        else {
            throw string("File couldn't open....");
        }
        fs.close();
    }
    void loadData() {
        string filepath = "sklad.txt";
        ifstream fs(filepath); 
            if (fs.is_open()) {
                string row;              
                while (getline(fs, row)) {
                    if (row.empty()) continue;
                    int r = 0;
                    string ad, miqdarkq, kiloqiymet;
                    for (auto character : row)
                    {
                        if (character != '#' && r == 0) {
                            ad += character; 
                        }
                        else if (character != '#' && r == 1) {
                            miqdarkq += character; 
                        }
                        else if (character != '#' && r == 2) {
                            kiloqiymet += character; 
                        }
                        else {
                            r++; 
                        }
                    }

                    if (miqdarkq.empty() || kiloqiymet.empty()) continue;

                    double miqdar_kq = stod(miqdarkq); 
                    double kilo_qiymet = stod(kiloqiymet);
                    Ingredient ing(ad, kilo_qiymet, miqdar_kq); 
                    inqrediyentler.push_back(ing);

                }
            }
            else {
                throw string("File not found.."); 
            }
        fs.close();
    }
    void inqrediyentElaveEt(Ingredient yeni) throw(string) {
        for (auto& i : inqrediyentler) {
            if (i.getAd() == yeni.getAd()) {
                i.MiqdarKqArtir(yeni.getMiqdarKg());
                return;
            }
        }
        inqrediyentler.push_back(yeni);
        saveData();
    }

    Ingredient* IngredientTap(string ingredient) {
        for (auto& i : inqrediyentler) {
            if (i.getAd() == ingredient)
                return &i;
        }
        return nullptr;
    }

    void InqrediyentCix(string ad, double miqdarKg) throw(string) {
        Ingredient* i = IngredientTap(ad);
        if (i == nullptr) {
            throw string("Bu adla inqrediyent anbarda yoxdur: " + ad);
        }
        i->MiqdarKqCix(miqdarKg);
        saveData();
    }

    void ButunInqrediyentGoster() {
        cout << "--------------Anbardaki inqrediyentlər----------- " << endl;
        for (auto& i : inqrediyentler) {
            cout << i.getAd();
            cout << "Qiymət Kq: " << i.getKiloQiymeti() << "₼" << endl;
            cout << "Miqdar Kq: " << i.getMiqdarKg() << " kg" << endl;
            cout << "----------------------------" << endl;
        }
    }
};
class Food {
    string YemekAd;
    string YemekInfo;
    double YemekQiymet;
    vector<Ingredient> inqrediyentler;
    bool aktivdir;
    int PorsiyaSayi;

public:
    Food() = default;

    Food(string YemekAd, string YemekInfo, double YemekQiymet, int PorsiyaSayi) {
        setAd(YemekAd);
        setInfo(YemekInfo);
        setQiymet(YemekQiymet);
        this->PorsiyaSayi = PorsiyaSayi;
        aktivdir = true;
    }

    string getYemekAd()const  noexcept { return YemekAd; }
    string getInfo()const  noexcept { return YemekInfo; }
    double getQiymet()const  noexcept { return YemekQiymet; }
    bool isAktiv()const  noexcept { return aktivdir; }
    int getPorsiyaSayi() const noexcept { return PorsiyaSayi; }


    void setAd(string YemekAd) throw(string) {
        if (YemekAd.size() < 2) {
            throw string("Yeməyin adı en azı 2 herif olmalıdır");
        }
        else {
            this->YemekAd = YemekAd;
        }

    }

    void setInfo(string YemekInfo)throw(string) {
        if (YemekInfo.size() < 10) {
            throw string("Yemek haqda info da en azı 10 herif olmalidir ");
        }
        else {
            this->YemekInfo = YemekInfo;
        }
    }

    void setQiymet(double YemekQiymet) throw(string) {
        if (YemekQiymet <= 0) {
            throw string("Qiymət 0 dan böyük olmalıdır");
        }
        this->YemekQiymet = YemekQiymet;
    }

    void inqrediyentElaveEt(const Ingredient& ing) {
        inqrediyentler.push_back(ing);
    }


    void porsiyaAzalt() throw(string) {
        if (PorsiyaSayi <= 0) {
            throw string("Bu yeməkdən artıq porsiya qalmayıb");
        }
        PorsiyaSayi--;
    }
    int HesablaPorsiyaSayi(Anbar& anbar) const {
        int minPorsiya = INT_MAX;
        for (const auto& r : inqrediyentler) {
            Ingredient* i = anbar.IngredientTap(r.getAd());
            if (i == nullptr || i->getMiqdarKg() < r.getMiqdarKg()) {
                return 0;
            }
            int porsiya = static_cast<int>(i->getMiqdarKg() / r.getMiqdarKg());
            if (porsiya < minPorsiya) {
                minPorsiya = porsiya;
            }
        }
        return minPorsiya;
    }


    void reseptiGoster() {
        cout << "Yemək: " << YemekAd << " Qiymət: " << YemekQiymet << "₼" << endl;
        cout << "Yemək Info: " << YemekInfo << endl;
        cout << "Resept:" << endl;
        for (auto& i : inqrediyentler) {
            cout << i.getAd() << " : " << i.getMiqdarKg() << " kg" << endl;
        }
    }

    void AktivYoxla(Anbar& anbar) {
        PorsiyaSayi = HesablaPorsiyaSayi(anbar);
        aktivdir = (PorsiyaSayi > 0);
    }

    void YemekBisir(Anbar& anbar) throw(string) {
        if (!aktivdir) {
            throw string("Bu yemək hazırda aktiv deyil: " + YemekAd);
        }
        if (PorsiyaSayi <= 0) {
            throw string("Bu yeməkdən qalmayıb: " + YemekAd);
        }

        for (auto& r : inqrediyentler) {
            anbar.InqrediyentCix(r.getAd(), r.getMiqdarKg());
        }
        porsiyaAzalt();
    }

};
class Menu {
    vector<Food> yemekler;

public:
    Menu()
    {
        try
        {
            loadData();
        }
        catch (string ex)
        {
            Food yemek("Pizza", "Gobelekli Extra pendirli", 8.5, 1);

        }
    }

    void saveDataMenu() {
        string filepath = "menu.txt";
        ofstream fs(filepath);

        if (fs.is_open()) {
            for (size_t i = 0; i < yemekler.size(); i++)
            {
                if (i == yemekler.size() - 1) {
                    fs << yemekler[i].getYemekAd() << "#" << yemekler[i].getInfo() << "#" << yemekler[i].getQiymet()<< yemekler[i].getPorsiyaSayi();
                    continue;
                }
                fs << yemekler[i].getYemekAd() << "#" << yemekler[i].getInfo() << "#" << yemekler[i].getQiymet()<<yemekler[i].getPorsiyaSayi() << "\n";
            }
        }
        else {
            throw string("File couldn't open....");
        }
        fs.close();
    }
    void loadData() {
        string filepath = "menu.txt"; 
            ifstream fs(filepath); 
            if (fs.is_open()) {
                string row;
                while (getline(fs, row)) {
                   
                    if (row.empty()) continue;

                     

                        int r = 0; 
                        string YemekAd, YemekInfo, YemekQiymet, YemekPorsiya; 
                        for (auto character : row)
                        {
                            if (character != '#' && r == 0) {
                                YemekAd += character; 
                            }
                            else if (character != '#' && r == 1) {
                                YemekInfo += character; 
                            }
                            else if (character != '#' && r == 2) {
                                YemekQiymet += character; 
                            }
                            else if (character != '#' && r == 3) {
                                YemekPorsiya += character; 
                            }
                            else {
                                r++; 
                            }
                        }
                    if (YemekQiymet.empty() || YemekPorsiya.empty()) continue; 

                    double Yemek_Qiymet = stod(YemekQiymet); 
                        int Yemek_Porsiya = stoi(YemekPorsiya); 
                        Food food(YemekAd, YemekInfo, Yemek_Qiymet, Yemek_Porsiya); 
                        yemekler.push_back(food); 
                }
            }
            else {
                throw string("File not found.."); 
            }
        fs.close(); 
    }
    void ElaveEt(const Food& yemek) {
        yemekler.push_back(yemek);
        saveDataMenu();
    }

    void AktivlikYoxla(Anbar& anbar) {
        for (auto& y : yemekler) {
            y.AktivYoxla(anbar);
        }
    }

    void MenuGoster() const {
        cout << "------ Menu ------" << endl;
        for (const auto& y : yemekler) {
            if (y.isAktiv()) {
                cout << "Yemek: " << y.getYemekAd() << " ";
                cout << "Qiymət: " << y.getQiymet() << "₼" << endl;
                cout << "Info: " << y.getInfo() << endl;
                cout << "------------------------" << endl;
            }
        }
    }

    Food* tap(string ad) {
        for (auto& y : yemekler) {
            if (y.getYemekAd() == ad)
                return &y;
        }
        return nullptr;
    }

    void Bisir(string ad, Anbar& anbar) {
        Food* y = tap(ad);
        if (!y) {
            cout << "Yemek Yoxdu" << ad << endl;
            return;
        }

        y->AktivYoxla(anbar);
        if (y->isAktiv()) {
            try {
                y->YemekBisir(anbar);
                cout << ad << "Bisirildi";
                anbar.saveData();
            }
            catch (string ex) {
                cout << ex << endl;
            }
        }
        else {
            cout << ad << "Inqridient catmir";
        }
    }
};


class User; 
class Admin; 

class Sebet {
    vector<string> secilmisAdlar;
public:
   void yemekElaveEt(const string& ad, Menu& menu) {
        Food* yemek = menu.tap(ad);
        if (yemek == nullptr) {
            cout << "Menyuda belə bir yemək yoxdur: " << ad << endl;
            return;
        }
        secilmisAdlar.push_back(ad);
        cout << "Səbətə əlavə olundu: " << ad << endl;
    }

    void goster() const {
        cout << "-----Sebet-----" << endl;
        for (const auto& ad : secilmisAdlar) {
            cout << "Yemek adi:" << ad << endl;
        }
    }
    void sifarisEt(Menu& menu, Anbar& anbar,User& user,Admin& admin);
};

class User {
    string istifadeciAdi;
    string sifre;
    string telefon;
    double pul = 100;
    Sebet sebet;
public:
    User() = default;

    User(const string& ad, const string& kod, const string& tel) {
        setAd(ad);
        setSifre(kod);
        setTelefon(tel);
    }

    string getAd() const { return istifadeciAdi;
    }
    string getSifre() const { return sifre; }
    string getTelefon() const { return telefon;
    }
    Sebet& getSebet() { return sebet; }

    void setAd(const string& ad) throw(string) {
        if (ad.empty()) {
            throw string("İstifadəçi adı boş ola bilməz");
        }
        istifadeciAdi = ad;
    }
    void PulCix(double mebleg) {
        if (mebleg > pul) {
            throw string("Bütcə kifayət etmir");
        }
        pul -= mebleg;
    }

    void setSifre(const string& kod) throw(string) {
        if (kod.length() < 4) {
            throw string("Şifrə ən azı 4 simvol olmalıdır");
        }
        sifre = kod;
    }

    void setTelefon(const string& tel)throw(string) {
        if (tel.length() != 10) {
            throw string("Telefon nömrəsi 10 rəqəmli olmalıdır");
        }
        telefon = tel;
    }
    void PulGoster() const {
        cout << "Pul goster: " << pul << "₼" << endl;
    }

    void qeydiyyat()throw(string) {
        cout << "Ad: ";
        getline(cin,istifadeciAdi);
        try {
            vector<User> siyahi = LoadData();
            for (const auto& user : siyahi) {
                if (user.getAd() == istifadeciAdi) {                    
                    throw string("Bu istifadəçi adı artıq qeydiyyatdan keçib.");
                    
                }
            }
        }
        catch ( string ex) {
            cout << ex << endl;
            return;
        }
        cout << "Şifrə: ";
        getline(cin, sifre);
        cout << "Telefon: ";
        getline(cin, telefon);
        try {
            setAd(istifadeciAdi);
            setSifre(sifre);
            setTelefon(telefon);
        }
        catch (string ex) {
            cout << ex << endl;
            return;
        }

        yaddaSaxla();
        cout << "Qeydiyyat uğurla tamamlandı";
    }

    void yaddaSaxla() {
        ofstream fayl("istifadeciler.txt", ios::app);
        if (fayl.is_open()) {
            fayl << istifadeciAdi << "#" << sifre << "#" << telefon << "#" << pul << "\n";
            fayl.close();
        }
        else {
            throw string("File couldn't open....");
        }

    }
    vector<User> LoadData() {
        vector<User> siyahi;
        string filepath = "istifadeciler.txt";
        ifstream fs(filepath);
        if (fs.is_open()) {
            string row;
            while (getline(fs, row)) {
                if (row.empty()) continue;
                int r = 0;
                string istifadeciAdi, sifre, telefon;
                for (auto character : row)
                {
                    if (character != '#' && r == 0) {
                        istifadeciAdi += character;
                    }
                    else if (character != '#' && r == 1) {
                        sifre += character;
                    }
                    else if (character != '#' && r == 2) {
                        telefon += character;
                    }
                    else {
                        r++;
                    }
                }
                User user(istifadeciAdi, sifre, telefon);
                siyahi.push_back(user);
            }
        }
        else {
            throw string("File not found..");
        }
        fs.close();
        return siyahi;
    }

};

class Admin {
    string istifadeciAdi;
    string sifre;
    Menu menu;
    Anbar sklad;
    double butce = 500;
public:
    Admin() : istifadeciAdi("admin"), sifre("admin") {}
    void budcedenPulCix(double mebleg) {
        if (mebleg > butce) {
            throw string("Bütcə kifayət etmir");
        }
        butce -= mebleg;
    }
    void pulElaveEt(double mebleg) {
        butce += mebleg;
    }

    void yemekElaveEt(const Food& yeniYemek) {
        menu.ElaveEt(yeniYemek);
        cout << "Menyuya əlavə olundu: " << yeniYemek.getYemekAd() << endl;
    }

    void anbaraElaveEt(const string& ad, double miqdarKg, double qiymetiKg) {
        Ingredient ing(ad, miqdarKg, qiymetiKg);
        sklad.inqrediyentElaveEt(ing);
        cout << "Anbara əlavə olundu: " << ad << ", Ceki" << miqdarKg << " kg" << endl;
    }

    void menyunuGoster() {
        menu.AktivlikYoxla(sklad);
        menu.MenuGoster();
    }

    void anbarGoster() {
        sklad.ButunInqrediyentGoster();
    }


    void butceGoster() const {
        cout << "Cari büdcə: " << butce << "₼" << endl;
    }

    Menu& getMenu() { return menu; }

    Anbar& getAnbar() { return sklad; }
};

void Sebet::sifarisEt(Menu& menu, Anbar& anbar, User& user, Admin& admin) {
    cout << "Sifariş hazırlanır";
    for (const auto& ad : secilmisAdlar) {
        Food* yemek = menu.tap(ad);
        if (yemek != nullptr) {
            try {
                double qiymet = yemek->getQiymet();
                
                user.PulCix(qiymet); 
                admin.pulElaveEt(qiymet); 
                
                yemek->YemekBisir(anbar);
                cout << "Bişirildi: " << ad << endl;
            }
            catch (string ex) {
                cout << ex << endl;
            }
        }
    }
    secilmisAdlar.clear();
}

void main() {
    vector<User> istifadeciler;
    User temp;
    try {
        istifadeciler = temp.LoadData();
    }
    catch (string ex) {
        cout <<ex << endl;
    }

    Admin admin;

    while (true) {
        
        cout << "--- ANA MENYU ---"<<endl;
        cout << "1. Qeydiyyat" << endl;
        cout << "2. Giriş" << endl;
        cout << "3. Admin Paneli" << endl;
        cout << "4. Cixis" << endl;
        cout << "Seçim: ";

        int secim;
        cin >> secim;
        cin.ignore();

        if (secim == 1) {
            User yeni;
            yeni.qeydiyyat();
            istifadeciler.push_back(yeni);
        }

        else if (secim == 2) {
            string ad, kod;
            cout << "İstifadeci adı: "; 
            getline(cin, ad);
            cout << "Şifre: ";
            getline(cin, kod);

            bool tapildi = false;
            for (User& u : istifadeciler) {
                if (u.getAd() == ad && u.getSifre() == kod) {
                    cout << "Giriş uğurludur" << endl;
                    tapildi = true;

                    while (true) {
                        
                        cout << "--- İSTİFADEÇİ PANELİ ---" << endl;
                        cout << "1. Menyuya bax" << endl;
                        cout << "2. Sebete elave et" << endl; 
                        cout << "3. Sebete bax" << endl; 
                        cout << "4. Sifariş et" << endl;
                        cout << "5. Pula bax" << endl;
                        cout << "6. Geri don" << endl;                       
                        cout << "Seçim: ";

                        int iceriSecim;
                        cin >> iceriSecim;
                        cin.ignore();

                        if (iceriSecim == 1) {
                            admin.menyunuGoster();
                        }
                        else if (iceriSecim == 2) {
                            string yemekAd;
                            cout << "Yemeyin adı: "; 
                            getline(cin, yemekAd);
                            u.getSebet().yemekElaveEt(yemekAd, admin.getMenu());
                        }
                        else if (iceriSecim == 3) {
                            u.getSebet().goster();
                        }
                        else if (iceriSecim == 4) {
                            u.getSebet().sifarisEt(admin.getMenu(), admin.getAnbar() ,u ,admin);
                        }
                        else if (iceriSecim == 5) {
                            u.PulGoster();
                        }
                        else if (iceriSecim == 6) {
                            break;
                        }
                        else {
                            cout << "Sef seçim" << endl;
                        }
                    }

                    break;
                }
            }

            if (!tapildi) {
                cout << "Ad ve ya şifre sefdir " << endl;
            }
        }

        else if (secim == 3) {
            string kod;
            cout << "Admin şifre: "; 
            getline(cin, kod);

            if (kod == "admin") {
                while (true) {
                    
                    cout << "--- ADMIN PANELİ ---" << endl;
                    cout << "1. Anbara inqrediyent elave et" << endl;
                    cout << "2. Yeni yemek elave et" << endl;
                    cout << "3. Menyuya bax" << endl;
                    cout << "4. Anbara bax" << endl;
                    cout << "5. Büdcəye bax" << endl;
                    cout << "6. Geri dön" << endl;
                    cout << "Seçim: ";

                    int adminSecim;
                    cin >> adminSecim;
                    cin.ignore();

                    if (adminSecim == 1) {
                        string ad;
                        double qiymet, miqdar;
                        cout << "Ad: "; 
                        getline(cin, ad);
                        cout << "Kilo qiymeti: "; 
                        cin >> qiymet;
                        cout << "Miqdar (kg): "; 
                        cin >> miqdar;
                        cin.ignore();

                        try {
                            admin.budcedenPulCix(qiymet * miqdar);
                            admin.anbaraElaveEt(ad, qiymet, miqdar);
                        }
                        catch (string ex) {
                            cout<< ex << endl;
                        }
                    }

                    else if (adminSecim == 2) {
                        string ad, info;
                        double qiymet;
                        int porsiya, say;

                        cout << "Yemek adı: "; 
                        getline(cin, ad); 
                        cout << "Elave info: "; 
                        getline(cin, info);
                        cout << "Qiymet: "; 
                        cin >> qiymet;
                        cout << "Porsiya sayı: "; 
                        cin >> porsiya;
                        cout << "Neçe inqrediyent gedir: "; 
                        cin >> say;
                        cin.ignore();

                        Food yeni(ad, info, qiymet, porsiya);

                        for (int i = 0; i < say; i++) {
                            string ingAd;
                            double ingMiqdar;
                            cout << "Inqrediyent " << i + 1 << " adı: "; 
                            getline(cin, ingAd);
                            cout << "Miqdarı (kg): "; 
                            cin >> ingMiqdar;
                            cin.ignore();

                            Ingredient* tapilan = admin.getAnbar().IngredientTap(ingAd);
                            if (tapilan == nullptr) {
                                cout << "Anbarda yoxdur: " << ingAd << endl;
                                continue;
                            }

                            Ingredient ing(ingAd, tapilan->getKiloQiymeti(), ingMiqdar);
                            yeni.inqrediyentElaveEt(ing);
                        }

                        admin.yemekElaveEt(yeni);
                    }

                    else if (adminSecim == 3) {
                        admin.menyunuGoster();
                    }

                    else if (adminSecim == 4) {
                        admin.anbarGoster();
                    }

                    else if (adminSecim == 5) {
                        admin.butceGoster();
                    }

                    else if (adminSecim == 6) {
                        break;
                    }

                    else {
                        cout << "Yanlış secim" << endl;
                    }
                }
            }
            else {
                cout << "Sifre yanlışdır" << endl; 
            }
        }

        else if (secim == 4) {
            cout << "Sistemden cıxılır..." << endl; 
            break;
        }

        else {
            cout << "Yanlıs secim" << endl;
        }
    }
}






