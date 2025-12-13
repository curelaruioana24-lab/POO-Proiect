#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4566)
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//
// CLASA 1: ClientCorporativ - FAZA 3 (cu operatori suprâncărcați)
//
class ClientCorporativ {
private:
    char* numeCompanie;
    int nrAngajati;
    string codFiscal;
    double volumTransporturiLunar;
    char* adresaSediu;
    char* persoanaContact;
    bool esteActiv;
    int ID_CLIENT;

    static double discountCorporativ;
    static int numarTotalClienti;
    static int clientiActivi;

public:
    // Constructori
    ClientCorporativ()
        : numeCompanie(nullptr),
        adresaSediu(nullptr),
        persoanaContact(nullptr),
        nrAngajati(0),
        codFiscal("RO00000000"),
        volumTransporturiLunar(0.0),
        esteActiv(true),
        ID_CLIENT(++numarTotalClienti) {

        numeCompanie = new char[200];
        strcpy(numeCompanie, "Companie Necunoscuta");
        adresaSediu = new char[200];
        strcpy(adresaSediu, "Adresa nedefinita");
        persoanaContact = new char[200];
        strcpy(persoanaContact, "Contact necunoscut");
        clientiActivi++;
    }

    ClientCorporativ(const char* nume, const char* adresa, const char* contact,
        int angajati, string cod, double volum, bool activ)
        : numeCompanie(nullptr),
        adresaSediu(nullptr),
        persoanaContact(nullptr),
        nrAngajati(angajati),
        codFiscal(cod),
        volumTransporturiLunar(volum),
        esteActiv(activ),
        ID_CLIENT(++numarTotalClienti) {

        size_t len = strlen(nume);
        numeCompanie = new char[len + 1];
        strcpy(numeCompanie, nume);

        len = strlen(adresa);
        adresaSediu = new char[len + 1];
        strcpy(adresaSediu, adresa);

        len = strlen(contact);
        persoanaContact = new char[len + 1];
        strcpy(persoanaContact, contact);

        if (activ) clientiActivi++;
    }

    ClientCorporativ(const ClientCorporativ& c)
        : numeCompanie(nullptr),
        adresaSediu(nullptr),
        persoanaContact(nullptr),
        nrAngajati(c.nrAngajati),
        codFiscal(c.codFiscal),
        volumTransporturiLunar(c.volumTransporturiLunar),
        esteActiv(c.esteActiv),
        ID_CLIENT(c.ID_CLIENT) {

        size_t len = strlen(c.numeCompanie);
        numeCompanie = new char[len + 1];
        strcpy(numeCompanie, c.numeCompanie);

        len = strlen(c.adresaSediu);
        adresaSediu = new char[len + 1];
        strcpy(adresaSediu, c.adresaSediu);

        len = strlen(c.persoanaContact);
        persoanaContact = new char[len + 1];
        strcpy(persoanaContact, c.persoanaContact);
    }

    ~ClientCorporativ() {
        delete[] numeCompanie;
        delete[] adresaSediu;
        delete[] persoanaContact;
    }

    ClientCorporativ& operator=(const ClientCorporativ& c) {
        if (this != &c) {
            delete[] numeCompanie;
            delete[] adresaSediu;
            delete[] persoanaContact;

            size_t len = strlen(c.numeCompanie);
            numeCompanie = new char[len + 1];
            strcpy(numeCompanie, c.numeCompanie);

            len = strlen(c.adresaSediu);
            adresaSediu = new char[len + 1];
            strcpy(adresaSediu, c.adresaSediu);

            len = strlen(c.persoanaContact);
            persoanaContact = new char[len + 1];
            strcpy(persoanaContact, c.persoanaContact);

            nrAngajati = c.nrAngajati;
            codFiscal = c.codFiscal;
            volumTransporturiLunar = c.volumTransporturiLunar;
            esteActiv = c.esteActiv;
            ID_CLIENT = c.ID_CLIENT;
        }
        return *this;
    }

    // GETTERI
    const char* getNumeCompanie() const { return numeCompanie; }
    int getNrAngajati() const { return nrAngajati; }
    string getCodFiscal() const { return codFiscal; }
    double getVolumTransporturiLunar() const { return volumTransporturiLunar; }
    const char* getAdresaSediu() const { return adresaSediu; }
    const char* getPersoanaContact() const { return persoanaContact; }
    bool getEsteActiv() const { return esteActiv; }
    int getID() const { return ID_CLIENT; }

    // SETTERI
    void setNumeCompanie(const char* nume) {
        if (nume != nullptr) {
            delete[] numeCompanie;
            size_t len = strlen(nume);
            numeCompanie = new char[len + 1];
            strcpy(numeCompanie, nume);
        }
    }

    void setNrAngajati(int nr) {
        if (nr >= 0) nrAngajati = nr;
    }

    void setCodFiscal(string cod) {
        codFiscal = cod;
    }

    void setVolumTransporturiLunar(double volum) {
        if (volum >= 0) volumTransporturiLunar = volum;
    }

    void setAdresaSediu(const char* adresa) {
        if (adresa != nullptr) {
            delete[] adresaSediu;
            size_t len = strlen(adresa);
            adresaSediu = new char[len + 1];
            strcpy(adresaSediu, adresa);
        }
    }

    void setPersoanaContact(const char* contact) {
        if (contact != nullptr) {
            delete[] persoanaContact;
            size_t len = strlen(contact);
            persoanaContact = new char[len + 1];
            strcpy(persoanaContact, contact);
        }
    }

    void setEsteActiv(bool activ) {
        esteActiv = activ;
    }

    //  OPERATORI SUPRÂNCĂRCAȚI - FAZA 3 

    // 1. Operator + (adaugă angajați la client)
    ClientCorporativ operator+(int angajatiNoi) const {
        ClientCorporativ temp(*this);
        temp.nrAngajati += angajatiNoi;
        return temp;
    }

    // 2. Operator - (scade angajați de la client)
    ClientCorporativ operator-(int angajatiPlecat) const {
        ClientCorporativ temp(*this);
        temp.nrAngajati = (temp.nrAngajati - angajatiPlecat >= 0) ?
            temp.nrAngajati - angajatiPlecat : 0;
        return temp;
    }

    // 3. Operator += (crește volumul transporturi)
    ClientCorporativ& operator+=(double volumSuplimentar) {
        volumTransporturiLunar += volumSuplimentar;
        return *this;
    }

    // 4. Operator == (compară doi clienți după volum)
    bool operator==(const ClientCorporativ& c) const {
        return volumTransporturiLunar == c.volumTransporturiLunar;
    }

    // 5. Operator < (compară doi clienți după volum)
    bool operator<(const ClientCorporativ& c) const {
        return volumTransporturiLunar < c.volumTransporturiLunar;
    }

    // 6. Operator > (compară doi clienți după volum)
    bool operator>(const ClientCorporativ& c) const {
        return volumTransporturiLunar > c.volumTransporturiLunar;
    }

    // 7. Operator ! (verifică dacă clientul este inactiv)
    bool operator!() const {
        return !esteActiv;
    }

    // 8. Operator cast la int (returnează numărul de angajați)
    explicit operator int() const {
        return nrAngajati;
    }

    // 9. Operator [] (returnează caracterul de la poziția specificată din nume)
    char operator[](int index) const {
        if (index >= 0 && index < (int)strlen(numeCompanie)) {
            return numeCompanie[index];
        }
        return '\0';
    }

    // 10. Operator ++ pre-incrementare (crește numărul de angajați)
    ClientCorporativ& operator++() {
        nrAngajati++;
        return *this;
    }

    // 11. Operator ++ post-incrementare
    ClientCorporativ operator++(int) {
        ClientCorporativ temp(*this);
        nrAngajati++;
        return temp;
    }

    // 12. Operator () - calculează costul pe angajat
    double operator()(double costTotal) const {
        if (nrAngajati > 0) {
            return costTotal / nrAngajati;
        }
        return 0.0;
    }

    // Functii statice
    static double calculeazaPretFinal(double pretInitial, double volumLunar) {
        double discountTotal = discountCorporativ;
        if (volumLunar > 1000) discountTotal += 0.05;
        if (volumLunar > 5000) discountTotal += 0.10;
        return pretInitial * (1 - discountTotal);
    }

    static void setDiscount(double discount) {
        if (discount >= 0 && discount <= 1) discountCorporativ = discount;
    }

    static double getDiscount() { return discountCorporativ; }
    static int getNumarTotalClienti() { return numarTotalClienti; }
    static int getClientiActivi() { return clientiActivi; }

    void citeste() {
        cout << "\n--- Introduceti datele clientului ---" << endl;
        cout << "Nume companie: ";
        char buffer[200];
        cin.getline(buffer, 200);
        setNumeCompanie(buffer);

        cout << "Adresa sediu: ";
        cin.getline(buffer, 200);
        setAdresaSediu(buffer);

        cout << "Persoana contact: ";
        cin.getline(buffer, 200);
        setPersoanaContact(buffer);

        cout << "Numar angajati: ";
        cin >> nrAngajati;
        cout << "Cod fiscal (ex: RO12345678): ";
        cin >> codFiscal;
        cout << "Volum transporturi lunar (tone): ";
        cin >> volumTransporturiLunar;
        cin.ignore();
    }

    void afiseaza() const {
        cout << "\n" << endl;
        cout << "CLIENT CORPORATIV #" << ID_CLIENT << endl;
        cout << "" << endl;
        cout << "Companie: " << numeCompanie << endl;
        cout << "Adresa: " << adresaSediu << endl;
        cout << "Contact: " << persoanaContact << endl;
        cout << "Angajati: " << nrAngajati << endl;
        cout << "Cod Fiscal: " << codFiscal << endl;
        cout << "Volum/Luna: " << volumTransporturiLunar << " tone" << endl;
        cout << "Status: " << (esteActiv ? "ACTIV" : "INACTIV") << endl;
        cout << "" << endl;
    }

    // Declarare functii friend
    friend void aplicaDiscountSpecial(ClientCorporativ& client, double discountExtra);
    friend void afiseazaRaportClient(const ClientCorporativ& client);

    // Operatori friend pentru << și >>
    friend ostream& operator<<(ostream& out, const ClientCorporativ& c);
    friend istream& operator>>(istream& in, ClientCorporativ& c);
};

//
// CLASA 2: CursaInternationala - FAZA 3 (cu operatori)
//
class CursaInternationala {
private:
    char* taraOrigine;
    string taraDestinatie;
    double distantaKm;
    double durataTimpOre;
    int nrColete;
    char* soferId;
    char* dataPlecarii;
    bool esteFinalizata;
    string COD_CURSA;

    static double taxaVamalaFixa;
    static int numarTotalCurse;
    static int curseFinalizate;

public:
    CursaInternationala()
        : taraOrigine(nullptr),
        soferId(nullptr),
        dataPlecarii(nullptr),
        taraDestinatie("Necunoscuta"),
        distantaKm(0.0),
        durataTimpOre(0.0),
        nrColete(0),
        esteFinalizata(false),
        COD_CURSA("CURS-" + to_string(++numarTotalCurse)) {

        taraOrigine = new char[200];
        strcpy(taraOrigine, "Necunoscuta");
        soferId = new char[200];
        strcpy(soferId, "SOF-000");
        dataPlecarii = new char[200];
        strcpy(dataPlecarii, "01/01/2024");
    }

    CursaInternationala(const char* origine, string destinatie, double distanta,
        double durata, int colete, const char* sofer, const char* data)
        : taraOrigine(nullptr),
        soferId(nullptr),
        dataPlecarii(nullptr),
        taraDestinatie(destinatie),
        distantaKm(distanta),
        durataTimpOre(durata),
        nrColete(colete),
        esteFinalizata(false),
        COD_CURSA("CURS-" + to_string(++numarTotalCurse)) {

        size_t len = strlen(origine);
        taraOrigine = new char[len + 1];
        strcpy(taraOrigine, origine);

        len = strlen(sofer);
        soferId = new char[len + 1];
        strcpy(soferId, sofer);

        len = strlen(data);
        dataPlecarii = new char[len + 1];
        strcpy(dataPlecarii, data);
    }

    CursaInternationala(const CursaInternationala& c)
        : taraOrigine(nullptr),
        soferId(nullptr),
        dataPlecarii(nullptr),
        taraDestinatie(c.taraDestinatie),
        distantaKm(c.distantaKm),
        durataTimpOre(c.durataTimpOre),
        nrColete(c.nrColete),
        esteFinalizata(c.esteFinalizata),
        COD_CURSA(c.COD_CURSA) {

        size_t len = strlen(c.taraOrigine);
        taraOrigine = new char[len + 1];
        strcpy(taraOrigine, c.taraOrigine);

        len = strlen(c.soferId);
        soferId = new char[len + 1];
        strcpy(soferId, c.soferId);

        len = strlen(c.dataPlecarii);
        dataPlecarii = new char[len + 1];
        strcpy(dataPlecarii, c.dataPlecarii);
    }

    ~CursaInternationala() {
        delete[] taraOrigine;
        delete[] soferId;
        delete[] dataPlecarii;
    }

    CursaInternationala& operator=(const CursaInternationala& c) {
        if (this != &c) {
            delete[] taraOrigine;
            delete[] soferId;
            delete[] dataPlecarii;

            size_t len = strlen(c.taraOrigine);
            taraOrigine = new char[len + 1];
            strcpy(taraOrigine, c.taraOrigine);

            len = strlen(c.soferId);
            soferId = new char[len + 1];
            strcpy(soferId, c.soferId);

            len = strlen(c.dataPlecarii);
            dataPlecarii = new char[len + 1];
            strcpy(dataPlecarii, c.dataPlecarii);

            taraDestinatie = c.taraDestinatie;
            distantaKm = c.distantaKm;
            durataTimpOre = c.durataTimpOre;
            nrColete = c.nrColete;
            esteFinalizata = c.esteFinalizata;
            COD_CURSA = c.COD_CURSA;
        }
        return *this;
    }

    // GETTERI
    const char* getTaraOrigine() const { return taraOrigine; }
    string getTaraDestinatie() const { return taraDestinatie; }
    double getDistantaKm() const { return distantaKm; }
    double getDurataTimpOre() const { return durataTimpOre; }
    int getNrColete() const { return nrColete; }
    const char* getSoferId() const { return soferId; }
    const char* getDataPlecarii() const { return dataPlecarii; }
    bool getEsteFinalizata() const { return esteFinalizata; }
    string getCodCursa() const { return COD_CURSA; }

    // SETTERI
    void setTaraOrigine(const char* tara) {
        if (tara != nullptr) {
            delete[] taraOrigine;
            size_t len = strlen(tara);
            taraOrigine = new char[len + 1];
            strcpy(taraOrigine, tara);
        }
    }

    void setTaraDestinatie(string tara) {
        taraDestinatie = tara;
    }

    void setDistantaKm(double distanta) {
        if (distanta >= 0) distantaKm = distanta;
    }

    void setDurataTimpOre(double durata) {
        if (durata >= 0) durataTimpOre = durata;
    }

    void setNrColete(int nr) {
        if (nr >= 0) nrColete = nr;
    }

    void setSoferId(const char* sofer) {
        if (sofer != nullptr) {
            delete[] soferId;
            size_t len = strlen(sofer);
            soferId = new char[len + 1];
            strcpy(soferId, sofer);
        }
    }

    void setDataPlecarii(const char* data) {
        if (data != nullptr) {
            delete[] dataPlecarii;
            size_t len = strlen(data);
            dataPlecarii = new char[len + 1];
            strcpy(dataPlecarii, data);
        }
    }

    void setEsteFinalizata(bool finalizata) {
        if (finalizata && !esteFinalizata) curseFinalizate++;
        esteFinalizata = finalizata;
    }

    // = OPERATORI SUPRÂNCĂRCAȚI - FAZA 3 =

    // 1. Operator + (adaugă colete la cursă)
    CursaInternationala operator+(int coleteNoi) const {
        CursaInternationala temp(*this);
        temp.nrColete += coleteNoi;
        return temp;
    }

    // 2. Operator - (scade colete din cursă)
    CursaInternationala operator-(int coleteScazute) const {
        CursaInternationala temp(*this);
        temp.nrColete = (temp.nrColete - coleteScazute >= 0) ?
            temp.nrColete - coleteScazute : 0;
        return temp;
    }

    // 3. Operator += (crește distanța)
    CursaInternationala& operator+=(double distantaExtra) {
        distantaKm += distantaExtra;
        return *this;
    }

    // 4. Operator == (compară două curse după distanță)
    bool operator==(const CursaInternationala& c) const {
        return distantaKm == c.distantaKm;
    }

    // 5. Operator < (compară după distanță)
    bool operator<(const CursaInternationala& c) const {
        return distantaKm < c.distantaKm;
    }

    // 6. Operator > (compară după distanță)
    bool operator>(const CursaInternationala& c) const {
        return distantaKm > c.distantaKm;
    }

    // 7. Operator ! (verifică dacă cursa nu este finalizată)
    bool operator!() const {
        return !esteFinalizata;
    }

    // 8. Operator cast la double (returnează distanța)
    explicit operator double() const {
        return distantaKm;
    }

    // 9. Operator [] (returnează caracterul de la poziția specificată din origine)
    char operator[](int index) const {
        if (index >= 0 && index < (int)strlen(taraOrigine)) {
            return taraOrigine[index];
        }
        return '\0';
    }

    // 10. Operator ++ pre-incrementare (adaugă un colet)
    CursaInternationala& operator++() {
        nrColete++;
        return *this;
    }

    // 11. Operator ++ post-incrementare
    CursaInternationala operator++(int) {
        CursaInternationala temp(*this);
        nrColete++;
        return temp;
    }

    // 12. Operator () - calculează viteza medie
    double operator()() const {
        if (durataTimpOre > 0) {
            return distantaKm / durataTimpOre;
        }
        return 0.0;
    }

    static double calculeazaCostTotalCursa(double distanta, int nrColete, bool urgenta = false) {
        double costPerKm = (distanta > 2000) ? 0.45 : 0.50;
        double costTransport = distanta * costPerKm;
        double costColete = nrColete * 12.0;
        double taxaUrgenta = urgenta ? 150.0 : 0.0;
        return costTransport + costColete + taxaVamalaFixa + taxaUrgenta;
    }

    static void setTaxaVamala(double taxa) {
        if (taxa >= 0) taxaVamalaFixa = taxa;
    }

    static double getTaxaVamala() { return taxaVamalaFixa; }
    static int getNumarTotalCurse() { return numarTotalCurse; }
    static int getCurseFinalizate() { return curseFinalizate; }

    void citeste() {
        cout << "\n--- Introduceti datele cursei ---" << endl;
        char buffer[200];
        cout << "Tara origine: ";
        cin.getline(buffer, 200);
        setTaraOrigine(buffer);

        cout << "Tara destinatie: ";
        getline(cin, taraDestinatie);

        cout << "Distanta (km): ";
        cin >> distantaKm;
        cout << "Durata (ore): ";
        cin >> durataTimpOre;
        cout << "Numar colete: ";
        cin >> nrColete;
        cin.ignore();

        cout << "ID sofer: ";
        cin.getline(buffer, 200);
        setSoferId(buffer);

        cout << "Data plecarii (DD/MM/YYYY): ";
        cin.getline(buffer, 200);
        setDataPlecarii(buffer);
    }

    void afiseaza() const {
        cout << "\n" << endl;
        cout << "CURSA INTERNATIONALA" << endl;
        cout << "" << endl;
        cout << "Cod: " << COD_CURSA << endl;
        cout << "Ruta: " << taraOrigine << " -> " << taraDestinatie << endl;
        cout << "Distanta: " << distantaKm << " km" << endl;
        cout << "Durata: " << durataTimpOre << " ore" << endl;
        cout << "Colete: " << nrColete << endl;
        cout << "Sofer: " << soferId << endl;
        cout << "Data: " << dataPlecarii << endl;
        cout << "Status: " << (esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;
        cout << "" << endl;
    }

    friend void optimizeazaRuta(CursaInternationala& cursa);
    friend void afiseazaRaportCursa(const CursaInternationala& cursa);
    friend ostream& operator<<(ostream& out, const CursaInternationala& c);
    friend istream& operator>>(istream& in, CursaInternationala& c);
};

//
// CLASA 3: Factura - FAZA 3 (cu operatori)
//
class Factura {
private:
    char* numarFactura;
    string dataEmitere;
    char* clientDenumire;
    double* preturiServicii;
    int nrServicii;
    double TVA;
    char* moneda;
    bool estePlatita;
    int ID_FACTURA;

    static double cotaTVA;
    static int numarTotalFacturi;
    static double incasariTotale;

public:
    Factura()
        : numarFactura(nullptr),
        clientDenumire(nullptr),
        moneda(nullptr),
        preturiServicii(nullptr),
        dataEmitere("01/01/2024"),
        nrServicii(0),
        TVA(cotaTVA),
        estePlatita(false),
        ID_FACTURA(++numarTotalFacturi) {

        numarFactura = new char[50];
        strcpy(numarFactura, "FACT-000");
        clientDenumire = new char[200];
        strcpy(clientDenumire, "Nedefinit");
        moneda = new char[10];
        strcpy(moneda, "RON");
    }


   
    // --- SETTERS CORECTE pentru CLASA TA ---

    void setNumarFactura(const char* nr) {
        if (numarFactura != nullptr) delete[] numarFactura;
        numarFactura = new char[strlen(nr) + 1];
        strcpy(numarFactura, nr);
    }

    void setDataEmitere(const string& dataNoua) {
        dataEmitere = dataNoua;
    }

    void setClientDenumire(const char* den) {
        if (clientDenumire != nullptr) delete[] clientDenumire;
        clientDenumire = new char[strlen(den) + 1];
        strcpy(clientDenumire, den);
    }

    void setMoneda(const char* mon) {
        if (moneda != nullptr) delete[] moneda;
        moneda = new char[strlen(mon) + 1];
        strcpy(moneda, mon);
    }

    void setEstePlatita(bool platita) {
        estePlatita = platita;
    }

    void setPreturiServicii(const double* preturiNoi, int nr) {
        if (preturiServicii != nullptr) delete[] preturiServicii;

        nrServicii = nr;

        if (nrServicii > 0) {
            preturiServicii = new double[nrServicii];
            for (int i = 0; i < nrServicii; i++)
                preturiServicii[i] = preturiNoi[i];
        }
        else {
            preturiServicii = nullptr;
        }
    }


    // --- GETTERS CORECTE pentru CLASA TA ---

    const char* getNumarFactura() const { return numarFactura; }

    string getDataEmitere() const { return dataEmitere; }

    const char* getClientDenumire() const { return clientDenumire; }

    const char* getMoneda() const { return moneda; }

    bool getEstePlatita() const { return estePlatita; }

    int getNrServicii() const { return nrServicii; }

    const double* getPreturiServicii() const { return preturiServicii; }


    Factura(const char* nr, string data, const char* client,
        double* preturi, int nrServ, const char* mon, bool platita)
        : numarFactura(nullptr),
        clientDenumire(nullptr),
        moneda(nullptr),
        preturiServicii(nullptr),
        dataEmitere(data),
        nrServicii(nrServ),
        TVA(cotaTVA),
        estePlatita(platita),
        ID_FACTURA(++numarTotalFacturi) {

        size_t len = strlen(nr);
        numarFactura = new char[len + 1];
        strcpy(numarFactura, nr);

        len = strlen(client);
        clientDenumire = new char[len + 1];
        strcpy(clientDenumire, client);

        len = strlen(mon);
        moneda = new char[len + 1];
        strcpy(moneda, mon);

        if (nrServicii > 0) {
            preturiServicii = new double[nrServicii];
            for (int i = 0; i < nrServicii; i++) {
                preturiServicii[i] = preturi[i];
            }
        }
        else {
            preturiServicii = nullptr;
        }
    }

