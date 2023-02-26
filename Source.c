/* ****************************************************************************************************** */
/*                                                                                                        */
/*                                                     :::++++++++::    :::        :::   :::+++::+++:::   */
/*    SAE_S1_01.c									   :::        :::   :::        :::         ::         */
/*                                                     :::        :::   :::        :::         ++         */
/*    By: Mouhamed Nadir and Paul                      :::++++++++::    :::        :::         ++         */
/*                                                     :::++++++++::    :::        :::         ++         */
/*  Created: 2022/10/01 by Bsikri with perigault       :::        :::   :::        :::         ++         */
/*                                                     :::        :::   :::        :::         ::         */
/*	                                                   :::++++++++::    :::++++++++:::         ::		  */
/*   Impl�mentation d'un besoin client: Gestion d'une formation                                           */
/* ****************************************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)
#pragma warning(disable: 6202)

/*NB_SEMESTRES represente le nombre de semestres de la formation*/
/*MIN_UE et MAX_UE representent le nombre d'UE minimal et maximal de la formation*/
/*MAX_MATIERES est le nombre de mati�res possible � ins�rer dans la formation*/
/*MAX_EPREUVES est le nombre d'�preuves possible � ins�rer dans la formation*/
/* MAX_ETUDIANTS = 100 est le nombre d'�tudiants possible � ins�rer dans la formation*/
/*NOVALUE est la valeur par d�faut lorsqu'il n'y a pas de note pour une �preuve et pour mati�re donn�e*/
enum {
	NB_SEMESTRES = 2,
	MIN_UE = 3,
	MAX_UE = 6,
	MAX_MATIERES = 10,
	MAX_EPREUVES = 5,
	MAX_ETUDIANTS = 100,
	MAX_CHAR = 30,
	NOVALUE = -1,
	CONSTANTE = 50,
	CONSTANTE2 = 5,
};

/*cr�ation d'un type uint pour faciliter l'�criture de "unsigned int" par la suite.*/
typedef unsigned int uint;
/*definition d'un type enum Bool avec true et false qui prennent respectivement les valeurs 0 et 1*/
typedef enum { true = 1, false = 0 }Bool;

/*type struct Etudiant
* nom est un char qui repr�sente le nom de l'�tudiant
* notes est un tableau qui stock l'ensemble des notes de l'�tudiant*/
typedef struct {
	char nom[MAX_CHAR + 1];
	float notes[NB_SEMESTRES * (MAX_MATIERES * MAX_EPREUVES)];
}Etudiant;

/*type struct Epreuve
* nom est un char qui comporte le nom de l'�preuve
*coef est un tableau de float comportant les coefficients de l'�preuve pour chaque UE
*/
typedef struct {
	char nom[MAX_CHAR + 1];
	float coef[MAX_UE];
} Epreuve;

/*type struct Matiere
* nom est un char qui comporte le nom de la mati�re
* nbEpreuves, uint, est le nombre d'epreuves de la mati�re
* epreuve est un tableau de struct Epreuve(5max)
*/
typedef struct {
	char nom[MAX_CHAR + 1];
	uint nbEpreuves;
	Epreuve epreuve[MAX_EPREUVES];
}Matiere;

/*type struct Semestre
*nbMatieres, uint, represente le nombre de mati�re pour un semestre
* matiere est un tableau de struct Matiere (10 max)*/
typedef struct {
	uint nbMatieres;
	Matiere matieres[MAX_MATIERES];
} Semestre;

/*type struct Formation
semestres est un tableau  de struc Semestre (2max)
etudiants est un tableau de struct Etudiant(100max)
 nbrEtudiants est le nombre d'�tudiants actuel dans la formation.
*/
typedef struct {
	uint nbUE; // nombre de coef, commun � toutes les �preuvesSemestre semestres[NB_SEMESTRES];
	Semestre semestres[NB_SEMESTRES];
	Etudiant etudiants[MAX_ETUDIANTS];
	uint nbrEtudiants;
} Formation;

