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

int main() {

	int tempsCourse = 1440; //distance / vMoyenne * 60; //1440 = 24h
	int nbChangements = tempsCourse / 480; //3changements

	int hDepart = 12;
	int hChangement;

	int DEBUT_JOUR = 8;
	int DEBUT_NUIT = 20;
	int MINUIT = 24;

	bool estMatinee;
	bool estJour;
	bool estNuit;

	int tarifActuel;
	const float tarifJour = 1.f;
	const float tarifNuit = 1.6f;
	int x = 0; // tempsTarifJour
	int y = 0; //tempsTarifNuit
	int temp;


	while (nbChangements > 0) { //3

		estJour = (8 <= hDepart && hDepart < 20); // 1- 1

		cout << "Est Jour : " << estJour << " , Est Matinee : " << estMatinee
			  << " , est Nuit : " << estNuit << endl;

		tarifActuel = estJour ? tarifJour : tarifNuit; // choix du tarif
		// 1- tarifJour
		hChangement = estJour ? DEBUT_NUIT : hDepart < 8 ? DEBUT_JOUR : MINUIT;
		//1 - Debut nuit
		// choix du prochain changement d'heure pour bien calculer la diff de temps
		//enlever les () après

		if (estJour) { // 1 - on rentre
			if (nbChangements == 1) {
				cout << "hChangement = " << hChangement << endl;
				cout << "hDepart = " << hDepart << endl;
				x += (hDepart - hChangement) * 60;
				cout << " tour " << nbChangements << " nbCh = 1, x = " << x;
			} else {
				cout << "hChangement = " << hChangement << endl;
				cout << "hDepart = " << hDepart << endl;
				cout << "x = " << x << endl;
				x = 0;
				x += (hChangement - hDepart) * 60;
				cout << " tour " << nbChangements << " x = " << x;
			}
		} else {
			cout << "hChangement = " << hChangement << endl;
			cout << "hDepart = " << hDepart << endl;
			y += (hChangement - hDepart) * 60;
			cout << " tour " << nbChangements << " y = " << y;

		}

		temp = estMatinee;
		estMatinee = estNuit;
		estNuit = estJour;
		estJour = temp;

		hDepart = hChangement;

		if (estJour) {
			hChangement = DEBUT_NUIT;
		} else if (estNuit) {
			hChangement = MINUIT;
		} else { //estMatinee
			hChangement = 0;
		}

		cout << nbChangements << endl;
		--nbChangements;
	}

	cout << " x = " << x << " et y = " << y;
	int prixJour = x * tarifJour;
	int prixNuit = y * tarifNuit;

	int prixCourse = prixJour + prixNuit;

	cout << "Prix Course = " << prixCourse;
	return EXIT_SUCCESS;
}
