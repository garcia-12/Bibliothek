#include "bibliothek.h"
#include "buch.h"
#include "cds.h"


#include <iostream>
#include <string>
#include <algorithm> // für  std::find
#include <iomanip>  // für std::setw et std::left
#include <fstream>
#include <cstdlib>
#include <sstream> //für String in datei


using namespace std;

Bibliothek::Bibliothek() {}

Bibliothek::~Bibliothek()
{
    for (unsigned int i = 0; i < medien.size(); i++){
        delete medien[i];
    }
    medien.clear();
    cout << "Alle Medien wurden geloescht!"<<endl;
}



Medien *Bibliothek::MediaFinden(const int &nummer, const string &Name_borrower)
{
    if (nummer != 0){
        for(auto& buch: medien){
            if(buch->getID() == nummer)
                return buch;
        }
    }

    if(Name_borrower.size() != 0){
        for(auto& buch: medien){
            if(buch->getName_borrower() == Name_borrower)
                return buch;
        }
    }

    return nullptr;
}

void Bibliothek::BibliothekLaden(vector <Medien*>& medien, const string& myLibrary)
{
    ifstream file(myLibrary);
    if(!file){
        cout << "Fehler beim Laden"<<endl;
        return;
    }

    string line;
    int checkValueID = 1;
    bool isCDs = false;
    while(getline(file, line)){

        if(line.empty()){
            continue;
        }

        if(line[0] == 'C'){
            isCDs = true;
            continue;
        }


        istringstream stream(line);
        string autor, titel, time_str, page_str;
        string id_str;
        int id, time, pagenr;
        if(!isCDs){

            if(getline(stream, id_str, ';' ) and getline(stream, autor, ';') and getline(stream, titel, ';') and getline(stream, page_str, ';')){

                // stream >> BuchID;
                id_str = id_str.substr(0, id_str.find_last_not_of(" \t")+ 1);
                id = stoi(id_str);

                page_str = page_str.substr(0, page_str.find_last_not_of(" \t")+ 1);
                // pagenr = stoi(page_str);


                //um zusätzliche/mögliche Leerzeichen oder Tabulatoren am Ende von Zeichenketten zu entfernen
                autor = autor.substr(0, autor.find_last_not_of(" \t") + 1);
                titel = titel.substr(0, titel.find_last_not_of(" \t")+ 1);


                //Delet space between
                if(!titel.empty() and titel[0] == ' '){
                    titel.erase(0, 1);
                }

                Buch* newBuch = new Buch(id, autor, titel, page_str);

                medien.push_back(newBuch);

                if(checkValueID < id)
                    checkValueID = id;

            }
        }
        else {
            if(getline(stream, id_str, ';' ) and getline(stream, autor, ';') and getline(stream, titel, ';') and getline(stream, time_str, ';')){

                // stream >> BuchID;
                id_str = id_str.substr(0, id_str.find_last_not_of(" \t")+ 1);
                id = stoi(id_str);

                time_str = time_str.substr(0, time_str.find_last_not_of(" \t")+ 1);
                // time = stoi(time_str);


                //um zusätzliche/mögliche Leerzeichen oder Tabulatoren am Ende von Zeichenketten zu entfernen
                autor = autor.substr(0, autor.find_last_not_of(" \t") + 1);
                titel = titel.substr(0, titel.find_last_not_of(" \t")+ 1);


                //Delet space between
                if(!titel.empty() and titel[0] == ' '){
                    titel.erase(0, 1);
                }

                CDs* newCds = new CDs(id, autor, titel, time_str);

                medien.push_back(newCds);

                if(checkValueID < id)
                    checkValueID = id;

            }
        }


    }

    cout << "Bibliothek erfolgreich geladen" <<endl;
    Medien::setNextId(checkValueID + 1);
    file.close();
}

void Bibliothek::BibliothekSpeichern(const vector<Medien *> &buecher, const string &myLibrary)
{

    ofstream file(myLibrary);
    if(!file){
        cout << "Fehler beim Schreiben"<<endl;
        return;
    }

    file << "Bücher"<<endl;
    for(const auto& buch: medien){
        if (!buch->getIsCD()) {
            //save
            file << buch->getID() << "; "<<buch->getAutor()<< "; "<<buch->getTitle()<<"; "<<buch->getSeitenanzahlDauer() <<endl;
        }
    }
    file << "CDs"<<endl;
    for(const auto& buch: medien){
        if (buch->getIsCD()) {
            //save
            file << buch->getID() << "; "<<buch->getAutor()<< "; "<<buch->getTitle()<<"; "<<buch->getSeitenanzahlDauer() <<endl;
        }
    }

    cout << "Bibliothek erfolgreich gesichert!" <<endl;
    file.close();
}

