//============================================================================
// Name        : Phase2.cpp
// Author      :  Prud'homme, Hory
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

        float toFloat(string str)
        {
            stringstream is;
            float result;
            is.str(str);
            is >> result;
            return result;
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
			vector <string> VMotif; //Ce vecteur contiendra tout les motifs
			VMotif.push_back("0 ");
			vector <float> VnbMotif; //Ce vecteur contiendra les fréquences des motifs
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
						ChiffreFreq = toFloat(Freq);
						VnbMotif.push_back(ChiffreFreq);
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

			//minConf défini par l'utilisateur en unsigned
			float minConf = toFloat(MinConf);
			float Conf; //Ce nombre correspond à la confiance obtenue après calcul
			string Decode = ""; //Cette string servira à récupérer le 1er motif de chaque association
			string SingleMotif = "";
			unsigned k = 0;//Cette indice correspondra à la case du motif seul recherché
			for (unsigned i = 0; i < VMotif.size(); ++i)
			{
				Decode = VMotif[i]; //Decode contient chaque case du tableau VMotif

				//On explore decode à la recherche d'un motif unique
				for(unsigned j = 0; Decode[j] != ' '; ++j)
				{
					SingleMotif+= Decode[j]; //Le motif unique est contenu dans SingleMotif
				}
				SingleMotif += ' ';
				//On recherche la correspondance de SingleMotif dans le tableau VMotif
				for(unsigned j = 0; j < VMotif.size() && k == 0; ++j)
				{
					if (VMotif[j] == SingleMotif)
						k = j; //On retient l'indice de correspondance
				}
				SingleMotif="";
				Conf = VnbMotif[i]/VnbMotif[k];
				if (Conf >= minConf && Conf != 1) out << VMotif[i] << " -- " << Conf << '\n';
				k = 0;
			}
		}
}

int main(int argc, char* argv[])
{
	Confiancef::Confiance(argv[1], argv[2]);
	return 0;
}
