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

/*modifs:
- correction texte affichage selon la consigne
- enlevé unité monétaire
- enlevé certains RESET_BUFFER
- add cte de précision (2) + utilisation dans affichage
- chg RESET BUFFER
- chg largeurs pour affichage correct
*/

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout & cin
#include <limits>   // numeric_limits<streamsize>
#include <iomanip>  // setw(...) et setprecision(...)

using namespace std;

#define RESET_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

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
	// largeur des collones du tableau
	const int LARG_COL = 23;
	const int LARG_AFF_COMMANDE = 26;
	const int LARG_AFF_H_TICKET = 18;
	//largeur du ":"
	const int LARG_COL_P = 11; //de 7 à 11 pour aligner avec tranche horaire
	//cst de précision
	const short PRECISION = 2;



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
		  << "voici les conditions :" << endl
		  << "=======================" << endl
		  << fixed << setprecision(PRECISION)
		  << left    << setw(LARG_COL) << "- prise en charge"           << ":"
		  << right   << setw(LARG_COL_P) << TAXE_BASE << endl
		  << left    << setw(LARG_COL) << "- supp par bagage"           << ":" <<
		  right   << setw(LARG_COL_P) << SURTAXE_BAGAGES  << endl
		  << left    << setw(LARG_COL) << "- tarif/minute (jour)"           << ":"
		  << right   << setw(LARG_COL_P) << TARIF_MIN_JOUR  << endl
		  << left    << setw(LARG_COL) << "- tarif/minute (nuit)"           << ":"
		  << right   << setw(LARG_COL_P) << TARIF_MIN_NUIT << endl
		  << left    << setw(LARG_COL) << "- tarif jour"           << ":"
		  << right   << setw(LARG_COL_P) << " 8h00-20h00"<< endl << endl;


	// Saisie des données
	// -----------------------------------------
	cout << "Votre commande " << endl
		  << "==============" << endl
		  << left << setw(LARG_AFF_COMMANDE) << " - nbre de bagage "
		  << setw(LARG_COL_P) << right << " [0 - 4]" << " : " ;
	cin >> bagages;
	RESET_BUFFER;

	cout << left << setw(LARG_AFF_COMMANDE) << " - distance [km] "
	<< setw(LARG_COL_P) << right << " [0 - 500]" << " : ";
	cin >> distance;
	RESET_BUFFER;

	cout << left << setw(LARG_AFF_COMMANDE) << " - vitesse moyenne [km/h]"
		<< setw(LARG_COL_P) << right << " [30 - 120]" << " : ";
	cin >> vMoyenne;
	RESET_BUFFER;

	cout << left << setw(LARG_AFF_COMMANDE) << " - depart "
		<< setw(LARG_COL_P) << right << " [hh:mm]" << " : ";
	//cin.get(heures,':');
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
		  << "==============" << endl
		  << fixed << setprecision(PRECISION)
		  << left << setw(LARG_COL) << " - prise en charge" << ":"
		  << right << setw(LARG_COL_P) << TAXE_BASE  << endl
		<< left << setw(LARG_COL) << " - supp bagages"             << ":"
		<< right << setw(LARG_COL_P) <<	taxeBagages << endl
		<< left << setw(LARG_COL) << " - temps course " << endl
		  << right << setw(LARG_AFF_H_TICKET) << "xxx' @ " << TARIF_MIN_JOUR
		  << " : "
		  << right << setw(LARG_COL_P) << " XXX "  << endl
		  //REMPLACER PAR VRAIeS
		  // VALEURS + VARIABLES
		<< right << setw(LARG_AFF_H_TICKET) << "yyy' @ " << TARIF_MIN_NUIT << " : "
		<< right << setw(LARG_COL_P) << " YYY " << endl
		<< left << setw(LARG_COL) << "--------------------------"
		<< right << setw(LARG_COL_P)  << "------------" << endl
		<< right << setw(LARG_COL) << "TOTAL"             << " : "
		<< right << setw(LARG_COL_P) << prixTotal << endl;

	// Sortie
	cout << endl
		  << "Pressez ENTER pour quitter..." << endl;
	RESET_BUFFER;

	return EXIT_SUCCESS;
}
