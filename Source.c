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
/*   Implémentation d'un besoin client: Gestion d'une formation                                           */
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
/*MAX_MATIERES est le nombre de matières possible à insérer dans la formation*/
/*MAX_EPREUVES est le nombre d'épreuves possible à insérer dans la formation*/
/* MAX_ETUDIANTS = 100 est le nombre d'étudiants possible à insérer dans la formation*/
/*NOVALUE est la valeur par défaut lorsqu'il n'y a pas de note pour une épreuve et pour matière donnée*/
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

/*création d'un type uint pour faciliter l'écriture de "unsigned int" par la suite.*/
typedef unsigned int uint;
/*definition d'un type enum Bool avec true et false qui prennent respectivement les valeurs 0 et 1*/
typedef enum { true = 1, false = 0 }Bool;

/*type struct Etudiant
* nom est un char qui représente le nom de l'étudiant
* notes est un tableau qui stock l'ensemble des notes de l'étudiant*/
typedef struct {
	char nom[MAX_CHAR + 1];
	float notes[NB_SEMESTRES * (MAX_MATIERES * MAX_EPREUVES)];
}Etudiant;

/*type struct Epreuve
* nom est un char qui comporte le nom de l'épreuve
*coef est un tableau de float comportant les coefficients de l'épreuve pour chaque UE
*/
typedef struct {
	char nom[MAX_CHAR + 1];
	float coef[MAX_UE];
} Epreuve;

/*type struct Matiere
* nom est un char qui comporte le nom de la matière
* nbEpreuves, uint, est le nombre d'epreuves de la matière
* epreuve est un tableau de struct Epreuve(5max)
*/
typedef struct {
	char nom[MAX_CHAR + 1];
	uint nbEpreuves;
	Epreuve epreuve[MAX_EPREUVES];
}Matiere;

/*type struct Semestre
*nbMatieres, uint, represente le nombre de matière pour un semestre
* matiere est un tableau de struct Matiere (10 max)*/
typedef struct {
	uint nbMatieres;
	Matiere matieres[MAX_MATIERES];
} Semestre;

/*type struct Formation
semestres est un tableau  de struc Semestre (2max)
etudiants est un tableau de struct Etudiant(100max)
 nbrEtudiants est le nombre d'étudiants actuel dans la formation.
*/
typedef struct {
	uint nbUE; // nombre de coef, commun à toutes les épreuvesSemestre semestres[NB_SEMESTRES];
	Semestre semestres[NB_SEMESTRES];
	Etudiant etudiants[MAX_ETUDIANTS];
	uint nbrEtudiants;
} Formation;

/*La fonction Formation1 prend en paramètre un pointeur Formation et vérifie que
le nombre d'UE de la formation et bien situé entre 3 et 6. Elle ne renvoie rien.*/
void Formation1(Formation* numberue);

/*la fonction VerifCoeffs prend en parmètres une structure Formation et un tableau coeff non modifiable.
Elle retourne la somme des valeurs du tableau coeffs dans une variable de type float.*/
float VerifCoeffs(const Formation* Form, const float coeffs[]);

/*La fonction epreuve prend en paramètres un pointeur Formation, un entier, deux variables char et un tableau de float.
elle intègre le nom d'une matière, le nom d'une epreuve et ses coeffs, sous certaines conditions, à la sturcture formation. Elle ne renvoie rien*/
void epreuve(Formation* formation, uint numsem, const char nommat[], const char nomeprv[], const float coeffs[]);

/*La fonction Coefficients prend en paramètres un pointeur vers une structure Formation et un pointeur vers un entier non signé numerosem.
elle verifie pour chaque UE que tous les coefficients de l'UE sont non nuls. Elle ne renvoie rien.*/
void Coefficients(const Formation* formation, uint numerosem);

/*La fonction PrepaForm prend en argument un pointeur de structure Formation.Elle initialise
le nombre de matieres et d'epreuve à zero afin qu'on puisse s'en servir comme indice
et placer les matières,épreuves,étudiants et notes futurs au bon endroit. Elle ne renvoie rien.*/
void PreparForm(Formation* form);

/*La fonction IndNote prends en paramètres trois uint numerosem, j et k
et renvoie l'indice du tableau de notes dans lequel on doit placer la note de l'étudiant
ou l'indice du tableau de notes dans lequel est placé une note*/
int IndNote(uint numerosem, uint j, uint k);

