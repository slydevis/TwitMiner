/*
 * CSVToTrans.cpp
 *
 *  Created on: 24 mars 2014
 *      Author: p12003701
 */
#include <vector>
#include <iostream>
#include <fstream>
#include <ctype.h>
namespace CSVToTrans
{
	std::vector<std::string> Tab;

	std::string SuprCar(std::string str, char car)
	{
		int Cpt = 0;
		std::string chaine;
		for(int i = 0; str[i + Cpt] != '\0'; ++i)
		{
			if(str[i + Cpt] == car) Cpt++;
			chaine += str[i + Cpt];
		}
		return chaine;
	}

	std::string StrReplace(std::string str, char car, char characReplace)
	{
		std::string chaine;
		for(int i = 0; str[i] != '\0'; ++i)
		{
			if(str[i] == car) str[i] = characReplace;
			chaine += str[i];
		}
		return chaine;
	}

	std::vector<std::string> Explode(std::string str, char delimiteur)
	{
		std::vector<std::string> Tab;
		std::string buffer;
		for(int i = 0;str[i] != '\0'; ++i)
		{

			if(str[i] != delimiteur) buffer += str[i];
			if(str[i] == delimiteur || str[i+1] == '\0')
			{
				Tab.push_back(buffer);
				buffer = "";
			}
		}
		return Tab;
	}

	std::string ToLower(std::string str)
	{
		for(int i = 0;str[i] != '\0'; ++i) {
			str[i]= (tolower(str[i]));
		}
		return str;
	}
	void InitTab(const std::string cheminCSV)
	{
		std::ifstream is(cheminCSV.c_str(),std::ios::in);
		if (!is.fail())
		{
			std::string buff;
			std::string tmp;
			for(getline(is, buff);!is.eof();getline(is,buff))
			{
				for(unsigned i = 32; i < buff.size();++i)
				{
					tmp += buff[i];
				}
				tmp = SuprCar(tmp, '"');
				tmp = SuprCar(tmp, ' ');
				tmp = StrReplace(tmp, ';', ' ');
				tmp += ';';
				std::vector<std::string> Tabulation = Explode(tmp, ' ');
				tmp = "";
				for(unsigned i = 0; i < Tabulation.size(); ++i)
				{
					Tabulation[i] = ToLower(Tabulation[i]);
					Tab.push_back(Tabulation[i]);
				}
			}
			is.close();
		}
		else std::cout << "Erreur dans l'ouverture du fichier";
	}

	int FindDico(std::vector<std::string> tab, std::string str, int pos)
	{
		for(int i = 0; i < pos; ++i)
		{
			if(tab[i] == str) return i;
		}
		return (-1);
	}

	void AddFile(std::string cheminTrans)
	{
		std::ofstream os(cheminTrans.c_str());
		std::ofstream os2("resources.trad");
		if(!os.fail())
		{
			if(!os2.fail())
			{
				int Cpt = 0;
				int id = 0;
				int NbTransact = 0;
				for(unsigned i = 0; i != Tab.size(); ++i)
				{
					int LastCar = Tab[i].size();
					id = FindDico(Tab, Tab[i], i);

					if(Tab[i][LastCar - 1] == ';')
					{
						std::cout << "Transaction traité = " << NbTransact << std::endl;
						NbTransact++;
					}

					if((id) == -1) {
						os << Cpt << ' ';
						os2 << Tab[i] << "=" << Cpt << '\n';
						Cpt++;
					}
					else
					{
						os << id << ' ';
						os2 << Tab[i] << "=" << id << '\n';
					}

					if(Tab[i][LastCar - 1] == ';') os << ' ' << '\n' ;
				}
			}
			os.close();
			os2.close();
		}
		else std::cout << "Erreur dans l'écriture du fichier";
	}
}

int main()
{
	CSVToTrans::InitTab("ressources.csv");
	CSVToTrans::AddFile("ressources.trans");
	return 0;
}



