/***
* GestionVotages.h : Contient les données et les déclarations des fonctions pour gérer les voyageurs.
*				-  struct Voyageur
*				-  enum Événement
*				- TrouverFilePlusCourte()
*				- InsérerEnOrdreDansListeÉvénements()
*				- afficherListÉvénements()
*				- afficherLesGuichets()
*				- engendrerArrivée()
*				- enregistrerArrivée()
*				- engendrerDépart()
*				- enregistrerDépart()
* Commentaires dans les définitions dans le fichier GestionVoyageurs.cpp
*/

#ifndef GESTIONDONNÉES
#define GESTIONDONNÉES

#include <iostream> // in, out stream
#include <iomanip>  // Précision
#include <queue>	// Simuler une file d'attente (Guichet).
#include <list>		// List Evénements.
#include <array>	// Tableau en senquence taille fixe. contiendra les Guichts
#include "GestionHeures.h"

using namespace std;

// Constantes
const unsigned int NB_GUICHETS		 = 5; // Changer pour n'importe quel nombre de guichets à simuler
const unsigned int NB_MAX_ÉVÉNEMENTS = NB_GUICHETS + 1;

// Evenement types: 2 Types possibles
enum Événement { Arrivée, Départ };

// Voyageur Struct
struct Voyageur {
	unsigned int heureArrivée;			// L'heure d'arrivée d'un voyageur
	unsigned int heureDépartPrévu;		// L'heure de départ prévue
	unsigned int duréeService;			// La durée du service
	Événement	 événement;				// Le type d'évenement (Arrivée,Départ)
	unsigned int numéroFile;			// Le numéro de file
};

// typedefs : noms de type plus significatifs utilisés dans GestionVoyageures.cpp pour Faciliter la lécture du programme.
typedef array<queue<Voyageur>, NB_GUICHETS>	Guichets;
typedef list<Voyageur>						ListeÉvénements;

// Fonctions
bool		 operator<					( const Voyageur& a, const Voyageur& b); // (operator<) de comparaison des voyageurs selon dateÉvénement
void		 engendrerArrivée			( ListeÉvénements* listÉvénements );				// insért dans listÉvénements + Incremente l'horloge
void		 enregistrerArrivée			( Voyageur* voyageur, Guichets* guichets );	// insért dans FilePlusCourte + Générer tempsService1à15
void		 engendrerDépart			( Voyageur* v, ListeÉvénements* listÉvénements );	// insért dans listÉvénements
void		 enregistrerDépart			( Voyageur* voyageur, Guichets* p_guichets );	// calculer temps final + supprimer de la file
unsigned int TrouverFilePlusCourte		( const Guichets* guichets);
void InsérerEnOrdreDansListeÉvénements	( const Voyageur* voyageur, ListeÉvénements* listÉvénements );
void		 afficherListÉvénements		( const ListeÉvénements* listÉvénements );
void		 afficherLesGuichets		( Guichets guichets ); // par valeur pour ne pas détruire les files originales pendant l'affichage.

#endif