/*La fonction Formation1 prend en param�tre un pointeur Formation et v�rifie que
le nombre d'UE de la formation et bien situ� entre 3 et 6. Elle ne renvoie rien.*/
void Formation1(Formation* numberue);

/*la fonction VerifCoeffs prend en parm�tres une structure Formation et un tableau coeff non modifiable.
Elle retourne la somme des valeurs du tableau coeffs dans une variable de type float.*/
float VerifCoeffs(const Formation* Form, const float coeffs[]);

/*La fonction epreuve prend en param�tres un pointeur Formation, un entier, deux variables char et un tableau de float.
elle int�gre le nom d'une mati�re, le nom d'une epreuve et ses coeffs, sous certaines conditions, � la sturcture formation. Elle ne renvoie rien*/
void epreuve(Formation* formation, uint numsem, const char nommat[], const char nomeprv[], const float coeffs[]);

/*La fonction Coefficients prend en param�tres un pointeur vers une structure Formation et un pointeur vers un entier non sign� numerosem.
elle verifie pour chaque UE que tous les coefficients de l'UE sont non nuls. Elle ne renvoie rien.*/
void Coefficients(const Formation* formation, uint numerosem);

/*La fonction PrepaForm prend en argument un pointeur de structure Formation.Elle initialise
le nombre de matieres et d'epreuve � zero afin qu'on puisse s'en servir comme indice
et placer les mati�res,�preuves,�tudiants et notes futurs au bon endroit. Elle ne renvoie rien.*/
void PreparForm(Formation* form);

/*La fonction IndNote prends en param�tres trois uint numerosem, j et k
et renvoie l'indice du tableau de notes dans lequel on doit placer la note de l'�tudiant
ou l'indice du tableau de notes dans lequel est plac� une note*/
int IndNote(uint numerosem, uint j, uint k);

/*La fonction AjoutNote prend en param�tres un pointeur Formation, un uint numerosem, un const char nometudiant
,un const char nommat, un const char nomeprv et un float noteetud. Elle ajoute la note noteetud � l'etudiant nometudiant
pour le semestre numerosem-1 pour l'�preuve nomeprv de la mati�re nommat. Elle ne renvoie rien*/
void AjoutNote(Formation* form, uint numerosem, const char nometudiant[], const char nommat[], const char nomeprv[], float noteetud);

/*La fonction SemestreValid prends en param�tre un pointeur Formation (non modifi�), un uint numerosem et renvoie un Bool
selon si le numerosem est valide ou non,c'est � dire s'il n'est pas �gal � NB_SEMESTRES ou � NB_SEMESTRES-1*/
Bool SemestreValid(const Formation* form, const uint numerosem);

/*la fonction Note prend en param�tre un pointeur Formation form, un uint numerosem et un const char nometudiant
et v�rifie si l'�tudiant nometudiant a une note pour l'ensemble des �preuves du semestre numerosem*/
void Note(const Formation* form, uint numerosem, const char nometudiant[]);

/*La fonction VerifsCoeffsUE prend en param�tres un Pointeur Formtation qu'elle ne modifie pas, ainsi qu'un uint numerosem
,un numero de semestre, et v�rifie si les coefficients de chaque UE du semestre numerosem sont corrects ou non en renvoyant
un Bool*/
Bool VerifsCoeffsUE(const Formation* form, uint numerosem);

/*La fonction PlusLongNom prend en param�tres un Pointeur Formtation qu'elle ne modifie pas
, ainsi qu'un uint numerosem,un numero de semestre,
et renvoie la longueur du nom de la mati�re du semestre de la formation qui a le nom le plus long.
Le mot le plus long par d�faut est "Moyennes"*/
uint PlusLongNom(const Formation* form, uint numerosem);

/*La fonction Releve prends en param�tres un pointeur Formation, un uint numerosem, et un nometudiant. 
Elle affiche le relev� de moyenne pour l'�tudiant nometudiant et pour le semestre numerosem*/
void Releve(const Formation* formation, uint numerosem, const char nometudiant[]);

