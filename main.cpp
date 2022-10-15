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

/*
modifs:
- correction texte affichage selon la consigne
- enlevé unité monétaire
- enlevé certains RESET_BUFFER
- add cte de précision (2) + utilisation dans affichage
- chg RESET BUFFER
- chg largeurs pour affichage correct

Remarques
afin d'éviter des pertes de précision tous les 
calcules seront fait en minutes
*/

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout & cin
#include <limits>   // numeric_limits<streamsize>
#include <iomanip>  // setw(...) et setprecision(...)

using namespace std;


#define UNITE_MONAIE " fr"
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
		BAG_MAX = 4,
		DIST_MAX =500,
		DIST_MIN = 0,
		VITESSE_MIN =30,
		VITESSE_MAX=120;
	// largeur des collones du tableau
	const int LARG_COL = 23;
	const int LARG_AFF_COMMANDE = 26;
	const int LARG_AFF_H_TICKET = 18;
	//largeur du ":"
	const int LARG_COL_P = 11; //de 7 à 11 pour aligner avec tranche horaire
	//cst de précision
	const short PRECISION = 2;



	// boolean
	bool tarifJour,
		 saisieOK;

	// Variables numériques
	short bagages,
		hDepart,
		mDepart,
		minTotalDepart,
		tempsTotal,
		tempsJournee,
		tempsNuit;
		

	float     distance,
		vMoyenne,
		taxeBagages,
		prixCourse,
		prixTotal;


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
	cout << "Votre commande " << endl
		  << "==============" << endl
		  << left << setw(LARG_AFF_COMMANDE) << " - nbre de bagage "
		  << setw(LARG_COL_P) << right << " [0 - 4]" << " : " ;
	cin >> bagages;
	RESET_BUFFER;
	// ce boolean deviendra vrai seulement si toutes les conditions de saisie sont OK
	saisieOK=false;
	if (bagages>=BAG_MIN && bagages<=BAG_MAX)
	{
	cout << left << setw(LARG_AFF_COMMANDE) << " - distance [km] "
	<< setw(LARG_COL_P) << right << " [0 - 500]" << " : ";
	cin >> distance;
	RESET_BUFFER;
	
	 if (distance>=DIST_MIN && distance <= DIST_MAX)
	{

	cout << left << setw(LARG_AFF_COMMANDE) << " - vitesse moyenne [km/h]"
		<< setw(LARG_COL_P) << right << " [30 - 120]" << " : ";
	cin >> vMoyenne;
	RESET_BUFFER;
	
	if (vMoyenne>=VITESSE_MIN && vMoyenne <=120) 

	cout << left << setw(LARG_AFF_COMMANDE) << " - depart "
		<< setw(LARG_COL_P) << right << " [hh:mm]" << " : ";
	//cin.get(heures,':');
	RESET_BUFFER;
	// saisie du temps au forma HH:MM
	cin >> hDepart;
	cin.ignore(numeric_limits<streamsize>::max(), ':');
	cin >> mDepart;
	if (hDepart<24 && mDepart<60)
	{
		// convertion en minutes du départ
		minTotalDepart=hDepart*60+mDepart;
		saisieOK=true;
	}
	}
}

	//calcul des temps
	//------------------------------------------

	// controle si on est la journée alors... sinon on est la nuit ...
	if (minTotalDepart<=H_FIN_JOUR*60)
	{
	tempsJournee=H_FIN_JOUR*60-minTotalDepart;
	tempsNuit=tempsTotal-tempsJournee;
	}
	else{
		tempsNuit=H_FIN_NUIT*60-minTotalDepart;
		tempsJournee=tempsTotal-tempsNuit;
	}

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
		  << right << setw(LARG_COL_P) << tempsJournee  << endl
		  //REMPLACER PAR VRAIeS
		  // VALEURS + VARIABLES
		<< right << setw(LARG_AFF_H_TICKET) << "yyy' @ " << TARIF_MIN_NUIT << " : "
		<< right << setw(LARG_COL_P) << tempsNuit << endl
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
