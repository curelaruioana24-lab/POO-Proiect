#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4566)
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
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
// FUNCTIA MAIN - CU TESTE PENTRU FAZA 3 (plecand de la FAZA 2)
//
int main() {
    cout << "" << endl;
    cout << "  SISTEM MANAGEMENT TRANSPORT" << endl;
    cout << "  VERSIUNEA COMPLETA - FAZA 3" << endl;
    cout << "\n" << endl;

    int optiune;
    vector<ClientCorporativ*> clienti;
    vector<CursaInternationala*> curse;
    vector<Factura*> facturi;

    do {
        cout << "\n MENIU PRINCIPAL " << endl;
        cout << "--- CLIENTI CORPORATIVI ---" << endl;
        cout << "1. Creare client nou (citire)" << endl;
        cout << "2. Afisare toti clientii" << endl;
        cout << "3. Test constructori Client (si operatori)" << endl;
        cout << "4. Calcul pret cu discount (functie statica)" << endl;
        cout << "5. Modificare discount corporativ" << endl;
        cout << "6. Afisare statistici clienti" << endl;
        cout << "7. Test getteri/setteri Client" << endl;
        cout << "8. Aplicare discount special (functie friend)" << endl;
        cout << "9. Raport detaliat client (functie friend)" << endl;

        cout << "\n--- CURSE INTERNATIONALE ---" << endl;
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

        cout << "\n--- FACTURI ---" << endl;
        cout << "20. Creare factura noua (citire)" << endl;
        cout << "21. Afisare toate facturile" << endl;
        cout << "22. Marcare factura ca platita" << endl;
        cout << "23. Test constructori Factura (si operatori)" << endl;
        cout << "24. Modificare cota TVA" << endl;
        cout << "25. Afisare statistici facturi" << endl;
        cout << "26. Test getteri/setteri Factura" << endl;
        cout << "27. Aplicare reducere (functie friend)" << endl;
        cout << "28. Raport detaliat factura (functie friend)" << endl;

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

        case 0:
            cout << "\nIesire din program..." << endl;
            for (auto c : clienti) delete c;
            for (auto c : curse) delete c;
            for (auto f : facturi) delete f;
            clienti.clear();
            curse.clear();
            facturi.clear();
            break;

        default:
            cout << "\nOptiune invalida!" << endl;
        }

    } while (optiune != 0);

    return 0;
}
