/*
 * ------------------------------------------
 * File     	: main.cpp
 * Authors  	: Vitória Oliveira, Nicolas Sonnard
 * 			 	 (Original : Jonas Huegli & Sebastian Diaz)
 * Date    	 	: 11.10.2022
 * Purpose  	: Ce programme calcule le prix d'une course de taxi.
 * 			  	  L'utilisateur est prié de saisir quelques informations pour le
 * 			  	  calcul du prix, puis un ticket complet lui est présenté.
 * Remarque(s) : Le ticket est imprimé selon un format imposé dans la consigne.
					  La saisie utilisateur est contrôlée, auquel cas le programme
 				 	  s'interrompt avec un message à l'utilisateur.
 				 	  Chaque minute consommée est facturée.
Compilateur    : Mingw-w64 g++ 12.2.0, C++23

 * ------------------------------------------
 */

/*
modifs: Vitória (14/10)
- correction texte affichage selon la consigne
- enlevé unité monétaire
- enlevé certains RESET_BUFFER
- add cte de précision (2) + utilisation dans affichage
- chg RESET BUFFER
- chg largeurs pour affichage correct

modifs: Vitória (15 & 16/10)
 - ajout interruption du programme + messages d'erreur
 - touts les calculs dans derniere branche if => car si les saisies ne sont pas ok,
 alors on n'aura pas besoin de procéder.
 - rm variables non utilisés
 - gestion des warnings

Remarques
afin d'éviter des pertes de précision tous les 
calcules seront fait en minutes
*/

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout & cin
#include <limits>   // numeric_limits<streamsize>
#include <iomanip>  // setw(...) et setprecision(...)
#include <cmath>

using namespace std;

#define RESET_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

