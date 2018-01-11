#include <iostream> // cin, cout
#include <iomanip>  // Précision
#include <cstdlib>  // srand, rand.
#include <ctime>    // seulement pour initialiser random. srand(time(NULL));
#include "GestionHeures.h" // Contient l'horloge et les fonctions pour gérer l'heure en format militaire. 
using namespace std;

/***
* L'horloge du programme
*/
HeureMilitaire& HeureMilitaire::horloge() // Sigleton horloge
{								 
	static HeureMilitaire horloge;
	return horloge;
}

/***
* Obtenir l'heure en format militaire. ex : 900, 1000, 1100
*/
unsigned int HeureMilitaire::getTime()
{
	unsigned int heures  = tempsEnMinutes / 60;
	unsigned int minutes = tempsEnMinutes % 60;
	return heures * 100 + minutes;
}

/***
* afficher l'heure en format militaire. ex : 0900, 1030, 1100
*/
void HeureMilitaire::afficherTempsMilitaire(unsigned int nbMinutes)
{
	cout << "Horloge :"<< setw(4) << setfill('0') << HeureMilitaire::horloge().getTime() << endl << setfill(' ');
}

/***
* Ajouter des minutes à l'horloge.
*/
void HeureMilitaire::ajouterMinutes(int p_minutes)
{
	tempsEnMinutes += p_minutes;
}

/***
* Générer l'heure d'arrivée d'un voyageur et incrémente l'horloge.
*/
unsigned int HeureMilitaire::GénérerHeureArrivée()
{
	HeureMilitaire::horloge().ajouterMinutes((unsigned int)(rand() % 3 + 1));
	return HeureMilitaire::horloge().getTime();
}

/***
* Génère le temps de service du voyageur
*/
unsigned int HeureMilitaire::GénérerTempsService()
{
	return (unsigned int)rand() % 15 + 1;
}

/***
* Génère l'heure du départ prévu
*/
unsigned int HeureMilitaire::GénérerHeureDépart(const unsigned int& p_duréeService)
{
	unsigned int heures  = (horloge().tempsEnMinutes + p_duréeService) / 60;
	unsigned int minutes = (horloge().tempsEnMinutes + p_duréeService) % 60;
	return heures * 100 + minutes;
}