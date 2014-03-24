/*
 *  Created on: 20 mars 2014
 *      Author: Prud'homme Kévin
 */

/*==================================================
M�thodes pour r�pondre � la conversion trans/out --> csv
- r�cup�rer la ligne du fichier check
- Rep�rer le nombre entre 2 espaces (le nombre correspondra � un code de tableau que Guillaume fera)
- Remplacer le nombre par le texte correspondant au nombre indiquant la case du tableau
- Mettre en norme check
==================================================*/
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

namespace TransToCSV
{
		//Cette fonction conserve le nom du fichier mais change son format en .csv
		string TakeName(string fichier, string extension)
		{
			string nom;
			for(unsigned i = 0; fichier[i] != '.'; ++i)
			{
				nom += fichier[i];
			}
			nom += extension;
			return nom;
		}

		//Cette fonction renvoie la string indiqu�e par l'int nombre
		string decodage (string id, string fichier)
		{
			string ligne;
			string chaine;
			string iden;
			bool egale = false;
			bool correspondance = false;
			ifstream flux(fichier.c_str(), ios::in);
			for(getline(flux,ligne) ; !flux.eof(); getline(flux,ligne))
			{
				for (unsigned i = 0; i < ligne.size(); i++)
				{
					if (egale) iden += ligne[i];
					if (ligne[i] == '=') egale = true;
				}
				egale = false;
				if (iden == id) correspondance = true;
				else iden = "";
				for (unsigned i = 0 ; correspondance && ligne[i] != '='; i++)
				{
					chaine += ligne[i];
				}
				if (!chaine.empty()) break;
			}
			flux.close(); // on ferme le flux
			return chaine;  // on renvoie la chaine correspondant � l'id
		}

		//Applique la fonction concern�e
		void TransTOCSV (string fichier)
		{
			ifstream flux(fichier.c_str(), ios::in); //Ouvre le fichier plac� en param�tre
			string ficTrad = TakeName(fichier, ".trad");
			ofstream out((TakeName(fichier, ".csv")).c_str(), ios::out | ios::trunc); //Cr�er un fichier de m�me nom en extension .csv
			if (flux.fail()) //V�rifie que le fichier est bien ouvert en lecture
				{
					cout << "Fichier � lire introuvable\n";
					return;
				}
			if (out.fail()) //V�rifie que le fichier est en mode �criture. S'il n'existe pas, il se cr�e
				{
					cout << "Ecriture impossible.\n";
					return;
				}
			string ligne; //Cette string servira comme r�colteur de chaque ligne du fichier
			string decode; //Ce caract�re sera utile pour la ligne d�crite juste au dessus
			string message; //Cette string correspond au message codé qui sera écrit dans le flux
			for(getline(flux,ligne) ; !flux.eof() ; getline(flux,ligne))
			{
				out << '"'; //Chaque ligne du csv commence avec un "
				for (unsigned i = 0; i < ligne.size(); i++){
					if (ligne[i] == ' ' || ligne[i] == '\n') //Si c'est un espace, il est remplac� par ";"
					{
						message = decodage(decode, ficTrad); //si c'est un espace, on d�code ce qu'il y a avant
						out << message << '"' << ';' << '"'; // on ajoute un ";"
						decode=""; // on r�initialise r�colte
					}
					else {
						decode += ligne[i]; // si ce n'est pas un espace, r�colte prend ce caract�re en plus
					}
				}
				out << '"' << '\n'; //Chaque ligne du csv doit se terminer par un "
				out << ligne << '\n';
			}
			flux.close(); //On ferme les flux
			out.close();
		}
}

int main(int argc, char *argv[])
{
	TransToCSV::TransTOCSV(argv[1]);
	return 0;
}
