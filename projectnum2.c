#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct {
	int jour;
	int mois;
	int annee;
}date;
typedef struct {
	char nom[20];
	date d;
	char pays;
}str_p;
typedef struct{
	str_p p;
	date demb;
	char fonction[20];
	str_p cojoint;
	int nbre;
	str_p enfant[5];
}str_comm;
typedef struct{
	char rs[20];
	date d_o;
	char address[50];
	int nbrc;
	str_comm comm[20];
}str_agen;
typedef struct{
	char rs[20];
	char rc[20];
	int patente;
	int annee_creation;
	char type_activite[20];
	int chiffre_aff;
	int nbrab;
	str_agen agence[20];
}str_bank;

typedef struct{
	str_bank bank[100];
	int cpt;
}str_gb;

date saisie_date(){
	date d;
	printf("donner le jour: ");
	scanf("%d", &d.jour);
	printf("donner mois: ");
	scanf("%d", &d.mois);
	printf("donner annee: ");
	scanf("%d", &d.annee);
	return d;
}
str_p saisie_personne() {
	str_p p;
	printf("donner le nom: ");
	scanf("%s", p.nom);
	printf("\n donner la date de naissance :");
	p.d = saisie_date();
	printf("donner le pays: ");
	scanf("%s", p.pays);
	return p;
}
str_comm saisie_commerciale() {
	str_comm comm;
	comm.p = saisie_personne();
	comm.demb = saisie_date();
	printf("saisir les informations du cojoint: ");
	comm.cojoint = saisie_personne();
	printf("donner le nombre des enfants: ");
	scanf("%d", &comm.nbre);
	for(int i = 0; i < comm.nbre; i++){
		printf("donner les info de la %d enfant", i+1);
		comm.enfant[i] = saisie_personne();
	}
	printf("donner la fonction de commeriale: ");
	scanf("%s", comm.fonction);
	return comm;
}
str_agen saisie_agence(){
	str_agen a;
	printf("donner la raison sociale: ");
	scanf("%s", a.rs);
	a.d_o = saisie_date();
	printf("donner l'address de l'agence: ");
	scanf("%s", a.address);
	printf("donner le nombre des commercials: ");
	scanf("%s", a.nbrc);
	for(int i = 0; i < a.nbrc; i++)
		a.comm[i] = saisie_commerciale();
	return a;
}
str_bank saisie_bank(){
	str_bank b;
	printf("donner la raison sociale: ");
	scanf("%s", b.rs );
	printf("donner le registre de commerce: ");
	scanf("%s", b.rc );
	printf("donner le numero de patente: ");
	scanf("%d", &b.patente );
	printf("donner l'annee de creation: ");
	scanf("%d", &b.annee_creation );
	printf("donner le type d'activite: ");
	scanf("%s", b.type_activite );
	printf("donner le chiffre d'affaire: ");
	scanf("%d", &b.chiffre_aff );
	printf("donner le nombre des agences a ajouter: ");
	scanf("%d", &b.nbrab);
	for(int i = 0; i < b.nbrab; i++)
		b.agence[i] = saisie_agence();
	return b;
}
void remplir_groupement(str_gb *gp, int n){
	for(int i = gp->cpt; i < gp->cpt + n; i++){
		gp->bank[i] = saisie_bank();
	}
	gp->cpt += n;
}
int trouver_bank(str_gb GB, char RS[]){
	int p = -1;
	for ( int i = 0; i<GB.cpt ; i++){
		if ( strcmp(GB.bank[i].rs, RS) == 0)
		p = i;
	}
	return p;
}

void modifier_bank(str_gb *GB, char RS[], int n){
	int p = trouver_bank(*GB, RS);
	if(p == -1){
		printf("agence introuvable");
	} else {
		int i;
		for(i = 0; i < n; i++){
			GB->bank[p].agence[i] = saisie_agence();
		}
		GB->bank[p].nbrab = n;
	}
}

void afficher_date(date d){
	printf("la date est: %d/%d/%d", d.jour,d.mois,d.annee);
}
void afficher_info(str_p p){
	printf("le nom est: %s", p.nom);
	printf("pays: %s", p.pays);
	afficher_date(p.d);
}
void afficher_comm(str_comm comm){
	afficher_info(comm.p);
	printf("la date d'embauche: ");
	afficher_date(comm.demb);
	printf("la fonction de commerciale est: %s", comm.fonction);
	printf("les info de cojoint: ");
	afficher_info(comm.cojoint);
	int i;
	for(i = 0; i < comm.nbre; i++){
		afficher_info(comm.enfant[i]);
	}
}
void afficher_agence(str_agen a){
	printf("la raison sociale est: %s", a.rs);
	printf("la date d'overture est:");
	afficher_date(a.d_o);
	printf("l'address est: %s", a.address);
	for(int i = 0; i < a.nbrc; i++){
		afficher_comm(a.comm[i]);
	}
}
void afficher_bank(str_bank b){
	printf("la raison sociale est: %s", b.rs);
	printf("la raison commerciale est: %s", b.rc);
	printf("la type d'activite est: %s", b.type_activite);
	printf("l'annee de creation est: %d", b.annee_creation);
	for(int i=0; i < b.nbrab; i++){
		afficher_agence(b.agence[i]);
	}
}
void bank_par_activite(str_gb b, char act[]){
	for(int i = 0; i < b.cpt; i++){
		if(strcmp(b.bank[i].type_activite, act) == 0){
			afficher_bank(b.bank[i]);
		}
	}
}

void afficher_agence_enfant(str_bank b){
	for(int i = 0; i < b.nbrab; i++){
		for(int j = 0; j < b.agence[i].nbrc ;j++ ){
			if(b.agence[i].comm[j].nbre > 3){
				afficher_agence(b.agence[i]);
			}
		}
	}
}

void suppression(str_gb *GB, char RS[]){
	int p = trouver_bank(*GB, RS);
	if (p != -1){
		for(int i = p; i < GB->bank[p].nbrab; i++){
			GB->bank[i] = GB->bank[i+1];
		}
		GB->bank[p].nbrab--;
	}
}

void exporter(str_gb GB){
	FILE *f = NULL;
	f = fopen("exam.txt", "w");
	if(f!= NULL){
		for(int i = 0; i < GB.cpt; i++){
			printf("la raison sociale est: %s la raison commerciale est: %s le numero de patente est: %s l'annee de creation: %d le type d'activite: %s le chiffre d'affaire: %d avec %d agence bancaire", GB.bank[i].rc, GB.bank[i].rs, GB.bank[i].patente, GB.bank[i].annee_creation, GB.bank[i].type_activite, GB.bank[i].chiffre_aff, GB.bank[i].nbrab);
			for (int j = 0; i < GB.bank[i].nbrab; i++){
				// Example: fill in the correct arguments for fprintf
				// fprintf(f, "la raison sociale est: %s la date ouverture est %d/%d/%d l'address est %s", GB.bank[i].agence[j].rs, GB.bank[i].agence[j].d_o.jour, GB.bank[i].agence[j].d_o.mois, GB.bank[i].agence[j].d_o.annee, GB.bank[i].agence[j].address);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	return 0;
}