void Bibliothek::bubbleSort(vector<Medien*> &b)
{
    int n = b.size();
    bool swapped;

    for (int i = 0; i < n -1 ; i++){
        swapped = false;

        for(int j = 0; j < n -1; j++){
            if(b[j]->getAutor() > b[j + 1]->getAutor()){
                swap(b[j], b[j+1]);
                swapped = true;
            }
        }

        if (!swapped){
            break;
        }
    }

}

void Bibliothek::displayMedien(vector<Medien *> &b) const
{

    cout << setw(8)<< "Id"
         <<" | " << setw(30)<< "Autor"
         <<" | " << setw(50) << "Titel"
         <<" | " << setw(10)<< "Dauer/Seiteanzahl"
         <<endl;

    cout << setfill('-') << setw(120) << "-" <<endl;
    cout << setfill(' ');

    for (const auto& buch: b){
        buch->anzeigen();
    }


}


void Bibliothek::dialog()
{
    while (true) {
        char eingabe;

        string titel, autor, spieldauer, seiteanhzal;
        int nummer;

        cout << "\nBibliotheksverwaltung\n"<<endl;
        cout << "(1) Buch anlegen"<<endl;
        cout << "(2) Buch loeschen"<<endl;
        cout << "(3) Bestand anzeigen"<<endl;
        cout << "(4) Buecher nach Autor"<<endl;
        cout << "(5) Buch empfehlen" <<endl;
        cout << "(6) Bibliothek speichern"<<endl;
        cout << "(7) Bibliothek laden"<<endl;
        cout << "(8) Buch ausleihen"<<endl;
        cout << "(9) Buch zurueckgeben"<<endl;
        cout << "(0) Programm verlassen"<<endl;
        cin >> eingabe;

        switch (eingabe) {
            //Anlegen
        case '1':{

            char unter_eingabe;
            cout << "\n     (a) Buch "
                    "\n     (b) Cds ";

            cin>>unter_eingabe;
            switch (unter_eingabe) {
            case 'a':{
                cout << "       Name des Autors: ";
                cin.ignore(10, '\n');
                getline(cin, autor);

                cout << "       Name des Buches: ";
                // cin.ignore(10, '\n');
                getline(cin, titel);


                cout << "       Seiteanzahl: "; cin >> seiteanhzal;

                Buch* newBuch = new Buch(autor, titel, seiteanhzal);
                medien.push_back(newBuch);
            }
                break;

            case 'b':{
                cout << "       Name des Buches: ";
                cin.ignore(10, '\n');
                getline(cin, titel);

                cout << "       Name des Autors: "<<endl;
                // cin.ignore(10, '\n');
                getline(cin, autor);




                cout << "       Spieldauer: "; cin >> spieldauer;

                CDs* newCDs = new CDs(autor, titel, spieldauer);
                medien.push_back(newCDs);
            }
            break;
            default:
                break;
            }

        }

            break;
            //Loeschen
        case '2':{            

            cout << "   Eindeutige Nummer des Mediens: ";
            cin >> nummer;

            Medien* m = MediaFinden(nummer);

            if(m == nullptr){
                cout << "   Dieses Medium existiert nicht!"<<endl;
                break;
            }

            if(!m->getIsLoan()){
                auto it = std::find(medien.begin(), medien.end(), m);
                medien.erase(it);
                cout << "   Das Medium wurde erfolgreich geloescht"<<endl;
            }
            else{
                cout << "   Das Medium kann nicht geloescht werden, weil dieses ausgeliehen wurde"<<endl;
            }
        }
            break;

        case '3':{
            displayMedien(medien);

        }
            break;

        case '4':{
            vector <Medien*> triMedien;
            triMedien = medien;
            bubbleSort(triMedien);
            displayMedien(triMedien);
        }

            break;


        case '5':{

            cout <<"        Was fuer ein Medium moechten Sie lesen/hoeren? ";
            char unter_eingabe;
            cout << "       \n     (a) Buch "
                    "       \n     (b) Cds ";
            cin>>unter_eingabe;
            cout << "           Name des Autors:  "
                    "\n             Wenn Sie kein favorisierter autor auswaehlen wollen <<0>> eingeben"<<endl;
            cin.ignore(10, '\n');
            getline(cin, autor);
            int randonNummer;
            srand(time(0));
            switch (unter_eingabe) {
            case 'a':{
                if(autor == "0"){
                    randonNummer = rand()%(medien.size());
                    while(medien[randonNummer]->getIsCD()){
                        randonNummer = rand()%(medien.size());
                    }
                    cout<<"         Sie koenen das Buch " << medien[randonNummer]->getAutor() << "; " << medien[randonNummer]->getTitle() << "; " << medien[randonNummer]->getID()<< " lesen" << endl;
                    break;
                }
                vector <Medien*> buchempfehlung;
                for (const auto b: medien){
                    if(b->getAutor() == autor and !b->getIsLoan() and !b->getIsCD()){
                        buchempfehlung.push_back(b);
                    }
                }
                if(buchempfehlung.size() == 0)
                    cout << "           Buch nicht gefunden oder wurde ausgeliehen"<<endl;
                else{
                    //DebugAusgabe
                    // displayBuecher(buchempfehlung);
                    randonNummer = rand()%(buchempfehlung.size());
                    cout<<"         Sie koenen das Buch " << buchempfehlung[randonNummer]->getAutor() << "; " << buchempfehlung[randonNummer]->getTitle() << "; " << buchempfehlung[randonNummer]->getID()<<" lesen" << endl;

                }
            }
            break;

            case 'b':{
                if(autor == "0"){
                    while(!medien[randonNummer]->getIsCD()){
                        randonNummer = rand()%(medien.size());
                    }
                    cout<<"     Sie koenen das CDs " << medien[randonNummer]->getAutor() << "; " << medien[randonNummer]->getTitle() << "; " << medien[randonNummer]->getID()<< " hoeren!" << endl;
                    break;
                }
                vector <Medien*> buchempfehlung;
                for (const auto b: medien){
                    if(b->getAutor() == autor and !b->getIsLoan() and b->getIsCD()){
                        buchempfehlung.push_back(b);
                    }
                }
                if(buchempfehlung.size() == 0)
                    cout << "       Media nicht gefunden oder wurde ausgeliehen"<<endl;
                else{
                    //DebugAusgabe
                    // displayBuecher(buchempfehlung);
                    randonNummer = rand()%(buchempfehlung.size());
                    cout<<"     Sie koenen das CDs " << buchempfehlung[randonNummer]->getAutor() << "; " << buchempfehlung[randonNummer]->getTitle() << "; " << buchempfehlung[randonNummer]->getID()<<" hoeren" << endl;

                }
            }
            break;
            default:
                break;
            }


        }
        break;

        case '6':{

            BibliothekSpeichern(medien, "datei.txt");
        }
            break;

        case '7':{
            //Loeschung von Inhaalt von Buecher:
            for (unsigned int i = 0; i < medien.size(); i++){
                delete medien[i];
            }

            medien.clear();

            BibliothekLaden(medien, "datei.txt");
        }
            break;
            //Buch ausleihen
        case '8':{
            // char unter_eingabe;
            // cout << "\n     (a) Buch "
            //         "\n     (b) Cds ";

            // cin>>unter_eingabe;
            // switch (unter_eingabe) {
            // case 'a':{

            // }
            // break;

            // case 'b':{

            // }
            // break;
            // default:
            //     break;
            // }
            string name;
            cout << "       Ihr nachname bitte : "; cin >> name;

            cout << "       Eindeutige Nummer des Buches: "; cin >> nummer;

            Medien* medium = MediaFinden(nummer);
            if(medium == nullptr){
                cout << "       Das Buch existiert nicht"<<endl;
            }

            if( !medium->getIsLoan()){
                medium->setLoan(true);
                medium->setName_borrower(name);
                cout << "       Das Buch wurde erfolgreich ausgeliehen "<<endl;
            }
            else
                cout << "       Das Buch wurde schon ausgeliehen" <<endl;

            // char unter_eingabe;
            // cout << "\n     (a) Buch "
            //         "\n     (b) Cds ";

            // cin>>unter_eingabe;
            // switch (unter_eingabe) {
            // case 'a':{

            // }
            // break;

            // case 'b':{

            // }
            // break;
            // default:
            //     break;
            // }



        }
            break;

        case '9':{
            string name;
            cout << "       Ihr nachname bitte : "; cin >> name;

            Medien* medium = MediaFinden(0, name);
            if(medium == nullptr){
                cout << "       kein Buch wurde mit diesem Name ausgeliehen"<<endl;
                break;
            }
            medium->setLoan(false);
            cout << "       Zurueckgegeben!!!"<<endl;

        }
            break;
        case '0':{

            return;
        }
            break;
        default:
            break;
        }


    }
}






























