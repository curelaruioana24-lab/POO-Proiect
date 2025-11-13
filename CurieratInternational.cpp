#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4566)
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

//
// CLASA 1: ClientCorporativ - COMPLET CU CONSTRUCTORI
//
class ClientCorporativ {
public:
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

    // Constructor fără parametri
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

    // Constructor cu toți parametrii
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

    // Constructor de copiere
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

    // Destructor
    ~ClientCorporativ() {
        delete[] numeCompanie;
        delete[] adresaSediu;
        delete[] persoanaContact;
    }

    // Operator =
    ClientCorporativ& operator=(const ClientCorporativ& c) {
        if (this != &c) {
            delete[] numeCompanie;
            delete[] adresaSediu;
            delete[] persoanaContact;

            numeCompanie = new char[strlen(c.numeCompanie) + 1];
            strcpy(numeCompanie, c.numeCompanie);

            adresaSediu = new char[strlen(c.adresaSediu) + 1];
            strcpy(adresaSediu, c.adresaSediu);

            persoanaContact = new char[strlen(c.persoanaContact) + 1];
            strcpy(persoanaContact, c.persoanaContact);

            nrAngajati = c.nrAngajati;
            codFiscal = c.codFiscal;
            volumTransporturiLunar = c.volumTransporturiLunar;
            esteActiv = c.esteActiv;
            ID_CLIENT = c.ID_CLIENT;
        }
        return *this;
    }

    // Functie statica
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
        cin.getline(numeCompanie, 200);
        cout << "Adresa sediu: ";
        cin.getline(adresaSediu, 200);
        cout << "Persoana contact: ";
        cin.getline(persoanaContact, 200);
        cout << "Numar angajati: ";
        cin >> nrAngajati;
        cout << "Cod fiscal (ex: RO12345678): ";
        cin >> codFiscal;
        cout << "Volum transporturi lunar (tone): ";
        cin >> volumTransporturiLunar;
        cin.ignore();
    }

    void afiseaza() const {
        cout << "\n========================================" << endl;
        cout << "CLIENT CORPORATIV #" << ID_CLIENT << endl;
        cout << "========================================" << endl;
        cout << "Companie: " << numeCompanie << endl;
        cout << "Adresa: " << adresaSediu << endl;
        cout << "Contact: " << persoanaContact << endl;
        cout << "Angajati: " << nrAngajati << endl;
        cout << "Cod Fiscal: " << codFiscal << endl;
        cout << "Volum/Luna: " << volumTransporturiLunar << " tone" << endl;
        cout << "Status: " << (esteActiv ? "ACTIV" : "INACTIV") << endl;
        cout << "========================================" << endl;
    }
};

//
// CLASA 2: CursaInternationala - COMPLET CU CONSTRUCTORI
//
class CursaInternationala {
public:
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

    // Constructor fără parametri
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

    // Constructor cu toți parametrii
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

    // Constructor de copiere
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

    // Destructor
    ~CursaInternationala() {
        delete[] taraOrigine;
        delete[] soferId;
        delete[] dataPlecarii;
    }

    // Operator =
    CursaInternationala& operator=(const CursaInternationala& c) {
        if (this != &c) {
            delete[] taraOrigine;
            delete[] soferId;
            delete[] dataPlecarii;

            taraOrigine = new char[strlen(c.taraOrigine) + 1];
            strcpy(taraOrigine, c.taraOrigine);

            soferId = new char[strlen(c.soferId) + 1];
            strcpy(soferId, c.soferId);

            dataPlecarii = new char[strlen(c.dataPlecarii) + 1];
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
        cout << "Tara origine: ";
        cin.getline(taraOrigine, 200);
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
        cin.getline(soferId, 200);
        cout << "Data plecarii (DD/MM/YYYY): ";
        cin.getline(dataPlecarii, 200);
    }

    void afiseaza() const {
        cout << "\n========================================" << endl;
        cout << "CURSA INTERNATIONALA" << endl;
        cout << "========================================" << endl;
        cout << "Cod: " << COD_CURSA << endl;
        cout << "Ruta: " << taraOrigine << " -> " << taraDestinatie << endl;
        cout << "Distanta: " << distantaKm << " km" << endl;
        cout << "Durata: " << durataTimpOre << " ore" << endl;
        cout << "Colete: " << nrColete << endl;
        cout << "Sofer: " << soferId << endl;
        cout << "Data: " << dataPlecarii << endl;
        cout << "Status: " << (esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;
        cout << "========================================" << endl;
    }
};

//
// CLASA 3: Factura - COMPLETA
//
class Factura {
public:
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

    // Constructor fără parametri
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

    // Constructor cu toți parametrii
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
    }

    // Constructor de copiere
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
    }