    Factura(const Factura& f)
        : numarFactura(nullptr),
        clientDenumire(nullptr),
        moneda(nullptr),
        preturiServicii(nullptr),
        dataEmitere(f.dataEmitere),
        nrServicii(f.nrServicii),
        TVA(f.TVA),
        estePlatita(f.estePlatita),
        ID_FACTURA(f.ID_FACTURA) {

        size_t len = strlen(f.numarFactura);
        numarFactura = new char[len + 1];
        strcpy(numarFactura, f.numarFactura);

        len = strlen(f.clientDenumire);
        clientDenumire = new char[len + 1];
        strcpy(clientDenumire, f.clientDenumire);

        len = strlen(f.moneda);
        moneda = new char[len + 1];
        strcpy(moneda, f.moneda);

        if (nrServicii > 0) {
            preturiServicii = new double[nrServicii];
            for (int i = 0; i < nrServicii; i++) {
                preturiServicii[i] = f.preturiServicii[i];
            }
        }
        else {
            preturiServicii = nullptr;
        }
    }

    ~Factura() {
        delete[] numarFactura;
        delete[] clientDenumire;
        delete[] moneda;
        delete[] preturiServicii;
    }

    Factura& operator=(const Factura& f) {
        if (this != &f) {
            delete[] numarFactura;
            delete[] clientDenumire;
            delete[] moneda;
            delete[] preturiServicii;

            size_t len = strlen(f.numarFactura);
            numarFactura = new char[len + 1];
            strcpy(numarFactura, f.numarFactura);

            len = strlen(f.clientDenumire);
            clientDenumire = new char[len + 1];
            strcpy(clientDenumire, f.clientDenumire);

            len = strlen(f.moneda);
            moneda = new char[len + 1];
            strcpy(moneda, f.moneda);

            dataEmitere = f.dataEmitere;
            nrServicii = f.nrServicii;

            if (nrServicii > 0) {
                preturiServicii = new double[nrServicii];
                for (int i = 0; i < nrServicii; i++) {
                    preturiServicii[i] = f.preturiServicii[i];
                }
            }
            else {
                preturiServicii = nullptr;
            }

            TVA = f.TVA;
            estePlatita = f.estePlatita;
            ID_FACTURA = f.ID_FACTURA;
        }
        return *this;
    }


    // = OPERATORI SUPRÂNCĂRCAȚI - FAZA 3 =

    // 1. Operator + (adaugă un serviciu cu preț la factură)
    Factura operator+(double pretNou) const {
        Factura temp(*this);
        double* preturiNoi = new double[temp.nrServicii + 1];
        for (int i = 0; i < temp.nrServicii; i++) {
            preturiNoi[i] = temp.preturiServicii[i];
        }
        preturiNoi[temp.nrServicii] = pretNou;
        delete[] temp.preturiServicii;
        temp.preturiServicii = preturiNoi;
        temp.nrServicii++;
        return temp;
    }

    // 2. Operator - (scade o valoare din toate prețurile)
    Factura operator-(double reducere) const {
        Factura temp(*this);
        for (int i = 0; i < temp.nrServicii; i++) {
            temp.preturiServicii[i] = (temp.preturiServicii[i] - reducere >= 0) ?
                temp.preturiServicii[i] - reducere : 0;
        }
        return temp;
    }

    // 3. Operator += (adaugă la toate prețurile)
    Factura& operator+=(double majorare) {
        for (int i = 0; i < nrServicii; i++) {
            preturiServicii[i] += majorare;
        }
        return *this;
    }

    // 4. Operator == (compară două facturi după total)
    bool operator==(const Factura& f) const {
        return calculeazaTotal() == f.calculeazaTotal();
    }

    // 5. Operator < (compară după total)
    bool operator<(const Factura& f) const {
        return calculeazaTotal() < f.calculeazaTotal();
    }

    // 6. Operator > (compară după total)
    bool operator>(const Factura& f) const {
        return calculeazaTotal() > f.calculeazaTotal();
    }

    // 7. Operator ! (verifică dacă factura nu este plătită)
    bool operator!() const {
        return !estePlatita;
    }

    // 8. Operator cast la double (returnează totalul cu TVA)
    explicit operator double() const {
        return calculeazaTotal() * (1 + TVA);
    }

    // 9. Operator [] (returnează prețul serviciului la indexul specificat)
    double operator[](int index) const {
        if (index >= 0 && index < nrServicii) {
            return preturiServicii[index];
        }
        return 0.0;
    }

    // 10. Operator ++ pre-incrementare (crește TVA cu 1%)
    Factura& operator++() {
        TVA += 0.01;
        return *this;
    }

    // 11. Operator ++ post-incrementare
    Factura operator++(int) {
        Factura temp(*this);
        TVA += 0.01;
        return temp;
    }

    // 12. Operator () - calculează prețul mediu per serviciu
    double operator()() const {
        if (nrServicii > 0) {
            return calculeazaTotal() / nrServicii;
        }
        return 0.0;
    }

    static double calculeazaTotalCuTVA(double sumaBaza) {
        return sumaBaza * (1 + cotaTVA);
    }

    static void setCotaTVA(double cota) {
        if (cota >= 0 && cota <= 1) cotaTVA = cota;
    }

    static double getCotaTVA() { return cotaTVA; }
    static int getNumarTotalFacturi() { return numarTotalFacturi; }
    static double getIncasariTotale() { return incasariTotale; }

    double calculeazaTotal() const {
        double suma = 0;
        for (int i = 0; i < nrServicii; i++) {
            suma += preturiServicii[i];
        }
        return suma;
    }

    void citeste() {
        cout << "\n--- Introduceti datele facturii ---" << endl;
        char buffer[200];
        cout << "Numar factura: ";
        cin.getline(buffer, 50);
        setNumarFactura(buffer);

        cout << "Data emitere (DD/MM/YYYY): ";
        getline(cin, dataEmitere);

        cout << "Denumire client: ";
        cin.getline(buffer, 200);
        setClientDenumire(buffer);

        cout << "Moneda (RON/EUR/USD): ";
        cin.getline(buffer, 10);
        setMoneda(buffer);

        cout << "Numar servicii: ";
        cin >> nrServicii;

        if (nrServicii > 0) {
            delete[] preturiServicii;
            preturiServicii = new double[nrServicii];
            for (int i = 0; i < nrServicii; i++) {
                cout << "Pret serviciu " << (i + 1) << ": ";
                cin >> preturiServicii[i];
            }
        }
        cin.ignore();
    }

    void afiseaza() const {
        cout << "\n" << endl;
        cout << "FACTURA #" << ID_FACTURA << endl;
        cout << "" << endl;
        cout << "Numar: " << numarFactura << endl;
        cout << "Data: " << dataEmitere << endl;
        cout << "Client: " << clientDenumire << endl;
        cout << "Nr. servicii: " << nrServicii << endl;
        double total = calculeazaTotal();
        cout << "Total fara TVA: " << total << " " << moneda << endl;
        cout << "TVA (" << (TVA * 100) << "%): " << (total * TVA) << " " << moneda << endl;
        cout << "Total cu TVA: " << (total * (1 + TVA)) << " " << moneda << endl;
        cout << "Status: " << (estePlatita ? "PLATITA" : "NEPLATITA") << endl;
        cout << "" << endl;
    }

    void marcheazaPlatita() {
        if (!estePlatita) {
            estePlatita = true;
            double total = calculeazaTotal() * (1 + TVA);
            incasariTotale += total;
            cout << "Factura " << numarFactura << " marcata ca PLATITA!" << endl;
            cout << "Suma incasata: " << total << " " << moneda << endl;
        }
        else {
            cout << "Factura este deja platita!" << endl;
        }
    }

