/***
* Statistics : Compte le nombre de voyageurs servis et calcule le temps moyen de service et le temps moyen d'attente
*		- appliquerStats(const Voyageur* voyageur) est appel�e au d�part de chaque voyageur. 
*		- afficherStats : affiche les statistiques sur les donn�es collectionn�es
*
*/

#ifndef STATS
#define STATS
#include "GestionDonn�es.h"

// Compteurs
static unsigned int cptVoyageursServis; // Nombre de voyageurs servis. (nb Repr�sentatif)
static float		avgTempsService;	// Dur�e moyenne de service
static float		avgTempsAttente;    // Dur�e moyenne d'attente : HeureD�part - HeureArriv�e - Dur�eService
static float		totalTempsService;  // Dur�e total de service 
static float		totalTempsAttente;  // Dur�e total d'attente : HeureD�part - HeureArriv�e - Dur�eService

void appliquerStats(const Voyageur* voyageur);
void afficherStats();

#endif