void main() {
	char command[MAX_CHAR + 1];

	/*declaration de notre structure formation*/
	Formation formation;
	formation.nbUE = 0;

	/*variable servant � savoir si le nombre d'UE est d�j� d�fini ou non*/
	uint nbdef = 0;

	/*variables pour r�cup�rer les donn�es saisies par l'utilisateur*/
	uint numerosem;
	char nommat[MAX_CHAR + 1];
	char nomeprv[MAX_CHAR + 1];
	float coeffs[MAX_UE];
	char nometudiant[MAX_CHAR];
	float noteetud;

	/*appel de la fonction prepaform afin de mettre le nombre de mati�res et d'�preuves � z�ro
	et de s'en servir comme indices par la suite pour savoir o� placer nos epreuves et nos mati�res*/
	PreparForm(&formation);

	do {
		scanf("%s", command);
		if (strcmp(command, "formation") == 0) {
			//commande 2
			nbdef = formation.nbUE;
			if (nbdef != 0) {
				printf("Le nombre d'UE est deja defini\n");
			}
			else {
				scanf("%u", &formation.nbUE);
				Formation1(&formation);
			}
		}
		else if (strcmp(command, "epreuve") == 0) {
			//commande3
			if (formation.nbUE == 0) {
				printf("Le nombre d'UE n'est pas defini\n");
			}
			else {
				//variables pour la commande3

				scanf("%u %s %s", &numerosem, &nommat, &nomeprv);
				for (unsigned int i = 0; i < formation.nbUE; ++i) {
					scanf("%f", &coeffs[i]);
				}
				epreuve(&formation, numerosem, nommat, nomeprv, coeffs);
			}
		}
		else if (strcmp(command, "coefficients") == 0) {
			//commande4
			if (formation.nbUE == 0) {
				printf("Le nombre d'UE n'est pas defini\n");
			}
			else {
				uint numerosem;
				scanf("%u", &numerosem);
				Coefficients(&formation, numerosem);
			}
		}//fin commande 4
		else if (strcmp(command, "note") == 0) {
			//commande 5
			if (formation.nbUE == 0) {
				printf("Le nombre d'UE n'est pas defini\n");
			}
			else {
				scanf("%u %s %s %s %f", &numerosem, &nometudiant, &nommat, &nomeprv, &noteetud);
				AjoutNote(&formation, numerosem, nometudiant, nommat, nomeprv, noteetud);
			}
		}
		else if (strcmp(command, "notes") == 0) {
			//commande 6
			if (formation.nbUE == 0) {
				printf("Le nombre d'UE n'est pas defini\n");
			}
			else {
				scanf("%u", &numerosem);
				scanf("%s", &nometudiant);

				Note(&formation, numerosem, nometudiant);
			}
		}
		else if (strcmp(command, "releve") == 0) {
			//commande 7
			if (formation.nbUE == 0) {
				printf("Le nombre d'UE n'est pas defini\n");
			}
			else {
				scanf("%u", &numerosem);
				scanf("%s", &nometudiant);

				Releve(&formation, numerosem, nometudiant);
			}
		}
	} while (strcmp(command, "exit") != 0);/* Commande 1, fait quitter le programme.*/
}

Bool SemestreValid(const Formation* form, const uint numerosem) {
	Bool bool = true;
	if (numerosem < NB_SEMESTRES - 1 || numerosem > NB_SEMESTRES) {
		bool = false;
	}
	return bool;
}

void PreparForm(Formation* form) {
	for (uint i = 0; i < NB_SEMESTRES; ++i) {
		form->semestres[i].nbMatieres = 0;
	}

	for (uint j = 0; j < NB_SEMESTRES; ++j) {
		for (uint k = 0; k < MAX_MATIERES; ++k) {
			form->semestres[j].matieres[k].nbEpreuves = 0;
		}
	}
	form->nbrEtudiants = 0;

	for (uint l = 0; l < MAX_ETUDIANTS; ++l) {
		for (uint m = 0; m < NB_SEMESTRES * (MAX_MATIERES * MAX_EPREUVES); ++m) {
			form->etudiants[l].notes[m] = NOVALUE;
		}
	}
}

