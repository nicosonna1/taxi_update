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



#define NICOLAS 1 



using namespace std;

int main() {

	int tempsCourse = 27*60; //distance / vMoyenne * 60; //1440 = 24h
	int nbChangements = tempsCourse / 480; //3changements
	int tempsNuit;
	int tempsJour;
int heure;
int minute;


	int hDepart = 12;
	int hChangement;
	int nbJour,
		jourIncomplet;

	int DEBUT_JOUR = 8;
	int DEBUT_NUIT = 20;
	const int TEMP_JOURNEE = DEBUT_NUIT-DEBUT_JOUR;
	const int TEMP_NUIT =24 - TEMP_JOURNEE;
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

	#ifdef NICOLAS
	
	cout << "entrer une valeure hh:mm" << endl;
	//cin >> heure >> minute;
	heure =12;
	minute = 12 + heure *60;
	cout << minute << endl;
	cout << "temps nuit --> " << TEMP_NUIT << "temps journe " << TEMP_JOURNEE<< endl;

	nbJour=tempsCourse/1440;		// calcul du nombre de jours
	jourIncomplet=tempsCourse%1440;	// calcule du reste si il y en a un
	tempsNuit=nbJour*TEMP_NUIT*60;	
	tempsJour=nbJour*TEMP_JOURNEE*60;
	if (jourIncomplet!=0)
	{

		cout << "jour plus grand que 1 --> " << nbJour << "reste  " << jourIncomplet << endl;
	}
	else{
	cout << "jour plus petit que 1 --> " << nbJour << "rest" << jourIncomplet << endl;
	}
			
			if (jourIncomplet>0){
			// on se calle dans l'intervale de la journée
			cout << "jour incomplet >0  " << endl;
			if (minute <DEBUT_NUIT*60 && minute >DEBUT_JOUR*60){
				cout << "calcule journee --> " << endl;
				int calcule =   DEBUT_NUIT*60-jourIncomplet;

			// si la diférence entre le temps du rest (jourIncomplet) est plus grande que la journée 
			// on fait une soustraction pour trouver le temps de nuit
			if (jourIncomplet<TEMP_JOURNEE*60)
			{

				cout << "journée plus grande que " << endl;
				tempsJour+=jourIncomplet;
			}
			//a faire pour la nuit 
			else{

			}
			 //tempsJour = jourIncomplet - (DEBUT_NUIT*60);

		}
			}

	cout << "temps jour  --> " << tempsJour/60 << "temps nuit " << tempsNuit/60 << endl;

}
 
	#else

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
#endif
