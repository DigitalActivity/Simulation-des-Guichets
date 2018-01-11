#include "Stats.h"
#include <cmath> // nearbyint, arrondir en int le plus proche

/***
* Appliquer les stats : Calculer le temps d'attente moyen. et incr�menter le nombre de voyageurs servis
*/
void appliquerStats(const Voyageur* voyageur)
{
	++cptVoyageursServis;
	totalTempsService += voyageur->dur�eService;
	totalTempsAttente += voyageur->heureD�partPr�vu - (float) voyageur->heureArriv�e - (float) voyageur->dur�eService;

	avgTempsService = totalTempsService / (float) cptVoyageursServis;
	avgTempsAttente = totalTempsAttente / (float) cptVoyageursServis;
}

/***
* Afficher les stats
*/
void afficherStats()
{
	std::cout << std::setw(22) << "Voyageurs servis    :" << cptVoyageursServis			<< setprecision(0) << endl
			  << std::setw(22) << "Temps moyen Service :" << nearbyint(avgTempsService) << " minutes." << std::endl
			  << std::setw(22) << "Temps moyen Attente :" << nearbyint(avgTempsAttente) << " minutes." << std::endl << std::endl;
}