void Formation1(Formation* formation) {
	if (formation->nbUE < MIN_UE || formation->nbUE > MAX_UE) {
		printf("Le nombre d'UE est incorrect\n");
		formation->nbUE = 0;
	}
	else {
		printf("Le nombre d'UE est defini\n");
	}
}

float VerifCoeffs(const Formation* Form, const float coeffs[]) {
	float somcoeffs = 0.0;
	for (uint l = 0; l < Form->nbUE; ++l) {
		somcoeffs += coeffs[l];
	}
	return somcoeffs;
}

void epreuve(Formation* f, uint numsem, const char nommat[], const char nomeprv[], const float coeffs[])
{
	Semestre* s = &(f->semestres[numsem - 1]);
	uint i;

	/*verification de la validit� du num�ro de semestre*/
	if (SemestreValid(f,numsem) == false)
	{
		printf("Le numero de semestre est incorrect\n");
		return;
	}

	/*parcours de toutes les mati�res acquises jusqu'� en trouver une
	qui porte le m�me nom que celle entr�e par l'utilisateur.
	*/
	for (i = 0; i < s->nbMatieres; ++i) {
		Matiere* m = &(s->matieres[i]);
		if (strcmp(nommat, m->nom) == 0) {

			uint j = 0;

			/*On verifie que notre epreuve n'existe pas deja dans la mati�re,
			sinon, on l'ajoute dans notre mati�re
			*/
			while (j < m->nbEpreuves && strcmp(nomeprv, m->epreuve[j].nom) != 0)
				++j;

			/*Si j est inferieur � notre nombre d'epreuve, c'est que l'autre condition du while s'est arret�e.
			Cela veut dire que nous avons trouv� notre epreuve.*/
			if (j < m->nbEpreuves) {
				printf("Une meme epreuve existe deja\n");
				return;
			}
			/*on commence par v�rifier nos coefficients.
			Si le coefficient est n�gatif, on affiche un message et on quitte la fonction.*/
			for (uint k = 0; k < f->nbUE; ++k) {
				if (coeffs[k] < 0) {
					printf("Au moins un des coefficients est incorrect\n");
					return;
				}
			}
			//appel � verifcoeffs pour v�rifier qu'au moins un des coefficients est sup�rieur � z�ro.
			if (VerifCoeffs(f, coeffs) == 0) {
				printf("Au moins un des coefficients est incorrect\n");
				return;
			}
			/*conditions verifi�es,
			on ajoute notre epreuve � notre formation pour la mati�re concern�e.*/
			strcpy(m->epreuve[j].nom, nomeprv);
			/*on ajoute 1 � notre nombre d'epreuve pour la mati�re concern�e.*/
			++(m->nbEpreuves);
			for (uint l = 0; l < f->nbUE; ++l) {
				m->epreuve[j].coef[l] = coeffs[l];
			}
			printf("Epreuve ajoutee a la formation\n");
			return;
		}
	}

	/** mati�re entr�e par l'utilisateur ne porte le nom d'aucune des mati�res d�j� acquises.
	on l'ajoute alors � notre formation.
	on ajoute l'�preuve dans cette mati�re m�me.*/
	if (i == s->nbMatieres) {
		if (VerifCoeffs(f, coeffs) == 0) {
			printf("Au moins un des coefficients est incorrect\n");
			return;
		}
		for (uint k = 0; k < f->nbUE; ++k) {
			if (coeffs[k] < 0) {
				printf("Au moins un des coefficients est incorrect\n");
				return;
			}
		}
		/*Sinon, les coeffs sont valides, on ajoute notre premi�re �preuve � notre premi�re mati�re,
		elle-m�me ajout�e � notre formation.*/
		strcpy(s->matieres[i].nom, nommat);
		++(s->nbMatieres);
		printf("Matiere ajoutee a la formation\n");

		strcpy(s->matieres[i].epreuve[0].nom, nomeprv);
		(s->matieres[i].nbEpreuves) = 1;
		/*on integre les coefficients � la premi�re epreuve de la premi�re mati�re de la formation.*/
		for (uint l = 0; l < f->nbUE; ++l) {
			s->matieres[i].epreuve[0].coef[l] = coeffs[l];
		}
		printf("Epreuve ajoutee a la formation\n");
		return;
	}
}