    friend void aplicaReducere(Factura& factura, double procentReducere);
    friend void afiseazaRaportFactura(const Factura& factura);
    friend ostream& operator<<(ostream& out, const Factura& f);
    friend istream& operator>>(istream& in, Factura& f);
};

// Initializare membri statici
double ClientCorporativ::discountCorporativ = 0.15;
int ClientCorporativ::numarTotalClienti = 0;
int ClientCorporativ::clientiActivi = 0;
double CursaInternationala::taxaVamalaFixa = 75.0;
int CursaInternationala::numarTotalCurse = 0;
int CursaInternationala::curseFinalizate = 0;
double Factura::cotaTVA = 0.19;
int Factura::numarTotalFacturi = 0;
double Factura::incasariTotale = 0.0;

//
// OPERATORI << SI >> PENTRU ClientCorporativ
//
ostream& operator<<(ostream& out, const ClientCorporativ& c) {
    out << "\n" << endl;
    out << "CLIENT CORPORATIV #" << c.ID_CLIENT << endl;
    out << "" << endl;
    out << "Companie: " << c.numeCompanie << endl;
    out << "Adresa: " << c.adresaSediu << endl;
    out << "Contact: " << c.persoanaContact << endl;
    out << "Angajati: " << c.nrAngajati << endl;
    out << "Cod Fiscal: " << c.codFiscal << endl;
    out << "Volum/Luna: " << c.volumTransporturiLunar << " tone" << endl;
    out << "Status: " << (c.esteActiv ? "ACTIV" : "INACTIV") << endl;
    out << "" << endl;
    return out;
}

istream& operator>>(istream& in, ClientCorporativ& c) {
    cout << "Nume companie: ";
    char buffer[200];
    in.getline(buffer, 200);
    c.setNumeCompanie(buffer);

    cout << "Adresa sediu: ";
    in.getline(buffer, 200);
    c.setAdresaSediu(buffer);

    cout << "Persoana contact: ";
    in.getline(buffer, 200);
    c.setPersoanaContact(buffer);

    cout << "Numar angajati: ";
    in >> c.nrAngajati;

    cout << "Cod fiscal: ";
    in >> c.codFiscal;

    cout << "Volum transporturi lunar: ";
    in >> c.volumTransporturiLunar;

    in.ignore();
    return in;
}

//
// OPERATORI << SI >> PENTRU CursaInternationala
//
ostream& operator<<(ostream& out, const CursaInternationala& c) {
    out << "\n" << endl;
    out << "CURSA INTERNATIONALA" << endl;
    out << "" << endl;
    out << "Cod: " << c.COD_CURSA << endl;
    out << "Ruta: " << c.taraOrigine << " -> " << c.taraDestinatie << endl;
    out << "Distanta: " << c.distantaKm << " km" << endl;
    out << "Durata: " << c.durataTimpOre << " ore" << endl;
    out << "Colete: " << c.nrColete << endl;
    out << "Sofer: " << c.soferId << endl;
    out << "Data plecare: " << c.dataPlecarii << endl;
    out << "Status: " << (c.esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;
    out << "" << endl;
    return out;
}

istream& operator>>(istream& in, CursaInternationala& c) {
    cout << "Tara origine: ";
    char buffer[200];
    in.getline(buffer, 200);
    c.setTaraOrigine(buffer);

    cout << "Tara destinatie: ";
    string dest;
    getline(in, dest);
    c.setTaraDestinatie(dest);

    cout << "Distanta (km): ";
    in >> c.distantaKm;
    cout << "Durata (ore): ";
    in >> c.durataTimpOre;
    cout << "Numar colete: ";
    in >> c.nrColete;
    in.ignore();

    cout << "ID sofer: ";
    in.getline(buffer, 200);
    c.setSoferId(buffer);

    cout << "Data plecarii (DD/MM/YYYY): ";
    in.getline(buffer, 200);
    c.setDataPlecarii(buffer);

    return in;
}

//
// OPERATORI << SI >> PENTRU Factura
//
ostream& operator<<(ostream& out, const Factura& f) {
    out << "\n" << endl;
    out << "FACTURA #" << f.ID_FACTURA << endl;
    out << "" << endl;
    out << "Numar: " << f.numarFactura << endl;
    out << "Data: " << f.dataEmitere << endl;
    out << "Client: " << f.clientDenumire << endl;
    out << "Nr. servicii: " << f.nrServicii << endl;
    double total = f.calculeazaTotal();
    out << "Total fara TVA: " << total << " " << f.moneda << endl;
    out << "TVA (" << (f.TVA * 100) << "%): " << (total * f.TVA) << " " << f.moneda << endl;
    out << "Total cu TVA: " << (total * (1 + f.TVA)) << " " << f.moneda << endl;
    out << "Status: " << (f.estePlatita ? "PLATITA" : "NEPLATITA") << endl;
    out << "" << endl;
    return out;
}

istream& operator>>(istream& in, Factura& f) {
    cout << "Numar factura: ";
    char buffer[200];
    in.getline(buffer, 200);
    f.setNumarFactura(buffer);

    cout << "Data emitere (DD/MM/YYYY): ";
    string data;
    getline(in, data);
    f.setDataEmitere(data);

    cout << "Denumire client: ";
    in.getline(buffer, 200);
    f.setClientDenumire(buffer);

    cout << "Moneda (RON/EUR/USD): ";
    in.getline(buffer, 10);
    f.setMoneda(buffer);

    cout << "Numar servicii: ";
    in >> f.nrServicii;
    if (f.nrServicii > 0) {
        delete[] f.preturiServicii;
        f.preturiServicii = new double[f.nrServicii];
        for (int i = 0; i < f.nrServicii; i++) {
            cout << "Pret serviciu " << (i + 1) << ": ";
            in >> f.preturiServicii[i];
        }
    }
    in.ignore();
    return in;
}

//
// FUNCTII GLOBALE FRIEND - PENTRU ClientCorporativ
//
void aplicaDiscountSpecial(ClientCorporativ& client, double discountExtra) {
    cout << "\n APLICARE DISCOUNT SPECIAL " << endl;
    cout << "Client: " << client.numeCompanie << endl;
    cout << "Volum curent: " << client.volumTransporturiLunar << " tone" << endl;

    double volumNou = client.volumTransporturiLunar * (1 + discountExtra);
    client.volumTransporturiLunar = volumNou;

    cout << "Discount aplicat: " << (discountExtra * 100) << "%" << endl;
    cout << "Volum nou: " << client.volumTransporturiLunar << " tone" << endl;
}

void afiseazaRaportClient(const ClientCorporativ& client) {
    cout << "\n= RAPORT CLIENT DETALIAT =" << endl;
    cout << "ID: " << client.ID_CLIENT << endl;
    cout << "Companie: " << client.numeCompanie << endl;
    cout << "Sediu: " << client.adresaSediu << endl;
    cout << "Contact: " << client.persoanaContact << endl;
    cout << "Angajati: " << client.nrAngajati << endl;
    cout << "Cod Fiscal: " << client.codFiscal << endl;
    cout << "Volum lunar: " << client.volumTransporturiLunar << " tone" << endl;
    cout << "Status: " << (client.esteActiv ? "ACTIV" : "INACTIV") << endl;

    // Calcule suplimentare
    double pretEstimat = 10000.0; // Pret mediu per transport
    double pretFinal = ClientCorporativ::calculeazaPretFinal(pretEstimat, client.volumTransporturiLunar);
    cout << "\nANALIZA FINANCIARA:" << endl;
    cout << "Pret standard (estimat): " << pretEstimat << " EUR" << endl;
    cout << "Pret cu discount: " << pretFinal << " EUR" << endl;
    cout << "Economie lunara: " << (pretEstimat - pretFinal) << " EUR" << endl;
    cout << "" << endl;
}

//
// FUNCTII GLOBALE FRIEND - PENTRU CursaInternationala
//
void optimizeazaRuta(CursaInternationala& cursa) {
    cout << "\n OPTIMIZARE RUTA " << endl;
    cout << "Cursa: " << cursa.COD_CURSA << endl;
    cout << "Ruta: " << cursa.taraOrigine << " -> " << cursa.taraDestinatie << endl;
    cout << "Distanta initiala: " << cursa.distantaKm << " km" << endl;
    cout << "Durata initiala: " << cursa.durataTimpOre << " ore" << endl;

    // Simulare optimizare: reducere 8% distanta, 10% durata
    double distantaOptimizata = cursa.distantaKm * 0.92;
    double durataOptimizata = cursa.durataTimpOre * 0.90;

    double economieDistanta = cursa.distantaKm - distantaOptimizata;
    double economieDurata = cursa.durataTimpOre - durataOptimizata;

    cursa.distantaKm = distantaOptimizata;
    cursa.durataTimpOre = durataOptimizata;

    cout << "\nDupa optimizare:" << endl;
    cout << "Distanta noua: " << cursa.distantaKm << " km (economie: "
        << economieDistanta << " km)" << endl;
    cout << "Durata noua: " << cursa.durataTimpOre << " ore (economie: "
        << economieDurata << " ore)" << endl;
    cout << "" << endl;
}

void afiseazaRaportCursa(const CursaInternationala& cursa) {
    cout << "\n= RAPORT CURSA DETALIAT =" << endl;
    cout << "Cod: " << cursa.COD_CURSA << endl;
    cout << "Origine: " << cursa.taraOrigine << endl;
    cout << "Destinatie: " << cursa.taraDestinatie << endl;
    cout << "Distanta: " << cursa.distantaKm << " km" << endl;
    cout << "Durata: " << cursa.durataTimpOre << " ore" << endl;
    cout << "Colete: " << cursa.nrColete << endl;
    cout << "Sofer: " << cursa.soferId << endl;
    cout << "Data plecare: " << cursa.dataPlecarii << endl;
    cout << "Status: " << (cursa.esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;

    // Calcule suplimentare
    double cost = CursaInternationala::calculeazaCostTotalCursa(
        cursa.distantaKm, cursa.nrColete, false);
    double vitezaMedie = (cursa.durataTimpOre > 0) ? (cursa.distantaKm / cursa.durataTimpOre) : 0;

    cout << "\nANALIZA TEHNICA:" << endl;
    cout << "Cost total estimat: " << cost << " EUR" << endl;
    cout << "Viteza medie: " << vitezaMedie << " km/h" << endl;
    cout << "Cost per km: " << ((cursa.distantaKm > 0) ? (cost / cursa.distantaKm) : 0) << " EUR/km" << endl;
    cout << "Cost per colet: " << ((cursa.nrColete > 0) ? (cost / cursa.nrColete) : 0) << " EUR/colet" << endl;
    cout << "" << endl;
}

//
// FUNCTII GLOBALE FRIEND - PENTRU Factura
//
void aplicaReducere(Factura& factura, double procentReducere) {
    cout << "\n APLICARE REDUCERE FACTURA " << endl;
    cout << "Factura: " << factura.numarFactura << endl;
    cout << "Client: " << factura.clientDenumire << endl;

    double totalInitial = factura.calculeazaTotal();
    cout << "Total initial (fara TVA): " << totalInitial << " " << factura.moneda << endl;
    cout << "Reducere aplicata: " << (procentReducere * 100) << "%" << endl;

    // Aplica reducere pe toate preturile
    for (int i = 0; i < factura.nrServicii; i++) {
        factura.preturiServicii[i] *= (1 - procentReducere);
    }

    double totalNou = factura.calculeazaTotal();
    cout << "Total nou (fara TVA): " << totalNou << " " << factura.moneda << endl;
    cout << "Economie: " << (totalInitial - totalNou) << " " << factura.moneda << endl;
    cout << "" << endl;
}

void afiseazaRaportFactura(const Factura& factura) {
    cout << "\n= RAPORT FACTURA DETALIAT =" << endl;
    cout << "ID: " << factura.ID_FACTURA << endl;
    cout << "Numar: " << factura.numarFactura << endl;
    cout << "Data emitere: " << factura.dataEmitere << endl;
    cout << "Client: " << factura.clientDenumire << endl;
    cout << "Moneda: " << factura.moneda << endl;
    cout << "Status: " << (factura.estePlatita ? "PLATITA" : "NEPLATITA") << endl;

    cout << "\nDETALII SERVICII:" << endl;
    for (int i = 0; i < factura.nrServicii; i++) {
        cout << "  Serviciu " << (i + 1) << ": "
            << factura.preturiServicii[i] << " " << factura.moneda << endl;
    }

    double total = factura.calculeazaTotal();
    double tva = total * factura.TVA;
    double totalCuTVA = total + tva;

    cout << "\nANALIZA FINANCIARA:" << endl;
    cout << "Subtotal: " << total << " " << factura.moneda << endl;
    cout << "TVA (" << (factura.TVA * 100) << "%): " << tva << " " << factura.moneda << endl;
    cout << "Total cu TVA: " << totalCuTVA << " " << factura.moneda << endl;
    if (factura.nrServicii > 0)
        cout << "Pret mediu per serviciu: " << (total / factura.nrServicii)
        << " " << factura.moneda << endl;
    cout << "==" << endl;
}

//
// CLASA 4: ComandaTransport - FAZA 5 (relatii has-a cu celelalte clase)
//
class ComandaTransport {
private:
    char* numarComanda;
    string dataComanda;

    // RELATII HAS-A cu celelalte clase
    ClientCorporativ* client;              // Pointer la client (has-a)
    CursaInternationala cursaPrincipala;   // Obiect cursa (has-a)
    Factura* factura;                      // Pointer la factura (has-a)
    vector<CursaInternationala*> curseAditionale;  // Vector de pointeri (has-a)

    char* observatii;
    bool esteFinalizata;
    double valoareTotala;
    int ID_COMANDA;

    static int numarTotalComenzi;
    static double incasariTotale;

public:
    // Constructor fara parametri
    ComandaTransport()
        : numarComanda(nullptr),
        dataComanda("01/01/2024"),
        client(nullptr),
        cursaPrincipala(),
        factura(nullptr),
        observatii(nullptr),
        esteFinalizata(false),
        valoareTotala(0.0),
        ID_COMANDA(++numarTotalComenzi) {

        numarComanda = new char[50];
        strcpy(numarComanda, "CMD-000");

        observatii = new char[500];
        strcpy(observatii, "Fara observatii");
    }

    // Constructor cu parametri
    ComandaTransport(const char* numar, string data, ClientCorporativ* cli,
        const CursaInternationala& cursa, Factura* fact, const char* obs)
        : numarComanda(nullptr),
        dataComanda(data),
        client(cli),
        cursaPrincipala(cursa),
        factura(fact),
        observatii(nullptr),
        esteFinalizata(false),
        valoareTotala(0.0),
        ID_COMANDA(++numarTotalComenzi) {

        size_t len = strlen(numar);
        numarComanda = new char[len + 1];
        strcpy(numarComanda, numar);

        len = strlen(obs);
        observatii = new char[len + 1];
        strcpy(observatii, obs);

        calculeazaValoareTotala();
    }

    // Constructor de copiere
    ComandaTransport(const ComandaTransport& c)
        : numarComanda(nullptr),
        dataComanda(c.dataComanda),
        client(c.client),
        cursaPrincipala(c.cursaPrincipala),
        factura(c.factura),
        observatii(nullptr),
        esteFinalizata(c.esteFinalizata),
        valoareTotala(c.valoareTotala),
        ID_COMANDA(c.ID_COMANDA) {

        if (c.numarComanda) {
            size_t len = strlen(c.numarComanda);
            numarComanda = new char[len + 1];
            strcpy(numarComanda, c.numarComanda);
        }

        if (c.observatii) {
            size_t len = strlen(c.observatii);
            observatii = new char[len + 1];
            strcpy(observatii, c.observatii);
        }

        // Copiere vector de pointeri (shallow copy)
        curseAditionale = c.curseAditionale;
    }

    // Destructor
    ~ComandaTransport() {
        delete[] numarComanda;
        delete[] observatii;
        // Nu stergem pointerii client si factura - sunt gestionate extern
        // Nu stergem cursele din vector - sunt gestionate extern
    }

    // Operator de atribuire
    ComandaTransport& operator=(const ComandaTransport& c) {
        if (this != &c) {
            delete[] numarComanda;
            delete[] observatii;

            if (c.numarComanda) {
                size_t len = strlen(c.numarComanda);
                numarComanda = new char[len + 1];
                strcpy(numarComanda, c.numarComanda);
            }

            if (c.observatii) {
                size_t len = strlen(c.observatii);
                observatii = new char[len + 1];
                strcpy(observatii, c.observatii);
            }

            dataComanda = c.dataComanda;
            client = c.client;
            cursaPrincipala = c.cursaPrincipala;
            factura = c.factura;
            curseAditionale = c.curseAditionale;
            esteFinalizata = c.esteFinalizata;
            valoareTotala = c.valoareTotala;
            ID_COMANDA = c.ID_COMANDA;
        }
        return *this;
    }

    // GETTERI
    const char* getNumarComanda() const { return numarComanda; }
    string getDataComanda() const { return dataComanda; }
    ClientCorporativ* getClient() const { return client; }
    CursaInternationala getCursaPrincipala() const { return cursaPrincipala; }
    Factura* getFactura() const { return factura; }
    const char* getObservatii() const { return observatii; }
    bool getEsteFinalizata() const { return esteFinalizata; }
    double getValoareTotala() const { return valoareTotala; }
    int getID() const { return ID_COMANDA; }
    const vector<CursaInternationala*>& getCurseAditionale() const { return curseAditionale; }

    // SETTERI
    void setNumarComanda(const char* numar) {
        if (numar != nullptr) {
            delete[] numarComanda;
            size_t len = strlen(numar);
            numarComanda = new char[len + 1];
            strcpy(numarComanda, numar);
        }
    }

    void setDataComanda(string data) {
        dataComanda = data;
    }

    void setClient(ClientCorporativ* cli) {
        client = cli;
    }

    void setCursaPrincipala(const CursaInternationala& cursa) {
        cursaPrincipala = cursa;
    }

    void setFactura(Factura* fact) {
        factura = fact;
    }

    void setObservatii(const char* obs) {
        if (obs != nullptr) {
            delete[] observatii;
            size_t len = strlen(obs);
            observatii = new char[len + 1];
            strcpy(observatii, obs);
        }
    }

    void setEsteFinalizata(bool finalizata) {
        esteFinalizata = finalizata;
        if (finalizata) {
            incasariTotale += valoareTotala;
        }
    }

    // Adauga cursa aditionala la comanda
    void adaugaCursaAditionala(CursaInternationala* cursa) {
        if (cursa != nullptr) {
            curseAditionale.push_back(cursa);
            calculeazaValoareTotala();
        }
    }

    // Calculeaza valoarea totala a comenzii
    void calculeazaValoareTotala() {
        valoareTotala = 0.0;

        // Cost cursa principala
        double costPrincipala = CursaInternationala::calculeazaCostTotalCursa(
            cursaPrincipala.getDistantaKm(),
            cursaPrincipala.getNrColete(),
            false
        );
        valoareTotala += costPrincipala;

        // Cost curse aditionale
        for (auto cursa : curseAditionale) {
            double cost = CursaInternationala::calculeazaCostTotalCursa(
                cursa->getDistantaKm(),
                cursa->getNrColete(),
                false
            );
            valoareTotala += cost;
        }

        // Aplica discount daca clientul are volum mare
        if (client != nullptr) {
            double volumClient = client->getVolumTransporturiLunar();
            if (volumClient > 5000) {
                valoareTotala *= 0.90;  // 10% discount
            }
            else if (volumClient > 2000) {
                valoareTotala *= 0.95;  // 5% discount
            }
        }
    }

    // OPERATORI - FAZA 5 (minim 3)

    // 1. Operator + (adauga o cursa aditionala)
    ComandaTransport operator+(CursaInternationala* cursa) const {
        ComandaTransport temp(*this);
        temp.adaugaCursaAditionala(cursa);
        return temp;
    }

    // 2. Operator == (compara doua comenzi dupa valoare)
    bool operator==(const ComandaTransport& c) const {
        return valoareTotala == c.valoareTotala;
    }

    // 3. Operator < (compara dupa valoare)
    bool operator<(const ComandaTransport& c) const {
        return valoareTotala < c.valoareTotala;
    }

    // 4. Operator [] (returneaza cursa aditionala la index)
    CursaInternationala* operator[](int index) const {
        if (index >= 0 && index < (int)curseAditionale.size()) {
            return curseAditionale[index];
        }
        return nullptr;
    }

    // 5. Operator cast la double (returneaza valoarea totala)
    explicit operator double() const {
        return valoareTotala;
    }

    // Metode statice
    static int getNumarTotalComenzi() { return numarTotalComenzi; }
    static double getIncasariTotale() { return incasariTotale; }

    // Metoda de afisare
    void afiseaza() const {
        cout << "\n" << endl;
        cout << "          COMANDA TRANSPORT #" << ID_COMANDA << endl;
        cout << "" << endl;
        cout << "Numar comanda: " << numarComanda << endl;
        cout << "Data: " << dataComanda << endl;

        if (client != nullptr) {
            cout << "\n CLIENT " << endl;
            cout << "Companie: " << client->getNumeCompanie() << endl;
            cout << "Cod fiscal: " << client->getCodFiscal() << endl;
            cout << "Volum lunar: " << client->getVolumTransporturiLunar() << " tone" << endl;
        }
        else {
            cout << "\n CLIENT: Nu este asociat " << endl;
        }

        cout << "\n CURSA PRINCIPALA " << endl;
        cout << "Cod: " << cursaPrincipala.getCodCursa() << endl;
        cout << "Ruta: " << cursaPrincipala.getTaraOrigine() << " -> "
            << cursaPrincipala.getTaraDestinatie() << endl;
        cout << "Distanta: " << cursaPrincipala.getDistantaKm() << " km" << endl;
        cout << "Colete: " << cursaPrincipala.getNrColete() << endl;

        if (!curseAditionale.empty()) {
            cout << "\n  CURSE ADITIONALE (" << curseAditionale.size() << ") " << endl;
            for (size_t i = 0; i < curseAditionale.size(); i++) {
                cout << (i + 1) << ". " << curseAditionale[i]->getCodCursa()
                    << " - " << curseAditionale[i]->getTaraDestinatie()
                    << " (" << curseAditionale[i]->getDistantaKm() << " km)" << endl;
            }
        }

        if (factura != nullptr) {
            cout << "\n FACTURA " << endl;
            cout << "Numar: " << factura->getNumarFactura() << endl;
            cout << "Total factura: " << factura->calculeazaTotal() << " "
                << factura->getMoneda() << endl;
            cout << "Status plata: " << (factura->getEstePlatita() ? "PLATITA" : "NEPLATITA") << endl;
        }
        else {
            cout << "\n FACTURA: Nu este asociata " << endl;
        }

        cout << "\n  DETALII COMANDA " << endl;
        cout << "Valoare totala: " << valoareTotala << " EUR" << endl;
        cout << "Observatii: " << observatii << endl;
        cout << "Status: " << (esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;
        cout << "\n" << endl;
    }

    // Operatori friend
    friend ostream& operator<<(ostream& out, const ComandaTransport& cmd);
    friend istream& operator>>(istream& in, ComandaTransport& cmd);
};

// Initializare membri statici
int ComandaTransport::numarTotalComenzi = 0;
double ComandaTransport::incasariTotale = 0.0;

// Operator 
ostream& operator<<(ostream& out, const ComandaTransport& cmd) {
    out << "\n═══ COMANDA #" << cmd.ID_COMANDA << " ═══" << endl;
    out << "Numar: " << cmd.numarComanda << endl;
    out << "Data: " << cmd.dataComanda << endl;

    if (cmd.client != nullptr) {
        out << "Client: " << cmd.client->getNumeCompanie() << endl;
    }

    out << "Cursa principala: " << cmd.cursaPrincipala.getCodCursa() << endl;
    out << "Curse aditionale: " << cmd.curseAditionale.size() << endl;
    out << "Valoare: " << cmd.valoareTotala << " EUR" << endl;
    out << "Status: " << (cmd.esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;

    return out;
}

// Operator >>
istream& operator>>(istream& in, ComandaTransport& cmd) {
    cout << "Numar comanda: ";
    char buffer[200];
    in.getline(buffer, 200);
    cmd.setNumarComanda(buffer);

    cout << "Data comanda (DD/MM/YYYY): ";
    string data;
    getline(in, data);
    cmd.setDataComanda(data);

    cout << "Observatii: ";
    in.getline(buffer, 500);
    cmd.setObservatii(buffer);

    return in;
}



//  FAZA 6 - METODE PENTRU LUCRU CU FISIERE TEXT SI BINARE
//  CLIENTCORPORATIV - METODE FISIERE


class ClientCorporativFileManager {
public:
    // FISIER TEXT - SCRIERE
    static void salvareTextClient(const ClientCorporativ& client, const char* numeFisier) {
        ofstream f(numeFisier, ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        f << " CLIENT CORPORATIV " << endl;
        f << "ID: " << client.getID() << endl;
        f << "Companie: " << client.getNumeCompanie() << endl;
        f << "Adresa: " << client.getAdresaSediu() << endl;
        f << "Contact: " << client.getPersoanaContact() << endl;
        f << "Angajati: " << client.getNrAngajati() << endl;
        f << "Cod Fiscal: " << client.getCodFiscal() << endl;
        f << "Volum Lunar: " << client.getVolumTransporturiLunar() << endl;
        f << "Activ: " << (client.getEsteActiv() ? "DA" : "NU") << endl;
        f << "" << endl;

        f.close();
        cout << "✓ Client salvat in fisier text: " << numeFisier << endl;
    }

    // FISIER TEXT - CITIRE
    static void citireTextClient(const char* numeFisier) {
        ifstream f(numeFisier);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CONTINUT FISIER TEXT CLIENTI " << endl;
        string linie;
        while (getline(f, linie)) {
            cout << linie << endl;
        }

        f.close();
    }

    // FISIER BINAR - SCRIERE
    static void salvareBinarClient(const ClientCorporativ& client, const char* numeFisier) {
        ofstream f(numeFisier, ios::binary | ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        // Salvare ID
        int id = client.getID();
        f.write((char*)&id, sizeof(int));

        // Salvare nume companie
        int len = strlen(client.getNumeCompanie());
        f.write((char*)&len, sizeof(int));
        f.write(client.getNumeCompanie(), len);

        // Salvare adresa
        len = strlen(client.getAdresaSediu());
        f.write((char*)&len, sizeof(int));
        f.write(client.getAdresaSediu(), len);

        // Salvare contact
        len = strlen(client.getPersoanaContact());
        f.write((char*)&len, sizeof(int));
        f.write(client.getPersoanaContact(), len);

        // Salvare numar angajati
        int angajati = client.getNrAngajati();
        f.write((char*)&angajati, sizeof(int));

        // Salvare cod fiscal
        string codFiscal = client.getCodFiscal();
        len = codFiscal.length();
        f.write((char*)&len, sizeof(int));
        f.write(codFiscal.c_str(), len);

        // Salvare volum
        double volum = client.getVolumTransporturiLunar();
        f.write((char*)&volum, sizeof(double));

        // Salvare activ
        bool activ = client.getEsteActiv();
        f.write((char*)&activ, sizeof(bool));

        f.close();
        cout << "✓ Client salvat in fisier binar: " << numeFisier << endl;
    }

    // FISIER BINAR - CITIRE
    static void citireBinarClient(const char* numeFisier) {
        ifstream f(numeFisier, ios::binary);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CITIRE FISIER BINAR CLIENTI " << endl;
        int nrClienti = 0;

        while (f.peek() != EOF) {
            nrClienti++;
            cout << "\n Client #" << nrClienti << " " << endl;

            // Citire ID
            int id;
            f.read((char*)&id, sizeof(int));
            cout << "ID: " << id << endl;

            // Citire nume companie
            int len;
            f.read((char*)&len, sizeof(int));
            char* buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Companie: " << buffer << endl;
            delete[] buffer;

            // Citire adresa
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Adresa: " << buffer << endl;
            delete[] buffer;

            // Citire contact
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Contact: " << buffer << endl;
            delete[] buffer;

            // Citire angajati
            int angajati;
            f.read((char*)&angajati, sizeof(int));
            cout << "Angajati: " << angajati << endl;

            // Citire cod fiscal
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Cod Fiscal: " << buffer << endl;
            delete[] buffer;

            // Citire volum
            double volum;
            f.read((char*)&volum, sizeof(double));
            cout << "Volum: " << volum << endl;

            // Citire activ
            bool activ;
            f.read((char*)&activ, sizeof(bool));
            cout << "Activ: " << (activ ? "DA" : "NU") << endl;
        }

        f.close();
        cout << "\nTotal clienti cititi: " << nrClienti << endl;
    }
};


//  CURSAINTERNATIONALA - METODE FISIERE


class CursaInternationalaFileManager {
public:
    
    static void salvareTextCursa(const CursaInternationala& cursa, const char* numeFisier) {
        ofstream f(numeFisier, ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        f << " CURSA INTERNATIONALA " << endl;
        f << "Cod: " << cursa.getCodCursa() << endl;
        f << "Origine: " << cursa.getTaraOrigine() << endl;
        f << "Destinatie: " << cursa.getTaraDestinatie() << endl;
        f << "Distanta: " << cursa.getDistantaKm() << " km" << endl;
        f << "Durata: " << cursa.getDurataTimpOre() << " ore" << endl;
        f << "Colete: " << cursa.getNrColete() << endl;
        f << "Sofer: " << cursa.getSoferId() << endl;
        f << "Data: " << cursa.getDataPlecarii() << endl;
        f << "Finalizata: " << (cursa.getEsteFinalizata() ? "DA" : "NU") << endl;
        f << "" << endl;

        f.close();
        cout << "✓ Cursa salvata in fisier text: " << numeFisier << endl;
    }

    // FISIER TEXT - CITIRE
    static void citireTextCursa(const char* numeFisier) {
        ifstream f(numeFisier);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CONTINUT FISIER TEXT CURSE " << endl;
        string linie;
        while (getline(f, linie)) {
            cout << linie << endl;
        }

        f.close();
    }

    // FISIER BINAR - SCRIERE
    static void salvareBinarCursa(const CursaInternationala& cursa, const char* numeFisier) {
        ofstream f(numeFisier, ios::binary | ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        // Salvare cod cursa
        string cod = cursa.getCodCursa();
        int len = cod.length();
        f.write((char*)&len, sizeof(int));
        f.write(cod.c_str(), len);

        // Salvare origine
        len = strlen(cursa.getTaraOrigine());
        f.write((char*)&len, sizeof(int));
        f.write(cursa.getTaraOrigine(), len);

        // Salvare destinatie
        string dest = cursa.getTaraDestinatie();
        len = dest.length();
        f.write((char*)&len, sizeof(int));
        f.write(dest.c_str(), len);

        // Salvare distanta
        double distanta = cursa.getDistantaKm();
        f.write((char*)&distanta, sizeof(double));

        // Salvare durata
        double durata = cursa.getDurataTimpOre();
        f.write((char*)&durata, sizeof(double));

        // Salvare colete
        int colete = cursa.getNrColete();
        f.write((char*)&colete, sizeof(int));

        // Salvare sofer
        len = strlen(cursa.getSoferId());
        f.write((char*)&len, sizeof(int));
        f.write(cursa.getSoferId(), len);

        // Salvare data
        len = strlen(cursa.getDataPlecarii());
        f.write((char*)&len, sizeof(int));
        f.write(cursa.getDataPlecarii(), len);

        // Salvare finalizata
        bool finalizata = cursa.getEsteFinalizata();
        f.write((char*)&finalizata, sizeof(bool));

        f.close();
        cout << "✓ Cursa salvata in fisier binar: " << numeFisier << endl;
    }

    // FISIER BINAR - CITIRE
    static void citireBinarCursa(const char* numeFisier) {
        ifstream f(numeFisier, ios::binary);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CITIRE FISIER BINAR CURSE " << endl;
        int nrCurse = 0;

        while (f.peek() != EOF) {
            nrCurse++;
            cout << "\n Cursa #" << nrCurse << " " << endl;

            // Citire cod
            int len;
            f.read((char*)&len, sizeof(int));
            char* buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Cod: " << buffer << endl;
            delete[] buffer;

            // Citire origine
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Origine: " << buffer << endl;
            delete[] buffer;

            // Citire destinatie
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Destinatie: " << buffer << endl;
            delete[] buffer;

            // Citire distanta
            double distanta;
            f.read((char*)&distanta, sizeof(double));
            cout << "Distanta: " << distanta << " km" << endl;

            // Citire durata
            double durata;
            f.read((char*)&durata, sizeof(double));
            cout << "Durata: " << durata << " ore" << endl;

            // Citire colete
            int colete;
            f.read((char*)&colete, sizeof(int));
            cout << "Colete: " << colete << endl;

            // Citire sofer
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Sofer: " << buffer << endl;
            delete[] buffer;

            // Citire data
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Data: " << buffer << endl;
            delete[] buffer;

            // Citire finalizata
            bool finalizata;
            f.read((char*)&finalizata, sizeof(bool));
            cout << "Finalizata: " << (finalizata ? "DA" : "NU") << endl;
        }

        f.close();
        cout << "\nTotal curse citite: " << nrCurse << endl;
    }
};


//  FACTURA - METODE FISIERE


class FacturaFileManager {
public:
    // FISIER TEXT - SCRIERE
    static void salvareTextFactura(const Factura& factura, const char* numeFisier) {
        ofstream f(numeFisier, ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        f << " FACTURA " << endl;
        f << "Numar: " << factura.getNumarFactura() << endl;
        f << "Data: " << factura.getDataEmitere() << endl;
        f << "Client: " << factura.getClientDenumire() << endl;
        f << "Nr. Servicii: " << factura.getNrServicii() << endl;

        const double* preturi = factura.getPreturiServicii();
        for (int i = 0; i < factura.getNrServicii(); i++) {
            f << "  Serviciu " << (i + 1) << ": " << preturi[i] << endl;
        }

        f << "Total: " << factura.calculeazaTotal() << " " << factura.getMoneda() << endl;
        f << "Platita: " << (factura.getEstePlatita() ? "DA" : "NU") << endl;
        f << "" << endl;

        f.close();
        cout << "✓ Factura salvata in fisier text: " << numeFisier << endl;
    }

    // FISIER TEXT - CITIRE
    static void citireTextFactura(const char* numeFisier) {
        ifstream f(numeFisier);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CONTINUT FISIER TEXT FACTURI " << endl;
        string linie;
        while (getline(f, linie)) {
            cout << linie << endl;
        }

        f.close();
    }

    // FISIER BINAR - SCRIERE
    static void salvareBinarFactura(const Factura& factura, const char* numeFisier) {
        ofstream f(numeFisier, ios::binary | ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        // Salvare numar factura
        int len = strlen(factura.getNumarFactura());
        f.write((char*)&len, sizeof(int));
        f.write(factura.getNumarFactura(), len);

        // Salvare data
        string data = factura.getDataEmitere();
        len = data.length();
        f.write((char*)&len, sizeof(int));
        f.write(data.c_str(), len);

        // Salvare client
        len = strlen(factura.getClientDenumire());
        f.write((char*)&len, sizeof(int));
        f.write(factura.getClientDenumire(), len);

        // Salvare moneda
        len = strlen(factura.getMoneda());
        f.write((char*)&len, sizeof(int));
        f.write(factura.getMoneda(), len);

        // Salvare nr servicii si preturi
        int nrServ = factura.getNrServicii();
        f.write((char*)&nrServ, sizeof(int));

        const double* preturi = factura.getPreturiServicii();
        for (int i = 0; i < nrServ; i++) {
            f.write((char*)&preturi[i], sizeof(double));
        }

        // Salvare platita
        bool platita = factura.getEstePlatita();
        f.write((char*)&platita, sizeof(bool));

        f.close();
        cout << "✓ Factura salvata in fisier binar: " << numeFisier << endl;
    }

    // FISIER BINAR - CITIRE
    static void citireBinarFactura(const char* numeFisier) {
        ifstream f(numeFisier, ios::binary);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CITIRE FISIER BINAR FACTURI " << endl;
        int nrFacturi = 0;

        while (f.peek() != EOF) {
            nrFacturi++;
            cout << "\n Factura #" << nrFacturi << " " << endl;

            // Citire numar
            int len;
            f.read((char*)&len, sizeof(int));
            char* buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Numar: " << buffer << endl;
            delete[] buffer;

            // Citire data
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Data: " << buffer << endl;
            delete[] buffer;

            // Citire client
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Client: " << buffer << endl;
            delete[] buffer;

            // Citire moneda
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Moneda: " << buffer << endl;
            delete[] buffer;

            // Citire servicii
            int nrServ;
            f.read((char*)&nrServ, sizeof(int));
            cout << "Nr. Servicii: " << nrServ << endl;

            double total = 0;
            for (int i = 0; i < nrServ; i++) {
                double pret;
                f.read((char*)&pret, sizeof(double));
                cout << "  Serviciu " << (i + 1) << ": " << pret << endl;
                total += pret;
            }
            cout << "Total: " << total << endl;

            // Citire platita
            bool platita;
            f.read((char*)&platita, sizeof(bool));
            cout << "Platita: " << (platita ? "DA" : "NU") << endl;
        }

        f.close();
        cout << "\nTotal facturi citite: " << nrFacturi << endl;
    }
};


//  COMANDATRANSPORT - METODE FISIERE

class ComandaTransportFileManager {
public:
    // FISIER TEXT - SCRIERE
    static void salvareTextComanda(const ComandaTransport& comanda, const char* numeFisier) {
        ofstream f(numeFisier, ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        f << "COMANDA TRANSPORT" << endl;
        f << "ID: " << comanda.getID() << endl;
        f << "Numar: " << comanda.getNumarComanda() << endl;
        f << "Data: " << comanda.getDataComanda() << endl;

        if (comanda.getClient() != nullptr) {
            f << "Client: " << comanda.getClient()->getNumeCompanie() << endl;
        }

        f << "Cursa principala: " << comanda.getCursaPrincipala().getCodCursa() << endl;
        f << "Curse aditionale: " << comanda.getCurseAditionale().size() << endl;

        for (size_t i = 0; i < comanda.getCurseAditionale().size(); i++) {
            f << "  Cursa " << (i + 1) << ": " << comanda.getCurseAditionale()[i]->getCodCursa() << endl;
        }

        f << "Valoare totala: " << comanda.getValoareTotala() << " EUR" << endl;
        f << "Observatii: " << comanda.getObservatii() << endl;
        f << "Finalizata: " << (comanda.getEsteFinalizata() ? "DA" : "NU") << endl;

        f.close();
        cout << "✓ Comanda salvata in fisier text: " << numeFisier << endl;
    }

    // FISIER TEXT - CITIRE
    static void citireTextComanda(const char* numeFisier) {
        ifstream f(numeFisier);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n  CONTINUT FISIER TEXT COMENZI " << endl;
        string linie;
        while (getline(f, linie)) {
            cout << linie << endl;
        }

        f.close();
    }

    // FISIER BINAR - SCRIERE
    static void salvareBinarComanda(const ComandaTransport& comanda, const char* numeFisier) {
        ofstream f(numeFisier, ios::binary | ios::app);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        // Salvare ID
        int id = comanda.getID();
        f.write((char*)&id, sizeof(int));

        // Salvare numar comanda
        int len = strlen(comanda.getNumarComanda());
        f.write((char*)&len, sizeof(int));
        f.write(comanda.getNumarComanda(), len);

        // Salvare data
        string data = comanda.getDataComanda();
        len = data.length();
        f.write((char*)&len, sizeof(int));
        f.write(data.c_str(), len);

        // Salvare nume client (daca exista)
        bool areClient = (comanda.getClient() != nullptr);
        f.write((char*)&areClient, sizeof(bool));
        if (areClient) {
            const char* numeClient = comanda.getClient()->getNumeCompanie();
            len = strlen(numeClient);
            f.write((char*)&len, sizeof(int));
            f.write(numeClient, len);
        }

        // Salvare cod cursa principala
        string codCursa = comanda.getCursaPrincipala().getCodCursa();
        len = codCursa.length();
        f.write((char*)&len, sizeof(int));
        f.write(codCursa.c_str(), len);

        // Salvare numar curse aditionale
        int nrCurseAd = comanda.getCurseAditionale().size();
        f.write((char*)&nrCurseAd, sizeof(int));

        // Salvare valoare
        double valoare = comanda.getValoareTotala();
        f.write((char*)&valoare, sizeof(double));

        // Salvare observatii
        len = strlen(comanda.getObservatii());
        f.write((char*)&len, sizeof(int));
        f.write(comanda.getObservatii(), len);

        // Salvare finalizata
        bool finalizata = comanda.getEsteFinalizata();
        f.write((char*)&finalizata, sizeof(bool));

        f.close();
        cout << "✓ Comanda salvata in fisier binar: " << numeFisier << endl;
    }

    // FISIER BINAR - CITIRE
    static void citireBinarComanda(const char* numeFisier) {
        ifstream f(numeFisier, ios::binary);
        if (!f.is_open()) {
            cout << "Eroare la deschiderea fisierului " << numeFisier << endl;
            return;
        }

        cout << "\n CITIRE FISIER BINAR COMENZI " << endl;
        int nrComenzi = 0;

        while (f.peek() != EOF) {
            nrComenzi++;
            cout << "\n Comanda #" << nrComenzi << " " << endl;

            // Citire ID
            int id;
            f.read((char*)&id, sizeof(int));
            cout << "ID: " << id << endl;

            // Citire numar
            int len;
            f.read((char*)&len, sizeof(int));
            char* buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Numar: " << buffer << endl;
            delete[] buffer;

            // Citire data
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Data: " << buffer << endl;
            delete[] buffer;

            // Citire client
            bool areClient;
            f.read((char*)&areClient, sizeof(bool));
            if (areClient) {
                f.read((char*)&len, sizeof(int));
                buffer = new char[len + 1];
                f.read(buffer, len);
                buffer[len] = '\0';
                cout << "Client: " << buffer << endl;
                delete[] buffer;
            }

            // Citire cursa principala
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Cursa principala: " << buffer << endl;
            delete[] buffer;

            // Citire nr curse aditionale
            int nrCurseAd;
            f.read((char*)&nrCurseAd, sizeof(int));
            cout << "Curse aditionale: " << nrCurseAd << endl;

            // Citire valoare
            double valoare;
            f.read((char*)&valoare, sizeof(double));
            cout << "Valoare: " << valoare << " EUR" << endl;

            // Citire observatii
            f.read((char*)&len, sizeof(int));
            buffer = new char[len + 1];
            f.read(buffer, len);
            buffer[len] = '\0';
            cout << "Observatii: " << buffer << endl;
            delete[] buffer;

            // Citire finalizata
            bool finalizata;
            f.read((char*)&finalizata, sizeof(bool));
            cout << "Finalizata: " << (finalizata ? "DA" : "NU") << endl;
        }

        f.close();
        cout << "\n Total comenzi citite: " << nrComenzi << endl;
    }
};


//  FAZA 7 - MOSTENIRE SI UPCASTING
// 
//  CLASA 1 DERIVATA: ClientCorporativPremium (mosteneste ClientCorporativ)

class ClientCorporativPremium : public ClientCorporativ {
private:
    int nivelPremium;           // 1-5 (gold, platinum, diamond, etc.)
    double discountSuplimentar;
    char* managerDedicat;
    bool accesPrioritateSuport;
    int puncteFidelitate;

public:
    // Constructor implicit
    ClientCorporativPremium()
        : ClientCorporativ(),
        nivelPremium(1),
        discountSuplimentar(0.05),
        managerDedicat(nullptr),
        accesPrioritateSuport(true),
        puncteFidelitate(0) {

        managerDedicat = new char[100];
        strcpy(managerDedicat, "Manager Nedefinit");
    }

    // Constructor cu parametri
    ClientCorporativPremium(const char* nume, const char* adresa, const char* contact,
        int angajati, string cod, double volum, bool activ,
        int nivel, double discountExtra, const char* manager, int puncte)
        : ClientCorporativ(nume, adresa, contact, angajati, cod, volum, activ),
        nivelPremium(nivel),
        discountSuplimentar(discountExtra),
        managerDedicat(nullptr),
        accesPrioritateSuport(true),
        puncteFidelitate(puncte) {

        size_t len = strlen(manager);
        managerDedicat = new char[len + 1];
        strcpy(managerDedicat, manager);
    }

    // Constructor de copiere
    ClientCorporativPremium(const ClientCorporativPremium& c)
        : ClientCorporativ(c),
        nivelPremium(c.nivelPremium),
        discountSuplimentar(c.discountSuplimentar),
        managerDedicat(nullptr),
        accesPrioritateSuport(c.accesPrioritateSuport),
        puncteFidelitate(c.puncteFidelitate) {

        if (c.managerDedicat) {
            size_t len = strlen(c.managerDedicat);
            managerDedicat = new char[len + 1];
            strcpy(managerDedicat, c.managerDedicat);
        }
    }

    // Destructor
    ~ClientCorporativPremium() {
        delete[] managerDedicat;
    }

    // Operator de atribuire
    ClientCorporativPremium& operator=(const ClientCorporativPremium& c) {
        if (this != &c) {
            ClientCorporativ::operator=(c);

            delete[] managerDedicat;

            nivelPremium = c.nivelPremium;
            discountSuplimentar = c.discountSuplimentar;
            accesPrioritateSuport = c.accesPrioritateSuport;
            puncteFidelitate = c.puncteFidelitate;

            if (c.managerDedicat) {
                size_t len = strlen(c.managerDedicat);
                managerDedicat = new char[len + 1];
                strcpy(managerDedicat, c.managerDedicat);
            }
        }
        return *this;
    }

    // GETTERI specifici
    int getNivelPremium() const { return nivelPremium; }
    double getDiscountSuplimentar() const { return discountSuplimentar; }
    const char* getManagerDedicat() const { return managerDedicat; }
    bool getAccesPrioritateSuport() const { return accesPrioritateSuport; }
    int getPuncteFidelitate() const { return puncteFidelitate; }

    // SETTERI specifici
    void setNivelPremium(int nivel) {
        if (nivel >= 1 && nivel <= 5) nivelPremium = nivel;
    }

    void setDiscountSuplimentar(double discount) {
        if (discount >= 0 && discount <= 0.5) discountSuplimentar = discount;
    }

    void setManagerDedicat(const char* manager) {
        if (manager != nullptr) {
            delete[] managerDedicat;
            size_t len = strlen(manager);
            managerDedicat = new char[len + 1];
            strcpy(managerDedicat, manager);
        }
    }

    void setAccesPrioritateSuport(bool acces) {
        accesPrioritateSuport = acces;
    }

    void adaugaPuncteFidelitate(int puncte) {
        puncteFidelitate += puncte;
    }

    // Metoda specifica - calcul discount total
    double calculeazaDiscountTotal() const {
        double discountBaza = ClientCorporativ::getDiscount();
        return discountBaza + discountSuplimentar + (nivelPremium * 0.01);
    }

    // Metoda pentru upgrade nivel
    void upgradeNivel() {
        if (nivelPremium < 5) {
            nivelPremium++;
            discountSuplimentar += 0.02;
            cout << " Client promovat la nivel Premium " << nivelPremium << "!" << endl;
        }
        else {
            cout << "Client deja la nivel maxim!" << endl;
        }
    }

    // Suprascrierea metodei afiseaza() din clasa de baza
    void afiseaza() const {
        cout << "     CLIENT CORPORATIV PREMIUM #" << getID() << endl;

        // Afisare date din clasa de baza
        cout << "Companie: " << getNumeCompanie() << endl;
        cout << "Adresa: " << getAdresaSediu() << endl;
        cout << "Contact: " << getPersoanaContact() << endl;
        cout << "Angajati: " << getNrAngajati() << endl;
        cout << "Cod Fiscal: " << getCodFiscal() << endl;
        cout << "Volum/Luna: " << getVolumTransporturiLunar() << " tone" << endl;
        cout << "Status: " << (getEsteActiv() ? "ACTIV" : "INACTIV") << endl;

        // Afisare date specifice Premium
        cout << "\n STATUS PREMIUM " << endl;
        cout << "Nivel Premium: " << nivelPremium << " *";
        for (int i = 1; i < nivelPremium; i++) cout << "*";
        cout << endl;
        cout << "Discount Suplimentar: " << (discountSuplimentar * 100) << "%" << endl;
        cout << "Discount Total: " << (calculeazaDiscountTotal() * 100) << "%" << endl;
        cout << "Manager Dedicat: " << managerDedicat << endl;
        cout << "Acces Prioritate Suport: " << (accesPrioritateSuport ? "DA" : "NU") << endl;
        cout << "Puncte Fidelitate: " << puncteFidelitate << endl;
    }
};

//  CLASA 2 DERIVATA: CursaExpres (mosteneste CursaInternationala)

class CursaExpres : public CursaInternationala {
private:
    bool livrareGarantata24h;
    double taxaUrgenta;
    char* prioritate;           // "STANDARD", "EXPRESS", "SUPER_EXPRESS"
    int oreLivrareGarantate;
    bool asigurareInclusa;

public:
    // Constructor implicit
    CursaExpres()
        : CursaInternationala(),
        livrareGarantata24h(true),
        taxaUrgenta(200.0),
        prioritate(nullptr),
        oreLivrareGarantate(24),
        asigurareInclusa(true) {

        prioritate = new char[50];
        strcpy(prioritate, "EXPRESS");
    }

    // Constructor cu parametri
    CursaExpres(const char* origine, string destinatie, double distanta,
        double durata, int colete, const char* sofer, const char* data,
        bool garantie24h, double taxaUrg, const char* prior, int oreGarantate)
        : CursaInternationala(origine, destinatie, distanta, durata, colete, sofer, data),
        livrareGarantata24h(garantie24h),
        taxaUrgenta(taxaUrg),
        prioritate(nullptr),
        oreLivrareGarantate(oreGarantate),
        asigurareInclusa(true) {

        size_t len = strlen(prior);
        prioritate = new char[len + 1];
        strcpy(prioritate, prior);
    }

    // Constructor de copiere
    CursaExpres(const CursaExpres& c)
        : CursaInternationala(c),
        livrareGarantata24h(c.livrareGarantata24h),
        taxaUrgenta(c.taxaUrgenta),
        prioritate(nullptr),
        oreLivrareGarantate(c.oreLivrareGarantate),
        asigurareInclusa(c.asigurareInclusa) {

        if (c.prioritate) {
            size_t len = strlen(c.prioritate);
            prioritate = new char[len + 1];
            strcpy(prioritate, c.prioritate);
        }
    }

    // Destructor
    ~CursaExpres() {
        delete[] prioritate;
    }

    // Operator de atribuire
    CursaExpres& operator=(const CursaExpres& c) {
        if (this != &c) {
            CursaInternationala::operator=(c);

            delete[] prioritate;

            livrareGarantata24h = c.livrareGarantata24h;
            taxaUrgenta = c.taxaUrgenta;
            oreLivrareGarantate = c.oreLivrareGarantate;
            asigurareInclusa = c.asigurareInclusa;

            if (c.prioritate) {
                size_t len = strlen(c.prioritate);
                prioritate = new char[len + 1];
                strcpy(prioritate, c.prioritate);
            }
        }
        return *this;
    }

    // GETTERI specifici
    bool getLivrareGarantata24h() const { return livrareGarantata24h; }
    double getTaxaUrgenta() const { return taxaUrgenta; }
    const char* getPrioritate() const { return prioritate; }
    int getOreLivrareGarantate() const { return oreLivrareGarantate; }
    bool getAsigurareInclusa() const { return asigurareInclusa; }

    // SETTERI specifici
    void setLivrareGarantata24h(bool garantie) {
        livrareGarantata24h = garantie;
    }

    void setTaxaUrgenta(double taxa) {
        if (taxa >= 0) taxaUrgenta = taxa;
    }

    void setPrioritate(const char* prior) {
        if (prior != nullptr) {
            delete[] prioritate;
            size_t len = strlen(prior);
            prioritate = new char[len + 1];
            strcpy(prioritate, prior);
        }
    }

    void setOreLivrareGarantate(int ore) {
        if (ore > 0) oreLivrareGarantate = ore;
    }

    void setAsigurareInclusa(bool asigurare) {
        asigurareInclusa = asigurare;
    }

    // Metoda specifica - calcul cost total cu taxe expres
    double calculeazaCostTotalExpres() const {
        double costBaza = CursaInternationala::calculeazaCostTotalCursa(
            getDistantaKm(), getNrColete(), false);

        double costTotal = costBaza + taxaUrgenta;

        // Discount pentru volum mare
        if (getNrColete() > 50) {
            costTotal *= 0.95;  // 5% discount
        }

        // Cost asigurare
        if (asigurareInclusa) {
            costTotal += 100.0;
        }

        return costTotal;
    }

    // Metoda pentru upgrade prioritate
    void upgradePrioritate() {
        if (strcmp(prioritate, "STANDARD") == 0) {
            setPrioritate("EXPRESS");
            taxaUrgenta += 100.0;
            oreLivrareGarantate = 24;
        }
        else if (strcmp(prioritate, "EXPRESS") == 0) {
            setPrioritate("SUPER_EXPRESS");
            taxaUrgenta += 150.0;
            oreLivrareGarantate = 12;
        }
        else {
            cout << "Cursa deja la prioritate maxima!" << endl;
            return;
        }
        cout << "✓ Cursa promovata la " << prioritate << "!" << endl;
    }

    // Suprascrierea metodei afiseaza() din clasa de baza
    void afiseaza() const {
        cout << "        CURSA EXPRES INTERNATIONALA" << endl;

        // Afisare date din clasa de baza
        cout << "Cod: " << getCodCursa() << endl;
        cout << "Ruta: " << getTaraOrigine() << " → " << getTaraDestinatie() << endl;
        cout << "Distanta: " << getDistantaKm() << " km" << endl;
        cout << "Durata: " << getDurataTimpOre() << " ore" << endl;
        cout << "Colete: " << getNrColete() << endl;
        cout << "Sofer: " << getSoferId() << endl;
        cout << "Data: " << getDataPlecarii() << endl;
        cout << "Status: " << (getEsteFinalizata() ? "FINALIZATA" : "IN CURS") << endl;

        // Afisare date specifice Expres
        cout << "\n SERVICII EXPRES " << endl;
        cout << "Prioritate: " << prioritate << " ⚡" << endl;
        cout << "Livrare Garantata: " << (livrareGarantata24h ? "DA" : "NU") << endl;
        cout << "Ore Garantate: " << oreLivrareGarantate << "h" << endl;
        cout << "Taxa Urgenta: " << taxaUrgenta << " EUR" << endl;
        cout << "Asigurare Inclusa: " << (asigurareInclusa ? "DA" : "NU") << endl;
        cout << "Cost Total Expres: " << calculeazaCostTotalExpres() << " EUR" << endl;
    }
};

//  FUNCTII - UPCASTING

// Functie care primeste un pointer la clasa de baza ClientCorporativ
void proceseazaClient(ClientCorporativ* client) {
    cout << "\n→ PROCESARE CLIENT (UPCASTING)" << endl;
    cout << "Companie: " << client->getNumeCompanie() << endl;
    cout << "Volum: " << client->getVolumTransporturiLunar() << " tone" << endl;
    cout << "Angajati: " << client->getNrAngajati() << endl;

    // Calcul pret cu discount
    double pret = 10000.0;
    double pretFinal = ClientCorporativ::calculeazaPretFinal(pret,
        client->getVolumTransporturiLunar());
    cout << "Pret estimat: " << pretFinal << " EUR" << endl;
}

// Functie care primeste un pointer la clasa de baza CursaInternationala
void proceseazaCursa(CursaInternationala* cursa) {
    cout << "\n→ PROCESARE CURSA (UPCASTING)" << endl;
    cout << "Cod: " << cursa->getCodCursa() << endl;
    cout << "Destinatie: " << cursa->getTaraDestinatie() << endl;
    cout << "Distanta: " << cursa->getDistantaKm() << " km" << endl;
    cout << "Colete: " << cursa->getNrColete() << endl;

    // Calcul viteza medie
    if (cursa->getDurataTimpOre() > 0) {
        double viteza = cursa->getDistantaKm() / cursa->getDurataTimpOre();
        cout << "Viteza medie: " << viteza << " km/h" << endl;
    }
}

// Functie care proceseaza un vector de clienti (upcasting)
void proceseazaVectorClienti(ClientCorporativ** clienti, int nrClienti) {
    cout << "PROCESARE BATCH CLIENTI (UPCASTING)" << endl;

    double volumTotal = 0;
    int angajatiTotal = 0;

    for (int i = 0; i < nrClienti; i++) {
        cout << (i + 1) << ". " << clienti[i]->getNumeCompanie();
        cout << " - Volum: " << clienti[i]->getVolumTransporturiLunar() << " tone" << endl;

        volumTotal += clienti[i]->getVolumTransporturiLunar();
        angajatiTotal += clienti[i]->getNrAngajati();
    }

    cout << "\n STATISTICI GENERALE " << endl;
    cout << "Volum total: " << volumTotal << " tone" << endl;
    cout << "Angajati total: " << angajatiTotal << endl;
    cout << "Volum mediu/client: " << (volumTotal / nrClienti) << " tone" << endl;
}



//
// FUNCTIA MAIN - CU TESTE PENTRU FAZA 3 (plecand de la FAZA 2)
//
int main() {
    cout << "" << endl;
    cout << "  SISTEM MANAGEMENT TRANSPORT" << endl;
    cout << "\n" << endl;

    int optiune;
    vector<ClientCorporativ*> clienti;
    vector<CursaInternationala*> curse;
    vector<Factura*> facturi;
    vector<ClientCorporativ> vectorClienti;
    vector<CursaInternationala> vectorCurse;
    vector<Factura> vectorFacturi;
    vector<ComandaTransport*> comenzi;
    vector<ClientCorporativPremium*> clientiPremium;
    vector<CursaExpres*> curseExpres;

    do {
        cout << "\n MENIU PRINCIPAL " << endl;
        cout << " CLIENTI CORPORATIVI " << endl;
        cout << "1. Creare client nou (citire)" << endl;
        cout << "2. Afisare toti clientii" << endl;
        cout << "3. Test constructori Client (si operatori)" << endl;
        cout << "4. Calcul pret cu discount (functie statica)" << endl;
        cout << "5. Modificare discount corporativ" << endl;
        cout << "6. Afisare statistici clienti" << endl;
        cout << "7. Test getteri/setteri Client" << endl;
        cout << "8. Aplicare discount special (functie friend)" << endl;
        cout << "9. Raport detaliat client (functie friend)" << endl;

        cout << "\n  CURSE INTERNATIONALE " << endl;
        cout << "10. Creare cursa noua (citire)" << endl;
        cout << "11. Afisare toate cursele" << endl;
        cout << "12. Test constructori Cursa (si operatori)" << endl;
        cout << "13. Calcul cost total cursa (functie statica)" << endl;
        cout << "14. Modificare taxa vamala" << endl;
        cout << "15. Finalizare cursa" << endl;
        cout << "16. Afisare statistici curse" << endl;
        cout << "17. Test getteri/setteri Cursa" << endl;
        cout << "18. Optimizare ruta (functie friend)" << endl;
        cout << "19. Raport detaliat cursa (functie friend)" << endl;

        cout << "\n  FACTURI " << endl;
        cout << "20. Creare factura noua (citire)" << endl;
        cout << "21. Afisare toate facturile" << endl;
        cout << "22. Marcare factura ca platita" << endl;
        cout << "23. Test constructori Factura (si operatori)" << endl;
        cout << "24. Modificare cota TVA" << endl;
        cout << "25. Afisare statistici facturi" << endl;
        cout << "26. Test getteri/setteri Factura" << endl;
        cout << "27. Aplicare reducere (functie friend)" << endl;
        cout << "28. Raport detaliat factura (functie friend)" << endl;
        cout << "\n  FAZA 4 - VECTORI SI MATRICE " << endl;
        cout << "29. Test complet Faza 4 (vectori + matrice)" << endl;
        cout << "30. Operatii avansate (submeniu: operatori, comparatie, matrice)" << endl;

        cout << "\n  COMENZI TRANSPORT (HAS-A) " << endl;
        cout << "31. Creare comanda transport noua" << endl;
        cout << "32. Afisare toate comenzile" << endl;
        cout << "33. Test complet Faza 5 (relatii has-a)" << endl;
        cout << "34. Adauga cursa aditionala la comanda" << endl;
        cout << "35. Finalizare comanda" << endl;
        cout << "36. Statistici comenzi" << endl;
        cout << "\n  FISIERE TEXT SI BINARE " << endl;
        cout << "37. Salvare date in fisiere TEXT" << endl;
        cout << "38. Citire date din fisiere TEXT" << endl;
        cout << "39. Salvare date in fisiere BINARE" << endl;
        cout << "40. Citire date din fisiere BINARE" << endl;
        cout << "41. Test complet Faza 6 (toate fisierele)" << endl;
        cout << "\n  MOSTENIRE SI UPCASTING " << endl;
        cout << "42. Creare Client Premium" << endl;
        cout << "43. Creare Cursa Expres" << endl;
        cout << "44. Afisare Clienti Premium" << endl;
        cout << "45. Afisare Curse Expres" << endl;
        cout << "46. Test UPCASTING - Procesare ca clasa de baza" << endl;
        cout << "47. Test complet Faza 7 (mostenire + upcasting)" << endl;
        cout << "48. Upgrade nivel Premium / Prioritate Expres" << endl;
        cout << "\n0. Iesire" << endl;
        cout << "" << endl;
        cout << "Optiune: ";
        cin >> optiune;
        cin.ignore();

        switch (optiune) {
            // CLIENTI
        case 1: {
            ClientCorporativ* c = new ClientCorporativ();
            c->citeste();
            clienti.push_back(c);
            cout << "\n✓ Client creat cu succes!" << endl;
            break;
        }

        case 2:
            if (clienti.empty()) {
                cout << "\nNu exista clienti!" << endl;
            }
            else {
                for (auto c : clienti) c->afiseaza();
            }
            break;

        case 3:
            cout << "\n TEST CONSTRUCTORI CLIENT (SI OPERATORI) " << endl;
            {
                cout << "\n1. Constructor fara parametri:" << endl;
                ClientCorporativ c1;
                c1.afiseaza();

                cout << "\n2. Constructor cu toti parametrii:" << endl;
                ClientCorporativ c2("Transport SRL", "Str. Industriala 10",
                    "Ion Popescu", 50, "RO12345678", 1500.0, true);
                c2.afiseaza();

                cout << "\n3. Constructor de copiere:" << endl;
                ClientCorporativ c3(c2);
                c3.afiseaza();

                cout << "\n4. Operator de atribuire:" << endl;
                c1 = c2;
                c1.afiseaza();

                //  TEST OPERATORI FAZA 3 
                cout << "\n--- TEST OPERATORI CLIENT ---" << endl;
                ClientCorporativ cA("Alpha SRL", "A1", "Contact A", 20, "RO11111111", 500.0, true);
                ClientCorporativ cB("Alpha SRL", "A2", "Contact B", 30, "RO11111111", 1200.0, true);
                ClientCorporativ cC("Beta SRL", "B1", "Contact C", 10, "RO22222222", 300.0, true);

                cout << "cA == cB ? (volum): " << (cA == cB ? "DA" : "NU") << endl;
                cout << "cA == cC ? " << (cA == cC ? "DA" : "NU") << endl;
                cout << "cA < cB ? (volum): " << (cA < cB ? "DA" : "NU") << endl;

                ClientCorporativ cD = cA + 5;
                cout << "cA angajati: " << cA.getNrAngajati() << " | cD angajati (dupa +5): " << cD.getNrAngajati() << endl;

                cD += 100.0;
                cout << "cD volum (dupa +=100): " << cD.getVolumTransporturiLunar() << endl;

                ++cD;
                cout << "cD angajati (dupa ++): " << cD.getNrAngajati() << endl;

                cout << "Cost per angajat pentru cD la cost 10000: " << cD(10000.0) << endl;

                cout << "Operator [] pe nume (poz 0): " << cD[0] << endl;

                cout << "Operator ! pentru cD (este inactiv?): " << (!cD ? "DA" : "NU") << endl;

                cout << "Cast la int (nr angajati): " << static_cast<int>(cD) << endl;
             
            }
            cout << "\n✓ Toti constructorii si operatorii client functioneaza!" << endl;
            break;

        case 4: {
            double pret, volum;
            cout << "\nPret initial (EUR): ";
            cin >> pret;
            cout << "Volum lunar (tone): ";
            cin >> volum;
            double pretFinal = ClientCorporativ::calculeazaPretFinal(pret, volum);
            cout << "\nPret final: " << pretFinal << " EUR" << endl;
            cout << "Economie: " << (pret - pretFinal) << " EUR" << endl;
            break;
        }

        case 5: {
            double disc;
            cout << "\nDiscount curent: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            cout << "Nou discount (0-1): ";
            cin >> disc;
            ClientCorporativ::setDiscount(disc);
            cout << "✓ Discount actualizat!" << endl;
            break;
        }

        case 6:
            cout << "\n STATISTICI CLIENTI " << endl;
            cout << "Total clienti: " << ClientCorporativ::getNumarTotalClienti() << endl;
            cout << "Clienti activi: " << ClientCorporativ::getClientiActivi() << endl;
            cout << "Discount: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            break;

        case 7: {
            cout << "\n TEST GETTERI/SETTERI CLIENT " << endl;
            ClientCorporativ c;
            cout << "Client initial:" << endl;
            c.afiseaza();

            cout << "\nModificare date prin setteri..." << endl;
            c.setNumeCompanie("LogisticsPro SRL");
            c.setNrAngajati(75);
            c.setVolumTransporturiLunar(2500.0);
            c.setAdresaSediu("Bulevardul Unirii 45");
            c.setPersoanaContact("Maria Ionescu");

            cout << "\nClient dupa modificare:" << endl;
            c.afiseaza();

            cout << "\nTestare getteri:" << endl;
            cout << "Nume: " << c.getNumeCompanie() << endl;
            cout << "Angajati: " << c.getNrAngajati() << endl;
            cout << "Volum: " << c.getVolumTransporturiLunar() << " tone" << endl;
            cout << "✓ Getteri/Setteri functioneaza!" << endl;
            break;
        }

        case 8: {
            if (clienti.empty()) {
                cout << "\nNu exista clienti!" << endl;
            }
            else {
                cout << "\n CLIENTI DISPONIBILI " << endl;
                for (size_t i = 0; i < clienti.size(); i++) {
                    cout << (i + 1) << ". " << clienti[i]->getNumeCompanie() << endl;
                }
                int idx;
                cout << "Selectati client: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)clienti.size()) {
                    double discount;
                    cout << "Discount special (0-1, ex: 0.10 pentru 10%): ";
                    cin >> discount;
                    aplicaDiscountSpecial(*clienti[idx - 1], discount);
                }
            }
            break;
        }

        case 9: {
            if (clienti.empty()) {
                cout << "\nNu exista clienti!" << endl;
            }
            else {
                cout << "\n CLIENTI DISPONIBILI " << endl;
                for (size_t i = 0; i < clienti.size(); i++) {
                    cout << (i + 1) << ". " << clienti[i]->getNumeCompanie() << endl;
                }
                int idx;
                cout << "Selectati client: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)clienti.size()) {
                    afiseazaRaportClient(*clienti[idx - 1]);
                }
            }
            break;
        }

              // = CURSE =
        case 10: {
            CursaInternationala* c = new CursaInternationala();
            c->citeste();
            curse.push_back(c);
            cout << "\n✓ Cursa creata cu succes!" << endl;
            break;
        }

        case 11:
            if (curse.empty()) {
                cout << "\nNu exista curse!" << endl;
            }
            else {
                for (auto c : curse) c->afiseaza();
            }
            break;

        case 12:
            cout << "\n TEST CONSTRUCTORI CURSA (SI OPERATORI) " << endl;
            {
                cout << "\n1. Constructor fara parametri:" << endl;
                CursaInternationala c1;
                c1.afiseaza();

                cout << "\n2. Constructor cu toti parametrii:" << endl;
                CursaInternationala c2("Romania", "Germania", 2150.0, 24.5,
                    35, "SOF-123", "15/11/2024");
                c2.afiseaza();

                cout << "\n3. Constructor de copiere:" << endl;
                CursaInternationala c3(c2);
                c3.afiseaza();

                cout << "\n4. Operator de atribuire:" << endl;
                c1 = c2;
                c1.afiseaza();

                // == TEST OPERATORI FAZA 3 ==
                cout << "\n--- TEST OPERATORI CURSA ---" << endl;
                CursaInternationala ca("Romania", "Ungaria", 800.0, 10.0, 20, "SOF-1", "01/11/2024");
                CursaInternationala cb("Romania", "Ungaria", 800.0, 11.0, 25, "SOF-2", "02/11/2024");
                CursaInternationala cc("Polonia", "Franta", 1800.0, 20.0, 40, "SOF-3", "05/11/2024");

                cout << "ca == cb ? : " << (ca == cb ? "DA" : "NU") << endl;
                cout << "ca == cc ? : " << (ca == cc ? "DA" : "NU") << endl;
                cout << "ca < cc ? (distanta): " << (ca < cc ? "DA" : "NU") << endl;

                CursaInternationala cd = ca + 5; // adauga 5 colete
                cout << "ca nrColete: " << ca.getNrColete() << " | cd nrColete (dupa +5): " << cd.getNrColete() << endl;

                cd += 100.0;
                cout << "cd distanta (dupa +=100): " << cd.getDistantaKm() << endl;

                ++cd;
                cout << "cd nrColete (dupa ++): " << cd.getNrColete() << endl;

                cout << "Viteza medie pentru ca: " << ca() << " km/h" << endl;
                cout << "Operator [] pe origine (poz 0): " << ca[0] << endl;
                cout << "Cast la double (distanta cd): " << static_cast<double>(cd) << endl;
                cout << "Operator ! pentru cd (nu este finalizata?): " << (!cd ? "DA" : "NU") << endl;
                // 
            }
            cout << "\n✓ Toti constructorii si operatorii cursa functioneaza!" << endl;
            break;

        case 13: {
            double dist;
            int col;
            char urg;
            cout << "\nDistanta (km): ";
            cin >> dist;
            cout << "Nr. colete: ";
            cin >> col;
            cout << "Este urgenta? (d/n): ";
            cin >> urg;
            bool esteUrg = (urg == 'd' || urg == 'D');
            double cost = CursaInternationala::calculeazaCostTotalCursa(dist, col, esteUrg);
            cout << "\nCOST TOTAL: " << cost << " EUR" << endl;
            break;
        }

        case 14: {
            double taxa;
            cout << "\nTaxa vamala curenta: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            cout << "Noua taxa: ";
            cin >> taxa;
            CursaInternationala::setTaxaVamala(taxa);
            cout << "✓ Taxa actualizata!" << endl;
            break;
        }

        case 15: {
            if (curse.empty()) {
                cout << "\nNu exista curse!" << endl;
            }
            else {
                cout << "\n CURSE DISPONIBILE " << endl;
                for (size_t i = 0; i < curse.size(); i++) {
                    cout << (i + 1) << ". " << curse[i]->getCodCursa()
                        << " - Status: " << (curse[i]->getEsteFinalizata() ? "FINALIZATA" : "IN CURS") << endl;
                }
                int idx;
                cout << "Selectati cursa: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)curse.size()) {
                    curse[idx - 1]->setEsteFinalizata(true);
                    cout << "✓ Cursa finalizata!" << endl;
                }
            }
            break;
        }

        case 16:
            cout << "\n STATISTICI CURSE " << endl;
            cout << "Total curse: " << CursaInternationala::getNumarTotalCurse() << endl;
            cout << "Curse finalizate: " << CursaInternationala::getCurseFinalizate() << endl;
            cout << "Curse in curs: " << (CursaInternationala::getNumarTotalCurse() - CursaInternationala::getCurseFinalizate()) << endl;
            cout << "Taxa vamala: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            break;

        case 17: {
            cout << "\n TEST GETTERI/SETTERI CURSA " << endl;
            CursaInternationala c;
            cout << "Cursa initiala:" << endl;
            c.afiseaza();

            cout << "\nModificare date prin setteri..." << endl;
            c.setTaraOrigine("Bulgaria");
            c.setTaraDestinatie("Franta");
            c.setDistantaKm(2800.0);
            c.setDurataTimpOre(32.5);
            c.setNrColete(50);
            c.setSoferId("SOF-999");
            c.setDataPlecarii("20/11/2024");

            cout << "\nCursa dupa modificare:" << endl;
            c.afiseaza();

            cout << "\nTestare getteri:" << endl;
            cout << "Origine: " << c.getTaraOrigine() << endl;
            cout << "Destinatie: " << c.getTaraDestinatie() << endl;
            cout << "Distanta: " << c.getDistantaKm() << " km" << endl;
            cout << "✓ Getteri/Setteri functioneaza!" << endl;
            break;
        }

        case 18: {
            if (curse.empty()) {
                cout << "\nNu exista curse!" << endl;
            }
            else {
                cout << "\n CURSE DISPONIBILE " << endl;
                for (size_t i = 0; i < curse.size(); i++) {
                    cout << (i + 1) << ". " << curse[i]->getCodCursa() << endl;
                }
                int idx;
                cout << "Selectati cursa: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)curse.size()) {
                    optimizeazaRuta(*curse[idx - 1]);
                }
            }
            break;
        }

        case 19: {
            if (curse.empty()) {
                cout << "\nNu exista curse!" << endl;
            }
            else {
                cout << "\n CURSE DISPONIBILE " << endl;
                for (size_t i = 0; i < curse.size(); i++) {
                    cout << (i + 1) << ". " << curse[i]->getCodCursa() << endl;
                }
                int idx;
                cout << "Selectati cursa: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)curse.size()) {
                    afiseazaRaportCursa(*curse[idx - 1]);
                }
            }
            break;
        }

               // = FACTURI =
        case 20: {
            Factura* f = new Factura();
            f->citeste();
            facturi.push_back(f);
            cout << "\n✓ Factura creata cu succes!" << endl;
            break;
        }

        case 21:
            if (facturi.empty()) {
                cout << "\nNu exista facturi!" << endl;
            }
            else {
                for (auto f : facturi) f->afiseaza();
            }
            break;

        case 22: {
            if (facturi.empty()) {
                cout << "\nNu exista facturi!" << endl;
            }
            else {
                cout << "\n FACTURI DISPONIBILE " << endl;
                for (size_t i = 0; i < facturi.size(); i++) {
                    cout << (i + 1) << ". " << facturi[i]->getNumarFactura()
                        << " - " << facturi[i]->getClientDenumire()
                        << " - Status: " << (facturi[i]->getEstePlatita() ? "PLATITA" : "NEPLATITA") << endl;
                }
                int idx;
                cout << "Selectati factura: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)facturi.size()) {
                    facturi[idx - 1]->marcheazaPlatita();
                }
            }
            break;
        }

        case 23:
            cout << "\n TEST CONSTRUCTORI FACTURA (SI OPERATORI) " << endl;
            {
                cout << "\n1. Constructor fara parametri:" << endl;
                Factura f1;
                f1.afiseaza();

                cout << "\n2. Constructor cu toti parametrii:" << endl;
                double preturi[] = { 1000.0, 500.0, 250.0 };
                Factura f2("FACT-2024-001", "13/11/2024", "Transport Express SRL",
                    preturi, 3, "EUR", false);
                f2.afiseaza();

                cout << "\n3. Constructor de copiere:" << endl;
                Factura f3(f2);
                f3.afiseaza();

                cout << "\n4. Operator de atribuire:" << endl;
                f1 = f2;
                f1.afiseaza();

                // == TEST OPERATORI FAZA 3 ==
                cout << "\n--- TEST OPERATORI FACTURA ---" << endl;
                Factura fa("F-001", "01/11/2024", "Client A", preturi, 3, "EUR", false);
                Factura fb("F-002", "02/11/2024", "Client B", preturi, 3, "EUR", false);

                cout << "fa == fb ? : " << (fa == fb ? "DA" : "NU") << endl;

                cout << "Total fa: " << fa.calculeazaTotal() << " | Total fb: " << fb.calculeazaTotal() << endl;
                cout << "fa < fb ? : " << (fa < fb ? "DA" : "NU") << endl;

                cout << "Adaug un serviciu (operator + 120.0) pe fa." << endl;
                Factura fa2 = fa + 120.0;
                cout << "fa2 nrServicii: " << fa2.getNrServicii() << " | total: " << fa2.calculeazaTotal() << endl;

                cout << "Aplic operator -= (scadere) - FAZ3 uses operator- to create new object" << endl;
                Factura fa3 = fa2 - 50.0;
                cout << "fa3 total: " << fa3.calculeazaTotal() << endl;

                cout << "Aplic operator += (majorare 10.0) pe fa3 (mutativ):" << endl;
                fa3 += 10.0;
                cout << "fa3 total dupa +=: " << fa3.calculeazaTotal() << endl;

                cout << "Operator [] pret serviciu 0 din fa3: " << fa3[0] << endl;
                cout << "Cast la double (total cu TVA fa3): " << static_cast<double>(fa3) << endl;
                cout << "Operator () pret mediu per serviciu fa3: " << fa3() << endl;
                cout << "Operator ! pe fa3 (neplatita?): " << (!fa3 ? "DA" : "NU") << endl;
                ++fa3;
                cout << "TVA dupa ++: " << (Factura::getCotaTVA() * 100) << " (nota: acest ++ modifica doar TVA obiectului)" << endl;
                // 
            }
            cout << "\n✓ Toti constructorii si operatorii factura functioneaza!" << endl;
            break;

        case 24: {
            double tva;
            cout << "\nCota TVA curenta: " << (Factura::getCotaTVA() * 100) << "%" << endl;
            cout << "Noua cota (0-1, ex: 0.19): ";
            cin >> tva;
            Factura::setCotaTVA(tva);
            cout << "✓ Cota TVA actualizata!" << endl;
            break;
        }

        case 25:
            cout << "\n STATISTICI FACTURI " << endl;
            cout << "Total facturi: " << Factura::getNumarTotalFacturi() << endl;
            cout << "Incasari totale: " << Factura::getIncasariTotale() << " RON" << endl;
            cout << "Cota TVA: " << (Factura::getCotaTVA() * 100) << "%" << endl;
            {
                int platite = 0, neplatite = 0;
                for (auto f : facturi) {
                    if (f->getEstePlatita()) platite++;
                    else neplatite++;
                }
                cout << "Facturi platite: " << platite << endl;
                cout << "Facturi neplatite: " << neplatite << endl;
            }
            break;

        case 26: {
            cout << "\n TEST GETTERI/SETTERI FACTURA " << endl;
            Factura f;
            cout << "Factura initiala:" << endl;
            f.afiseaza();

            cout << "\nModificare date prin setteri..." << endl;
            f.setNumarFactura("FACT-2024-999");
            f.setDataEmitere("25/11/2024");
            f.setClientDenumire("MegaTransport SRL");
            f.setMoneda("EUR");
            double preturiNoi[] = { 2000.0, 1500.0 };
            f.setPreturiServicii(preturiNoi, 2);

            cout << "\nFactura dupa modificare:" << endl;
            f.afiseaza();

            cout << "\nTestare getteri:" << endl;
            cout << "Numar: " << f.getNumarFactura() << endl;
            cout << "Client: " << f.getClientDenumire() << endl;
            cout << "Moneda: " << f.getMoneda() << endl;
            cout << "Nr. servicii: " << f.getNrServicii() << endl;
            cout << "✓ Getteri/Setteri functioneaza!" << endl;
            break;
        }

        case 27: {
            if (facturi.empty()) {
                cout << "\nNu exista facturi!" << endl;
            }
            else {
                cout << "\n FACTURI DISPONIBILE " << endl;
                for (size_t i = 0; i < facturi.size(); i++) {
                    cout << (i + 1) << ". " << facturi[i]->getNumarFactura()
                        << " - " << facturi[i]->getClientDenumire() << endl;
                }
                int idx;
                cout << "Selectati factura: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)facturi.size()) {
                    double reducere;
                    cout << "Procent reducere (0-1, ex: 0.15 pentru 15%): ";
                    cin >> reducere;
                    aplicaReducere(*facturi[idx - 1], reducere);
                }
            }
            break;
        }

        case 28: {
            if (facturi.empty()) {
                cout << "\nNu exista facturi!" << endl;
            }
            else {
                cout << "\n FACTURI DISPONIBILE " << endl;
                for (size_t i = 0; i < facturi.size(); i++) {
                    cout << (i + 1) << ". " << facturi[i]->getNumarFactura()
                        << " - " << facturi[i]->getClientDenumire() << endl;
                }
                int idx;
                cout << "Selectati factura: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)facturi.size()) {
                    afiseazaRaportFactura(*facturi[idx - 1]);
                }
            }
            break;
        }


        case 29: {
            
            cout << "   TEST FAZA 4 - VECTORI DE OBIECTE" << endl;

            // 1. Populare vector ClientCorporativ
            cout << "1. VECTOR CLIENTI CORPORATIVI " << endl;
            vectorClienti.push_back(ClientCorporativ("Alpha Trans SRL", "Bucuresti, Str. Industriala 10",
                "Ion Popescu", 50, "RO12345678", 1500.0, true));
            vectorClienti.push_back(ClientCorporativ("Beta Logistics SRL", "Cluj-Napoca, Calea Turzii 45",
                "Maria Ionescu", 75, "RO87654321", 2800.0, true));
            vectorClienti.push_back(ClientCorporativ("Gamma Cargo SRL", "Timisoara, Bd. Revolutiei 23",
                "Andrei Vasilescu", 30, "RO11223344", 900.0, true));

            cout << "✓ Adaugat " << vectorClienti.size() << " clienti in vector\n" << endl;

            // Citire de la tastatura
            cout << "Introduceti date pentru un client nou:" << endl;
            ClientCorporativ clientNou;
            cin >> clientNou;
            vectorClienti.push_back(clientNou);

            // Afisare vector clienti
            cout << "\n AFISARE VECTOR CLIENTI " << endl;
            for (size_t i = 0; i < vectorClienti.size(); i++) {
                cout << "\n[Client " << (i + 1) << "]";
                cout << vectorClienti[i];
            }

            // 2. Populare vector CursaInternationala
            cout << "\n 2. VECTOR CURSE INTERNATIONALE" << endl;
            vectorCurse.push_back(CursaInternationala("Romania", "Germania", 2150.0, 24.5, 35, "SOF-101", "15/11/2024"));
            vectorCurse.push_back(CursaInternationala("Romania", "Franta", 2800.0, 32.0, 50, "SOF-102", "16/11/2024"));
            vectorCurse.push_back(CursaInternationala("Romania", "Italia", 1900.0, 22.0, 40, "SOF-103", "17/11/2024"));

            cout << " Adaugat " << vectorCurse.size() << " curse in vector\n" << endl;

            // Citire de la tastatura
            cout << "Introduceti date pentru o cursa noua:" << endl;
            CursaInternationala cursaNoua;
            cin >> cursaNoua;
            vectorCurse.push_back(cursaNoua);

            // Afisare vector curse
            cout << "\n AFISARE VECTOR CURSE " << endl;
            for (size_t i = 0; i < vectorCurse.size(); i++) {
                cout << "\n[Cursa " << (i + 1) << "]";
                cout << vectorCurse[i];
            }

            // 3. Populare vector Factura
            cout << "\n 3. VECTOR FACTURI " << endl;
            double preturi1[] = { 1000.0, 500.0, 250.0 };
            double preturi2[] = { 1500.0, 750.0 };
            double preturi3[] = { 2000.0, 1000.0, 500.0, 250.0 };

            vectorFacturi.push_back(Factura("FACT-2024-001", "13/11/2024", "Alpha Trans SRL",
                preturi1, 3, "EUR", false));
            vectorFacturi.push_back(Factura("FACT-2024-002", "14/11/2024", "Beta Logistics SRL",
                preturi2, 2, "EUR", true));
            vectorFacturi.push_back(Factura("FACT-2024-003", "15/11/2024", "Gamma Cargo SRL",
                preturi3, 4, "EUR", false));

            cout << " Adaugat " << vectorFacturi.size() << " facturi in vector\n" << endl;

            // Citire de la tastatura
            cout << "Introduceti date pentru o factura noua:" << endl;
            Factura facturaNoua;
            cin >> facturaNoua;
            vectorFacturi.push_back(facturaNoua);

            // Afisare vector facturi
            cout << "\n AFISARE VECTOR FACTURI" << endl;
            for (size_t i = 0; i < vectorFacturi.size(); i++) {
                cout << "\n[Factura " << (i + 1) << "]";
                cout << vectorFacturi[i];
            }

            // 4. Creare MATRICE de obiecte (ClientCorporativ)
            cout << "\n 4. MATRICE DE CLIENTI (3x2) " << endl;
            const int ROWS = 3;
            const int COLS = 2;
            ClientCorporativ matriceClienti[ROWS][COLS];

            // Initializare cu date
            matriceClienti[0][0] = ClientCorporativ("Matrice Client 1-1", "Adresa 1-1", "Contact 1-1",
                10, "RO11111111", 500.0, true);
            matriceClienti[0][1] = ClientCorporativ("Matrice Client 1-2", "Adresa 1-2", "Contact 1-2",
                20, "RO22222222", 600.0, true);
            matriceClienti[1][0] = ClientCorporativ("Matrice Client 2-1", "Adresa 2-1", "Contact 2-1",
                15, "RO33333333", 700.0, true);
            matriceClienti[1][1] = ClientCorporativ("Matrice Client 2-2", "Adresa 2-2", "Contact 2-2",
                25, "RO44444444", 800.0, true);
            matriceClienti[2][0] = ClientCorporativ("Matrice Client 3-1", "Adresa 3-1", "Contact 3-1",
                30, "RO55555555", 900.0, true);
            matriceClienti[2][1] = ClientCorporativ("Matrice Client 3-2", "Adresa 3-2", "Contact 3-2",
                35, "RO66666666", 1000.0, true);

            cout << " Creat matrice " << ROWS << "x" << COLS << " de clienti\n" << endl;

            // Afisare matrice
            cout << "\n AFISARE MATRICE CLIENTI " << endl;
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    cout << "\n[Pozitia [" << i << "][" << j << "]]";
                    cout << matriceClienti[i][j];
                }
            }

            cout << "   TEST FAZA 4 FINALIZAT CU SUCCES!" << endl;
          
            break;
        }
        
        case 30: {
            int subOptiune;
            do {
                cout << "   SUBMENIU FAZA 4 - OPERATII AVANSATE" << endl;
                cout << "1. Test intensiv operatori pe obiecte noi" << endl;
                cout << "2. Analiza comparativa intre clase" << endl;
                cout << "3. Operatii avansate cu matrice" << endl;
                cout << "0. Inapoi la meniul principal" << endl;
                cout << "Optiune: ";
                cin >> subOptiune;
                cin.ignore();

                switch (subOptiune) {
                   
                    // SUB-CASE 1: TEST INTENSIV OPERATORI
                case 1: {
                     
                    cout << "   TEST INTENSIV OPERATORI - TOATE CLASELE" << endl;
                     

                    //   TESTE CLIENTI CORPORATIVI  
                    cout << "\n TESTE CLIENTCORPORATIV \n" << endl;

                    ClientCorporativ c1("Alpha Transport SRL", "Bucuresti, Str. Industriala 10",
                        "Ion Popescu", 50, "RO12345678", 1500.0, true);
                    ClientCorporativ c2("Beta Logistics SRL", "Cluj-Napoca, Calea Turzii 45",
                        "Maria Ionescu", 75, "RO87654321", 2800.0, true);
                    ClientCorporativ c3("Gamma Cargo SRL", "Timisoara, Bd. Revolutiei 23",
                        "Andrei Vasilescu", 30, "RO11223344", 900.0, true);

                    cout << "  1. OPERATORI DE COMPARARE  " << endl;
                    cout << "c1 == c2 (volum)? " << (c1 == c2 ? "DA" : "NU") << endl;
                    cout << "c1 == c3 (volum)? " << (c1 == c3 ? "DA" : "NU") << endl;
                    cout << "c1 < c2 (volum)? " << (c1 < c2 ? "DA" : "NU") << endl;
                    cout << "c2 > c3 (volum)? " << (c2 > c3 ? "DA" : "NU") << endl;
                    cout << "c1 < c3 (volum)? " << (c1 < c3 ? "DA" : "NU") << endl;

                    cout << "\n  2. OPERATORI ARITMETICI  " << endl;
                    cout << "c1 angajati initial: " << c1.getNrAngajati() << endl;
                    ClientCorporativ c4 = c1 + 25;  // adaugă 25 angajați
                    cout << "c4 = c1 + 25 angajati: " << c4.getNrAngajati() << endl;

                    ClientCorporativ c5 = c2 - 10;  // scade 10 angajați
                    cout << "c2 angajati initial: " << c2.getNrAngajati() << endl;
                    cout << "c5 = c2 - 10 angajati: " << c5.getNrAngajati() << endl;

                    cout << "\n  3. OPERATOR += (mutativ)  " << endl;
                    cout << "c1 volum inainte: " << c1.getVolumTransporturiLunar() << " tone" << endl;
                    c1 += 500.0;  // crește volumul cu 500 tone
                    cout << "c1 volum dupa +=500: " << c1.getVolumTransporturiLunar() << " tone" << endl;

                    cout << "\n  4. OPERATORI INCREMENT  " << endl;
                    cout << "c2 angajati inainte: " << c2.getNrAngajati() << endl;
                    ++c2;  // pre-increment
                    cout << "c2 angajati dupa ++c2: " << c2.getNrAngajati() << endl;
                    ClientCorporativ c6 = c2++;  // post-increment
                    cout << "c2 angajati dupa c2++: " << c2.getNrAngajati() << endl;
                    cout << "c6 angajati (copie): " << c6.getNrAngajati() << endl;

                    cout << "\n  5. OPERATOR [] (indexare)  " << endl;
                    cout << "Primul caracter din numele c1: '" << c1[0] << "'" << endl;
                    cout << "Al doilea caracter din numele c1: '" << c1[1] << "'" << endl;
                    cout << "Al treilea caracter din numele c1: '" << c1[2] << "'" << endl;
                    cout << "Index invalid (100): '" << c1[100] << "' (ar trebui \\0)" << endl;

                    cout << "\n  6. OPERATOR () - functie  " << endl;
                    double costTotal = 100000.0;
                    double costPerAngajat = c1(costTotal);
                    cout << "Cost total: " << costTotal << " EUR" << endl;
                    cout << "Nr angajati c1: " << c1.getNrAngajati() << endl;
                    cout << "Cost per angajat: " << costPerAngajat << " EUR" << endl;

                    cout << "\n  7. OPERATOR ! (negatie)  " << endl;
                    cout << "c1 este inactiv (!c1)? " << (!c1 ? "DA" : "NU") << endl;
                    c1.setEsteActiv(false);
                    cout << "Dupa setare inactiv, c1 este inactiv? " << (!c1 ? "DA" : "NU") << endl;
                    c1.setEsteActiv(true);  // restabilire

                    cout << "\n  8. OPERATOR CAST LA INT  " << endl;
                    int nrAngajatiC2 = static_cast<int>(c2);
                    cout << "Cast c2 la int (nr angajati): " << nrAngajatiC2 << endl;
                    int nrAngajatiC3 = static_cast<int>(c3);
                    cout << "Cast c3 la int (nr angajati): " << nrAngajatiC3 << endl;

                    //   TESTE CURSE INTERNATIONALE  
                    cout << "\n\n  TESTE CURSAINTERNATIONALA \n" << endl;

                    CursaInternationala cr1("Romania", "Germania", 2150.0, 24.5, 35, "SOF-101", "15/11/2024");
                    CursaInternationala cr2("Romania", "Franta", 2800.0, 32.0, 50, "SOF-102", "16/11/2024");
                    CursaInternationala cr3("Romania", "Italia", 1900.0, 22.0, 40, "SOF-103", "17/11/2024");

                    cout << "  1. OPERATORI DE COMPARARE  " << endl;
                    cout << "cr1 == cr2 (distanta)? " << (cr1 == cr2 ? "DA" : "NU") << endl;
                    cout << "cr1 < cr2 (distanta)? " << (cr1 < cr2 ? "DA" : "NU") << endl;
                    cout << "cr2 > cr3 (distanta)? " << (cr2 > cr3 ? "DA" : "NU") << endl;
                    cout << "cr3 < cr1 (distanta)? " << (cr3 < cr1 ? "DA" : "NU") << endl;

                    cout << "\n  2. OPERATORI ARITMETICI  " << endl;
                    cout << "cr1 colete initial: " << cr1.getNrColete() << endl;
                    CursaInternationala cr4 = cr1 + 15;  // adaugă 15 colete
                    cout << "cr4 = cr1 + 15 colete: " << cr4.getNrColete() << endl;

                    CursaInternationala cr5 = cr2 - 5;  // scade 5 colete
                    cout << "cr2 colete initial: " << cr2.getNrColete() << endl;
                    cout << "cr5 = cr2 - 5 colete: " << cr5.getNrColete() << endl;

                    cout << "\n  3. OPERATOR +=  " << endl;
                    cout << "cr1 distanta inainte: " << cr1.getDistantaKm() << " km" << endl;
                    cr1 += 150.0;  // crește distanța cu 150 km
                    cout << "cr1 distanta dupa +=150: " << cr1.getDistantaKm() << " km" << endl;

                    cout << "\n  4. OPERATORI INCREMENT  " << endl;
                    cout << "cr2 colete inainte: " << cr2.getNrColete() << endl;
                    ++cr2;
                    cout << "cr2 colete dupa ++cr2: " << cr2.getNrColete() << endl;
                    cr2++;
                    cout << "cr2 colete dupa cr2++: " << cr2.getNrColete() << endl;

                    cout << "\n  5. OPERATOR []  " << endl;
                    cout << "Primul caracter origine cr1: '" << cr1[0] << "'" << endl;
                    cout << "Al doilea caracter origine cr1: '" << cr1[1] << "'" << endl;

                    cout << "\n  6. OPERATOR () - viteza medie  " << endl;
                    double vitezaMedie1 = cr1();
                    cout << "Viteza medie cr1: " << vitezaMedie1 << " km/h" << endl;
                    double vitezaMedie2 = cr2();
                    cout << "Viteza medie cr2: " << vitezaMedie2 << " km/h" << endl;

                    cout << "\n  7. OPERATOR !  " << endl;
                    cout << "cr1 nu este finalizata (!cr1)? " << (!cr1 ? "DA" : "NU") << endl;
                    cr1.setEsteFinalizata(true);
                    cout << "Dupa finalizare, cr1 nu este finalizata? " << (!cr1 ? "DA" : "NU") << endl;
                    cr1.setEsteFinalizata(false);  // restabilire

                    cout << "\n  8. OPERATOR CAST LA DOUBLE  " << endl;
                    double distantaCr2 = static_cast<double>(cr2);
                    cout << "Cast cr2 la double (distanta): " << distantaCr2 << " km" << endl;

                    //   TESTE FACTURI  
                    cout << "\n\n  TESTE FACTURA \n" << endl;

                    double preturi1[] = { 1000.0, 500.0, 250.0 };
                    double preturi2[] = { 1500.0, 750.0, 300.0, 200.0 };
                    double preturi3[] = { 2000.0, 1000.0 };

                    Factura f1("FACT-2024-001", "13/11/2024", "Alpha Transport SRL",
                        preturi1, 3, "EUR", false);
                    Factura f2("FACT-2024-002", "14/11/2024", "Beta Logistics SRL",
                        preturi2, 4, "EUR", true);
                    Factura f3("FACT-2024-003", "15/11/2024", "Gamma Cargo SRL",
                        preturi3, 2, "EUR", false);

                    cout <<  " 1. OPERATORI DE COMPARARE  " << endl;
                    cout << "Total f1: " << f1.calculeazaTotal() << " EUR" << endl;
                    cout << "Total f2: " << f2.calculeazaTotal() << " EUR" << endl;
                    cout << "Total f3: " << f3.calculeazaTotal() << " EUR" << endl;
                    cout << "f1 == f2 (total)? " << (f1 == f2 ? "DA" : "NU") << endl;
                    cout << "f1 < f2 (total)? " << (f1 < f2 ? "DA" : "NU") << endl;
                    cout << "f2 > f3 (total)? " << (f2 > f3 ? "DA" : "NU") << endl;

                    cout << "\n  2. OPERATORI ARITMETICI " << endl;
                    cout << "f1 nr servicii initial: " << f1.getNrServicii() << endl;
                    Factura f4 = f1 + 350.0;  // adaugă serviciu de 350 EUR
                    cout << "f4 = f1 + serviciu 350 EUR" << endl;
                    cout << "f4 nr servicii: " << f4.getNrServicii() << endl;
                    cout << "f4 total nou: " << f4.calculeazaTotal() << " EUR" << endl;

                    Factura f5 = f2 - 50.0;  // scade 50 EUR din toate serviciile
                    cout << "\nf2 total inainte: " << f2.calculeazaTotal() << " EUR" << endl;
                    cout << "f5 = f2 - 50 EUR (din fiecare serviciu)" << endl;
                    cout << "f5 total: " << f5.calculeazaTotal() << " EUR" << endl;

                    cout << "\n  3. OPERATOR +=   " << endl;
                    cout << "f1 total inainte: " << f1.calculeazaTotal() << " EUR" << endl;
                    f1 += 100.0;  // adaugă 100 EUR la toate serviciile
                    cout << "f1 total dupa +=100: " << f1.calculeazaTotal() << " EUR" << endl;
 
                    cout << "\n  4. OPERATORI INCREMENT (TVA)   " << endl;
                    double tvaInainte = Factura::getCotaTVA();
                    cout << "Cota TVA inainte: " << (tvaInainte * 100) << "%" << endl;
                    ++f1;  // crește TVA cu 1%
                    cout << "Cota TVA obiect f1 dupa ++: se modifica doar pentru obiect" << endl;

                    cout << "\n  5. OPERATOR []   " << endl;
                    cout << "Pret serviciu [0] din f1: " << f1[0] << " EUR" << endl;
                    cout << "Pret serviciu [1] din f1: " << f1[1] << " EUR" << endl;
                    cout << "Pret serviciu [2] din f1: " << f1[2] << " EUR" << endl;
                    cout << "Index invalid [10]: " << f1[10] << " EUR (ar trebui 0)" << endl;

                    cout << "\n  6. OPERATOR () - pret mediu   " << endl;
                    double pretMediu1 = f1();
                    cout << "Pret mediu per serviciu f1: " << pretMediu1 << " EUR" << endl;
                    double pretMediu2 = f2();
                    cout << "Pret mediu per serviciu f2: " << pretMediu2 << " EUR" << endl;

                    cout << "\n  7. OPERATOR !   " << endl;
                    cout << "f1 nu este platita (!f1)? " << (!f1 ? "DA" : "NU") << endl;
                    cout << "f2 nu este platita (!f2)? " << (!f2 ? "DA" : "NU") << endl;

                    cout << "\n  8. OPERATOR CAST LA DOUBLE   " << endl;
                    double totalCuTVA_f1 = static_cast<double>(f1);
                    cout << "Cast f1 la double (total cu TVA): " << totalCuTVA_f1 << " EUR" << endl;
                    double totalCuTVA_f3 = static_cast<double>(f3);
                    cout << "Cast f3 la double (total cu TVA): " << totalCuTVA_f3 << " EUR" << endl;
 
                    cout << "   TEST OPERATORI FINALIZAT CU SUCCES!" << endl;
                    break;
                }
                 
                      // SUB-CASE 2: ANALIZA COMPARATIVA
                     
                case 2: {
                     
                    cout << "   ANALIZA COMPARATIVA INTRE CLASE" << endl;
                   

                    // Creează seturi de date pentru comparație
                    ClientCorporativ c1("Transport Express SRL", "Bucuresti", "Contact1",
                        100, "RO11111111", 5000.0, true);
                    ClientCorporativ c2("Logistics Pro SRL", "Cluj", "Contact2",
                        50, "RO22222222", 2000.0, true);

                    CursaInternationala cr1("Romania", "Germania", 2000.0, 20.0, 50, "SOF-101", "01/12/24");
                    CursaInternationala cr2("Romania", "Franta", 2500.0, 25.0, 60, "SOF-102", "02/12/24");

                    double p1[] = { 1000.0, 500.0, 300.0 };
                    double p2[] = { 2000.0, 1000.0, 500.0 };
                    Factura f1("F-001", "01/12/24", "Client A", p1, 3, "EUR", false);
                    Factura f2("F-002", "02/12/24", "Client B", p2, 3, "EUR", false);

                    cout << "\n RAPORT COMPARATIV DETALIAT " << endl;

                    //   COMPARARE CLIENTI  
                    cout << "\n COMPARARE CLIENTI " << endl;
                    cout << "\nClient 1:" << endl;
                    cout << "  Nume: " << c1.getNumeCompanie() << endl;
                    cout << "  Angajati: " << c1.getNrAngajati() << endl;
                    cout << "  Volum: " << c1.getVolumTransporturiLunar() << " tone" << endl;

                    cout << "\nClient 2:" << endl;
                    cout << "  Nume: " << c2.getNumeCompanie() << endl;
                    cout << "  Angajati: " << c2.getNrAngajati() << endl;
                    cout << "  Volum: " << c2.getVolumTransporturiLunar() << " tone" << endl;

                    cout << "\nANALIZA:" << endl;
                    cout << "  Egalitate volum (c1 == c2): " << (c1 == c2 ? "DA" : "NU") << endl;
                    cout << "  Client 1 > Client 2: " << (c1 > c2 ? "DA" : "NU") << endl;
                    cout << "  Diferenta volum: " << abs(c1.getVolumTransporturiLunar() - c2.getVolumTransporturiLunar())
                        << " tone" << endl;
                    cout << "  Diferenta angajati: " << abs(c1.getNrAngajati() - c2.getNrAngajati()) << endl;
                    cout << "  Raport angajati C1:C2 = " << ((double)c1.getNrAngajati() / c2.getNrAngajati()) << ":1" << endl;
                    cout << "  Raport volum C1:C2 = " << (c1.getVolumTransporturiLunar() / c2.getVolumTransporturiLunar()) << ":1" << endl;

                    // Calcule financiare
                    double pretStandard = 10000.0;
                    double pretFinal1 = ClientCorporativ::calculeazaPretFinal(pretStandard, c1.getVolumTransporturiLunar());
                    double pretFinal2 = ClientCorporativ::calculeazaPretFinal(pretStandard, c2.getVolumTransporturiLunar());

                    cout << "\n  ANALIZA FINANCIARA (pentru pret standard " << pretStandard << " EUR):" << endl;
                    cout << "  Pret final Client 1: " << pretFinal1 << " EUR (discount: " << (pretStandard - pretFinal1) << " EUR)" << endl;
                    cout << "  Pret final Client 2: " << pretFinal2 << " EUR (discount: " << (pretStandard - pretFinal2) << " EUR)" << endl;
                    cout << "  Diferenta preturi finale: " << abs(pretFinal1 - pretFinal2) << " EUR" << endl;

                    //   COMPARARE CURSE  
                    cout << "\n  COMPARARE CURSE  " << endl;
                    cout << "\nCursa 1:" << endl;

                    cout << "  Cod: " << cr1.getCodCursa() << endl;
                    cout << "  Ruta: " << cr1.getTaraOrigine() << " -> " << cr1.getTaraDestinatie() << endl;
                    cout << "  Distanta: " << cr1.getDistantaKm() << " km" << endl;
                    cout << "  Durata: " << cr1.getDurataTimpOre() << " ore" << endl;
                    cout << "  Colete: " << cr1.getNrColete() << endl;

                    cout << "\nCursa 2:" << endl;
                    cout << "  Cod: " << cr2.getCodCursa() << endl;
                    cout << "  Ruta: " << cr2.getTaraOrigine() << " -> " << cr2.getTaraDestinatie() << endl;
                    cout << "  Distanta: " << cr2.getDistantaKm() << " km" << endl;
                    cout << "  Durata: " << cr2.getDurataTimpOre() << " ore" << endl;
                    cout << "  Colete: " << cr2.getNrColete() << endl;

                    cout << "\nANALIZA:" << endl;
                    cout << "  Egalitate distanta (cr1 == cr2): " << (cr1 == cr2 ? "DA" : "NU") << endl;
                    cout << "  Cursa 1 < Cursa 2: " << (cr1 < cr2 ? "DA" : "NU") << endl;
                    cout << "  Diferenta distanta: " << abs(cr1.getDistantaKm() - cr2.getDistantaKm()) << " km" << endl;
                    cout << "  Diferenta durata: " << abs(cr1.getDurataTimpOre() - cr2.getDurataTimpOre()) << " ore" << endl;
                    cout << "  Diferenta colete: " << abs(cr1.getNrColete() - cr2.getNrColete()) << endl;

                    double viteza1 = cr1();  // operator ()
                    double viteza2 = cr2();
                    cout << "  Viteza medie Cursa 1: " << viteza1 << " km/h" << endl;
                    cout << "  Viteza medie Cursa 2: " << viteza2 << " km/h" << endl;
                    cout << "  Diferenta viteze: " << abs(viteza1 - viteza2) << " km/h" << endl;

                    // Calcule costuri
                    double cost1 = CursaInternationala::calculeazaCostTotalCursa(cr1.getDistantaKm(), cr1.getNrColete(), false);
                    double cost2 = CursaInternationala::calculeazaCostTotalCursa(cr2.getDistantaKm(), cr2.getNrColete(), false);

                    cout << "\n  ANALIZA COSTURI:" << endl;
                    cout << "  Cost total Cursa 1: " << cost1 << " EUR" << endl;
                    cout << "  Cost total Cursa 2: " << cost2 << " EUR" << endl;
                    cout << "  Diferenta costuri: " << abs(cost1 - cost2) << " EUR" << endl;
                    cout << "  Cost/km Cursa 1: " << (cost1 / cr1.getDistantaKm()) << " EUR/km" << endl;
                    cout << "  Cost/km Cursa 2: " << (cost2 / cr2.getDistantaKm()) << " EUR/km" << endl;
                    cout << "  Cost/colet Cursa 1: " << (cost1 / cr1.getNrColete()) << " EUR/colet" << endl;
                    cout << "  Cost/colet Cursa 2: " << (cost2 / cr2.getNrColete()) << " EUR/colet" << endl;

                    //   COMPARARE FACTURI  
                    cout << "\n COMPARARE FACTURI " << endl;
                    cout << "\nFactura 1:" << endl;
                    cout << "  Numar: " << f1.getNumarFactura() << endl;
                    cout << "  Client: " << f1.getClientDenumire() << endl;
                    cout << "  Nr. servicii: " << f1.getNrServicii() << endl;
                    cout << "  Total fara TVA: " << f1.calculeazaTotal() << " EUR" << endl;
                    cout << "  Total cu TVA: " << static_cast<double>(f1) << " EUR" << endl;

                    cout << "\nFactura 2:" << endl;
                    cout << "  Numar: " << f2.getNumarFactura() << endl;
                    cout << "  Client: " << f2.getClientDenumire() << endl;
                    cout << "  Nr. servicii: " << f2.getNrServicii() << endl;
                    cout << "  Total fara TVA: " << f2.calculeazaTotal() << " EUR" << endl;
                    cout << "  Total cu TVA: " << static_cast<double>(f2) << " EUR" << endl;

                    cout << "\nANALIZA:" << endl;
                    cout << "  Egalitate valoare (f1 == f2): " << (f1 == f2 ? "DA" : "NU") << endl;
                    cout << "  Factura 1 < Factura 2: " << (f1 < f2 ? "DA" : "NU") << endl;
                    cout << "  Diferenta fara TVA: " << abs(f1.calculeazaTotal() - f2.calculeazaTotal()) << " EUR" << endl;
                    cout << "  Diferenta cu TVA: " << abs(static_cast<double>(f1) - static_cast<double>(f2)) << " EUR" << endl;
                    cout << "  Pret mediu/serviciu F1: " << f1() << " EUR" << endl;
                    cout << "  Pret mediu/serviciu F2: " << f2() << " EUR" << endl;

                    // SIMULARE SCENARIU BUSINESS 
                    cout << "\n--- SIMULARE SCENARIU BUSINESS ---" << endl;
                    cout << "\nScenariu: Clientul 1 face Cursa 1 si primeste Factura 1" << endl;
                    cout << "          Clientul 2 face Cursa 2 si primeste Factura 2" << endl;

                    cout << "\nClient 1:" << endl;
                    cout << "  Cost cursa: " << cost1 << " EUR" << endl;
                    cout << "  Valoare factura (cu TVA): " << static_cast<double>(f1) << " EUR" << endl;
                    double profit1 = static_cast<double>(f1) - cost1;
                    cout << "  PROFIT: " << profit1 << " EUR" << endl;
                    cout << "  Marja profit: " << ((profit1 / static_cast<double>(f1)) * 100) << "%" << endl;

                    cout << "\nClient 2:" << endl;
                    cout << "  Cost cursa: " << cost2 << " EUR" << endl;
                    cout << "  Valoare factura (cu TVA): " << static_cast<double>(f2) << " EUR" << endl;
                    double profit2 = static_cast<double>(f2) - cost2;
                    cout << "  PROFIT: " << profit2 << " EUR" << endl;
                    cout << "  Marja profit: " << ((profit2 / static_cast<double>(f2)) * 100) << "%" << endl;

                    cout << "\nCOMPARATIE PROFITABILITATE:" << endl;
                    cout << "  Diferenta profit: " << abs(profit1 - profit2) << " EUR" << endl;
                    if (profit1 > profit2) {
                        cout << "  Client 1 este mai profitabil cu " << ((profit1 / profit2) - 1) * 100 << "%" << endl;
                    }
                    else {
                        cout << "  Client 2 este mai profitabil cu " << ((profit2 / profit1) - 1) * 100 << "%" << endl;
                    }

                  
                    cout << "   ANALIZA COMPARATIVA FINALIZATA!" << endl;
                     
                    break;
                }

                      
                      // SUB-CASE 3: OPERATII AVANSATE MATRICE
                     
                case 3: {
                    
                    cout << "   OPERATII AVANSATE CU MATRICE" << endl;
                     

                    const int ROWS = 4;
                    const int COLS = 3;

                    cout << "Creare matrice " << ROWS << "x" << COLS << " pentru fiecare clasa...\n" << endl;

                    //  MATRICE CLIENTI 
                    ClientCorporativ matClienti[ROWS][COLS];

                    cout << "--- Populare matrice CLIENTI ---" << endl;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            string numeC = "Client[" + to_string(i) + "][" + to_string(j) + "] SRL";
                            string adresa = "Adresa " + to_string(i) + "-" + to_string(j);
                            string contact = "Contact " + to_string(i) + "-" + to_string(j);
                            int angajati = (i + 1) * 15 + (j + 1) * 5;
                            string cod = "RO" + to_string(10000000 + i * 10000 + j * 1000);
                            double volum = (i + 1) * 200.0 + (j + 1) * 150.0;

                            matClienti[i][j] = ClientCorporativ(
                                numeC.c_str(), adresa.c_str(), contact.c_str(),
                                angajati, cod, volum, true
                            );
                        }
                    }
                    cout << "✓ Matrice clienti creata!\n" << endl;

                    //  MATRICE CURSE 
                    CursaInternationala matCurse[ROWS][COLS];

                    cout << "--- Populare matrice CURSE ---" << endl;
                    string destinatii[] = { "Germania", "Franta", "Italia" };
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            string dest = destinatii[j % 3];
                            double distanta = 1000.0 + i * 300 + j * 200;
                            double durata = 10.0 + i * 2 + j * 3;
                            int colete = 20 + i * 10 + j * 5;
                            string sofer = "SOF-" + to_string(100 + i * 10 + j);
                            string data = to_string(1 + i) + "/12/2024";

                            matCurse[i][j] = CursaInternationala(
                                "Romania", dest, distanta, durata, colete,
                                sofer.c_str(), data.c_str()
                            );
                        }
                    }
                    cout << "✓ Matrice curse creata!\n" << endl;

                    //  AFISARE TABELARA CLIENTI 
                    cout << " MATRICE CLIENTI - VEDERE TABELARA " << endl;
                    cout << "Pozitie    | Nume                      | Angajati | Volum (tone)" << endl;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            cout << "[" << i << "][" << j << "]     | ";
                            string nume = matClienti[i][j].getNumeCompanie();
                            cout << nume.substr(0, 25);
                            for (size_t k = nume.length(); k < 25; k++) cout << " ";
                            cout << " | ";
                            cout << matClienti[i][j].getNrAngajati();
                            if (matClienti[i][j].getNrAngajati() < 10) cout << "        | ";
                            else if (matClienti[i][j].getNrAngajati() < 100) cout << "       | ";
                            else cout << "      | ";
                            cout << matClienti[i][j].getVolumTransporturiLunar() << endl;
                        }
                    }
                  
                    //  AFISARE TABELARA CURSE 
                    cout << " MATRICE CURSE - VEDERE TABELARA " << endl;
                    
                    cout << "Pozitie    | Cod          | Destinatie  | Distanta | Colete" << endl;
                    
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            cout << "[" << i << "][" << j << "]     | ";
                            cout << matCurse[i][j].getCodCursa();
                            string cod = matCurse[i][j].getCodCursa();
                            for (size_t k = cod.length(); k < 12; k++) cout << " ";
                            cout << " | ";
                            cout << matCurse[i][j].getTaraDestinatie();
                            string dest = matCurse[i][j].getTaraDestinatie();
                            for (size_t k = dest.length(); k < 11; k++) cout << " ";
                            cout << " | ";
                            cout << matCurse[i][j].getDistantaKm();
                            if (matCurse[i][j].getDistantaKm() < 10000) cout << "    | ";
                            else cout << "   | ";
                            cout << matCurse[i][j].getNrColete() << endl;
                        }
                    }
               
