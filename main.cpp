/*
 * ------------------------------------------
 * File     : labo1_taxi_grp01E.cpp
 * Authors  : Jonas Huegli & Sebastian Diaz
 * Date     : 29.09.2022
 * Purpose  : Calculer le prix d'un ticket
 *            basé sur le nombre de bagages,
 *            la distance et la vitesse.
 * ------------------------------------------
 */

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout & cin
#include <limits>   // numeric_limits<streamsize>
#include <iomanip>  // setw(...) et setprecision(...)

using namespace std;

// unité monétaire
#define UNITE_MONAIE "fr" 
#define RESET_BUFFER cout << "- Le nombre de bagages" << setw(8) << ": "

int main()
{
     // Variables
     // -----------------------------------------
     // Constantes
     const float TAXE_BASE = 5.00f, // En euros
         SURTAXE_BAGAGES = 2.60f,   // En euros
         TARIF_MIN_JOUR = 1.00f,    // En euros
         TARIF_MIN_NUIT = 1.60f;
         TAXE_BASE = 5.00f
     const short H_FIN_NUIT = 8,
                 H_FIN_JOUR = 20,
                 BAG_MIN = 0,
                 BAG_MAX = 4;
     // largeur des collones du tableau 
     const int LARG_COL = 25;
     //largeur du ":"
     const int LARG_COL_P = 7;



     // boolean
     bool tarifJour;

     // Variables numériques
     short bagages,
         heures,
         minutes;

     float     distance,
               vMoyenne,
               taxeBagages,
               prixCourse,
               prixTotal,
               tempsJour,
               tempsNuit;

     // Affichage de bienvenue
     // -----------------------------------------





     cout << "Bonjour, ce programme va vous demander de saisir des informations "
          << "sur votre voyage !" << endl
          << "Voici les conditions :" << endl
          << "============================" << endl
          << left    << setw(LARG_COL) << "- Prise en charge"           << ":" << right   << setw(LARG_COL_P) << TAXE_BASE << UNITE_MONAIE << endl
          << left    << setw(LARG_COL) << "- Suppl. par bagage"           << ":" << right   << setw(LARG_COL_P) << SURTAXE_BAGAGES << UNITE_MONAIE  << endl
          << left    << setw(LARG_COL) << "- Tarif/Minute (jour)"           << ":" << right   << setw(LARG_COL_P) << TARIF_MIN_JOUR << UNITE_MONAIE  << endl
          << left    << setw(LARG_COL) << "- Tarif/Minute (jour)"           << ":" << right   << setw(LARG_COL_P) << TARIF_MIN_NUIT << UNITE_MONAIE  << endl
          << left    << setw(LARG_COL) << "- Tarif jour"           << ":" << right   << setw(LARG_COL_P) << TARIF_MIN_NUIT << UNITE_MONAIE  << endl
          << endl;


     // Saisie des données
     // -----------------------------------------
     cout << "Votre commande : " << endl
          << "============================" << endl;
     RESET_BUFFER;
     cin >> bagages;
     RESET_BUFFER;

     cout << "- La distance [km]" << setw(12) << ": ";
     cin >> distance;
     RESET_BUFFER;

     cout << "- La vitesse moyenne [km/h]" << setw(3) << ": ";
     cin >> vMoyenne;
     RESET_BUFFER;

     cout << "- Heure de départ [HH:MM]" << setw(3) << ": ";
     cin.get(heures,':') >> vMoyenne;
     RESET_BUFFER;     

     // Calcul des prix
     // -----------------------------------------
     taxeBagages = bagages * SURTAXE_BAGAGES;
    //////////////////////////////////////////////////////////////////////// prixCourse = distance / vMoyenne * 60 * TARIF_MINUTES; // 1 minute = 60 secondes
     prixTotal = TAXE_BASE + taxeBagages + prixCourse;

     // Affichage du ticket
     // -----------------------------------------



     cout << endl
          << "Votre ticket : " << endl
          << "============================" << endl
          << fixed << setprecision(2)
          << "- Prise en charge"             << ":" << TAXE_BASE << UNITE_MONAIE << endl
          << "- Supp bagages"             << ":" << taxeBagages << UNITE_MONAIE << endl
          << "- Prix de la course"             << ":" << << prixCourse << UNITE_MONAIE << endl
          << "  TOTAL"             << ":" << prixTotal << UNITE_MONAIE << endl;

     // Sortie
     cout << endl
          << "Pressez ENTER pour quitter..." << endl;
     RESET_BUFFER;

     return EXIT_SUCCESS;
}