void Coefficients(const Formation* f, uint numerosem) {
	Semestre* s = &(f->semestres[numerosem - 1]);
	float somcoefue = 0.;
	//verification de la validit� du num�ro de semestre
	if (SemestreValid(f,numerosem)==false) {
		printf("Le numero de semestre est incorrect\n");
		return;
	}
	//S'il n'y a aucune mati�re, c'est qu'il n'y a aucune epreuve.
	if (s->nbMatieres == 0) {
		printf("Le semestre ne contient aucune epreuve\n");
		return;
	}
	if (VerifsCoeffsUE(f, numerosem - 1) == false) {
		printf("Les coefficients de ce semestre sont incorrects\n");
		return;
	}
}

int IndNote(uint numerosem, uint j, uint k) {
	int indtabnote = CONSTANTE * numerosem + CONSTANTE2 * j + k;
	return indtabnote;
}

void AjoutNote(Formation* form, uint numerosem, const char nometudiant[], const char nommat[], const char nomeprv[], float noteetud) {

	Semestre* s = &(form->semestres[numerosem - 1]);
	const float MIN_NOTE = 0.f, MAX_NOTE = 20.f;

	/*verification de la validit� du num�ro de semestre*/
	if (SemestreValid(form, numerosem) == false){
		printf("Le numero de semestre est incorrect\n");
		return;
	}
	/*verification de la note*/
	if (noteetud < MIN_NOTE || noteetud > MAX_NOTE) {
		printf("Note incorrecte\n");
		return;
	}

	/*declaration de variables utiles afin de
	le nombre de notes ou le nombre d'etudiant par exemple*/
	uint a = 0;
	uint i = 0;
	uint j = 0;
	uint indnbretudiant = form->nbrEtudiants;

	for (a = 0; a < indnbretudiant; ++a) {
		/*on cherche l'�tudiant parmis nos �tudiants*/
		Etudiant* etud = &(form->etudiants[a]);
		if (strcmp(nometudiant, etud->nom) == 0) {

			/*parcours des mati�res*/
			for (i = 0; i < s->nbMatieres; ++i) {
				Matiere* m = &(s->matieres[i]);
				if (strcmp(nommat, m->nom) == 0) {

					while (j < m->nbEpreuves && strcmp(nomeprv, m->epreuve[j].nom) != 0)
						++j;
					if (j < m->nbEpreuves) {
						if (etud->notes[IndNote(numerosem - 1, i, j)] != NOVALUE) {
							printf("Une note est deja definie pour cet etudiant\n");
							return;
						}
						else {
							etud->notes[IndNote(numerosem - 1, i, j)] = noteetud;
							printf("Note ajoutee a l'etudiant\n");
							return;
						}
					}
					printf("Epreuve inconnue\n");
					return;
				}
			}
			printf("Matiere inconnue\n");
			return;
		}
	}

	/*Si l'�tudiant n'existe pas, on l'ajoute � la formation*/
	if (a == indnbretudiant) {
		Etudiant* etudi = &(form->etudiants[a]);
		uint k;
		for (k = 0; k < s->nbMatieres; ++k) {
			Matiere* mat = &(s->matieres[k]);
			if (strcmp(nommat, mat->nom) == 0) {

				uint l = 0;
				while (l < mat->nbEpreuves && strcmp(nomeprv, mat->epreuve[l].nom) != 0)
					++l;
				if (l < mat->nbEpreuves) {
					strcpy(etudi->nom, nometudiant);
					++(form->nbrEtudiants);
					printf("Etudiant ajoute a la formation\n");

					etudi->notes[IndNote(numerosem - 1, k, l)] = noteetud;
					printf("Note ajoutee a l'etudiant\n");
					return;
				}
				printf("Epreuve inconnue\n");
				return;
			}
		}
		printf("Matiere inconnue\n");
		return;
	}
}