                    //  STATISTICI PE LINII (CLIENTI) 
                    cout << " STATISTICI PE LINII - CLIENTI " << endl;
                    for (int i = 0; i < ROWS; i++) {
                        double volumLinie = 0;
                        int angajatiLinie = 0;
                        for (int j = 0; j < COLS; j++) {
                            volumLinie += matClienti[i][j].getVolumTransporturiLunar();
                            angajatiLinie += matClienti[i][j].getNrAngajati();
                        }
                        cout << "Linia " << i << ": Volum total=" << volumLinie << " tone, "
                            << "Angajati total=" << angajatiLinie << ", "
                            << "Volum mediu=" << (volumLinie / COLS) << " tone" << endl;
                    }
                    cout << endl;

                    //  STATISTICI PE COLOANE (CURSE)
                    cout << " STATISTICI PE COLOANE - CURSE " << endl;
                    for (int j = 0; j < COLS; j++) {
                        double distantaColoana = 0;
                        int coleteColoana = 0;
                        double durataColoana = 0;
                        for (int i = 0; i < ROWS; i++) {
                            distantaColoana += matCurse[i][j].getDistantaKm();
                            coleteColoana += matCurse[i][j].getNrColete();
                            durataColoana += matCurse[i][j].getDurataTimpOre();
                        }
                        cout << "Coloana " << j << ": Distanta total=" << distantaColoana << " km, "
                            << "Colete total=" << coleteColoana << ", "
                            << "Viteza medie=" << (distantaColoana / durataColoana) << " km/h" << endl;
                    }
                    cout << endl;

