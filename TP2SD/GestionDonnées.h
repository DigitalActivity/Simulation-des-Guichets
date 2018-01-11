/***
* GestionVotages.h : Contient les donn�es et les d�clarations des fonctions pour g�rer les voyageurs.
*				-  struct Voyageur
*				-  enum �v�nement
*				- TrouverFilePlusCourte()
*				- Ins�rerEnOrdreDansListe�v�nements()
*				- afficherList�v�nements()
*				- afficherLesGuichets()
*				- engendrerArriv�e()
*				- enregistrerArriv�e()
*				- engendrerD�part()
*				- enregistrerD�part()
* Commentaires dans les d�finitions dans le fichier GestionVoyageurs.cpp
*/

#ifndef GESTIONDONN�ES
#define GESTIONDONN�ES

#include <iostream> // in, out stream
#include <iomanip>  // Pr�cision
#include <queue>	// Simuler une file d'attente (Guichet).
#include <list>		// List Ev�nements.
#include <array>	// Tableau en senquence taille fixe. contiendra les Guichts
#include "GestionHeures.h"

using namespace std;

// Constantes
const unsigned int NB_GUICHETS		 = 5; // Changer pour n'importe quel nombre de guichets � simuler
const unsigned int NB_MAX_�V�NEMENTS = NB_GUICHETS + 1;

// Evenement types: 2 Types possibles
enum �v�nement { Arriv�e, D�part };

// Voyageur Struct
struct Voyageur {
	unsigned int heureArriv�e;			// L'heure d'arriv�e d'un voyageur
	unsigned int heureD�partPr�vu;		// L'heure de d�part pr�vue
	unsigned int dur�eService;			// La dur�e du service
	�v�nement	 �v�nement;				// Le type d'�venement (Arriv�e,D�part)
	unsigned int num�roFile;			// Le num�ro de file
};

// typedefs : noms de type plus significatifs utilis�s dans GestionVoyageures.cpp pour Faciliter la l�cture du programme.
typedef array<queue<Voyageur>, NB_GUICHETS>	Guichets;
typedef list<Voyageur>						Liste�v�nements;

// Fonctions
bool		 operator<					( const Voyageur& a, const Voyageur& b); // (operator<) de comparaison des voyageurs selon date�v�nement
void		 engendrerArriv�e			( Liste�v�nements* list�v�nements );				// ins�rt dans list�v�nements + Incremente l'horloge
void		 enregistrerArriv�e			( Voyageur* voyageur, Guichets* guichets );	// ins�rt dans FilePlusCourte + G�n�rer tempsService1�15
void		 engendrerD�part			( Voyageur* v, Liste�v�nements* list�v�nements );	// ins�rt dans list�v�nements
void		 enregistrerD�part			( Voyageur* voyageur, Guichets* p_guichets );	// calculer temps final + supprimer de la file
unsigned int TrouverFilePlusCourte		( const Guichets* guichets);
void Ins�rerEnOrdreDansListe�v�nements	( const Voyageur* voyageur, Liste�v�nements* list�v�nements );
void		 afficherList�v�nements		( const Liste�v�nements* list�v�nements );
void		 afficherLesGuichets		( Guichets guichets ); // par valeur pour ne pas d�truire les files originales pendant l'affichage.

#endif