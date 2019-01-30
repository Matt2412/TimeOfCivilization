
#include "Unite.h"




//Constructeur
Unite::Unite(){}

Unite::Unite(int type_Unite2, int ID_Unite2, int posX_Unite2, int posY_Unite2)
{
    switch(type_Unite2)
    {
        case 0: //ville
        PV_Unite = 20;
        ATK_Unite = 5;
        PM_Unite = 0;
        DST_Unite = 0;
        type_Unite = type_Unite2;
        prix_Unite = 0;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Ville";break;

        case 1: //colon
        PV_Unite = 1;
        ATK_Unite = 0;
        PM_Unite = 2;
        DST_Unite =0;
        type_Unite = type_Unite2;
        prix_Unite = 50;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Colon";break;

        case 2: //hoplite
        PV_Unite = 5;
        ATK_Unite = 2;
        PM_Unite = 2;
        DST_Unite =1;
        type_Unite =type_Unite2;
        prix_Unite = 10;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Hoplite";break;

        case 3: //Archer
        PV_Unite = 2;
        ATK_Unite = 1;
        PM_Unite = 1;
        DST_Unite = 4;
        type_Unite = type_Unite2;
        prix_Unite = 15;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Archer";break;

        case 4: //Hussard
        PV_Unite = 10;
        ATK_Unite = 5;
        PM_Unite = 3;
        DST_Unite = 1;
        type_Unite = type_Unite2;
        prix_Unite = 25;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Hussard" ;break;

        case 5: //Canon
        PV_Unite = 5;
        ATK_Unite = 4;
        PM_Unite = 2;
        DST_Unite = 6;
        type_Unite = type_Unite2;
        prix_Unite = 35;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Canon";break;

        case 6: //tank
        PV_Unite = 50;
        ATK_Unite = 20;
        PM_Unite = 5;
        DST_Unite = 1;
        type_Unite = type_Unite2;
        prix_Unite = 150;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Tank";break;

        case 7: //Lance-Missile
        PV_Unite = 20;
        ATK_Unite = 30;
        PM_Unite = 3;
        DST_Unite = 8;
        type_Unite = type_Unite2;
        prix_Unite = 250;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Lance-Missile";
        break;

        case 8: //Bombe atomique
        PV_Unite = 1;
        ATK_Unite = 999;
        PM_Unite = 0;
        DST_Unite = 20;
        type_Unite = type_Unite2;
        prix_Unite = 1000;
        ID_Unite = ID_Unite2;
        posX_Unite = posX_Unite2;
        posY_Unite = posY_Unite2;
        nom_Unite = "Bombe atomique";
        break;
    }
}

    //Destructeur
Unite::~Unite() {cout<<"L'Unite est detruite"<<endl;}

    //Getters
int  Unite::getPV()const{return PV_Unite;}
int  Unite::getATK()const{return ATK_Unite;}
int  Unite::getPM()const{return PM_Unite;}
int  Unite::getDST()const{return DST_Unite;}
int  Unite::gettypeUnite()const{return type_Unite;}
int  Unite::getprix()const{return prix_Unite;}
int  Unite::getuniteID()const{return ID_Unite;}
int  Unite::getposX()const{return posX_Unite;}
int  Unite::getposY()const{return posY_Unite;}
int  Unite::getproprioUnite()const{return proprioUnite_Unite;}
string  Unite::getnomUnite()const{return nom_Unite;}

    //Setters
void  Unite::setPV(const int x){PV_Unite=x;}
void  Unite::setATK(const int x){ATK_Unite=x;}
void  Unite::setPM(const int x){PM_Unite=x;}
void  Unite::setDST(const int x){DST_Unite=x;}
void  Unite::settypeUnite(const int x){type_Unite=x;}
void  Unite::setprix(const int x){prix_Unite=x;}
void  Unite::setuniteID(const int x){ID_Unite=x;}
void  Unite::setposX(const int x){posX_Unite=x;}
void  Unite::setposY(const int x){posY_Unite=x;}
void  Unite::setnomUnite(const string x){nom_Unite=x;}
void  Unite::setproprioUnite(const int x){proprioUnite_Unite=x;}

    /////////////////////////////////////////////////////

//Autres fonctions utiles
void  Unite::Affronter_Unite(Unite* u_Adverse, Case c)
{

    u_Adverse->PV_Unite-=ATK_Unite;
    PV_Unite-=u_Adverse->ATK_Unite;
    cout<<"Attaque!!!!!!!!!!!!!!!!"<<endl;
}

void  Unite::Bombarder_Unite(Unite* u_Adverse,Case c)
{

    u_Adverse->PV_Unite-=ATK_Unite;
    cout<<"Attaque à distance!!!!!!!!!!!!!!!!"<<endl;
}

