#include "Stats.h"
#include <cmath> // nearbyint, arrondir en int le plus proche

/***
* Appliquer les stats : Calculer le temps d'attente moyen. et incrémenter le nombre de voyageurs servis
*/
void appliquerStats(const Voyageur* voyageur)
{
	++cptVoyageursServis;
	totalTempsService += voyageur->duréeService;
	totalTempsAttente += voyageur->heureDépartPrévu - (float) voyageur->heureArrivée - (float) voyageur->duréeService;

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