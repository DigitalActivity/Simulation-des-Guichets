#include "GestionDonn�es.h"
using namespace std;

/***
* operator< pour comparer les voyageurs selon heureEvenement
*/
bool operator<(const Voyageur& a, const Voyageur& b)
{
	unsigned int aHeureEvenement = (a.�v�nement == �v�nement::Arriv�e ? a.heureArriv�e : a.heureD�partPr�vu);
	unsigned int bHeureEvenement = (b.�v�nement == �v�nement::Arriv�e ? b.heureArriv�e : b.heureD�partPr�vu);
	if (aHeureEvenement < bHeureEvenement)
		return true;

	return false;
}

/***
* Engendrer l'arriv�e d'un nouveau voyageur.
*/
void engendrerArriv�e(Liste�v�nements* p_list�v�nements)
{
	Voyageur v	= Voyageur();
	v.heureArriv�e		= GESTIONHEURES::HeureMilitaire::horloge().G�n�rerHeureArriv�e(); // horloge += nb Al�atoire entre 1 et 3

	if (v.heureArriv�e > HEURE_FIN_OPERATIONS) // Ajuster l'arriv�e du dernier voyageur.
		v.heureArriv�e  = HEURE_FIN_OPERATIONS;

	v.�v�nement			= �v�nement::Arriv�e;
	v.dur�eService		= 0; // G�n�r�e � l'enregistrement d'une Arriv�e
	v.heureD�partPr�vu	= 0; // Estim�e pendant l'engendrement d'un d�part, Calcul� � l'enregistrement d'un d�part.
	v.num�roFile		= 0; // d�fini pendant le traitement

	Ins�rerEnOrdreDansListe�v�nements(&v, p_list�v�nements);
}

/***
* Enregistrer une Arriv�e
*/
void enregistrerArriv�e(Voyageur* p_voyageur, Guichets* p_guichets)
{
	p_voyageur->dur�eService	= HeureMilitaire::horloge().G�n�rerTempsService(); // dur�eService Al�atoire entre 1 et 15;
	p_voyageur->num�roFile		= TrouverFilePlusCourte(p_guichets); // Trouver la file la plus courte
	p_guichets->at(p_voyageur->num�roFile).push(*p_voyageur);  // ins�rer le voyageur dans la file (queue) la plus courte.
}

/***
* Engendrer le d�part d'un voyageur.
*/
void engendrerD�part(Voyageur* v, Liste�v�nements* p_list�v�nements)
{
	v->�v�nement		= �v�nement::D�part;
	v->heureD�partPr�vu = HeureMilitaire::horloge().G�n�rerHeureD�part(v->dur�eService);
	Ins�rerEnOrdreDansListe�v�nements(v, p_list�v�nements);
}

/***
* Enregistrer un D�part
*/
void enregistrerD�part(Voyageur* p_voyageur, Guichets*	p_guichets)
{	// Enlever le voyageur de la file (queue)
	p_guichets->at(p_voyageur->num�roFile).pop();
}

/***
* Trouver la file la plus courte
*/
unsigned int TrouverFilePlusCourte(const Guichets* p_guichets)
{
	unsigned int filePlusCourte = 0; // Par d�faut, la premi�re file est consid�r�e la plus courte.

	for (unsigned int i = 0; i < NB_GUICHETS - 1; ++i)		// pour chaque file (queue)
		if (p_guichets->at(i).size() > p_guichets->at(i + 1).size())		// Si la file_suivante est plus courte
			filePlusCourte = i + 1;							// fileplusCourte == file_suivante

	return filePlusCourte;
}

/***
* Ins�rer en ordre dans la liste d'�v�nements
*/
void Ins�rerEnOrdreDansListe�v�nements(const Voyageur* p_voyageur, Liste�v�nements* p_list�v�nements)
{
	if (p_list�v�nements->empty())
	{	// ins�rer au d�but
		p_list�v�nements->push_front(*p_voyageur);
		return;
	}

	for (Liste�v�nements::iterator it = p_list�v�nements->begin(); it != p_list�v�nements->end(); ++it)
		if (*p_voyageur < *it) // Notre op�rateur < surd�fini pour comparer (Voyageur.heureEvenement < Voyageur.heureEvenement)
		{
			p_list�v�nements->insert(it, *p_voyageur); // ins�rer � la bonne position
			return;
		}

	// Si aucune heure dans la liste n'est plus grande, ins�rer l'�v�nement � la fin.
	p_list�v�nements->push_back(*p_voyageur);
}

/***
* Afficher la liste d'�v�nements
*/
void afficherList�v�nements(const Liste�v�nements* p_list�v�nements)
{
	if (p_list�v�nements->empty())
		return;

	cout << "Liste d\'�v�nements (tri�e par heure d'�v�nement):" << endl << endl;
	for (Liste�v�nements::const_iterator it = p_list�v�nements->begin(); it != p_list�v�nements->end(); ++it)
		cout << "�v�nement : " << setw(8) << (it->�v�nement == �v�nement::Arriv�e ? "Arriv�e" : "D�part")
			 << setw(6) << (it->�v�nement == �v�nement::Arriv�e ? it->heureArriv�e : it->heureD�partPr�vu)
			 << " file #" << setw(0) << it->num�roFile << endl;
}

/***
* Afficher les files de chaque guichet
*  Parameters : p_guichets : Copie des guichets. copie afin d'afficher les files sans d�truire les donn�es
*/
void afficherLesGuichets(Guichets p_guichets)
{
	for (unsigned short int i = 0; i < p_guichets.size(); ++i)
	{
		cout << "Guichet #" << i << " : ";
		while (!p_guichets[i].empty()) // affichage pour un guichet
		{
			cout << (p_guichets[i].front().�v�nement == �v�nement::Arriv�e ? "<-[Arr" : "<-[D�p")
				 << setw(5) << (p_guichets[i].front().�v�nement == �v�nement::Arriv�e ? p_guichets[i].front().heureArriv�e : p_guichets[i].front().heureD�partPr�vu)
				 << " serv :" << setw(3) << p_guichets[i].front().dur�eService << "]";
			p_guichets[i].pop();
		}
		cout << endl; // Fin affichage pour un guichet
	}
	cout << endl;	 // Fin affichage pour tous les guichets
}
