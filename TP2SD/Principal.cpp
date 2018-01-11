/***
* Programme : Simulation de guichets de la gare centrale. 
*				Performe une Simulation de service dans le but de d�t�rminer le temps moyen de service.
*
* commentaires   : - Changer GESTIONDONN�ES::NB_GUICHETS par un nombre de guichets � simuler.
*				 : - GESTIONHEURES::HeureMilitaire.horloge() est un singleton, l'unique horloge du programme.
*				 : - L'engendrement de nouveaux voyageurs s'arr�te � HEURE_FIN, le traitement des voyageurs d�ja
*						dans les files continu. Permet de traiter tous les voyageurs attendants le d�part.
*
* Projet	: TP2 Structures de donn�es.
*
* Par		: Rabdi_Younes - Szbechek McGurk
*/ 
#include "GestionDonn�es.h"  // Contient les fonctions pour g�rer les voyageurs. 
#include "Stats.h"
#include <string>
using namespace std;

// Conteneurs :
	/* Liste d'�v�nements, tri�e par heure d'arriv�e ou d�part pr�vu d'un voyageur.
		 - Avantages list : Acces et ins�rtion rapides � n'importe quelle position. 
							sans d�calage ou r�allocation des autres �l�ments. */
list<Voyageur> g_list�v�nements;

	/* array avec 5 Guichets/Files. array<T, size> conteneur en s�quence de taille fixe. 
		 - Avantages array: Simple et rapide (a le m�me effet qu'un tableau ordinaire ex : queue<Voyageur> guichets[5])
		 - Avantages queue: Pour chaque guichets[i], ins�rtion possible seulement � la fin, traitement � partir de la t�te. 
							Parfait pour simuler une file d'attente */
array<queue<Voyageur>, NB_GUICHETS>	g_guichets;

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL)); /* Permet d'initier random avec des valeurs differentes � chaque ex�cution du programme, 
					      donne des successions de r�sultats plus al�atoires. */

	// Initialisation des guichets avec des files vides.
	g_guichets.fill(queue<Voyageur>());

	// Initialisation de la liste d'�v�nements avec la premi�re arriv�e (Voyageur)
	GESTIONDONN�ES::engendrerArriv�e(&g_list�v�nements); // GESTIONDONN�ES:: pas necessaire. juste pour mieux visualliser l'ensemble

	// D�but des op�rations. Aucun voyageur ne sera oubli�, ni engendr� apr�s HEURE_FIN
	while (!g_list�v�nements.empty())
	{
		HeureMilitaire::horloge().afficherTempsMilitaire();
		STATS::afficherStats();
		GESTIONDONN�ES::afficherLesGuichets(g_guichets); // la seule fois ou les param�tres sont transmis par valeur. pour afficher les files sans les detruire	
		GESTIONDONN�ES::afficherList�v�nements(&g_list�v�nements);

		cout << endl << string(45, '=') << endl;
		system("pause");
		system("cls");


		// Copier le premier �l�ment de la liste d'�v�nements.
		Voyageur voyageur = g_list�v�nements.front();	

		// Supprimer le premier �l�ment de la liste d'�v�nements.	
		g_list�v�nements.pop_front();							

		if (voyageur.�v�nement == �v�nement::Arriv�e) 
		{ // ARRIV�E
			// Enregistrer arriv�e
			GESTIONDONN�ES::enregistrerArriv�e(&voyageur, &g_guichets);

			// Si seul �l�menent de la file, engendrer son D�part.
			if (g_guichets[voyageur.num�roFile].size() == 1)
				GESTIONDONN�ES::engendrerD�part(&voyageur, &g_list�v�nements);

			/* Engendrer la prochaine arriv�e. 
			   seulement si horloge < HEURE_FERMETURE  ET  liste�v�nements < NB_MAX_�V�NEMENTS */
			if (HeureMilitaire::horloge().getTime() < HEURE_FIN_OPERATIONS && g_list�v�nements.size() < NB_MAX_�V�NEMENTS)
				GESTIONDONN�ES::engendrerArriv�e(&g_list�v�nements);
		}
		else 
		{ // D�PART
			// Enregistrer D�part
			GESTIONDONN�ES::enregistrerD�part(&voyageur, &g_guichets);

			// Calculer le temps moyen d'attente, le temps moyen de service
			STATS::appliquerStats(&voyageur); 

			// Engendrer le d�part du prochain voyageur dans la file.
			if (!g_guichets[voyageur.num�roFile].empty())
				GESTIONDONN�ES::engendrerD�part(&g_guichets[voyageur.num�roFile].front(), &g_list�v�nements);
		}
	} // fin des op�rations.

	STATS::afficherStats();
	GESTIONDONN�ES::afficherLesGuichets(g_guichets); // la seule fonction ou les param�tres sont transmis par valeur. pour afficher les files (queue) sans les detruire
	GESTIONDONN�ES::afficherList�v�nements(&g_list�v�nements);
	system("pause");
} // Fin Main