void Note(const Formation* form, uint numerosem, const char nometudiant[]) {

	Semestre* s = &(form->semestres[numerosem - 1]);

	/*validit� du numero de semestre*/
	if (SemestreValid(form, numerosem) == false) {
		printf("Le numero de semestre est incorrect\n");
		return;
	}

	uint indnbretudiant = form->nbrEtudiants;
	uint i = 0;

	/*parcours des notes de l'�tudiant*/
	for (i = 0; i < indnbretudiant; ++i) {
		Etudiant* etud = &(form->etudiants[i]);
		if (strcmp(nometudiant, etud->nom) == 0) {

			for (uint j = 0; j < s->nbMatieres; ++j) {
				Matiere* m = &(s->matieres[j]);

				for (uint k = 0; k < m->nbEpreuves; ++k) {
					/*si l'�tudiant � une note NOVALUE, alors il lui manque une note*/
					if (etud->notes[IndNote(numerosem - 1, j, k)] == NOVALUE) {
						printf("Il manque au moins une note pour cet etudiant\n");
						return;
					}

				}
			}
			printf("Notes correctes\n");
			return;
		}
	}
	/*l'�tudiant n'exsite pas apr�s le parcours de tous les �tudiants*/
	if (i == indnbretudiant) {
		printf("Etudiant inconnu\n");
		return;
	}
}

Bool VerifsCoeffsUE(const Formation* form, uint numerosem) {
	Bool bool = true;
	Semestre* s = &(form->semestres[numerosem]);
	float somcoefue = 0.0;
	for (uint i = 0; i < form->nbUE; ++i) {
		for (uint j = 0; j < s->nbMatieres; ++j) {
			Matiere* mat = &(s->matieres[j]);
			for (uint k = 0; k < mat->nbEpreuves; ++k) {
				Epreuve* epr = &(mat->epreuve[k]);
				somcoefue += epr->coef[i];
			}
		}
		if (somcoefue == 0) {
			bool = false;
			return bool;
		}
		somcoefue = 0.0;


	}
	return bool;
}

uint PlusLongNom(const Formation* form, uint numerosem) {
	const char* Moyenne = "Moyennes";
	uint lenmax = strlen(Moyenne);
	Semestre* s = &(form->semestres[numerosem]);
	for (uint i = 0; i < s->nbMatieres; ++i) {
		Matiere* mat = &(s->matieres[i]);
		if (strlen(mat->nom) >= lenmax) {
			lenmax = strlen(mat->nom);
		}

	}
	return lenmax;
}

