#include "GestionDonnées.h"
using namespace std;

/***
* operator< pour comparer les voyageurs selon heureEvenement
*/
bool operator<(const Voyageur& a, const Voyageur& b)
{
	unsigned int aHeureEvenement = (a.événement == Événement::Arrivée ? a.heureArrivée : a.heureDépartPrévu);
	unsigned int bHeureEvenement = (b.événement == Événement::Arrivée ? b.heureArrivée : b.heureDépartPrévu);
	if (aHeureEvenement < bHeureEvenement)
		return true;

	return false;
}

/***
* Engendrer l'arrivée d'un nouveau voyageur.
*/
void engendrerArrivée(ListeÉvénements* p_listÉvénements)
{
	Voyageur v	= Voyageur();
	v.heureArrivée		= GESTIONHEURES::HeureMilitaire::horloge().GénérerHeureArrivée(); // horloge += nb Aléatoire entre 1 et 3

	if (v.heureArrivée > HEURE_FIN_OPERATIONS) // Ajuster l'arrivée du dernier voyageur.
		v.heureArrivée  = HEURE_FIN_OPERATIONS;

	v.événement			= Événement::Arrivée;
	v.duréeService		= 0; // Générée à l'enregistrement d'une Arrivée
	v.heureDépartPrévu	= 0; // Estimée pendant l'engendrement d'un départ, Calculé à l'enregistrement d'un départ.
	v.numéroFile		= 0; // défini pendant le traitement

	InsérerEnOrdreDansListeÉvénements(&v, p_listÉvénements);
}

/***
* Enregistrer une Arrivée
*/
void enregistrerArrivée(Voyageur* p_voyageur, Guichets* p_guichets)
{
	p_voyageur->duréeService	= HeureMilitaire::horloge().GénérerTempsService(); // duréeService Aléatoire entre 1 et 15;
	p_voyageur->numéroFile		= TrouverFilePlusCourte(p_guichets); // Trouver la file la plus courte
	p_guichets->at(p_voyageur->numéroFile).push(*p_voyageur);  // insérer le voyageur dans la file (queue) la plus courte.
}

/***
* Engendrer le départ d'un voyageur.
*/
void engendrerDépart(Voyageur* v, ListeÉvénements* p_listÉvénements)
{
	v->événement		= Événement::Départ;
	v->heureDépartPrévu = HeureMilitaire::horloge().GénérerHeureDépart(v->duréeService);
	InsérerEnOrdreDansListeÉvénements(v, p_listÉvénements);
}

/***
* Enregistrer un Départ
*/
void enregistrerDépart(Voyageur* p_voyageur, Guichets*	p_guichets)
{	// Enlever le voyageur de la file (queue)
	p_guichets->at(p_voyageur->numéroFile).pop();
}

/***
* Trouver la file la plus courte
*/
unsigned int TrouverFilePlusCourte(const Guichets* p_guichets)
{
	unsigned int filePlusCourte = 0; // Par défaut, la première file est considérée la plus courte.

	for (unsigned int i = 0; i < NB_GUICHETS - 1; ++i)		// pour chaque file (queue)
		if (p_guichets->at(i).size() > p_guichets->at(i + 1).size())		// Si la file_suivante est plus courte
			filePlusCourte = i + 1;							// fileplusCourte == file_suivante

	return filePlusCourte;
}

/***
* Insérer en ordre dans la liste d'événements
*/
void InsérerEnOrdreDansListeÉvénements(const Voyageur* p_voyageur, ListeÉvénements* p_listÉvénements)
{
	if (p_listÉvénements->empty())
	{	// insérer au début
		p_listÉvénements->push_front(*p_voyageur);
		return;
	}

	for (ListeÉvénements::iterator it = p_listÉvénements->begin(); it != p_listÉvénements->end(); ++it)
		if (*p_voyageur < *it) // Notre opérateur < surdéfini pour comparer (Voyageur.heureEvenement < Voyageur.heureEvenement)
		{
			p_listÉvénements->insert(it, *p_voyageur); // insérer à la bonne position
			return;
		}

	// Si aucune heure dans la liste n'est plus grande, insérer l'événement à la fin.
	p_listÉvénements->push_back(*p_voyageur);
}

/***
* Afficher la liste d'événements
*/
void afficherListÉvénements(const ListeÉvénements* p_listÉvénements)
{
	if (p_listÉvénements->empty())
		return;

	cout << "Liste d\'événements (triée par heure d'événement):" << endl << endl;
	for (ListeÉvénements::const_iterator it = p_listÉvénements->begin(); it != p_listÉvénements->end(); ++it)
		cout << "Événement : " << setw(8) << (it->événement == Événement::Arrivée ? "Arrivée" : "Départ")
			 << setw(6) << (it->événement == Événement::Arrivée ? it->heureArrivée : it->heureDépartPrévu)
			 << " file #" << setw(0) << it->numéroFile << endl;
}

/***
* Afficher les files de chaque guichet
*  Parameters : p_guichets : Copie des guichets. copie afin d'afficher les files sans détruire les données
*/
void afficherLesGuichets(Guichets p_guichets)
{
	for (unsigned short int i = 0; i < p_guichets.size(); ++i)
	{
		cout << "Guichet #" << i << " : ";
		while (!p_guichets[i].empty()) // affichage pour un guichet
		{
			cout << (p_guichets[i].front().événement == Événement::Arrivée ? "<-[Arr" : "<-[Dép")
				 << setw(5) << (p_guichets[i].front().événement == Événement::Arrivée ? p_guichets[i].front().heureArrivée : p_guichets[i].front().heureDépartPrévu)
				 << " serv :" << setw(3) << p_guichets[i].front().duréeService << "]";
			p_guichets[i].pop();
		}
		cout << endl; // Fin affichage pour un guichet
	}
	cout << endl;	 // Fin affichage pour tous les guichets
}