                    //  DIAGONALA PRINCIPALA 
                    cout << " DIAGONALA PRINCIPALA - CLIENTI " << endl;
                    double volumDiag = 0;
                    int angajatiDiag = 0;
                    int minSize = (ROWS < COLS) ? ROWS : COLS;

                    for (int i = 0; i < minSize; i++) {
                        volumDiag += matClienti[i][i].getVolumTransporturiLunar();
                        angajatiDiag += matClienti[i][i].getNrAngajati();
                        cout << "[" << i << "][" << i << "]: " << matClienti[i][i].getNumeCompanie()
                            << " - Volum: " << matClienti[i][i].getVolumTransporturiLunar() << " tone" << endl;
                    }
                    cout << "\nTotal diagonala:" << endl;
                    cout << "  Volum: " << volumDiag << " tone" << endl;
                    cout << "  Angajati: " << angajatiDiag << endl;
                    cout << "  Volum mediu: " << (volumDiag / minSize) << " tone\n" << endl;

                    //  GASIRE ELEMENTE EXTREME - CLIENTI 
                    cout << "  ELEMENTE EXTREME - CLIENTI  " << endl;
                    ClientCorporativ* clientMin = &matClienti[0][0];
                    ClientCorporativ* clientMax = &matClienti[0][0];
                    int minI = 0, minJ = 0, maxI = 0, maxJ = 0;

                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            if (matClienti[i][j] < *clientMin) {  // operator 
                                clientMin = &matClienti[i][j];
                                minI = i;
                                minJ = j;
                            }
                            if (matClienti[i][j] > *clientMax) {  // operator >
                                clientMax = &matClienti[i][j];
                                maxI = i;
                                maxJ = j;
                            }
                        }
                    }

                    cout << "Volum MINIM:" << endl;
                    cout << "  Pozitie: [" << minI << "][" << minJ << "]" << endl;
                    cout << "  Client: " << clientMin->getNumeCompanie() << endl;
                    cout << "  Volum: " << clientMin->getVolumTransporturiLunar() << " tone" << endl;

                    cout << "\nVolum MAXIM:" << endl;
                    cout << "  Pozitie: [" << maxI << "][" << maxJ << "]" << endl;
                    cout << "  Client: " << clientMax->getNumeCompanie() << endl;
                    cout << "  Volum: " << clientMax->getVolumTransporturiLunar() << " tone\n" << endl;

                    //  GASIRE ELEMENTE EXTREME - CURSE 
                    cout << "  ELEMENTE EXTREME - CURSE  " << endl;
                    double distMin = 999999, distMax = 0;
                    int posMinI_c = 0, posMinJ_c = 0, posMaxI_c = 0, posMaxJ_c = 0;

                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            double d = matCurse[i][j].getDistantaKm();
                            if (d < distMin) {
                                distMin = d;
                                posMinI_c = i;
                                posMinJ_c = j;
                            }
                            if (d > distMax) {
                                distMax = d;
                                posMaxI_c = i;
                                posMaxJ_c = j;
                            }
                        }
                    }

                    cout << "Distanta MINIMA:" << endl;
                    cout << "  Pozitie: [" << posMinI_c << "][" << posMinJ_c << "]" << endl;
                    cout << "  Cursa: " << matCurse[posMinI_c][posMinJ_c].getCodCursa() << endl;
                    cout << "  Distanta: " << distMin << " km" << endl;

                    cout << "\nDistanta MAXIMA:" << endl;
                    cout << "  Pozitie: [" << posMaxI_c << "][" << posMaxJ_c << "]" << endl;
                    cout << "  Cursa: " << matCurse[posMaxI_c][posMaxJ_c].getCodCursa() << endl;
                    cout << "  Distanta: " << distMax << " km\n" << endl;

                    //  STATISTICI GENERALE MATRICE 
                    cout << " STATISTICI GENERALE MATRICE " << endl;

                    double volumTotalMat = 0;
                    int angajatiTotalMat = 0;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            volumTotalMat += matClienti[i][j].getVolumTransporturiLunar();
                            angajatiTotalMat += matClienti[i][j].getNrAngajati();
                        }
                    }

                    cout << "MATRICE CLIENTI (" << ROWS << "x" << COLS << "):" << endl;
                    cout << "  Elemente totale: " << (ROWS * COLS) << endl;
                    cout << "  Volum total: " << volumTotalMat << " tone" << endl;
                    cout << "  Angajati total: " << angajatiTotalMat << endl;
                    cout << "  Volum mediu: " << (volumTotalMat / (ROWS * COLS)) << " tone/client" << endl;
                    cout << "  Angajati mediu: " << (angajatiTotalMat / (ROWS * COLS)) << " angajati/client" << endl;

                    double distTotalMat = 0;
                    int coleteTotalMat = 0;
                    double durataTotalMat = 0;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            distTotalMat += matCurse[i][j].getDistantaKm();
                            coleteTotalMat += matCurse[i][j].getNrColete();
                            durataTotalMat += matCurse[i][j].getDurataTimpOre();
                        }
                    }

                    cout << "\nMATRICE CURSE (" << ROWS << "x" << COLS << "):" << endl;
                    cout << "  Elemente totale: " << (ROWS * COLS) << endl;
                    cout << "  Distanta totala: " << distTotalMat << " km" << endl;
                    cout << "  Colete totale: " << coleteTotalMat << endl;
                    cout << "  Durata totala: " << durataTotalMat << " ore" << endl;
                    cout << "  Distanta medie: " << (distTotalMat / (ROWS * COLS)) << " km/cursa" << endl;
                    cout << "  Viteza medie generala: " << (distTotalMat / durataTotalMat) << " km/h" << endl;

                  
                    cout << "   OPERATII MATRICE FINALIZATE!" << endl;
                  
                    break;
                }

                case 0:
                    cout << "\nRevenire la meniul principal..." << endl;
                    break;

                default:
                    cout << "\n⚠️  Optiune invalida! Incercati din nou." << endl;
                }

            } while (subOptiune != 0);
            break;
        }

        // === COMENZI TRANSPORT - FAZA 5 ===
        case 31: {
            cout << "\n=== CREARE COMANDA NOUA ===" << endl;

            if (clienti.empty()) {
                cout << "Nu exista clienti! Creati mai intai un client." << endl;
                break;
            }
            if (curse.empty()) {
                cout << "Nu exista curse! Creati mai intai o cursa." << endl;
                break;
            }

            // Selectare client
            cout << "\nClienti disponibili:" << endl;
            for (size_t i = 0; i < clienti.size(); i++) {
                cout << (i + 1) << ". " << clienti[i]->getNumeCompanie() << endl;
            }
            int idxClient;
            cout << "Selectati client: ";
            cin >> idxClient;
            cin.ignore();

            if (idxClient < 1 || idxClient >(int)clienti.size()) {
                cout << "Selectie invalida!" << endl;
                break;
            }

            // Selectare cursa principala
            cout << "\nCurse disponibile:" << endl;
            for (size_t i = 0; i < curse.size(); i++) {
                cout << (i + 1) << ". " << curse[i]->getCodCursa()
                    << " - " << curse[i]->getTaraDestinatie() << endl;
            }
            int idxCursa;
            cout << "Selectati cursa principala: ";
            cin >> idxCursa;
            cin.ignore();

            if (idxCursa < 1 || idxCursa >(int)curse.size()) {
                cout << "Selectie invalida!" << endl;
                break;
            }

            // Selectare factura (optional)
            Factura* facturaSelectata = nullptr;
            if (!facturi.empty()) {
                cout << "\nFacturi disponibile:" << endl;
                cout << "0. Fara factura" << endl;
                for (size_t i = 0; i < facturi.size(); i++) {
                    cout << (i + 1) << ". " << facturi[i]->getNumarFactura()
                        << " - " << facturi[i]->getClientDenumire() << endl;
                }
                int idxFactura;
                cout << "Selectati factura (0 pentru fara): ";
                cin >> idxFactura;
                cin.ignore();

                if (idxFactura > 0 && idxFactura <= (int)facturi.size()) {
                    facturaSelectata = facturi[idxFactura - 1];
                }
            }

            // Creare comanda
            char numCmd[50], obs[500];
            string dataCmd;

            cout << "\nNumar comanda: ";
            cin.getline(numCmd, 50);
            cout << "Data comanda (DD/MM/YYYY): ";
            getline(cin, dataCmd);
            cout << "Observatii: ";
            cin.getline(obs, 500);

            ComandaTransport* cmd = new ComandaTransport(
                numCmd, dataCmd,
                clienti[idxClient - 1],
                *curse[idxCursa - 1],
                facturaSelectata,
                obs
            );

            comenzi.push_back(cmd);
            cout << "\n✓ Comanda creata cu succes!" << endl;
            cmd->afiseaza();
            break;
        }

        case 32: {
            if (comenzi.empty()) {
                cout << "\nNu exista comenzi!" << endl;
            }
            else {
                cout << "\n=== TOATE COMENZILE ===" << endl;
                for (auto cmd : comenzi) {
                    cmd->afiseaza();
                }
            }
            break;
        }

        case 33: {
            cout << "\n" << endl;
            cout << "TEST COMPLET FAZA 5 - RELATII HAS-A " << endl;
            cout << "\n" << endl;

            // 1. Creare obiecte pentru test
            cout << "1. Creare obiecte de test..." << endl;

            ClientCorporativ* clientTest1 = new ClientCorporativ(
                "MegaTransport SRL", "Bucuresti, Sector 1",
                "Ion Popescu", 100, "RO99999999", 3000.0, true
            );

            ClientCorporativ* clientTest2 = new ClientCorporativ(
                "SuperLogistics SRL", "Cluj-Napoca",
                "Maria Ionescu", 75, "RO88888888", 2500.0, true
            );

            CursaInternationala* cursaTest1 = new CursaInternationala(
                "Romania", "Germania", 2200.0, 25.0, 45, "SOF-201", "20/12/2024"
            );

            CursaInternationala* cursaTest2 = new CursaInternationala(
                "Romania", "Franta", 2800.0, 30.0, 50, "SOF-202", "21/12/2024"
            );

            CursaInternationala* cursaTest3 = new CursaInternationala(
                "Romania", "Italia", 1900.0, 22.0, 40, "SOF-203", "22/12/2024"
            );

            double preturiTest[] = { 2000.0, 1500.0, 1000.0 };
            Factura* facturaTest1 = new Factura(
                "FACT-TEST-001", "20/12/2024", "MegaTransport SRL",
                preturiTest, 3, "EUR", false
            );

            Factura* facturaTest2 = new Factura(
                "FACT-TEST-002", "21/12/2024", "SuperLogistics SRL",
                preturiTest, 3, "EUR", false
            );

            cout << "✓ Obiecte create!\n" << endl;

            // 2. Demonstrare HAS-A cu obiecte
            cout << "2. TEST: Comanda cu obiect CursaInternationala (has-a)" << endl;
            ComandaTransport cmd1("CMD-TEST-001", "20/12/2024", clientTest1,
                *cursaTest1, facturaTest1,
                "Comanda test cu cursa principala");
            cmd1.afiseaza();

            // 3. Demonstrare HAS-A cu pointer
            cout << "3. TEST: Comanda cu pointer la Client (has-a)" << endl;
            cout << "Clientul comenzii: " << cmd1.getClient()->getNumeCompanie() << endl;
            cout << "Volum client: " << cmd1.getClient()->getVolumTransporturiLunar() << " tone\n" << endl;

            // 4. Demonstrare HAS-A cu vector de pointeri
            cout << "4. TEST: Adaugare curse aditionale (vector de pointeri - has-a)" << endl;
            cout << "Curse aditionale inainte: " << cmd1.getCurseAditionale().size() << endl;
            cmd1.adaugaCursaAditionala(cursaTest2);
            cmd1.adaugaCursaAditionala(cursaTest3);
            cout << "Curse aditionale dupa: " << cmd1.getCurseAditionale().size() << endl;
            cmd1.afiseaza();

            // 5. Test operatori
            cout << "5. TEST OPERATORI PE COMANDA" << endl;

            ComandaTransport cmd2("CMD-TEST-002", "21/12/2024", clientTest2,
                *cursaTest2, facturaTest2,
                "Comanda test 2");

            cout << "Valoare cmd1: " << static_cast<double>(cmd1) << " EUR" << endl;
            cout << "Valoare cmd2: " << static_cast<double>(cmd2) << " EUR" << endl;
            cout << "cmd1 == cmd2 ? " << (cmd1 == cmd2 ? "DA" : "NU") << endl;
            cout << "cmd1 < cmd2 ? " << (cmd1 < cmd2 ? "DA" : "NU") << endl;

            cout << "\nOperator [] - acces cursa aditionala:" << endl;
            CursaInternationala* cursaIdx = cmd1[0];
            if (cursaIdx != nullptr) {
                cout << "Cursa [0]: " << cursaIdx->getCodCursa()
                    << " - " << cursaIdx->getTaraDestinatie() << endl;
            }

            // 6. Demonstrare toate relatiile HAS-A
            cout << "\n6. REZUMAT RELATII HAS-A IN COMANDATRANSPORT:" << endl;
            cout << "" << endl;
            cout << "ClientCorporativ* client (pointer - has-a) " << endl;
            cout << "CursaInternationala cursaPrincipala (obj)   " << endl;
            cout << "Factura* factura (pointer - has-a)         " << endl;
            cout << "vector<CursaInternationala*> curseAditionale" << endl;
            cout << "(vector de pointeri - has-a)                " << endl;
            cout << "\n" << endl;

            // 7. Test cu operatori << si >>
            cout << "7. TEST OPERATOR <<" << endl;
            cout << cmd1 << endl;

            // 8. Statistici
            cout << "8. STATISTICI COMENZI" << endl;
            cout << "Total comenzi create: " << ComandaTransport::getNumarTotalComenzi() << endl;
            cout << "Incasari totale: " << ComandaTransport::getIncasariTotale() << " EUR" << endl;

            // Cleanup
            delete clientTest1;
            delete clientTest2;
            delete cursaTest1;
            delete cursaTest2;
            delete cursaTest3;
            delete facturaTest1;
            delete facturaTest2;

            cout << "\n" << endl;
            cout << "     TEST FAZA 5 FINALIZAT CU SUCCES!          " << endl;
            cout << "" << endl;
            break;
        }

        case 34: {
            if (comenzi.empty()) {
                cout << "\nNu exista comenzi!" << endl;
                break;
            }
            if (curse.empty()) {
                cout << "\nNu exista curse disponibile!" << endl;
                break;
            }

            cout << "\nADAUGARE CURSA ADITIONALA" << endl;
            cout << "\nComenzi disponibile:" << endl;
            for (size_t i = 0; i < comenzi.size(); i++) {
                cout << (i + 1) << ". " << comenzi[i]->getNumarComanda()
                    << " (Curse aditionale: " << comenzi[i]->getCurseAditionale().size() << ")" << endl;
            }

            int idxCmd;
            cout << "Selectati comanda: ";
            cin >> idxCmd;
            cin.ignore();

            if (idxCmd < 1 || idxCmd >(int)comenzi.size()) {
                cout << "Selectie invalida!" << endl;
                break;
            }

            cout << "\nCurse disponibile:" << endl;
            for (size_t i = 0; i < curse.size(); i++) {
                cout << (i + 1) << ". " << curse[i]->getCodCursa()
                    << " - " << curse[i]->getTaraDestinatie() << endl;
            }

            int idxCursa;
            cout << "Selectati cursa: ";
            cin >> idxCursa;
            cin.ignore();

            if (idxCursa < 1 || idxCursa >(int)curse.size()) {
                cout << "Selectie invalida!" << endl;
                break;
            }

            comenzi[idxCmd - 1]->adaugaCursaAditionala(curse[idxCursa - 1]);
            cout << "\n✓ Cursa adaugata cu succes!" << endl;
            comenzi[idxCmd - 1]->afiseaza();
            break;
        }

        case 35: {
            if (comenzi.empty()) {
                cout << "\nNu exista comenzi!" << endl;
                break;
            }

            cout << "\n FINALIZARE COMANDA " << endl;
            cout << "\nComenzi disponibile:" << endl;
            for (size_t i = 0; i < comenzi.size(); i++) {
                cout << (i + 1) << ". " << comenzi[i]->getNumarComanda()
                    << " - Status: " << (comenzi[i]->getEsteFinalizata() ? "FINALIZATA" : "IN CURS") << endl;
            }

            int idx;
            cout << "Selectati comanda: ";
            cin >> idx;
            cin.ignore();

            if (idx < 1 || idx >(int)comenzi.size()) {
                cout << "Selectie invalida!" << endl;
                break;
            }

            comenzi[idx - 1]->setEsteFinalizata(true);
            cout << "\n✓ Comanda finalizata!" << endl;
            cout << "Valoare: " << comenzi[idx - 1]->getValoareTotala() << " EUR" << endl;
            break;
        }

        case 36: {
            cout << "\n STATISTICI COMENZI" << endl;
            cout << "Total comenzi: " << ComandaTransport::getNumarTotalComenzi() << endl;
            cout << "Incasari totale: " << ComandaTransport::getIncasariTotale() << " EUR" << endl;

            if (!comenzi.empty()) {
                int finalizate = 0;
                double valoareTotala = 0;
                for (auto cmd : comenzi) {
                    if (cmd->getEsteFinalizata()) finalizate++;
                    valoareTotala += cmd->getValoareTotala();
                }
                cout << "Comenzi finalizate: " << finalizate << endl;
                cout << "Comenzi in curs: " << (comenzi.size() - finalizate) << endl;
                cout << "Valoare totala comenzi: " << valoareTotala << " EUR" << endl;
                cout << "Valoare medie/comanda: " << (valoareTotala / comenzi.size()) << " EUR" << endl;
            }
            cout << "" << endl;
            break;
        }
               // FAZA 6 - FISIERE
        case 37: {
            cout << "\n SALVARE DATE IN FISIERE TEXT " << endl;

            // Salvare clienti
            if (!clienti.empty()) {
                for (auto client : clienti) {
                    ClientCorporativFileManager::salvareTextClient(*client, "clienti.txt");
                }
                cout << "✓ " << clienti.size() << " clienti salvati in clienti.txt" << endl;
            }

            // Salvare curse
            if (!curse.empty()) {
                for (auto cursa : curse) {
                    CursaInternationalaFileManager::salvareTextCursa(*cursa, "curse.txt");
                }
                cout << "✓ " << curse.size() << " curse salvate in curse.txt" << endl;
            }

            // Salvare facturi
            if (!facturi.empty()) {
                for (auto factura : facturi) {
                    FacturaFileManager::salvareTextFactura(*factura, "facturi.txt");
                }
                cout << "✓ " << facturi.size() << " facturi salvate in facturi.txt" << endl;
            }

            // Salvare comenzi
            if (!comenzi.empty()) {
                for (auto comanda : comenzi) {
                    ComandaTransportFileManager::salvareTextComanda(*comanda, "comenzi.txt");
                }
                cout << comenzi.size() << " comenzi salvate in comenzi.txt" << endl;
            }

            cout << "\n TOATE DATELE AU FOST SALVATE IN FISIERE TEXT!" << endl;
            break;
        }

        case 38: {
            cout << "\n CITIRE DATE DIN FISIERE TEXT " << endl;
            int subOpt;
            cout << "1. Citire clienti.txt" << endl;
            cout << "2. Citire curse.txt" << endl;
            cout << "3. Citire facturi.txt" << endl;
            cout << "4. Citire comenzi.txt" << endl;
            cout << "5. Citire toate fisierele" << endl;
            cout << "Optiune: ";
            cin >> subOpt;
            cin.ignore();

            switch (subOpt) {
            case 1:
                ClientCorporativFileManager::citireTextClient("clienti.txt");
                break;
            case 2:
                CursaInternationalaFileManager::citireTextCursa("curse.txt");
                break;
            case 3:
                FacturaFileManager::citireTextFactura("facturi.txt");
                break;
            case 4:
                ComandaTransportFileManager::citireTextComanda("comenzi.txt");
                break;
            case 5:
                ClientCorporativFileManager::citireTextClient("clienti.txt");
                CursaInternationalaFileManager::citireTextCursa("curse.txt");
                FacturaFileManager::citireTextFactura("facturi.txt");
                ComandaTransportFileManager::citireTextComanda("comenzi.txt");
                break;
            default:
                cout << "Optiune invalida!" << endl;
            }
            break;
        }

        case 39: {
            cout << "\n SALVARE DATE IN FISIERE BINARE " << endl;

            // Salvare clienti
            if (!clienti.empty()) {
                for (auto client : clienti) {
                    ClientCorporativFileManager::salvareBinarClient(*client, "clienti.bin");
                }
                cout << clienti.size() << " clienti salvati in clienti.bin" << endl;
            }

            // Salvare curse
            if (!curse.empty()) {
                for (auto cursa : curse) {
                    CursaInternationalaFileManager::salvareBinarCursa(*cursa, "curse.bin");
                }
                cout << curse.size() << " curse salvate in curse.bin" << endl;
            }

            // Salvare facturi
            if (!facturi.empty()) {
                for (auto factura : facturi) {
                    FacturaFileManager::salvareBinarFactura(*factura, "facturi.bin");
                }
                cout << facturi.size() << " facturi salvate in facturi.bin" << endl;
            }

            // Salvare comenzi
            if (!comenzi.empty()) {
                for (auto comanda : comenzi) {
                    ComandaTransportFileManager::salvareBinarComanda(*comanda, "comenzi.bin");
                }
                cout << comenzi.size() << " comenzi salvate in comenzi.bin" << endl;
            }

            cout << "\n TOATE DATELE AU FOST SALVATE IN FISIERE BINARE!" << endl;
            break;
        }

        case 40: {
            cout << "\n CITIRE DATE DIN FISIERE BINARE " << endl;
            int subOpt;
            cout << "1. Citire clienti.bin" << endl;
            cout << "2. Citire curse.bin" << endl;
            cout << "3. Citire facturi.bin" << endl;
            cout << "4. Citire comenzi.bin" << endl;
            cout << "5. Citire toate fisierele" << endl;
            cout << "Optiune: ";
            cin >> subOpt;
            cin.ignore();

            switch (subOpt) {
            case 1:
                ClientCorporativFileManager::citireBinarClient("clienti.bin");
                break;
            case 2:
                CursaInternationalaFileManager::citireBinarCursa("curse.bin");
                break;
            case 3:
                FacturaFileManager::citireBinarFactura("facturi.bin");
                break;
            case 4:
                ComandaTransportFileManager::citireBinarComanda("comenzi.bin");
                break;
            case 5:
                ClientCorporativFileManager::citireBinarClient("clienti.bin");
                CursaInternationalaFileManager::citireBinarCursa("curse.bin");
                FacturaFileManager::citireBinarFactura("facturi.bin");
                ComandaTransportFileManager::citireBinarComanda("comenzi.bin");
                break;
            default:
                cout << "Optiune invalida!" << endl;
            }
            break;
        }

        case 41: {
            cout << "  TEST COMPLET FAZA 6 - FISIERE    " << endl;

            // Creare obiecte de test
            cout << "1. Creare obiecte de test pentru fisiere..." << endl;

            ClientCorporativ clientTest("FileTest SRL", "Adresa Test", "Contact Test",
                50, "RO12345678", 1500.0, true);

            CursaInternationala cursaTest("Romania", "Germania", 2000.0, 24.0,
                40, "SOF-999", "01/01/2025");

            double preturiTest[] = { 1000.0, 500.0 };
            Factura facturaTest("FACT-TEST", "01/01/2025", "FileTest SRL",
                preturiTest, 2, "EUR", false);

            ComandaTransport comandaTest("CMD-TEST", "01/01/2025", &clientTest,
                cursaTest, &facturaTest, "Test fisiere");

            cout << "✓ Obiecte create!\n" << endl;

            // TEST FISIERE TEXT
            cout << "2. TEST SALVARE/CITIRE FISIERE TEXT" << endl;
            cout << "" << endl;

            ClientCorporativFileManager::salvareTextClient(clientTest, "test_client.txt");
            CursaInternationalaFileManager::salvareTextCursa(cursaTest, "test_cursa.txt");
            FacturaFileManager::salvareTextFactura(facturaTest, "test_factura.txt");
            ComandaTransportFileManager::salvareTextComanda(comandaTest, "test_comanda.txt");

            cout << "\nCitire inapoi din fisiere TEXT:" << endl;
            ClientCorporativFileManager::citireTextClient("test_client.txt");

            // TEST FISIERE BINARE
            cout << "\n3. TEST SALVARE/CITIRE FISIERE BINARE" << endl;
            cout << "" << endl;

            ClientCorporativFileManager::salvareBinarClient(clientTest, "test_client.bin");
            CursaInternationalaFileManager::salvareBinarCursa(cursaTest, "test_cursa.bin");
            FacturaFileManager::salvareBinarFactura(facturaTest, "test_factura.bin");
            ComandaTransportFileManager::salvareBinarComanda(comandaTest, "test_comanda.bin");

            cout << "\nCitire inapoi din fisiere BINARE:" << endl;
            ClientCorporativFileManager::citireBinarClient("test_client.bin");

            // REZUMAT
            cout << "\n4. REZUMAT FAZA 6" << endl;
            cout << "" << endl;
            cout << "✓ ClientCorporativ: 2 metode TEXT + 2 metode BINAR" << endl;
            cout << "✓ CursaInternationala: 2 metode TEXT + 2 metode BINAR" << endl;
            cout << "✓ Factura: 2 metode TEXT + 2 metode BINAR" << endl;
            cout << "✓ ComandaTransport: 2 metode TEXT + 2 metode BINAR" << endl;
            cout << "" << endl;
            cout << "TOTAL: 8 metode TEXT + 8 metode BINAR = 16 metode" << endl;

            cout << "\n" << endl;
            cout << "      TEST FAZA 6 FINALIZAT CU SUCCES!            " << endl;
            cout << "" << endl;
            break;
        }
               // FAZA 7 - MOSTENIRE SI UPCASTING 

        case 42: {
            cout << "\n CREARE CLIENT PREMIUM " << endl;

            char nume[200], adresa[200], contact[200], manager[200];
            int angajati, nivel, puncte;
            string codFiscal;
            double volum, discountExtra;
            bool activ;
            char activChar;

            cout << "Nume companie: ";
            cin.getline(nume, 200);

            cout << "Adresa sediu: ";
            cin.getline(adresa, 200);

            cout << "Persoana contact: ";
            cin.getline(contact, 200);

            cout << "Numar angajati: ";
            cin >> angajati;

            cout << "Cod fiscal: ";
            cin >> codFiscal;

            cout << "Volum transporturi lunar (tone): ";
            cin >> volum;

            cout << "Activ (d/n): ";
            cin >> activChar;
            activ = (activChar == 'd' || activChar == 'D');

            cout << "\n DATE PREMIUM " << endl;
            cout << "Nivel Premium (1-5): ";
            cin >> nivel;

            cout << "Discount suplimentar (0-0.5, ex: 0.1 = 10%): ";
            cin >> discountExtra;

            cin.ignore();
            cout << "Manager dedicat: ";
            cin.getline(manager, 200);

            cout << "Puncte fidelitate initiale: ";
            cin >> puncte;
            cin.ignore();

            ClientCorporativPremium* clientPremium = new ClientCorporativPremium(
                nume, adresa, contact, angajati, codFiscal, volum, activ,
                nivel, discountExtra, manager, puncte
            );

            clientiPremium.push_back(clientPremium);
            cout << "\n Client Premium creat cu succes!" << endl;
            clientPremium->afiseaza();
            break;
        }

        case 43: {
            cout << "\n CREARE CURSA EXPRES" << endl;

            char origine[200], sofer[200], data[200], prior[50];
            string destinatie;
            double distanta, durata, taxaUrg;
            int colete, oreGarantate;
            bool garantie24h;
            char garantieChar;

            cout << "Tara origine: ";
            cin.getline(origine, 200);

            cout << "Tara destinatie: ";
            getline(cin, destinatie);

            cout << "Distanta (km): ";
            cin >> distanta;

            cout << "Durata (ore): ";
            cin >> durata;

            cout << "Numar colete: ";
            cin >> colete;

            cin.ignore();
            cout << "ID sofer: ";
            cin.getline(sofer, 200);

            cout << "Data plecarii (DD/MM/YYYY): ";
            cin.getline(data, 200);

            cout << "\n DATE EXPRES " << endl;
            cout << "Livrare garantata 24h (d/n): ";
            cin >> garantieChar;
            garantie24h = (garantieChar == 'd' || garantieChar == 'D');

            cout << "Taxa urgenta (EUR): ";
            cin >> taxaUrg;

            cin.ignore();
            cout << "Prioritate (STANDARD/EXPRESS/SUPER_EXPRESS): ";
            cin.getline(prior, 50);

            cout << "Ore livrare garantate: ";
            cin >> oreGarantate;
            cin.ignore();

            CursaExpres* cursaExpres = new CursaExpres(
                origine, destinatie, distanta, durata, colete, sofer, data,
                garantie24h, taxaUrg, prior, oreGarantate
            );

            curseExpres.push_back(cursaExpres);
            cout << "\n Cursa Expres creata cu succes!" << endl;
            cursaExpres->afiseaza();
            break;
        }

        case 44: {
            if (clientiPremium.empty()) {
                cout << "\nNu exista clienti premium!" << endl;
            }
            else {
                cout << "\n TOTI CLIENTII PREMIUM " << endl;
                for (auto client : clientiPremium) {
                    client->afiseaza();
                }
                cout << "Total clienti premium: " << clientiPremium.size() << endl;
            }
            break;
        }

        case 45: {
            if (curseExpres.empty()) {
                cout << "\n Nu exista curse expres!" << endl;
            }
            else {
                cout << "\n TOATE CURSELE EXPRES " << endl;
                for (auto cursa : curseExpres) {
                    cursa->afiseaza();
                }
                cout << "Total curse expres: " << curseExpres.size() << endl;
            }
            break;
        }

        case 46: {
            cout << "  TEST UPCASTING - CLASA DE BAZA      " << endl;

            if (clientiPremium.empty() && curseExpres.empty()) {
                cout << "Nu exista obiecte derivate! Creaza clienti premium sau curse expres." << endl;
                break;
            }

            // UPCASTING pentru ClientiPremium
            if (!clientiPremium.empty()) {
                cout << " UPCASTING CLIENTI PREMIUM → CLIENT CORPORATIV \n" << endl;

                for (size_t i = 0; i < clientiPremium.size(); i++) {
                    cout << "\n Client Premium #" << (i + 1) << ":" << endl;

                    // UPCASTING: Pointer la clasa derivata → Pointer la clasa de baza
                    ClientCorporativ* clientBaza = clientiPremium[i];

                    proceseazaClient(clientBaza);

                    cout << "\n Obiectul ClientCorporativPremium a fost tratat ca ClientCorporativ!" << endl;
                }
            }

            // UPCASTING pentru CurseExpres
            if (!curseExpres.empty()) {
                cout << "\n UPCASTING CURSE EXPRES → CURSA INTERNATIONALA \n" << endl;

                for (size_t i = 0; i < curseExpres.size(); i++) {
                    cout << "\nCursa Expres #" << (i + 1) << ":" << endl;

                    // UPCASTING: Pointer la clasa derivata → Pointer la clasa de baza
                    CursaInternationala* cursaBaza = curseExpres[i];

                    proceseazaCursa(cursaBaza);

                    cout << "\n Obiectul CursaExpres a fost tratat ca CursaInternationala!" << endl;
                }
            }

            // UPCASTING cu vector mixt
            if (!clientiPremium.empty() || !clienti.empty()) {
                cout << "\n\n  UPCASTING VECTOR MIXT DE CLIENTI \n" << endl;

                // Cream un vector de pointeri la clasa de baza
                vector<ClientCorporativ*> vectorMixt;

                // Adaugam clienti normali (deja sunt clasa de baza)
                for (auto client : clienti) {
                    vectorMixt.push_back(client);
                }

                // Adaugam clienti premium (UPCASTING automat)
                for (auto clientPrem : clientiPremium) {
                    vectorMixt.push_back(clientPrem);  // UPCASTING!
                }

                if (!vectorMixt.empty()) {
                    ClientCorporativ** arrayClienti = new ClientCorporativ * [vectorMixt.size()];
                    for (size_t i = 0; i < vectorMixt.size(); i++) {
                        arrayClienti[i] = vectorMixt[i];
                    }

                    proceseazaVectorClienti(arrayClienti, vectorMixt.size());

                    delete[] arrayClienti;

                    cout << "\n  Vector mixt procesat cu succes!" << endl;
                    cout << "  - Clienti normali: " << clienti.size() << endl;
                    cout << "  - Clienti premium: " << clientiPremium.size() << endl;
                    cout << "  - Total procesati: " << vectorMixt.size() << endl;
                }
            }

            cout << " UPCASTING CU SUCCES!" << endl;
            break;
        }

        case 47: {
            cout << " TEST COMPLET FAZA 7 - MOSTENIRE + UPCASTING  " << endl;

            // 1. Creare obiecte derivate
            cout << "1. CREARE OBIECTE DERIVATE\n" << endl;

            ClientCorporativPremium* premiumTest1 = new ClientCorporativPremium(
                "MegaCorp Premium SRL", "Bucuresti, Sector 1", "Ana Popescu",
                150, "RO99887766", 5000.0, true,
                3, 0.15, "Andrei Ionescu", 1500
            );

            ClientCorporativPremium* premiumTest2 = new ClientCorporativPremium(
                "EliteTransport SRL", "Cluj-Napoca", "Maria Georgescu",
                200, "RO55443322", 7000.0, true,
                5, 0.25, "Cristian Popescu", 3000
            );

            CursaExpres* expresTest1 = new CursaExpres(
                "Romania", "Germania", 2200.0, 20.0, 60, "SOF-EXPRES-01", "20/12/2024",
                true, 300.0, "SUPER_EXPRESS", 12
            );

            CursaExpres* expresTest2 = new CursaExpres(
                "Romania", "Franta", 2800.0, 24.0, 80, "SOF-EXPRES-02", "21/12/2024",
                true, 250.0, "EXPRESS", 24
            );

            cout << "✓ Obiecte derivate create!\n" << endl;

            // 2. Afisare obiecte derivate
            cout << "2. AFISARE OBIECTE DERIVATE (metode suprascrise)\n" << endl;
            premiumTest1->afiseaza();
            expresTest1->afiseaza();

            // 3. Demonstrare UPCASTING
            cout << "3. DEMONSTRARE UPCASTING\n" << endl;

            cout << "--- ClientCorporativPremium → ClientCorporativ ---" << endl;
            ClientCorporativ* clientBaza1 = premiumTest1;  // UPCASTING
            ClientCorporativ* clientBaza2 = premiumTest2;  // UPCASTING

            proceseazaClient(clientBaza1);
            proceseazaClient(clientBaza2);

            cout << "\n CursaExpres → CursaInternationala" << endl;
            CursaInternationala* cursaBaza1 = expresTest1;  // UPCASTING
            CursaInternationala* cursaBaza2 = expresTest2;  // UPCASTING

            proceseazaCursa(cursaBaza1);
            proceseazaCursa(cursaBaza2);

            // 4. Vector polimorfic (upcasting in vector)
            cout << "\n4. VECTOR POLIMORFIC (UPCASTING)\n" << endl;

            ClientCorporativ* vectorClienti[4];
            vectorClienti[0] = new ClientCorporativ("Standard SRL", "Timisoara", "Contact1",
                50, "RO11111111", 1000.0, true);
            vectorClienti[1] = premiumTest1;  // UPCASTING
            vectorClienti[2] = new ClientCorporativ("Basic SRL", "Iasi", "Contact2",
                30, "RO22222222", 800.0, true);
            vectorClienti[3] = premiumTest2;  // UPCASTING

            proceseazaVectorClienti(vectorClienti, 4);

            // 5. Test metode specifice claselor derivate
            cout << "\n5. TEST METODE SPECIFICE CLASE DERIVATE\n" << endl;

            cout << " Upgrade nivel Premium" << endl;
            premiumTest1->upgradeNivel();
            cout << "Discount total dupa upgrade: "
                << (premiumTest1->calculeazaDiscountTotal() * 100) << "%" << endl;

            cout << "\n Upgrade prioritate Expres" << endl;
            expresTest1->upgradePrioritate();
            cout << "Cost total dupa upgrade: "
                << expresTest1->calculeazaCostTotalExpres() << " EUR" << endl;

            // 6. Rezumat
            cout << "\n6. REZUMAT FAZA 7" << endl;
            cout << "- ClientCorporativPremium moștenește ClientCorporativ" << endl;
            cout << "- CursaExpres moștenește CursaInternationala" << endl;
            cout << "- Constructori, destructori și operatori implementați" << endl;
            cout << "- Getteri și setteri pentru atribute noi" << endl;
            cout << "- Metode suprascrise (afiseaza)" << endl;
            cout << "- Metode specifice claselor derivate" << endl;
            cout << "- UPCASTING demonstrat cu succes!" << endl;
            cout << "- Obiecte derivate tratate ca obiecte din clasa de bază" << endl;

            // Cleanup partial
            delete vectorClienti[0];
            delete vectorClienti[2];
            delete premiumTest1;
            delete premiumTest2;
            delete expresTest1;
            delete expresTest2;

            cout << "TEST FAZA 7 FINALIZAT CU SUCCES!         " << endl;
            break;
        }

        case 48: {
            cout << "\n UPGRADE NIVEL / PRIORITATE " << endl;
            cout << "1. Upgrade nivel Client Premium" << endl;
            cout << "2. Upgrade prioritate Cursa Expres" << endl;
            cout << "Optiune: ";
            int subOpt;
            cin >> subOpt;
            cin.ignore();

            if (subOpt == 1) {
                if (clientiPremium.empty()) {
                    cout << "Nu exista clienti premium!" << endl;
                    break;
                }

                cout << "\nClienti Premium disponibili:" << endl;
                for (size_t i = 0; i < clientiPremium.size(); i++) {
                    cout << (i + 1) << ". " << clientiPremium[i]->getNumeCompanie()
                        << " - Nivel: " << clientiPremium[i]->getNivelPremium() << endl;
                }

                int idx;
                cout << "Selectati client: ";
                cin >> idx;
                cin.ignore();

                if (idx >= 1 && idx <= (int)clientiPremium.size()) {
                    clientiPremium[idx - 1]->upgradeNivel();
                    clientiPremium[idx - 1]->afiseaza();
                }

            }
            else if (subOpt == 2) {
                if (curseExpres.empty()) {
                    cout << "Nu exista curse expres!" << endl;
                    break;
                }

                cout << "\nCurse Expres disponibile:" << endl;
                for (size_t i = 0; i < curseExpres.size(); i++) {
                    cout << (i + 1) << ". " << curseExpres[i]->getCodCursa()
                        << " - Prioritate: " << curseExpres[i]->getPrioritate() << endl;
                }

                int idx;
                cout << "Selectati cursa: ";
                cin >> idx;
                cin.ignore();

                if (idx >= 1 && idx <= (int)curseExpres.size()) {
                    curseExpres[idx - 1]->upgradePrioritate();
                    curseExpres[idx - 1]->afiseaza();
                }
            }
            break;
        }
        case 0:
            cout << "\nIesire din program..." << endl;
            for (auto c : clienti) delete c;
            for (auto c : curse) delete c;
            for (auto f : facturi) delete f;
            clienti.clear();
            curse.clear();
            facturi.clear();

            for (auto cmd : comenzi) delete cmd;
            comenzi.clear();

            for (auto client : clientiPremium) delete client;
            for (auto cursa : curseExpres) delete cursa;
            clientiPremium.clear();
            curseExpres.clear();

            break;


        default:
            cout << "\nOptiune invalida!" << endl;
        }

    } while (optiune != 0);

    return 0;
}