/*La fonction AjoutNote prend en paramètres un pointeur Formation, un uint numerosem, un const char nometudiant
,un const char nommat, un const char nomeprv et un float noteetud. Elle ajoute la note noteetud à l'etudiant nometudiant
pour le semestre numerosem-1 pour l'épreuve nomeprv de la matière nommat. Elle ne renvoie rien*/
void AjoutNote(Formation* form, uint numerosem, const char nometudiant[], const char nommat[], const char nomeprv[], float noteetud);

/*La fonction SemestreValid prends en paramètre un pointeur Formation (non modifié), un uint numerosem et renvoie un Bool
selon si le numerosem est valide ou non,c'est à dire s'il n'est pas égal à NB_SEMESTRES ou à NB_SEMESTRES-1*/
Bool SemestreValid(const Formation* form, const uint numerosem);

/*la fonction Note prend en paramètre un pointeur Formation form, un uint numerosem et un const char nometudiant
et vérifie si l'étudiant nometudiant a une note pour l'ensemble des épreuves du semestre numerosem*/
void Note(const Formation* form, uint numerosem, const char nometudiant[]);

/*La fonction VerifsCoeffsUE prend en paramètres un Pointeur Formtation qu'elle ne modifie pas, ainsi qu'un uint numerosem
,un numero de semestre, et vérifie si les coefficients de chaque UE du semestre numerosem sont corrects ou non en renvoyant
un Bool*/
Bool VerifsCoeffsUE(const Formation* form, uint numerosem);

/*La fonction PlusLongNom prend en paramètres un Pointeur Formtation qu'elle ne modifie pas
, ainsi qu'un uint numerosem,un numero de semestre,
et renvoie la longueur du nom de la matière du semestre de la formation qui a le nom le plus long.
Le mot le plus long par défaut est "Moyennes"*/
uint PlusLongNom(const Formation* form, uint numerosem);

/*La fonction Releve prends en paramètres un pointeur Formation, un uint numerosem, et un nometudiant. 
Elle affiche le relevé de moyenne pour l'étudiant nometudiant et pour le semestre numerosem*/
void Releve(const Formation* formation, uint numerosem, const char nometudiant[]);

