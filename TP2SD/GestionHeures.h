/***
* GestionHeures.h : Horloge en Heure-Militaire avec les méthodes necessaires à la géstion d'heure.
*				- getTime : Return l'heure en format militaire. 900 1000 1030 1110
*				- GénérerHeureArrivée : Générer Arrivée + Incrémenter l'horloge
*				- GénérerTempsService : Générer Temps service
*				- GénérerHeureDépart  : Générer Heure Départ
*/

#ifndef GESTIONHEURES
#define GESTIONHEURES

// Constantes
const unsigned int HEURE_DEBUT_OPERATIONS	= 900;
const unsigned int HEURE_FIN_OPERATIONS		= 1100;

/***
* class Singleton HeureMilitaire : l'horloge du programme. 
*/
class HeureMilitaire {
private :
	// Contient le nombre total de minutes depuit 00:00. (ex : 9:00 = 9 * 60)
	unsigned int tempsEnMinutes = HEURE_DEBUT_OPERATIONS * 60 / 100; // initialisé à  9 * 60 = 540
	void		 ajouterMinutes(int minutes); // Ajouter des minutes.

public :
	static HeureMilitaire& horloge(); // Singleton horloge. L'unique instance de l'HeureMilitaire. Permet d'avoir le control sur l'heure.
									  // Source (introduction à la programmation avec iso c++. Singletons, p428, MM).
	
	unsigned int getTime();  // return l'heure en format militaire. ex : 900, 930, 1015, 1030, 1100,...
	static unsigned int GénérerHeureArrivée();
	static unsigned int GénérerTempsService();
	static unsigned int GénérerHeureDépart(const unsigned int& duréeService);
	void afficherTempsMilitaire(unsigned int nbMinutes = horloge().tempsEnMinutes); // affiche le temps actuel si aucun parametre n'est passé.
};

#endif