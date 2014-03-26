//============================================================================
// Name        : Phase2.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Util.h"

using namespace std;

namespace Confiancef
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

		void Confiance(string fichier, string MinConf)
		{
			ifstream flux(fichier.c_str(), ios::in); //Ouvre le fichier plac� en param�tre
			ofstream out((TakeName(fichier, ".txt")).c_str(), ios::out | ios::trunc); //Cr�er un fichier de m�me nom en extension .conf
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
			string Motif = ""; //Cette string servira à récupérer les motifs
			string Freq; //Cette string récupère les fréquences
			unsigned ChiffreFreq; //Cet unsigned est le résultat de la conversion de Freq
			vector <string> VMotif; //Ce vecteur contiendra tout les motifs uniques
			VMotif.push_back("0");
			vector <unsigned> NbMotif; //Ce vecteur contiendra les fréquences des motifs
			bool RemplirFreq = false;
			for(getline(flux,ligne) ; !flux.eof() ; getline(flux,ligne))
			{
				for (unsigned i = 0; i < ligne.size(); ++i)
				{
					if (ligne[i] == '('){
						if (i > 0)
						{
							VMotif.push_back(Motif);
							Motif = "";
						}
						RemplirFreq = true;
					}
					else if (ligne[i] == ')')
					{
						RemplirFreq = false;
						ChiffreFreq = nsUtil::toUnsigned(Freq);
						NbMotif.push_back(ChiffreFreq);
						Freq = "";
						break;
					}
					else if (RemplirFreq)
					{
						Freq += ligne[i];
					}
					else Motif += ligne[i];
				}
			}
			flux.close();


		}
}

int main(int argc, char* argv[])
{
	Confiancef::Confiance(argv[1], argv[2]);
	return 0;
}
