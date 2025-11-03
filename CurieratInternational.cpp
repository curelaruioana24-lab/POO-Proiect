#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

//
// CLASA 1: ClientCorporativ - FAZA 1 (fara constructori)
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

    // Functie statica: calculeaza pret final cu discount
    static double calculeazaPretFinal(double pretInitial, double volumLunar) {
        double discountTotal = discountCorporativ;
        if (volumLunar > 1000) discountTotal += 0.05;
        if (volumLunar > 5000) discountTotal += 0.10;
        return pretInitial * (1 - discountTotal);
    }

    // Setteri si getteri pentru membri statici
    static void setDiscount(double discount) {
        if (discount >= 0 && discount <= 1) discountCorporativ = discount;
    }

    static double getDiscount() { return discountCorporativ; }
    static int getNumarTotalClienti() { return numarTotalClienti; }
    static int getClientiActivi() { return clientiActivi; }

    // Metoda de initializare
    void initializeaza() {
        numeCompanie = new char[200];
        adresaSediu = new char[200];
        persoanaContact = new char[200];
        ID_CLIENT = ++numarTotalClienti;
        esteActiv = true;
        clientiActivi++;
    }

    // Metoda de citire de la tastatura
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

    // Metoda de afisare
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

    // Destructor pentru eliberare memorie
    void elibereaza() {
        delete[] numeCompanie;
        delete[] adresaSediu;
        delete[] persoanaContact;
    }
};

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

    // Functie statica: calculeaza cost total cursa
    static double calculeazaCostTotalCursa(double distanta, int nrColete, bool urgenta = false) {
        double costPerKm = (distanta > 2000) ? 0.45 : 0.50;
        double costTransport = distanta * costPerKm;
        double costColete = nrColete * 12.0;
        double taxaUrgenta = urgenta ? 150.0 : 0.0;
        return costTransport + costColete + taxaVamalaFixa + taxaUrgenta;
    }

    // Setteri si getteri pentru membri statici
    static void setTaxaVamala(double taxa) {
        if (taxa >= 0) taxaVamalaFixa = taxa;
    }

    static double getTaxaVamala() { return taxaVamalaFixa; }
    static int getNumarTotalCurse() { return numarTotalCurse; }
    static int getCurseFinalizate() { return curseFinalizate; }

    // Metoda de initializare
    void initializeaza() {
        taraOrigine = new char[200];
        soferId = new char[200];
        dataPlecarii = new char[200];
        numarTotalCurse++;
        COD_CURSA = "CURS-" + to_string(numarTotalCurse);
        esteFinalizata = false;
    }

    // Metoda de citire de la tastatura
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

    // Metoda de afisare
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

    // Metoda pentru eliberare memorie
    void elibereaza() {
        delete[] taraOrigine;
        delete[] soferId;
        delete[] dataPlecarii;
    }
};

// Initializare membri statici
double ClientCorporativ::discountCorporativ = 0.15;
int ClientCorporativ::numarTotalClienti = 0;
int ClientCorporativ::clientiActivi = 0;
double CursaInternationala::taxaVamalaFixa = 75.0;
int CursaInternationala::numarTotalCurse = 0;
int CursaInternationala::curseFinalizate = 0;