void  Unite::Fonder_Ville(char action)
{
    switch(action)
    {
        case 'v':
        PV_Unite = 20;
        ATK_Unite = 5;
        PM_Unite = 0;
        DST_Unite = 0;
        type_Unite = 0;
        prix_Unite = 0;
        nom_Unite = "Ville";
        break;
    }
}

void  Unite::Atomiser_Unite(Unite * u_Adverse, Case c)
{
    if(type_Unite==8)
    {

        u_Adverse->PV_Unite-=ATK_Unite;
    }
}



void Unite::Deplacer_Unite(char action,int taille_Horizontale,int taille_Verticale)
{
    bool ok = true;
    do {
            switch(action)
            {
                case 'w':
                if (posY_Unite!=0) //ATTENTION IL FAUT VOIR SI LA FUTURE CASE EST VIDE OU NON
                {
                    posY_Unite-=1;
                    PM_Unite-=1;
                }
                ok = false;
                break;
                case 's':
                if (posY_Unite!= taille_Verticale) //ATTENTION IL FAUT VOIR SI LA FUTURE CASE EST VIDE OU NON
                {
                    posY_Unite+=1;
                    PM_Unite-=1;
                }
                ok = false;
                break;
                case 'a':
                if(posX_Unite!=0) //ATTENTION IL FAUT VOIR SI LA FUTURE CASE EST VIDE OU NON
                {
                    posX_Unite-=1;
                    PM_Unite-=1;
                }
                ok = false;
                break;
                case 'd':
                if(posX_Unite!= taille_Horizontale) //ATTENTION IL FAUT VOIR SI LA FUTURE CASE EST VIDE OU NON
                {
                    posX_Unite+=1;
                    PM_Unite-=1;
                }
                ok = false;
                break;
            }
    }while(ok);
}

void Unite::TestRegression_Unite()
{
    cout<<"Voici le test de regression du module Unite, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree une case et des unites "<<endl;

    Unite * colon0 = new Unite(1,67,1,1);
    Unite * hoplite0 = new Unite(2,22,1,1);
    Unite * archer0 = new Unite(3,89,1,1);
    Unite * bombe0 = new Unite(8,13,1,1);
    Unite * tank1 = new Unite(6,9,2,1);

    Case case0;
    case0.setCaseID(1);
    case0.setDejaOccupe(0);
    case0.setX(1); case0.setY(1);
    Case case1;
    case1.setCaseID(2);
    case1.setDejaOccupe(1);
    case1.setX(2); case1.setY(1);


    cout<<"- void Affronter_Unite(Unite* u_Adverse, Case c) effectue les calculs pour l'assault d'une unite de melee"<<endl;
    cout<<"Les PV du tank avant attaque : "<<tank1->getPV()<<endl;
    hoplite0->Affronter_Unite(tank1, case1);
    cout<<"Les PV du tank apres attaque : "<<tank1->getPV()<<endl;


    cout<<"- void Bombarder_Unite(Unite* u_Adverse, Case c) effectue les calculs pour le bombardement d'une unite de melee"<<endl;
    cout<<"Les PV du tank avant attaque : "<<tank1->getPV()<<endl;
    archer0->Bombarder_Unite(tank1,case1);
    cout<<"Les PV du tank apres attaque : "<<tank1->getPV()<<endl;

    cout<<"- void Atomiser_Unite(Unite * u_Adverse, Case c) effectue les calculs pour l'atomisation d'une ou plusieurs unites"<<endl;
    cout<<"Les PV du tank avant attaque : "<<tank1->getPV()<<endl;
    bombe0->Atomiser_Unite(tank1,case1);
    cout<<"Les PV du tank apres attaque : "<<tank1->getPV()<<endl;


    cout<<"- void Deplacer_Unite(char action,int taille_Horizontale,int taille_Verticale) effectue les calculs pour deplacer une unite a droite"<<endl;
    cout<<"La position de l'archer avant attaque : ( "<<archer0->getposX()<<" , "<<archer0->getposY()<<" )"<<endl;
    archer0->Deplacer_Unite('d',2,1);
    cout<<"La position de l'archer avant attaque : ( "<<archer0->getposX()<<" , "<<archer0->getposY()<<" )"<<endl;


    cout<<"- void Fonder_Ville(char action) transforme un colon en ville"<<endl;
    cout<<"Le nom de l'unite avant fondation : "<<colon0->getnomUnite()<<endl;
    colon0->Fonder_Ville('v');
    cout<<"Le nom de l'unite apres fondation : "<<colon0->getnomUnite()<<endl;

    cout<<"Ceci marque la fin du test de regression du module Unite"<<endl;
    delete colon0; delete hoplite0; delete archer0; delete bombe0; delete tank1;
}









