/*
 * ------------------------------------------
 * File     	: main.cpp
 * Authors  	: Vitória Oliveira, Nicolas Sonnard
 * 			 	 (Original : Jonas Huegli & Sebastian Diaz)
 * Date    	 	: 11.10.2022
 * Purpose  	: Ce programme calcule le prix d'une course de taxi.
 * 			  	  L'utilisateur est prié de saisir quelques informations sur la
 * 			  	  course, puis un ticket complet lui est présenté.
 * 			  	  Deux tarifs (jour/nuit) sont à appliquer sur la durée du trajet
 * 				  pour le calcul du prix total.
 * Remarque(s) : L'heure de départ doit être saisie au format [hh:mm], où l'heure
 * 				  est comprise entre [0, 23] et les minutes sont comprise entre
 * 				  [0, 59]. Le symbole ":" est obligatoire dans la saisie.
 * 				  Chaque minute consommée est facturée.
 * 				  Le ticket est imprimé selon un format imposé dans la consigne.
 * 				  Ce programme ne gère pas les erreurs de saisie mais dans le cas
 * 				  de valeurs saisies en dehors des intervalles demandés, le programme
 				 	  s'interrompt avec un message à l'utilisateur.
 				 	  Si les intervalles des données saisies sont changés, il faudrait
 				 	  examiner à nouveau les types des variables et tenir compte des
 				 	  possibles dépassements.
Compilateur    : Mingw-w64 g++ 12.2.0, C++23

 * ------------------------------------------
 */

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout & cin
#include <limits>   // numeric_limits<streamsize>
#include <iomanip>  // setw(...) et setprecision(...)
#include <cmath>    // ceil()

using namespace std;

#define RESET_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

