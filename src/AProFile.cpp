//-----------------------------------------------------
//---------------Fichier AProFile.cpp------------------
// R�le : Implementation de la classe AProFile,
//facilite l'utilisation des fichiers.
// Cr�� le : 13/04/2010
// Modifi� le : 24/04/2010
/// Appartient � la soci�t� Atlanti's Corporation,
///toute modification est interdite sauf en pr�sence de
///la lisence AProLisence_ModVx2.5.
//-----------------------------------------------------

#include "AProFile.h"
namespace APro
{

//-------------------------------------
//-Classe : AProFile
//-Fonction : Constructeur
//-Valeur demand�e : const char*
//-Valeur retourn�e : Aucune
//-------------------------------------
AProFile::AProFile(const char* nomFichier) : nomFichierComplet(nomFichier)
{
    fichier = new std::ofstream(nomFichier,std::ios::out);
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : Constructeur
//-Valeur demand�e : std::string
//-Valeur retourn�e : Aucune
//-------------------------------------
AProFile::AProFile(std::string string) : nomFichierComplet(string)
{
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : exist (test l'existence d'un fichier)
//-Valeur demand�e : Aucune
//-Valeur retourn�e : bool�en
//-------------------------------------
bool AProFile::exists() const
{
    std::ifstream File(nomFichierComplet.c_str());
    return File.is_open();
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : FullName (renvoie le nom complet d'un fichier)
//-Valeur demand�e : Aucune
//-Valeur retourn�e : const std::string&
//-------------------------------------
const std::string& AProFile::FullName() const
{
    return nomFichierComplet;
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : FileName (renvoie le nom d'un fichier avec extension)
//-Valeur demand�e : Aucune
//-Valeur retourn�e : std::string
//-------------------------------------
std::string AProFile::FileName() const
{
    std::string::size_type Position = nomFichierComplet.find_last_of("\\/");
    if (Position != std::string::npos)
        return nomFichierComplet.substr(Position+1, std::string::npos);
    else
        return nomFichierComplet;
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : Extension (retourne l'extension d'un fichier)
//-Valeur demand�e : Aucune
//-Valeur retourn�e : std::string
//-------------------------------------
std::string AProFile::Extension() const
{
    std::string::size_type Position = nomFichierComplet.find_last_of(".");
    if (Position != std::string::npos)
        return nomFichierComplet.substr(Position+1, std::string::npos);
    else
        return "";
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : getLine
//-Valeur demand�e : int (num�ro de ligne)
//-Valeur retourn�e : std::string
//-------------------------------------
std::string AProFile::getLine(int line)
{
    std::ifstream fichier_getline(nomFichierComplet.c_str());
    std::string stringline;
    for (int i = 0; i < line; i++)
    {
        std::getline(fichier_getline,stringline);
    }
    std::getline(fichier_getline,stringline);
    return stringline;
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : getFile (renvoie le fichier)
//-Valeur demand�e : Aucune
//-Valeur retourn�e : const std::ofstream&
//-------------------------------------
const std::ofstream& AProFile::getFile()
{
    return *fichier;
}

//-------------------------------------
//-Classe : AProFile
//-Fonction : eraseFile(efface le fichier)
//-Valeur demand�e : Aucune
//-Valeur retourn�e : Aucune
//-------------------------------------
void AProFile::eraseFile()
{
    fichier->close();
    if (remove(nomFichierComplet.c_str())!=0)
        AProFileLogger::reportError("Le fichier "+nomFichierComplet+" n'a pas pu �tre supprim� !", "ErrorFile.log");
    delete this;
}

}//Fin du namespace APro
