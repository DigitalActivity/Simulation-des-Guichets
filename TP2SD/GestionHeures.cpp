#include <iostream> // cin, cout
#include <iomanip>  // Pr�cision
#include <cstdlib>  // srand, rand.
#include <ctime>    // seulement pour initialiser random. srand(time(NULL));
#include "GestionHeures.h" // Contient l'horloge et les fonctions pour g�rer l'heure en format militaire. 
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
* Ajouter des minutes � l'horloge.
*/
void HeureMilitaire::ajouterMinutes(int p_minutes)
{
	tempsEnMinutes += p_minutes;
}

/***
* G�n�rer l'heure d'arriv�e d'un voyageur et incr�mente l'horloge.
*/
unsigned int HeureMilitaire::G�n�rerHeureArriv�e()
{
	HeureMilitaire::horloge().ajouterMinutes((unsigned int)(rand() % 3 + 1));
	return HeureMilitaire::horloge().getTime();
}

/***
* G�n�re le temps de service du voyageur
*/
unsigned int HeureMilitaire::G�n�rerTempsService()
{
	return (unsigned int)rand() % 15 + 1;
}

/***
* G�n�re l'heure du d�part pr�vu
*/
unsigned int HeureMilitaire::G�n�rerHeureD�part(const unsigned int& p_dur�eService)
{
	unsigned int heures  = (horloge().tempsEnMinutes + p_dur�eService) / 60;
	unsigned int minutes = (horloge().tempsEnMinutes + p_dur�eService) % 60;
	return heures * 100 + minutes;
}