int main() {
	// Variables
	// ---------------------------

	// Constantes de prix
	const float
		TAXE_BASE = 5.0f,
		SURTAXE_BAGAGES = 2.6f,
		TARIF_MNT_JOUR = 1.0f,
		TARIF_MNT_NUIT = 1.6f;

	// Constantes des bornes d'intervalle des saisies
	const short
		H_FIN_NUIT = 8,
		H_FIN_JOUR = 20,
		BAG_MIN = 0,
		BAG_MAX = 4,
		DIST_MAX = 500,
		DIST_MIN = 0,
		V_MIN = 30,
		V_MAX = 120,

	// Constantes de temps
		MNT_DANS_H = 60;


	// Constantes d'affichage (largeur des collones du tableau)
	const short
		LARG_COL = 23,
		LARG_COL_P = 11, // largeur du ":"
		LARG_COMMANDE = 26,
		LARG_H_TICKET = 18,
		LARG_PRIX_TICKET = 10,
		LARG_TOTAL = 22,

	// Constante de précision
		PRECISION = 2;

	// Constante message de fin du programme
	const string
		MSG_FIN = "Presser ENTER pour quitter";

	// Variables numériques
	short
		bagages,
		hDepart,
		mDepart;

	// Les variables ci-dessous sont de type entier afin d'éviter des conversions
	// implicites dangereuses.
	// On initialise tempsJournee & tempsNuit, autrement elles peuvent être utilisées
	// sans être initialisées.
	int
		tempsJournee = 0,
		tempsNuit = 0,
		minTotalDepart,
		prochainChgTarif,
		tempsTotal;

	float
		distance,
		vMoyenne,
		taxeBagages,
		prixJournee,
		prixNuit,
		prixTotal;

	bool
		estJour;


	// Affichage de bienvenue
	// ---------------------------
	cout << "Bonjour, ce programme va vous demander de saisir des informations "
		  << "sur votre voyage !" 														<< endl
		  << "voici les conditions :" 												<< endl
		  << "======================="												<< endl
		  << fixed	<< setprecision(PRECISION)
		  << left  	<< setw(LARG_COL) 	<< " - prise en charge" 		<< ":"
		  << right 	<< setw(LARG_COL_P) 	<< TAXE_BASE 						<< endl
		  << left  	<< setw(LARG_COL) 	<< " - supp par bagage" 		<< ":"
		  << right 	<< setw(LARG_COL_P) 	<< SURTAXE_BAGAGES 				<< endl
		  << left  	<< setw(LARG_COL) 	<< " - tarif/minute (jour)"	<< ":"
		  << right 	<< setw(LARG_COL_P) 	<< TARIF_MNT_JOUR 				<< endl
		  << left  	<< setw(LARG_COL) 	<< " - tarif/minute (nuit)" 	<< ":"
		  << right 	<< setw(LARG_COL_P) 	<< TARIF_MNT_NUIT 				<< endl
		  << left  	<< setw(LARG_COL) 	<< " - tarif jour" 				<< ":"
		  << right 	<< setw(LARG_COL_P) 	<< " 8h00-20h00" 					<< endl
		  << endl;



	// Saisie des données
	// -----------------------------------------
	cout << "Votre commande " 														<< endl
		  << "==============" 														<< endl
		  << left 	<< setw(LARG_COMMANDE) 	<< " - nbre de bagage "
		  << right	<< setw(LARG_COL_P) 	 	<< " [0 - 4]" 				<< " : ";
	cin  >> bagages;
	RESET_BUFFER;

	// Vérification des saisies
	if (bagages >= BAG_MIN && bagages <= BAG_MAX) {
		cout << left 	<< setw(LARG_COMMANDE) 	<< " - distance [km] "
			  << right	<< setw(LARG_COL_P) 		<< " [0 - 500]" 		<< " : ";
		cin  >> distance;
		RESET_BUFFER;

		if (distance >= DIST_MIN && distance <= DIST_MAX) {

			cout << left 	<< setw(LARG_COMMANDE) 	<< " - vitesse moyenne [km/h]"
				  << right 	<< setw(LARG_COL_P) 		<< " [30 - 120]" << " : ";
			cin  >> vMoyenne;
			RESET_BUFFER;

			if (vMoyenne >= V_MIN && vMoyenne <= V_MAX) {

				cout << left 	<< setw(LARG_COMMANDE) 	<< " - depart "
					  << right 	<< setw(LARG_COL_P) 		<< " [hh:mm]" << " : ";
				cin  >> hDepart;
				cin.ignore(numeric_limits<streamsize>::max(), ':');
				cin  >> mDepart;
				RESET_BUFFER;


				if (hDepart >= 0 && hDepart < 24 && mDepart >= 0 && mDepart < 60) {

					estJour = hDepart >= H_FIN_NUIT && hDepart < H_FIN_JOUR;
					minTotalDepart = hDepart * MNT_DANS_H + mDepart;

					// On estime que la conversion explicite ci dessous n'est pas
					// dangereuse car tempsTotal maximal possible est de 1001 minutes.
					tempsTotal = int(ceil(distance / vMoyenne * MNT_DANS_H));

					if (estJour) {

						prochainChgTarif = H_FIN_JOUR * MNT_DANS_H - minTotalDepart;

						if (tempsTotal >= prochainChgTarif) {

							tempsJournee = H_FIN_JOUR * MNT_DANS_H - minTotalDepart - 1;
							tempsTotal -= tempsJournee;

							if (tempsTotal <= 12 * MNT_DANS_H) {
								tempsNuit = tempsTotal;
							} else {
								tempsNuit = 12 * MNT_DANS_H;
								tempsTotal -= tempsNuit;
								tempsJournee += tempsTotal;
							}
						} else {
							tempsJournee = tempsTotal;
						}

					} else {
						cout << "Jour: " << estJour << endl;
						cout << "Temps total = " << tempsTotal << endl;
						cout << " Temps nuit = " << tempsNuit << endl;

						//temps jusqu'à minuit
						tempsNuit += 24 * MNT_DANS_H - minTotalDepart;
						tempsTotal -= tempsNuit;
						cout << "Temps total = " << tempsTotal << endl;
						cout << " Temps nuit = " << tempsNuit << endl;

						prochainChgTarif = H_FIN_NUIT * MNT_DANS_H;

						if (tempsTotal >= prochainChgTarif) {

							tempsNuit += H_FIN_NUIT * MNT_DANS_H - 1;
							tempsTotal -= H_FIN_NUIT * MNT_DANS_H - 1;
							tempsJournee += tempsTotal;

							//test
							cout << "Temps Nuit = " << tempsNuit << endl;
							cout << "Temps total = " << tempsTotal << endl;
							cout << "Temps journee = " << tempsJournee << endl;

						} else {
							tempsNuit += tempsTotal;
							cout << "Temps total = " << tempsTotal << endl;
							cout << " Temps nuit = " << tempsNuit << endl;
							}
						}

					// Calcul des prix
					// -----------------------------------------
					// conversion exp pas dagereuse car bag max = 4
					taxeBagages = (float) bagages * SURTAXE_BAGAGES;
					//conversion pas dangereuse car tempsTotal MAX = 1001, alors
					// tempsJournee et tempsNuit forcément < 1001.
					prixJournee = float(tempsJournee) * TARIF_MNT_JOUR;
					prixNuit = float(tempsNuit) * TARIF_MNT_NUIT;
					prixTotal = TAXE_BASE + taxeBagages + prixJournee + prixNuit;

					// Affichage du ticket
					// -----------------------------------------
					cout << endl
						  << "Votre ticket " << endl
						<< "==============" << endl
						<< fixed << setprecision(PRECISION)
						<< left << setw(LARG_COL) << " - prise en charge" << ":"
						<< right << setw(LARG_COL_P) << TAXE_BASE << endl
						<< left << setw(LARG_COL) << " - supp bagages" << ":"
						<< right << setw(LARG_COL_P) << taxeBagages << endl
						<< left << setw(LARG_COL) << " - temps course" << endl
						<< right << setw(LARG_H_TICKET) << "xxx' @ "
						<< TARIF_MNT_JOUR
						<< " : "
						<< right << setw(LARG_PRIX_TICKET) << prixJournee << endl
						<< right << setw(LARG_H_TICKET) << "yyy' @ "
						<< TARIF_MNT_NUIT << " : "
						<< right << setw(LARG_PRIX_TICKET) << prixNuit << endl
						<< left << setw(LARG_COL) << "---------------------- "
						<< right << setw(LARG_COL_P) << "  -----------" << endl
						<< right << setw(LARG_TOTAL) << "TOTAL" << " : "
						<< right << setw(LARG_PRIX_TICKET) << prixTotal << endl;

				} else {
					cout << "L'heure de depart doit etre comprise dans entre [00:00, "
							  "23:59]. " << endl
						  << MSG_FIN;
					return EXIT_FAILURE;
				}
			} else {
				cout << "La vitesse doit etre comprise entre [30, 120] [km/h]. "
					  << endl
					  << MSG_FIN;
				RESET_BUFFER;
				return EXIT_FAILURE;
			}
		} else {
			cout << "La distance doit etre comprise entre [0, 500] [km]. " << endl
				  << MSG_FIN;
			RESET_BUFFER;
			return EXIT_FAILURE;
		}
	} else {
		cout << "Le nombre de bagages doit etre compris entre [0, 4]. " << endl
			  << MSG_FIN;
		RESET_BUFFER;
		return EXIT_FAILURE;
	}
	cout << endl << MSG_FIN;
	RESET_BUFFER;
	return EXIT_SUCCESS;

}