    // Destructor
    ~Factura() {
        delete[] numarFactura;
        delete[] clientDenumire;
        delete[] moneda;
        delete[] preturiServicii;
    }

    // Operator =
    Factura& operator=(const Factura& f) {
        if (this != &f) {
            delete[] numarFactura;
            delete[] clientDenumire;
            delete[] moneda;
            delete[] preturiServicii;

            numarFactura = new char[strlen(f.numarFactura) + 1];
            strcpy(numarFactura, f.numarFactura);

            clientDenumire = new char[strlen(f.clientDenumire) + 1];
            strcpy(clientDenumire, f.clientDenumire);

            moneda = new char[strlen(f.moneda) + 1];
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
        cout << "Numar factura: ";
        cin.getline(numarFactura, 50);
        cout << "Data emitere (DD/MM/YYYY): ";
        getline(cin, dataEmitere);
        cout << "Denumire client: ";
        cin.getline(clientDenumire, 200);
        cout << "Moneda (RON/EUR/USD): ";
        cin.getline(moneda, 10);
        cout << "Numar servicii: ";
        cin >> nrServicii;

        if (nrServicii > 0) {
            preturiServicii = new double[nrServicii];
            for (int i = 0; i < nrServicii; i++) {
                cout << "Pret serviciu " << (i + 1) << ": ";
                cin >> preturiServicii[i];
            }
        }
        cin.ignore();
    }

    void afiseaza() const {
        cout << "\n========================================" << endl;
        cout << "FACTURA #" << ID_FACTURA << endl;
        cout << "========================================" << endl;
        cout << "Numar: " << numarFactura << endl;
        cout << "Data: " << dataEmitere << endl;
        cout << "Client: " << clientDenumire << endl;
        cout << "Nr. servicii: " << nrServicii << endl;
        double total = calculeazaTotal();
        cout << "Total fara TVA: " << total << " " << moneda << endl;
        cout << "TVA (" << (TVA * 100) << "%): " << (total * TVA) << " " << moneda << endl;
        cout << "Total cu TVA: " << (total * (1 + TVA)) << " " << moneda << endl;
        cout << "Status: " << (estePlatita ? "PLATITA" : "NEPLATITA") << endl;
        cout << "========================================" << endl;
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
// FUNCTIA MAIN
//
int main() {
    cout << "========================================" << endl;
    cout << "  SISTEM MANAGEMENT TRANSPORT" << endl;
    cout << "  VERSIUNEA COMPLETA - FAZA 1" << endl;
    cout << "========================================\n" << endl;

    int optiune;
    vector<ClientCorporativ*> clienti;
    vector<CursaInternationala*> curse;
    vector<Factura*> facturi;

    do {
        cout << "\n========== MENIU PRINCIPAL ===========" << endl;
        cout << "--- CLIENTI CORPORATIVI ---" << endl;
        cout << "1. Creare client nou (citire)" << endl;
        cout << "2. Afisare toti clientii" << endl;
        cout << "3. Test constructori Client" << endl;
        cout << "4. Calcul pret cu discount (functie statica)" << endl;
        cout << "5. Modificare discount corporativ" << endl;
        cout << "6. Afisare statistici clienti" << endl;
        cout << "\n--- CURSE INTERNATIONALE ---" << endl;
        cout << "7. Creare cursa noua (citire)" << endl;
        cout << "8. Afisare toate cursele" << endl;
        cout << "9. Test constructori Cursa" << endl;
        cout << "10. Calcul cost total cursa (functie statica)" << endl;
        cout << "11. Modificare taxa vamala" << endl;
        cout << "12. Finalizare cursa" << endl;
        cout << "13. Afisare statistici curse" << endl;
        cout << "\n--- FACTURI ---" << endl;
        cout << "14. Creare factura noua (citire)" << endl;
        cout << "15. Afisare toate facturile" << endl;
        cout << "16. Marcare factura ca platita" << endl;
        cout << "17. Test constructori Factura" << endl;
        cout << "18. Modificare cota TVA" << endl;
        cout << "19. Afisare statistici facturi" << endl;
        cout << "\n0. Iesire" << endl;
        cout << "=======================================" << endl;
        cout << "Optiune: ";
        cin >> optiune;
        cin.ignore();

        switch (optiune) {
            // ========== CLIENTI ==========
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
            cout << "\n=== TEST CONSTRUCTORI CLIENT ===" << endl;
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
            }
            cout << "\n✓ Toti constructorii functioneaza!" << endl;
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
            cout << "\n=== STATISTICI CLIENTI ===" << endl;
            cout << "Total clienti: " << ClientCorporativ::getNumarTotalClienti() << endl;
            cout << "Clienti activi: " << ClientCorporativ::getClientiActivi() << endl;
            cout << "Discount: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            break;

            // ========== CURSE ==========
        case 7: {
            CursaInternationala* c = new CursaInternationala();
            c->citeste();
            curse.push_back(c);
            cout << "\n✓ Cursa creata cu succes!" << endl;
            break;
        }

        case 8:
            if (curse.empty()) {
                cout << "\nNu exista curse!" << endl;
            }
            else {
                for (auto c : curse) c->afiseaza();
            }
            break;

        case 9:
            cout << "\n=== TEST CONSTRUCTORI CURSA ===" << endl;
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
            }
            cout << "\n✓ Toti constructorii functioneaza!" << endl;
            break;

        case 10: {
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

        case 11: {
            double taxa;
            cout << "\nTaxa vamala curenta: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            cout << "Noua taxa: ";
            cin >> taxa;
            CursaInternationala::setTaxaVamala(taxa);
            cout << "✓ Taxa actualizata!" << endl;
            break;
        }

        case 12: {
            if (curse.empty()) {
                cout << "\nNu exista curse!" << endl;
            }
            else {
                cout << "\n=== CURSE DISPONIBILE ===" << endl;
                for (size_t i = 0; i < curse.size(); i++) {
                    cout << (i + 1) << ". " << curse[i]->COD_CURSA
                        << " - Status: " << (curse[i]->esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;
                }
                int idx;
                cout << "Selectati cursa: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)curse.size()) {
                    if (!curse[idx - 1]->esteFinalizata) {
                        curse[idx - 1]->esteFinalizata = true;
                        CursaInternationala::curseFinalizate++;
                        cout << "✓ Cursa finalizata!" << endl;
                    }
                    else {
                        cout << "Cursa este deja finalizata!" << endl;
                    }
                }
                else {
                    cout << "Numar invalid!" << endl;
                }
            }
            break;
        }

        case 13:
            cout << "\n=== STATISTICI CURSE ===" << endl;
            cout << "Total curse: " << CursaInternationala::getNumarTotalCurse() << endl;
            cout << "Curse finalizate: " << CursaInternationala::getCurseFinalizate() << endl;
            cout << "Curse in curs: " << (CursaInternationala::getNumarTotalCurse() - CursaInternationala::getCurseFinalizate()) << endl;
            cout << "Taxa vamala: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            break;

            // ========== FACTURI ==========
        case 14: {
            Factura* f = new Factura();
            f->citeste();
            facturi.push_back(f);
            cout << "\n✓ Factura creata cu succes!" << endl;
            break;
        }

        case 15:
            if (facturi.empty()) {
                cout << "\nNu exista facturi!" << endl;
            }
            else {
                for (auto f : facturi) f->afiseaza();
            }
            break;

        case 16: {
            if (facturi.empty()) {
                cout << "\nNu exista facturi!" << endl;
            }
            else {
                cout << "\n=== FACTURI DISPONIBILE ===" << endl;
                for (size_t i = 0; i < facturi.size(); i++) {
                    cout << (i + 1) << ". " << facturi[i]->numarFactura
                        << " - " << facturi[i]->clientDenumire
                        << " - Status: " << (facturi[i]->estePlatita ? "PLATITA" : "NEPLATITA") << endl;
                }
                int idx;
                cout << "Selectati factura: ";
                cin >> idx;
                if (idx >= 1 && idx <= (int)facturi.size()) {
                    facturi[idx - 1]->marcheazaPlatita();
                }
                else {
                    cout << "Numar invalid!" << endl;
                }
            }
            break;
        }

        case 17:
            cout << "\n=== TEST CONSTRUCTORI FACTURA ===" << endl;
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
            }
            cout << "\n✓ Toti constructorii functioneaza!" << endl;
            break;

        case 18: {
            double tva;
            cout << "\nCota TVA curenta: " << (Factura::getCotaTVA() * 100) << "%" << endl;
            cout << "Noua cota (0-1, ex: 0.19): ";
            cin >> tva;
            Factura::setCotaTVA(tva);
            cout << "✓ Cota TVA actualizata!" << endl;
            break;
        }

        case 19:
            cout << "\n=== STATISTICI FACTURI ===" << endl;
            cout << "Total facturi: " << Factura::getNumarTotalFacturi() << endl;
            cout << "Incasari totale: " << Factura::getIncasariTotale() << " RON" << endl;
            cout << "Cota TVA: " << (Factura::getCotaTVA() * 100) << "%" << endl;
            {
                int platite = 0, neplatite = 0;
                for (auto f : facturi) {
                    if (f->estePlatita) platite++;
                    else neplatite++;
                }
                cout << "Facturi platite: " << platite << endl;
                cout << "Facturi neplatite: " << neplatite << endl;
            }
            break;

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