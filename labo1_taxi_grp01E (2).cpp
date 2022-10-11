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

int main()
{
     // Variables
     // -----------------------------------------
     // Constantes
     const float TAXE_BASE = 5.00f, // En euros
         SURTAXE_BAGAGES = 2.60f,   // En euros
         TARIF_MIN_JOUR = 1.00f,    // En euros
         TARIF_MIN_NUIT = 1.60f;
     const short H_FIN_NUIT = 8,
                 H_FIN_JOUR = 20,
                 BAG_MIN = 0,
                 BAG_MAX = 4;
                 
     // boolean
     bool tarifJour;

     // Variables numériques
     short bagages,
         heures,
         minutes;

     float distance,
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
          << "- Prise en charge   : " << taxeBase << endl
          << "- Suppl. par bagage : " << SURTAXE_BAGAGES << endl
          << "- Tarif/Minute      : " << TARIF_MINUTES << endl
          << endl;

     // Saisie des données
     // -----------------------------------------
     cout << "Votre commande : " << endl
          << "============================" << endl;
     cout << "- Le nombre de bagages" << setw(8) << ": ";
     cin >> bagages;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');

     cout << "- La distance [km]" << setw(12) << ": ";
     cin >> distance;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');

     cout << "- La vitesse moyenne [km/h]" << setw(3) << ": ";
     cin >> vMoyenne;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');

     // Calcul des prix
     // -----------------------------------------
     taxeBagages = bagages * SURTAXE_BAGAGES;
     prixCourse = distance / vMoyenne * 60 * TARIF_MINUTES; // 1 minute = 60 secondes
     prixTotal = taxeBase + taxeBagages + prixCourse;

     // Affichage du ticket
     // -----------------------------------------
     cout << endl
          << "Votre ticket : " << endl
          << "============================" << endl
          << fixed << setprecision(2)
          << "- Prise en charge      : " << taxeBase << "€" << endl
          << "- Supp bagages         : " << taxeBagages << "€" << endl
          << "- Prix de la course    : " << prixCourse << "€" << endl
          << "  TOTAL                : " << prixTotal << "€" << endl;

     // Sortie
     cout << endl
          << "Pressez ENTER pour quitter..." << endl;
     cin.ignore(numeric_limits<streamsize>::max(), '\n');

     return EXIT_SUCCESS;
}