void main() {
	char command[MAX_CHAR + 1];

	/*declaration de notre structure formation*/
	Formation formation;
	formation.nbUE = 0;

	/*variable servant à savoir si le nombre d'UE est déjà défini ou non*/
	uint nbdef = 0;

	/*variables pour récupérer les données saisies par l'utilisateur*/
	uint numerosem;
	char nommat[MAX_CHAR + 1];
	char nomeprv[MAX_CHAR + 1];
	float coeffs[MAX_UE];
	char nometudiant[MAX_CHAR];
	float noteetud;

	/*appel de la fonction prepaform afin de mettre le nombre de matières et d'épreuves à zéro
	et de s'en servir comme indices par la suite pour savoir où placer nos epreuves et nos matières*/
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

	/*verification de la validité du numéro de semestre*/
	if (SemestreValid(f,numsem) == false)
	{
		printf("Le numero de semestre est incorrect\n");
		return;
	}

	/*parcours de toutes les matières acquises jusqu'à en trouver une
	qui porte le même nom que celle entrée par l'utilisateur.
	*/
	for (i = 0; i < s->nbMatieres; ++i) {
		Matiere* m = &(s->matieres[i]);
		if (strcmp(nommat, m->nom) == 0) {

			uint j = 0;

			/*On verifie que notre epreuve n'existe pas deja dans la matière,
			sinon, on l'ajoute dans notre matière
			*/
			while (j < m->nbEpreuves && strcmp(nomeprv, m->epreuve[j].nom) != 0)
				++j;

			/*Si j est inferieur à notre nombre d'epreuve, c'est que l'autre condition du while s'est arretée.
			Cela veut dire que nous avons trouvé notre epreuve.*/
			if (j < m->nbEpreuves) {
				printf("Une meme epreuve existe deja\n");
				return;
			}
			/*on commence par vérifier nos coefficients.
			Si le coefficient est négatif, on affiche un message et on quitte la fonction.*/
			for (uint k = 0; k < f->nbUE; ++k) {
				if (coeffs[k] < 0) {
					printf("Au moins un des coefficients est incorrect\n");
					return;
				}
			}
			//appel à verifcoeffs pour vérifier qu'au moins un des coefficients est supérieur à zéro.
			if (VerifCoeffs(f, coeffs) == 0) {
				printf("Au moins un des coefficients est incorrect\n");
				return;
			}
			/*conditions verifiées,
			on ajoute notre epreuve à notre formation pour la matière concernée.*/
			strcpy(m->epreuve[j].nom, nomeprv);
			/*on ajoute 1 à notre nombre d'epreuve pour la matière concernée.*/
			++(m->nbEpreuves);
			for (uint l = 0; l < f->nbUE; ++l) {
				m->epreuve[j].coef[l] = coeffs[l];
			}
			printf("Epreuve ajoutee a la formation\n");
			return;
		}
	}

	/** matière entrée par l'utilisateur ne porte le nom d'aucune des matières déjà acquises.
	on l'ajoute alors à notre formation.
	on ajoute l'épreuve dans cette matière même.*/
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
		/*Sinon, les coeffs sont valides, on ajoute notre première épreuve à notre première matière,
		elle-même ajoutée à notre formation.*/
		strcpy(s->matieres[i].nom, nommat);
		++(s->nbMatieres);
		printf("Matiere ajoutee a la formation\n");

		strcpy(s->matieres[i].epreuve[0].nom, nomeprv);
		(s->matieres[i].nbEpreuves) = 1;
		/*on integre les coefficients à la première epreuve de la première matière de la formation.*/
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
	//verification de la validité du numéro de semestre
	if (SemestreValid(f,numerosem)==false) {
		printf("Le numero de semestre est incorrect\n");
		return;
	}
	//S'il n'y a aucune matière, c'est qu'il n'y a aucune epreuve.
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

	/*verification de la validité du numéro de semestre*/
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
		/*on cherche l'étudiant parmis nos étudiants*/
		Etudiant* etud = &(form->etudiants[a]);
		if (strcmp(nometudiant, etud->nom) == 0) {

			/*parcours des matières*/
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

	/*Si l'étudiant n'existe pas, on l'ajoute à la formation*/
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

	/*validité du numero de semestre*/
	if (SemestreValid(form, numerosem) == false) {
		printf("Le numero de semestre est incorrect\n");
		return;
	}

	uint indnbretudiant = form->nbrEtudiants;
	uint i = 0;

	/*parcours des notes de l'étudiant*/
	for (i = 0; i < indnbretudiant; ++i) {
		Etudiant* etud = &(form->etudiants[i]);
		if (strcmp(nometudiant, etud->nom) == 0) {

			for (uint j = 0; j < s->nbMatieres; ++j) {
				Matiere* m = &(s->matieres[j]);

				for (uint k = 0; k < m->nbEpreuves; ++k) {
					/*si l'étudiant à une note NOVALUE, alors il lui manque une note*/
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
	/*l'étudiant n'exsite pas après le parcours de tous les étudiants*/
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

	//verification de la validité du numéro de semestre
	if (SemestreValid(formation, numerosem) == false) {
		printf("Le numero de semestre est incorrect\n");
		return;
	}

	uint a = 0;
	uint indnbretudiant;
	indnbretudiant = formation->nbrEtudiants;
	Etudiant* etudiant;

	/*on verifie l'existance de l'étuidiant*/
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

	/*verifiaction si l'étudiant à toutes les notes*/
	for (uint j = 0; j < s->nbMatieres; ++j) {
		Matiere* m = &(s->matieres[j]);
		for (uint k = 0; k < m->nbEpreuves; ++k) {
			if (etudiant->notes[IndNote(numerosem - 1, j, k)] == NOVALUE) {
				printf("Il manque au moins une note pour cet etudiant\n");
				return;
			}
		}
	}

	// recherche de la longueur du nom de la matière ayant le nom le plus nom dans le semestre pour les alignements du tableau
	uint pluslongnom = PlusLongNom(formation, numerosem - 1);

	/*affichages des UE avec un espacement du début de l'affichage égal à la longueur du nom le plus long +1 */
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

	/*On parcours les matières*/
	for (uint j = 0; j < s->nbMatieres; ++j) {
		Matiere* matr = &(s->matieres[j]);

		/*l'espace entre le nom de l'épreuve et la prmière note et égal au nombre de caractères de la matière ayant le nom le plus long
		soustrait au nom de la matière affichée +1*/
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
				/*affichage de la moyenne pondérée de la matière pour une UE*/
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