int main() {
	// Variables
	// ---------------------------

	// Constantes de prix
	const float
		TAXE_BASE = 5.00f, // En euros
		SURTAXE_BAGAGES = 2.60f,   // En euros
		TARIF_MNT_JOUR = 1.00f,    // En euros
		TARIF_MNT_NUIT = 1.60f;

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
		LARG_AFF_COMMANDE = 26,
		LARG_AFF_H_TICKET = 18,
		LARG_AFF_PRIX_TICKET = 10,
		LARG_AFF_TOTAL = 22,

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
	int
		tempsJournee,
		tempsNuit,
		minTotalDepart,
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
		  << "sur votre voyage !" << endl
		  << "voici les conditions :" << endl
		  << "=======================" << endl
		  << fixed << setprecision(PRECISION)
		  << left << setw(LARG_COL) << " - prise en charge" << ":"
		  << right << setw(LARG_COL_P) << TAXE_BASE << endl
		  << left << setw(LARG_COL) << " - supp par bagage" << ":"
		  << right << setw(LARG_COL_P) << SURTAXE_BAGAGES << endl
		  << left << setw(LARG_COL) << " - tarif/minute (jour)" << ":"
		  << right << setw(LARG_COL_P) << TARIF_MNT_JOUR << endl
		  << left << setw(LARG_COL) << " - tarif/minute (nuit)" << ":"
		  << right << setw(LARG_COL_P) << TARIF_MNT_NUIT << endl
		  << left << setw(LARG_COL) << " - tarif jour" << ":"
		  << right << setw(LARG_COL_P) << " 8h00-20h00" << endl << endl;



	// Saisie des données
	// -----------------------------------------
	cout << "Votre commande " << endl
		  << "==============" << endl
		  << left << setw(LARG_AFF_COMMANDE) << " - nbre de bagage "
		  << setw(LARG_COL_P) << right << " [0 - 4]" << " : ";
	cin >> bagages;
	RESET_BUFFER;

	// ce boolean deviendra vrai seulement si toutes les conditions de saisie sont OK
	//je crois qu'on a pas besoin de ça car dès que la valeur entrée est fausse, il
	// faudra tout de suite arrêter le programme.

	// Vérification des saisies
	if (bagages >= BAG_MIN && bagages <= BAG_MAX) {
		cout << left << setw(LARG_AFF_COMMANDE) << " - distance [km] "
			  << setw(LARG_COL_P) << right << " [0 - 500]" << " : ";
		cin >> distance;
		RESET_BUFFER;

		if (distance >= DIST_MIN && distance <= DIST_MAX) {

			cout << left << setw(LARG_AFF_COMMANDE) << " - vitesse moyenne [km/h]"
				  << setw(LARG_COL_P) << right << " [30 - 120]" << " : ";
			cin >> vMoyenne;
			RESET_BUFFER;

			if (vMoyenne >= V_MIN && vMoyenne <= V_MAX) {

				cout << left << setw(LARG_AFF_COMMANDE) << " - depart "
					  << setw(LARG_COL_P) << right << " [hh:mm]" << " : ";
				cin >> hDepart;
				cin.ignore(numeric_limits<streamsize>::max(), ':');
				cin >> mDepart;
				RESET_BUFFER;


				if (hDepart >= 0 && hDepart < 24 && mDepart >= 0 && mDepart < 60) {
					// convertion en minutes du départ

					estJour = hDepart >= H_FIN_NUIT && hDepart < H_FIN_JOUR;
					// test avec hDepart: 07:58, distance = 500, vMoyenne = 30
					minTotalDepart = hDepart * MNT_DANS_H + mDepart;   //478

					//calcul de temps de la course

					//on estime que la conversion explicite ci dessous n'est pas
					// dangereuse car tempsTotal MAX = 1001
					tempsTotal = int(ceil(distance / vMoyenne * MNT_DANS_H));
					//test
					cout << distance / vMoyenne * MNT_DANS_H << endl;

					// controle si on est la journée alors... sinon on est la nuit ...
					// => 8 <= hDepart < 20, On pourrait aussi remplacer par un bool pour être plus
					// facile à lire
					// CAS OU ON COMMENCE LA JOURNEE
					if (estJour) {
						//non car hDepart = 7
						tempsJournee = H_FIN_JOUR * MNT_DANS_H - minTotalDepart;
						tempsTotal -= tempsJournee;

						if (tempsTotal <=
							 8 * MNT_DANS_H) { // si le temps restant est plus petit que 8h
							tempsNuit = tempsTotal;  //on met le temps restant dans temps nuit
						} else { // dans ce cas le temps restant est plus grand que 8h
							tempsNuit = 8 * MNT_DANS_H; //on met 8h dans temps nuit
							tempsTotal -= tempsNuit; //on enleve les 8h qui ont été affecté à tempsNuit
							tempsJournee += tempsTotal; // et on rajoute le reste à tempsJour
						}

						//CAS OU ON COMMENCE LA NUIT
					} else {
						//test
						cout << "Temps total = " << tempsTotal << endl;

						tempsNuit = H_FIN_NUIT * MNT_DANS_H - minTotalDepart;
						// 480 - 478 = 2
						tempsTotal -= tempsNuit; // 1000 - 2 = 998

						//test
						cout << "Temps restant = " << tempsTotal << endl
							  << "Temps jour = " << tempsJournee << endl
							  << "Temps nuit = " << tempsNuit << endl;

						if (tempsTotal <= 8 * MNT_DANS_H) { //non
							tempsJournee = tempsTotal;

							//test
							cout << "Temps restant = " << tempsTotal << endl
								  << "Temps jour = " << tempsJournee << endl
								  << "Temps nuit = " << tempsNuit << endl;

						} else {
							tempsJournee = 8 * MNT_DANS_H; // 480
							tempsTotal -= tempsJournee; // 998 - 480 =  518

							//test
							cout << "Temps restant = " << tempsTotal << endl
								  << "Temps jour = " << tempsJournee << endl
								  << "Temps nuit = " << tempsNuit << endl;

							if (tempsTotal <= 8 * MNT_DANS_H) {
								tempsNuit += tempsTotal;

								//test
								cout << "Temps restant = " << tempsTotal << endl
									  << "Temps jour = " << tempsJournee << endl
									  << "Temps nuit = " << tempsNuit << endl;

							} else {// s'il reste encore plus que 480 min
								tempsNuit += 8 * MNT_DANS_H;
								tempsTotal -= 8 * MNT_DANS_H;
								tempsJournee += tempsTotal;

								//test
								cout << "Temps restant = " << tempsTotal << endl
									  << "Temps jour = " << tempsJournee << endl
									  << "Temps nuit = " << tempsNuit << endl;

							}

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
						  << right << setw(LARG_AFF_H_TICKET) << "xxx' @ "
						  << TARIF_MNT_JOUR
						  << " : "
						  << right << setw(LARG_AFF_PRIX_TICKET) << prixJournee << endl
						  << right << setw(LARG_AFF_H_TICKET) << "yyy' @ "
						  << TARIF_MNT_NUIT << " : "
						  << right << setw(LARG_AFF_PRIX_TICKET) << prixNuit << endl
						  << left << setw(LARG_COL) << "---------------------- "
						  << right << setw(LARG_COL_P) << "  -----------" << endl
						  << right << setw(LARG_AFF_TOTAL) << "TOTAL" << " : "
						  << right << setw(LARG_AFF_PRIX_TICKET) << prixTotal << endl;

				} else {
					cout << "L'heure de depart doit etre comprise dans entre [00:00, "
							  "23:59]. " << endl
							  << MSG_FIN;
					return EXIT_FAILURE;
				}
			} else {
				cout << "La vitesse doit etre comprise entre [30, 120] [km/h]. " << endl
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
