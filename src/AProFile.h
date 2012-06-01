//-----------------------------------------------------
//-----------------Fichier AProFile.h------------------
// Rôle : Decrit la classe AProFile, facilite l'
//utilisation des fichiers.
// Créé le : 13/04/2010
// Modifié le : 24/04/2010
/// Appartient à la société Atlanti's Corporation,
///toute modification est interdite sauf en présence de
///la lisence AProLisence_ModVx2.5.
//-----------------------------------------------------

#ifndef APROFILE_H
#define APROFILE_H

#include "AProFileLogger.h"
#include <iostream>
#include <fstream>
#include <string>

namespace APro
{
    class AProFile
    {
        public :

        //-------------------------------------
        //Constructeur à partir d'un const char*
        //-------------------------------------
        AProFile(const char* nomFichier = "Inconnu.txt");

        //-------------------------------------
        //Constructeur à partir d'un std::string
        //-------------------------------------
        AProFile(std::string string);

        //-------------------------------------
        //----Renvoie l'existence du fichier---
        //-------------------------------------
        bool exists() const;

        //-------------------------------------
        //--Renvoie le nom complet du fichier--
        //-------------------------------------
        const std::string& FullName() const;

        //-------------------------------------
        //Renvoie le nom du fichier avec extension
        //-------------------------------------
        std::string FileName() const;

        //-------------------------------------
        //Renvoie le nom du fichier sans extension
        //-------------------------------------
        std::string ShortFileName() const;

        //-------------------------------------
        //----Renvoie l'extension du fichier---
        //-------------------------------------
        std::string Extension() const;

        //-------------------------------------
        //-----Renvoie une ligne du fichier----
        //-------------------------------------
        std::string getLine(int line);

        //-------------------------------------
        //----Renvoie le fichier (ofstream)----
        //-------------------------------------
        const std::ofstream& getFile();

        //-------------------------------------
        //---------Efface le fichier-----------
        //-------------------------------------
        void eraseFile();

        private :

        std::string nomFichierComplet;
        std::ofstream *fichier;
    };
}// Fin du namespace APro

#endif // Fin de APROFILE_H
