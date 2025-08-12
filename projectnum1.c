#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct date{
	int j ;
	int m ;
	int a ;
}date;
typedef struct match{
	date d ;
	char adv[50] ;
	char lieu[50] ;
}match;
typedef struct joueur{
	char nom[50] ;
	int num ;
	int age ;
	int nb ;
	match M[100] ;
}joueur;
typedef struct equipe{
	joueur J[20] ;
	int cpt ;
}equipe;
joueur creerjoueur(){
	joueur j ;
	printf("Saisir le nom : ") ;
	scanf("%s",j.nom) ;
	printf("Saisir le numero : ") ;
	scanf("%d",&j.num) ;
	printf("Saisir l'age : ") ;
	scanf("%d",&j.age) ;
	j.nb = 0 ;
	return j ;
}
void ajouterjoueurs(equipe *E){
	int N , i ;
	do{
		printf("Saisir nombre des joueurs : ") ;
		scanf("%d",&N) ;
	}while(N<0 || N+E->cpt>20);
	for(i=E->cpt ;i<N+E->cpt ;i++){
		printf("le joueur %d >> \n",i) ;
		E->J[i] = creerjoueur() ;
	}
	E->cpt += N ;
}
match creermatch(){
	match m ;
	printf("Saisir le nom d'equipe adversaire : ") ;
	scanf("%s",m.adv) ;
	printf("Saisir le lieu : ") ;
	scanf("%s",m.lieu) ;
	printf("Saisir la date \n");
	scanf("%d %d %d",&m.d.j,&m.d.m,&m.d.a) ;
	return m ;
}
int recherche(equipe E,char nom[]){
	int i , pos = -1 ;
	for(i=0;i<E.cpt;i++){
		if(strcmp(E.J[i].nom,nom) == 0 )
			pos = i ;
	}
	return pos ;
}
void ajoutermatch(equipe *E,char nom[]){
	int i = recherche(*E,nom) ;
	if(i!=-1){
		E->J[i].M[E->J[i].nb++ ] = creermatch() ; 
	}
	else
		printf("aucun correspondant \n") ;
}

void affichermatch(match m){
	printf("Le nom d'equipe adversaire %s .",m.adv) ;
	printf("le lieu %s .",m.lieu) ;
	printf("la date %d / %d / %d \n",m.d.j,m.d.m,m.d.a) ;
}
void afficherjoueur(joueur j){
	int i ;
	printf("le nom %s \n",j.nom);
	printf("le numero %d \n",j.num) ;
	printf("l'age %d \n",j.age) ;
	printf("liste des matchs joues : \n") ;
	for(i=0;i<j.nb;i++){
		affichermatch(j.M[i]) ;
	}
}
void afficherequipe(equipe E){
	int i ;
	printf("listes des joueur : \n\n");
	for(i=0;i<E.cpt;i++){
		afficherjoueur(E.J[i]) ;
		printf("\n\n") ;
 	}
}

void afficherinfo(equipe E,char nom[]){
	int i , j ;
	i = recherche(E,nom) ; 
	if( i != -1){
		printf("liste des matchs joues : \n") ;
		for(j=0;j<E.J[i].nb;j++){
			affichermatch(E.J[i].M[j]) ;
		}
	}
	else
		printf("aucun correspondant \n") ;
}

void exporter(equipe E,int indicateur){
	FILE *f ;
	int i , j ;
	if (indicateur == 1) 
		f = fopen("Exam.txt","w") ;
	else
		f = fopen("Exam.txt","a") ;
	if(f!=NULL){
		for(i=0;i<E.cpt;i++){
			fprintf(f,"%s %d %d %d\n",E.J[i].nom,E.J[i].num,E.J[i].age,E.J[i].nb) ;
			for(j=0;j<E.J[i].nb;j++){
				fprintf(f,"%s %s %d %d %d\n",E.J[i].M[j].adv,E.J[i].M[j].lieu,E.J[i].M[j].d.j,E.J[i].M[j].d.m,E.J[i].M[j].d.a) ;
			}
		}
		fclose(f) ;
	}
	else
		printf("erreur d'exporter \n") ;
}

void importer(equipe *E){
	FILE *f ;
	int i , j ;
	f = fopen("Exam.txt","r") ;
	if(f!=NULL){
		int i = 0 ;
		while ( !feof(f)){
			fscanf(f,"%s %d %d %d\n",E->J[i].nom,&E->J[i].num,&E->J[i].age,&E->J[i].nb) ;
			for(j=0;j<E->J[i].nb;j++){
				fscanf(f,"%s %s %d %d %d\n",E->J[i].M[j].adv,E->J[i].M[j].lieu,&E->J[i].M[j].d.j,&E->J[i].M[j].d.m,&E->J[i].M[j].d.a) ;
			}
			i++ ;
		}
		E->cpt = i ;
		fclose(f) ;
	}
	else
		printf("erreur d'importer \n") ;
}
int menu(){
	int n ;
	do{
		printf("1 : pour ajouter N joueur \n") ;
		printf("2 : pour ajouter un match \n") ;
		printf("3 : pour afficher la liste \n") ;
		printf("4 : pour afficher les matchs d'un joueur \n") ;
		printf("5 : pour exporter (ecraser le contenu) \n");
		printf("6 : pour exporter (garder le contenu) \n") ;
		printf("7 : pour importer \n");
		printf("8 : pour quitter le programme \n");
		printf("\n\tVotre choix : ") ;
		scanf("%d",&n) ;
 	}while(n<1 || n>8) ;
 	return n ;
}
void main(){
	int n ;
	char nom[50] ;
	equipe E ;
	E.cpt = 0 ;
	do{
		n = menu();
		switch(n){
			case 1 :ajouterjoueurs(&E) ;
					break ;
			case 2 :printf("Saisir le nom de joueur : ") ;
					scanf("%s",nom) ;
					ajoutermatch(&E,nom) ;
					break ;
			case 3 :afficherequipe(E) ;
					break ;
			case 4 :printf("Saisir le nom de joueur : ") ;
					scanf("%s",nom) ;
					afficherinfo(E,nom) ;
					break ;
			case 5 :exporter(E,1) ;
					break ;
			case 6 :exporter(E,0) ;
					break ;
			case 7 :importer(&E);
					break ;
			case 8 :printf("vous etes quitter le programme ");
					break ;
		}
	}while( n != 8);
}