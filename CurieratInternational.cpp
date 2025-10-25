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

// Initializare membri statici
double ClientCorporativ::discountCorporativ = 0.15;
int ClientCorporativ::numarTotalClienti = 0;
int ClientCorporativ::clientiActivi = 0;

//
// FUNCTIA MAIN - TESTARE MANUALA
//
int main() {
    cout << "========================================" << endl;
    cout << "  TEST CLASA ClientCorporativ - FAZA 1" << endl;
    cout << "  TESTARE MANUALA DE LA TASTATURA" << endl;
    cout << "========================================\n" << endl;

    int optiune;
    vector<ClientCorporativ*> clienti;

    do {
        cout << "\n========== MENIU ===========" << endl;
        cout << "1. Creare client nou" << endl;
        cout << "2. Afisare toti clientii" << endl;
        cout << "3. Calcul pret cu discount (functie statica)" << endl;
        cout << "4. Modificare discount corporativ" << endl;
        cout << "5. Afisare statistici (membri statici)" << endl;
        cout << "0. Iesire" << endl;
        cout << "Optiune: ";
        cin >> optiune;
        cin.ignore();

        switch (optiune) {
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
            cout << "\n=== STATISTICI GLOBALE ===" << endl;
            cout << "========================================" << endl;
            cout << "Total clienti creati: " << ClientCorporativ::getNumarTotalClienti() << endl;
            cout << "Clienti activi: " << ClientCorporativ::getClientiActivi() << endl;
            cout << "Discount corporativ: " << (ClientCorporativ::getDiscount() * 100) << "%" << endl;
            cout << "========================================" << endl;
            break;

        case 0:
            cout << "\nIesire din program..." << endl;
            // Eliberare memorie
            for (size_t i = 0; i < clienti.size(); i++) {
                clienti[i]->elibereaza();
                delete clienti[i];
            }
            clienti.clear();
            break;

        default:
            cout << "\nOptiune invalida! Incercati din nou." << endl;
        }

    } while (optiune != 0);

    return 0;
}