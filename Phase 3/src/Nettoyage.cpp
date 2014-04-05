//============================================================================
// Name        : Phase2.cpp
// Author      : Prud'homme/Hory
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace
{
		//Cette fonction conserve le nom du fichier mais change son format en l'extention souhaitée
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

		bool decodage (string id, string fichier)
		{
			string ligne = "";
			string iden = "";
			bool egale = false;
			ifstream flux(fichier.c_str(), ios::in);
			for(getline(flux,ligne) ; !flux.eof(); getline(flux,ligne))
			{
				for (unsigned i = 0; i < (ligne.size() - 1); i++)
				{
					if (egale) iden += ligne[i];
					if (ligne[i] == '=') egale = true;
				}
				egale = false;
				if (iden == id)
				{
					flux.close(); // on ferme le flux
					return true;
				}
				iden = "";
			}
			flux.close(); // on ferme le flux
			return false;
		}

		void Nettoyage (string fichier)
		{
			ifstream flux(fichier.c_str(), ios::in); //Ouvre le fichier plac� en param�tre
			string ficTrad = "motinutiles.txt";
			ofstream out((TakeName(fichier, ".nette")).c_str(), ios::out | ios::trunc);
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
			string freq; //Cette string représente la fréquence du motif
			string message; //Cette string emmagasinera chaque decode jusqu'à un ' ' ou '('
			bool nettoyage; //Cette bool sera utile pour une meilleure présentation
			for(getline(flux,ligne) ; !flux.eof() ; getline(flux,ligne))
			{
				nettoyage = false;
				for (unsigned i = 0; i < ligne.size(); i++)
				{
					if (ligne[i] == ' ' && !decode.empty())
					{
						if (decodage(decode, ficTrad))
						{
							nettoyage = true;
							break; 
						}
						message += decode + ' ';
						decode="";
					}
					else if (ligne[i] == '(')
					{
						out << message;
						for (unsigned j = (i+1); j < ligne.size(); j++)
						{
							if (ligne[j] == ')') break;
							freq += ligne[j];
						}
						out << '(' << freq << ')';
						freq = "";
						break;
					}
					else {
						decode += ligne[i];
					}
				}
				message = "";
				decode = "";
				if (!nettoyage) out << '\n';
			}
		}

}
int main(int argc, char* argv[])
{
	Nettoyage(argv[1]);
	return 0;
}