//
// FUNCTIA MAIN - TESTARE MANUALA
//
int main() {
    cout << "========================================" << endl;
    cout << "  SISTEM MANAGEMENT TRANSPORT" << endl;
    cout << "  TESTARE CLIENTI SI CURSE" << endl;
    cout << "========================================\n" << endl;

    int optiune;
    vector<ClientCorporativ*> clienti;
    vector<CursaInternationala*> curse;

    do {
        cout << "\n========== MENIU PRINCIPAL ===========" << endl;
        cout << "--- CLIENTI CORPORATIVI ---" << endl;
        cout << "1. Creare client nou" << endl;
        cout << "2. Afisare toti clientii" << endl;
        cout << "3. Calcul pret cu discount (functie statica)" << endl;
        cout << "4. Modificare discount corporativ" << endl;
        cout << "5. Afisare statistici clienti" << endl;
        cout << "\n--- CURSE INTERNATIONALE ---" << endl;
        cout << "6. Creare cursa noua" << endl;
        cout << "7. Afisare toate cursele" << endl;
        cout << "8. Calcul cost total cursa (functie statica)" << endl;
        cout << "9. Modificare taxa vamala" << endl;
        cout << "10. Finalizare cursa" << endl;
        cout << "11. Afisare statistici curse" << endl;
        cout << "\n0. Iesire" << endl;
        cout << "Optiune: ";
        cin >> optiune;
        cin.ignore();

        switch (optiune) {
            // ========== CLIENTI CORPORATIVI ==========
        case 1: {
            cout << "\n=== CREARE CLIENT NOU ===" << endl;
            ClientCorporativ* clientNou = new ClientCorporativ();
            clientNou->initializeaza();
            clientNou->citeste();
            clienti.push_back(clientNou);
            cout << "\nClient creat cu succes! (ID: " << clientNou->ID_CLIENT << ")" << endl;
            break;
        }

        case 2:
            cout << "\n=== AFISARE TOTI CLIENTII ===" << endl;
            if (clienti.empty()) {
                cout << "Nu exista clienti creati!" << endl;
            }
            else {
                cout << "Total clienti: " << clienti.size() << endl;
                for (size_t i = 0; i < clienti.size(); i++) {
                    cout << "\n--- CLIENT " << (i + 1) << " ---";
                    clienti[i]->afiseaza();
                }
            }
            break;

        case 3: {
            cout << "\n=== CALCUL PRET CU DISCOUNT ===" << endl;
            double pret, volum;
            cout << "Introduceti pretul initial (EUR): ";
            cin >> pret;
            cout << "Introduceti volumul lunar (tone): ";
            cin >> volum;

            double pretFinal = ClientCorporativ::calculeazaPretFinal(pret, volum);
            cout << "\nPret initial: " << pret << " EUR" << endl;
            cout << "Volum lunar: " << volum << " tone" << endl;
            cout << "Discount aplicat: " << (ClientCorporativ::getDiscount() * 100);
            if (volum > 1000) cout << " + 5%";
            if (volum > 5000) cout << " + 10%";
            cout << endl;
            cout << "Pret final: " << pretFinal << " EUR" << endl;
            cout << "Economie: " << (pret - pretFinal) << " EUR" << endl;
            break;
        }

        case 4: {
            cout << "\n=== MODIFICARE DISCOUNT ===" << endl;
            cout << "Discount curent: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            double discountNou;
            cout << "Introduceti noul discount (0-1, ex: 0.20 pentru 20%): ";
            cin >> discountNou;
            ClientCorporativ::setDiscount(discountNou);
            cout << "Discount actualizat: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            break;
        }

        case 5:
            cout << "\n=== STATISTICI CLIENTI ===" << endl;
            cout << "========================================" << endl;
            cout << "Total clienti creati: " << ClientCorporativ::getNumarTotalClienti() << endl;
            cout << "Clienti activi: " << ClientCorporativ::getClientiActivi() << endl;
            cout << "Discount corporativ: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            cout << "========================================" << endl;
            break;

            // ========== CURSE INTERNATIONALE ==========
        case 6: {
            cout << "\n=== CREARE CURSA NOUA ===" << endl;
            CursaInternationala* cursaNoua = new CursaInternationala();
            cursaNoua->initializeaza();
            cursaNoua->citeste();
            curse.push_back(cursaNoua);
            cout << "\nCursa creata cu succes! (Cod: " << cursaNoua->COD_CURSA << ")" << endl;
            break;
        }

        case 7:
            cout << "\n=== AFISARE TOATE CURSELE ===" << endl;
            if (curse.empty()) {
                cout << "Nu exista curse create!" << endl;
            }
            else {
                cout << "Total curse: " << curse.size() << endl;
                for (size_t i = 0; i < curse.size(); i++) {
                    cout << "\n--- CURSA " << (i + 1) << " ---";
                    curse[i]->afiseaza();
                }
            }
            break;

        case 8: {
            cout << "\n=== CALCUL COST TOTAL CURSA ===" << endl;
            double distanta;
            int nrColete;
            char urgenta;

            cout << "Introduceti distanta (km): ";
            cin >> distanta;
            cout << "Introduceti numarul de colete: ";
            cin >> nrColete;
            cout << "Este urgenta? (d/n): ";
            cin >> urgenta;

            bool esteUrgenta = (urgenta == 'd' || urgenta == 'D');
            double costTotal = CursaInternationala::calculeazaCostTotalCursa(distanta, nrColete, esteUrgenta);

            cout << "\n--- DETALII COST ---" << endl;
            cout << "Distanta: " << distanta << " km" << endl;
            cout << "Colete: " << nrColete << endl;
            cout << "Taxa vamala: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            cout << "Urgenta: " << (esteUrgenta ? "DA (+150 EUR)" : "NU") << endl;
            cout << "COST TOTAL: " << costTotal << " EUR" << endl;
            break;
        }

        case 9: {
            cout << "\n=== MODIFICARE TAXA VAMALA ===" << endl;
            cout << "Taxa vamala curenta: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            double taxaNoua;
            cout << "Introduceti noua taxa vamala (EUR): ";
            cin >> taxaNoua;
            CursaInternationala::setTaxaVamala(taxaNoua);
            cout << "Taxa vamala actualizata: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            break;
        }

        case 10: {
            cout << "\n=== FINALIZARE CURSA ===" << endl;
            if (curse.empty()) {
                cout << "Nu exista curse create!" << endl;
            }
            else {
                cout << "Curse disponibile:" << endl;
                for (size_t i = 0; i < curse.size(); i++) {
                    cout << (i + 1) << ". " << curse[i]->COD_CURSA
                        << " (" << curse[i]->taraOrigine << " -> " << curse[i]->taraDestinatie << ")"
                        << " - Status: " << (curse[i]->esteFinalizata ? "FINALIZATA" : "IN CURS") << endl;
                }

                int indexCursa;
                cout << "Selectati numarul cursei de finalizat: ";
                cin >> indexCursa;

                if (indexCursa >= 1 && indexCursa <= (int)curse.size()) {
                    if (curse[indexCursa - 1]->esteFinalizata) {
                        cout << "Cursa este deja finalizata!" << endl;
                    }
                    else {
                        curse[indexCursa - 1]->esteFinalizata = true;
                        CursaInternationala::curseFinalizate++;
                        cout << "Cursa " << curse[indexCursa - 1]->COD_CURSA << " a fost finalizata!" << endl;
                    }
                }
                else {
                    cout << "Numar invalid!" << endl;
                }
            }
            break;
        }

        case 11:
            cout << "\n=== STATISTICI CURSE ===" << endl;
            cout << "========================================" << endl;
            cout << "Total curse create: " << CursaInternationala::getNumarTotalCurse() << endl;
            cout << "Curse finalizate: " << CursaInternationala::getCurseFinalizate() << endl;
            cout << "Curse in curs: " << (CursaInternationala::getNumarTotalCurse() - CursaInternationala::getCurseFinalizate()) << endl;
            cout << "Taxa vamala: " << CursaInternationala::getTaxaVamala() << " EUR" << endl;
            cout << "========================================" << endl;
            break;

        case 0:
            cout << "\nIesire din program..." << endl;
            // Eliberare memorie clienti
            for (size_t i = 0; i < clienti.size(); i++) {
                clienti[i]->elibereaza();
                delete clienti[i];
            }
            clienti.clear();

            // Eliberare memorie curse
            for (size_t i = 0; i < curse.size(); i++) {
                curse[i]->elibereaza();
                delete curse[i];
            }
            curse.clear();
            break;

        default:
            cout << "\nOptiune invalida! Incercati din nou." << endl;
        }

    } while (optiune != 0);

    return 0;
}