/***
* Programme : Simulation de guichets de la gare centrale. 
*				Performe une Simulation de service dans le but de détérminer le temps moyen de service.
*
* commentaires   : - Changer GESTIONDONNÉES::NB_GUICHETS par un nombre de guichets à simuler.
*				 : - GESTIONHEURES::HeureMilitaire.horloge() est un singleton, l'unique horloge du programme.
*				 : - L'engendrement de nouveaux voyageurs s'arrête à HEURE_FIN, le traitement des voyageurs déja
*						dans les files continu. Permet de traiter tous les voyageurs attendants le départ.
*
* Projet	: TP2 Structures de données.
*
* Par		: Rabdi_Younes - Szbechek McGurk
*/ 
#include "GestionDonnées.h"  // Contient les fonctions pour gérer les voyageurs. 
#include "Stats.h"
#include <string>
using namespace std;

// Conteneurs :
	/* Liste d'événements, triée par heure d'arrivée ou départ prévu d'un voyageur.
		 - Avantages list : Acces et insértion rapides à n'importe quelle position. 
							sans décalage ou réallocation des autres éléments. */
list<Voyageur> g_listÉvénements;

	/* array avec 5 Guichets/Files. array<T, size> conteneur en séquence de taille fixe. 
		 - Avantages array: Simple et rapide (a le même effet qu'un tableau ordinaire ex : queue<Voyageur> guichets[5])
		 - Avantages queue: Pour chaque guichets[i], insértion possible seulement à la fin, traitement à partir de la tête. 
							Parfait pour simuler une file d'attente */
array<queue<Voyageur>, NB_GUICHETS>	g_guichets;

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL)); /* Permet d'initier random avec des valeurs differentes à chaque exécution du programme, 
					      donne des successions de résultats plus aléatoires. */

	// Initialisation des guichets avec des files vides.
	g_guichets.fill(queue<Voyageur>());

	// Initialisation de la liste d'événements avec la première arrivée (Voyageur)
	GESTIONDONNÉES::engendrerArrivée(&g_listÉvénements); // GESTIONDONNÉES:: pas necessaire. juste pour mieux visualliser l'ensemble

	// Début des opérations. Aucun voyageur ne sera oublié, ni engendré après HEURE_FIN
	while (!g_listÉvénements.empty())
	{
		HeureMilitaire::horloge().afficherTempsMilitaire();
		STATS::afficherStats();
		GESTIONDONNÉES::afficherLesGuichets(g_guichets); // la seule fois ou les paramètres sont transmis par valeur. pour afficher les files sans les detruire	
		GESTIONDONNÉES::afficherListÉvénements(&g_listÉvénements);

		cout << endl << string(45, '=') << endl;
		system("pause");
		system("cls");


		// Copier le premier élément de la liste d'événements.
		Voyageur voyageur = g_listÉvénements.front();	

		// Supprimer le premier élément de la liste d'événements.	
		g_listÉvénements.pop_front();							

		if (voyageur.événement == Événement::Arrivée) 
		{ // ARRIVÉE
			// Enregistrer arrivée
			GESTIONDONNÉES::enregistrerArrivée(&voyageur, &g_guichets);

			// Si seul élémenent de la file, engendrer son Départ.
			if (g_guichets[voyageur.numéroFile].size() == 1)
				GESTIONDONNÉES::engendrerDépart(&voyageur, &g_listÉvénements);

			/* Engendrer la prochaine arrivée. 
			   seulement si horloge < HEURE_FERMETURE  ET  listeÉvénements < NB_MAX_ÉVÉNEMENTS */
			if (HeureMilitaire::horloge().getTime() < HEURE_FIN_OPERATIONS && g_listÉvénements.size() < NB_MAX_ÉVÉNEMENTS)
				GESTIONDONNÉES::engendrerArrivée(&g_listÉvénements);
		}
		else 
		{ // DÉPART
			// Enregistrer Départ
			GESTIONDONNÉES::enregistrerDépart(&voyageur, &g_guichets);

			// Calculer le temps moyen d'attente, le temps moyen de service
			STATS::appliquerStats(&voyageur); 

			// Engendrer le départ du prochain voyageur dans la file.
			if (!g_guichets[voyageur.numéroFile].empty())
				GESTIONDONNÉES::engendrerDépart(&g_guichets[voyageur.numéroFile].front(), &g_listÉvénements);
		}
	} // fin des opérations.

	STATS::afficherStats();
	GESTIONDONNÉES::afficherLesGuichets(g_guichets); // la seule fonction ou les paramètres sont transmis par valeur. pour afficher les files (queue) sans les detruire
	GESTIONDONNÉES::afficherListÉvénements(&g_listÉvénements);
	system("pause");
} // Fin Main