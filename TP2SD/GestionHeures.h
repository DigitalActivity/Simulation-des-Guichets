/***
* GestionHeures.h : Horloge en Heure-Militaire avec les m�thodes necessaires � la g�stion d'heure.
*				- getTime : Return l'heure en format militaire. 900 1000 1030 1110
*				- G�n�rerHeureArriv�e : G�n�rer Arriv�e + Incr�menter l'horloge
*				- G�n�rerTempsService : G�n�rer Temps service
*				- G�n�rerHeureD�part  : G�n�rer Heure D�part
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
	unsigned int tempsEnMinutes = HEURE_DEBUT_OPERATIONS * 60 / 100; // initialis� �  9 * 60 = 540
	void		 ajouterMinutes(int minutes); // Ajouter des minutes.

public :
	static HeureMilitaire& horloge(); // Singleton horloge. L'unique instance de l'HeureMilitaire. Permet d'avoir le control sur l'heure.
									  // Source (introduction � la programmation avec iso c++. Singletons, p428, MM).
	
	unsigned int getTime();  // return l'heure en format militaire. ex : 900, 930, 1015, 1030, 1100,...
	static unsigned int G�n�rerHeureArriv�e();
	static unsigned int G�n�rerTempsService();
	static unsigned int G�n�rerHeureD�part(const unsigned int& dur�eService);
	void afficherTempsMilitaire(unsigned int nbMinutes = horloge().tempsEnMinutes); // affiche le temps actuel si aucun parametre n'est pass�.
};

#endif