void Releve(const Formation* formation, uint numerosem, const char nometudiant[]) {
	Semestre* s = &(formation->semestres[numerosem - 1]);

	//verification de la validit� du num�ro de semestre
	if (SemestreValid(formation, numerosem) == false) {
		printf("Le numero de semestre est incorrect\n");
		return;
	}

	uint a = 0;
	uint indnbretudiant;
	indnbretudiant = formation->nbrEtudiants;
	Etudiant* etudiant;

	/*on verifie l'existance de l'�tuidiant*/
	for (a = 0; a < indnbretudiant; ++a) {
		if (strcmp(nometudiant, formation->etudiants[a].nom) == 0) {
			break;

		}
	}
	if (a == indnbretudiant) {
		printf("Etudiant inconnu\n");
		return;
	}
	etudiant = &(formation->etudiants[a]);

	/*on verifie si les coefficients du semestre sont corrects*/
	if (VerifsCoeffsUE(formation, numerosem - 1) == false) {
		printf("Les coefficients de ce semestre sont incorrects\n");
		return;
	}

	/*verifiaction si l'�tudiant � toutes les notes*/
	for (uint j = 0; j < s->nbMatieres; ++j) {
		Matiere* m = &(s->matieres[j]);
		for (uint k = 0; k < m->nbEpreuves; ++k) {
			if (etudiant->notes[IndNote(numerosem - 1, j, k)] == NOVALUE) {
				printf("Il manque au moins une note pour cet etudiant\n");
				return;
			}
		}
	}

	// recherche de la longueur du nom de la mati�re ayant le nom le plus nom dans le semestre pour les alignements du tableau
	uint pluslongnom = PlusLongNom(formation, numerosem - 1);

	/*affichages des UE avec un espacement du d�but de l'affichage �gal � la longueur du nom le plus long +1 */
	printf("%*s", pluslongnom + 1, "");
	for (int u = 0; u < formation->nbUE; ++u) {
		if (u == 0) {
			printf(" UE%d  ", u + 1);
		}
		else if (u == (formation->nbUE) - 1) {
			printf("UE%d ", u + 1);
		}
		else
			printf("UE%d  ", u + 1);
	}
	printf("\n");

	float moypond = 0.0, totalnotes = 0.0, sommecoeffs = 0.0;

	/*On parcours les mati�res*/
	for (uint j = 0; j < s->nbMatieres; ++j) {
		Matiere* matr = &(s->matieres[j]);

		/*l'espace entre le nom de l'�preuve et la prmi�re note et �gal au nombre de caract�res de la mati�re ayant le nom le plus long
		soustrait au nom de la mati�re affich�e +1*/
		uint strmatr = strlen(matr->nom);
		uint espace = pluslongnom - strmatr + 1;
		printf("%s%*s", matr->nom, espace, "");

		for (uint k = 0; k < formation->nbUE; ++k) {
			for (uint l = 0; l < matr->nbEpreuves; l++)
			{
				totalnotes += (etudiant->notes[IndNote(numerosem - 1, j, l)] * matr->epreuve[l].coef[k]);
				sommecoeffs += matr->epreuve[l].coef[k];
			}
			if (sommecoeffs == 0) {
				printf("  ND ");
			}
			else {
				/*affichage de la moyenne pond�r�e de la mati�re pour une UE*/
				moypond = totalnotes / sommecoeffs;
				if (moypond >= 10.0)
					printf("%.1f ", floorf(moypond * 10) / 10);
				else
					printf(" %.1f ", floorf(moypond * 10) / 10);
				totalnotes = 0.0;
				sommecoeffs = 0.0;
			}
		}
		printf("\n");
	}

	float moyUEtotal = 0.0, notesUEtotal = 0.0, somcoefUEtotal = 0.0;
	printf("--\n");
	const char* Moyenne = "Moyennes";
	uint strmoy = strlen(Moyenne);
	uint espace2 = (pluslongnom - strmoy) + 1;
	printf("%s%*s", Moyenne, espace2, "");

	for (uint k = 0; k < formation->nbUE; ++k) {
		for (uint j = 0; j < s->nbMatieres; ++j) {
			Matiere* matr = &(s->matieres[j]);
			for (uint l = 0; l < matr->nbEpreuves; l++) {
				notesUEtotal += (etudiant->notes[IndNote(numerosem - 1, j, l)] * matr->epreuve[l].coef[k]);
				somcoefUEtotal += matr->epreuve[l].coef[k];


			}
		}
		moyUEtotal = notesUEtotal / somcoefUEtotal;
		if (moyUEtotal >= 10.0) {
			printf("%.1f ", floorf(moyUEtotal * 10) / 10);
		}
		else {
			printf(" %.1f ", floorf(moyUEtotal * 10) / 10);
		}
		notesUEtotal = 0.0;
		somcoefUEtotal = 0.0;
	}
	printf("\n");
}