/***
* Statistics : Compte le nombre de voyageurs servis et calcule le temps moyen de service et le temps moyen d'attente
*		- appliquerStats(const Voyageur* voyageur) est appelée au départ de chaque voyageur. 
*		- afficherStats : affiche les statistiques sur les données collectionnées
*
*/

#ifndef STATS
#define STATS
#include "GestionDonnées.h"

// Compteurs
static unsigned int cptVoyageursServis; // Nombre de voyageurs servis. (nb Représentatif)
static float		avgTempsService;	// Durée moyenne de service
static float		avgTempsAttente;    // Durée moyenne d'attente : HeureDépart - HeureArrivée - DuréeService
static float		totalTempsService;  // Durée total de service 
static float		totalTempsAttente;  // Durée total d'attente : HeureDépart - HeureArrivée - DuréeService

void appliquerStats(const Voyageur* voyageur);
void afficherStats();

#endif