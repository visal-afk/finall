#include <iostream>
#include <string>
#include<vector>
#include<fstream>
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
        ofstream fs(filepath);

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
            while (!fs.eof()) {
                string row;
                getline(fs, row);
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
                double miqdar_kq = stod(miqdarkq);
                double kilo_qiymet = stod(kiloqiymet);
                Ingredient ing(ad, miqdar_kq, kilo_qiymet);
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
        PorsiyaSayi = 0;
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
            while (!fs.eof()) {
                string row;
                getline(fs, row);
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

    void sifarisEt(Menu& menu, Anbar& anbar) {
        cout << "Sifariş hazırlanır";
        for (const auto& ad : secilmisAdlar) {
            Food* yemek = menu.tap(ad);
            if (yemek != nullptr) {
                try {
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
};
class Admin {
    string istifadeciAdi;
    string sifre;
    Menu menu;
    Anbar sklad;
    double butce = 0.0;

public:
    Admin() : istifadeciAdi("admin"), sifre("admin") {}

    void yemekElaveEt(const Food& yeniYemek) {
        menu.ElaveEt(yeniYemek);
        cout << "Menyuya əlavə olundu: " << yeniYemek.getYemekAd() << endl;
    }

    void anbaraElaveEt(const string& ad, double miqdarKg,double qiymetiKg) {
        Ingredient ing(ad, miqdarKg, qiymetiKg);
        sklad.inqrediyentElaveEt(ing);
        cout << "Anbara əlavə olundu: " << ad << ", Ceki" << miqdarKg << " kg" << endl;
    }

    void menyunuGoster() {
        menu.AktivlikYoxla(sklad);
        menu.MenuGoster();
    }

    void anbarGoster()  {
        sklad.ButunInqrediyentGoster();
    }


    void butceGoster() const {
        cout << "Cari büdcə: " << butce << "₼" << endl;
    }

    Menu& getMenu() { return menu; }

    Anbar& getAnbar() { return sklad; }
};
void main() {
    
}






