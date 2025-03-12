#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000//nr table maxim

//nu merge define-ul asa
/*
#define ♟ p
#define ♞ n
#define ♝ b
#define ♜ r
#define ♛ q
#define ♚ k
#define ♙ P
#define ♘ N
#define ♗ B
#define ♖ R
#define ♕ Q
#define ♔ K
*/

typedef struct patrat
{
    unsigned int piesa:3;//gol-0 pion-1 cal-2 nebun-3 tura-4 regina-5 regele-6
    unsigned int culoare:2;//gol-2 alb-0 negru-1
    unsigned int pozitia_i:3;//posibil cam useless momentan
    unsigned int pozitia_j:3;//posibil cam useless momentan
    unsigned int valoarea:21;//gol-0 pion-1 cal-3 nebun-3 tura-5 regina-9 regele-(2^21)-1=2097151
}patrat;

void clearr(int n)
{
    for(int i=0;i<n;i++)
    {
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");
    }
}

void meniu()
{
    printf("Alege optiunea: \n0.Iesire\n1.Creeare tabla introdusa manual\n2.Afisare toate tablele\n3.Creeare tabla de inceput joc\n4.incepe jocul de la o tabla din cele create\nOPTIUNEA: ");
}

void eroare()
{
    printf("\nSomething went wrong!\n");
}

void instructions()
{
    printf("\nNIMIC: O sau o(nu 0)\nPION: P sau p\nCAL: N sau n\nNEBUN: B sau b\nTURA: R sau r\nREGINA: Q sau q\nREGELE: K sau k\n\n");
}

int valid_nebun(int n, patrat Tabla[n][n], int i0,int j0, int ix,int jx)// sa nu sara peste piese
{//4 variante:dreapta-sus stanga-jos dreapta-jos stanga-sus
    if(ix>i0&&jx>j0)//dreapta-sus
    {
        int i=i0+1,j=j0+1;
        while(i<ix&&j<jx)
        {
            if(Tabla[i][j].piesa) return 0;//piesa encountered
            i++;
            j++;
        }
    }
    if(ix<i0&&jx<j0)//stanga-jos
    {
        int i=i0-1,j=j0-1;
        while(i>ix&&j>jx)
        {
            if(Tabla[i][j].piesa) return 0;//piesa encountered
            i--;
            j--;
        }
    }
    if(ix>i0&&jx<j0)//dreapta-jos
    {
        int i=i0+1,j=j0-1;
        while(i<ix&&j>jx)
        {
            if(Tabla[i][j].piesa) return 0;//piesa encountered
            i++;
            j--;
        }
    }
    if(ix<i0&&jx>j0)//stanga-sus
    {
        int i=i0-1,j=j0+1;
        while(i>ix&&j<jx)
        {
            if(Tabla[i][j].piesa) return 0;//piesa encountered
            i--;
            j++;
        }
    }
    return 1;
}

int valid_tura(int n, patrat Tabla[n][n], int i0,int j0, int ix,int jx)// sa nu sara peste piese
{
    if(jx==j0){
    if(i0>ix)
    {
        for(int i=i0+1;i<ix;i++)
        {
            if(Tabla[i][j0].piesa) return 0;//exista o piesa pe drum
        }
    }
    if(i0<ix)
    {
        for(int i=ix+1;i<i0;i++)
        {
            if(Tabla[i][j0].piesa) return 0;//exista piesa pe drum
        }
    }
    }

    if(i0==ix)
    {
        if(j0>jx)
    {
        for(int j=j0+1;j<jx;j++)
        {
            if(Tabla[i0][j].piesa) return 0;//exista o piesa pe drum
        }
    }
    if(j0<jx)
    {
        for(int j=jx+1;j<j0;j++)
        {
            if(Tabla[i0][j].piesa) return 0;//exista piesa pe drum
        }
    }
    }
    return 1;//nu am gasit probleme
}

int isincheck(int n, patrat Tabla[n][n],int cine_muta,int ikw,int jkw,int ikb,int jkb)
{
    //return 0;//il voi comenta cand voi repara cu certitudine functia
    switch (cine_muta)
    {
    case 0://alb
        //cal: if((ix==i0+1&&jx==j0-2)||                                                                                                              (ix==i0+2&&jx==j0-1)||                                                                                                                       (ix==i0+2&&jx==j0+1)||                                                                                                                     (ix==i0+1&&jx==j0+2)||                                                                                                                       (ix==i0-1&&jx==j0+2)||                                                                                                                      (ix==i0-2&&jx==j0+1)||                                                                                                                      (ix==i0-2&&jx==j0-1)||                                                                                                                       (ix==i0-1&&jx==j0-2))
        if((ikw+1<8&&jkw-2<8&&ikw+1>0&&jkw-2>0&&Tabla[ikw+1][jkw-2].piesa==3&&Tabla[ikw+1][jkw-2].culoare!=cine_muta&&Tabla[ikw+1][jkw-2].culoare!=2)||(ikw+2<8&&jkw-1<8&&ikw+2>0&&jkw-1>0&&Tabla[ikw+2][jkw-1].piesa==3&&Tabla[ikw+2][jkw-1].culoare!=cine_muta&&Tabla[ikw+2][jkw-1].culoare!=2)||(ikw+2<8&&jkw+1<8&&ikw+2>0&&jkw+1>0&&Tabla[ikw+2][jkw+1].piesa==3&&Tabla[ikw+2][jkw+1].culoare!=cine_muta&&Tabla[ikw+2][jkw+1].culoare!=2)||(ikw+1<8&&jkw+2<8&&ikw+1>0&&jkw+2>0&&Tabla[ikw+1][jkw+2].piesa==3&&Tabla[ikw+1][jkw+2].culoare!=cine_muta&&Tabla[ikw+1][jkw+2].culoare!=2)||(ikw-1<8&&jkw+2<8&&ikw-1>0&&jkw+2>0&&Tabla[ikw-1][jkw+2].piesa==3&&Tabla[ikw-1][jkw+2].culoare!=cine_muta&&Tabla[ikw-1][jkw+2].culoare!=2)||(ikw-2<8&&jkw+1<8&&ikw-2>0&&jkw+1>0&&Tabla[ikw-2][jkw+1].piesa==3&&Tabla[ikw-2][jkw+1].culoare!=cine_muta&&Tabla[ikw-2][jkw+1].culoare!=2)||(ikw-2<8&&jkw-1<8&&ikw-2>0&&jkw-1>0&&Tabla[ikw-2][jkw-1].piesa==3&&Tabla[ikw-2][jkw-1].culoare!=cine_muta&&Tabla[ikw-2][jkw-1].culoare!=2)||(ikw-1<8&&jkw-2<8&&ikw-1>0&&jkw-2>0&&Tabla[ikw-1][jkw-2].piesa==3&&Tabla[ikw-1][jkw-2].culoare!=cine_muta&&Tabla[ikw-1][jkw-2].culoare!=2)) return 1;
        //tura(+regina): if((i0==ix||j0==jx)&&valid_tura(n,Tabla,i0,j0,ix,jx))
        if(ikw+1<n){
        for(int i=ikw+1;i<n;i++)
        {
            if(Tabla[i][jkw].piesa)//daca intampinam o piesa(nu va mai trebui sa verificam daca e gol patratul cu tabla...==2)
            {
                if((Tabla[i][jkw].piesa==4||Tabla[i][jkw].piesa==5)&&Tabla[i][jkw].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        if(ikw-1>=0){
        for(int i=ikw-1;i>=0;i--)
        {
            if(Tabla[i][jkw].piesa)//daca intampinam o piesa
            {
                if((Tabla[i][jkw].piesa==4||Tabla[i][jkw].piesa==5)&&Tabla[i][jkw].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        if(jkw+1<n){
        for(int j=jkw+1;j<n;j++)
        {
            if(Tabla[ikw][j].piesa)//daca intampinam o piesa
            {
                if((Tabla[ikw][j].piesa==4||Tabla[ikw][j].piesa==5)&&Tabla[ikw][j].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        if(jkw-1>=0){
        for(int j=jkw-1;j>=0;j--)
        {
            if(Tabla[ikw][j].piesa)//daca intampinam o piesa
            {
                if((Tabla[ikw][j].piesa==4||Tabla[ikw][j].piesa==5)&&Tabla[ikw][j].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        //nebun(+regina): if((i0+j0==ix+jx||i0-j0==ix-jx)&&valid_nebun(n,Tabla,i0,j0,ix,jx))
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(valid_nebun(n,Tabla,ikw,jkw,i,j))//daca gaseste o piesa conectata in relatie directa nebun cu regele returneaza 1, sper, altfel iar as coda ca la tura, desi si acolo cred ca mergea asa
                {
                    if((i+j==ikw+jkw||i-j==ikw-jkw)&&Tabla[i][j].culoare!=cine_muta&&Tabla[i][j].culoare!=2&&(Tabla[i][j].piesa==3||Tabla[i][j].piesa==5)) return 1;
                }
            }
        }
        //pion negru(cel alb nu ne va ataca)
        if((Tabla[ikw+1][jkw+1].piesa==1&&Tabla[ikw+1][jkw+1].culoare!=cine_muta)||(Tabla[ikw+1][jkw-1].piesa==1&&Tabla[ikw+1][jkw-1].culoare!=cine_muta)) return 1;
        break;
    case 1://negru
        //cal: if((ix==i0+1&&jx==j0-2)||                                                                                                              (ix==i0+2&&jx==j0-1)||                                                                                                                       (ix==i0+2&&jx==j0+1)||                                                                                                                     (ix==i0+1&&jx==j0+2)||                                                                                                                       (ix==i0-1&&jx==j0+2)||                                                                                                                      (ix==i0-2&&jx==j0+1)||                                                                                                                      (ix==i0-2&&jx==j0-1)||                                                                                                                       (ix==i0-1&&jx==j0-2))
        if((ikb+1<8&&jkb-2<8&&ikb+1>0&&jkb-2>0&&Tabla[ikb+1][jkb-2].piesa==3&&Tabla[ikb+1][jkb-2].culoare!=cine_muta&&Tabla[ikb+1][jkb-2].culoare!=2)||(ikb+2<8&&jkb-1<8&&ikb+2>0&&jkb-1>0&&Tabla[ikb+2][jkb-1].piesa==3&&Tabla[ikb+2][jkb-1].culoare!=cine_muta&&Tabla[ikb+2][jkb-1].culoare!=2)||(ikb+2<8&&jkb+1<8&&ikb+2>0&&jkb+1>0&&Tabla[ikb+2][jkb+1].piesa==3&&Tabla[ikb+2][jkb+1].culoare!=cine_muta&&Tabla[ikb+2][jkb+1].culoare!=2)||(ikb+1<8&&jkb+2<8&&ikb+1>0&&jkb+2>0&&Tabla[ikb+1][jkb+2].piesa==3&&Tabla[ikb+1][jkb+2].culoare!=cine_muta&&Tabla[ikb+1][jkb+2].culoare!=2)||(ikb-1<8&&jkb+2<8&&ikb-1>0&&jkb+2>0&&Tabla[ikb-1][jkb+2].piesa==3&&Tabla[ikb-1][jkb+2].culoare!=cine_muta&&Tabla[ikb-1][jkb+2].culoare!=2)||(ikb-2<8&&jkb+1<8&&ikb-2>0&&jkb+1>0&&Tabla[ikb-2][jkb+1].piesa==3&&Tabla[ikb-2][jkb+1].culoare!=cine_muta&&Tabla[ikb-2][jkb+1].culoare!=2)||(ikb-2<8&&jkb-1<8&&ikb-2>0&&jkb-1>0&&Tabla[ikb-2][jkb-1].piesa==3&&Tabla[ikb-2][jkb-1].culoare!=cine_muta&&Tabla[ikb-2][jkb-1].culoare!=2)||(ikb-1<8&&jkb-2<8&&ikb-1>0&&jkb-2>0&&Tabla[ikb-1][jkb-2].piesa==3&&Tabla[ikb-1][jkb-2].culoare!=cine_muta&&Tabla[ikb-1][jkb-2].culoare!=2)) return 1;
        //tura(+regina): if((i0==ix||j0==jx)&&valid_tura(n,Tabla,i0,j0,ix,jx))
        if(ikb+1<n){
        for(int i=ikb+1;i<n;i++)
        {
            if(Tabla[i][jkb].piesa)//daca intampinam o piesa(nu va mai trebui sa verificam daca e gol patratul cu tabla...==2)
            {
                if((Tabla[i][jkb].piesa==4||Tabla[i][jkb].piesa==5)&&Tabla[i][jkb].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        if(ikb-1>=0){
        for(int i=ikb-1;i>=0;i--)
        {
            if(Tabla[i][jkb].piesa)//daca intampinam o piesa
            {
                if((Tabla[i][jkb].piesa==4||Tabla[i][jkb].piesa==5)&&Tabla[i][jkb].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        if(jkb+1<n){
        for(int j=jkb+1;j<n;j++)
        {
            if(Tabla[ikb][j].piesa)//daca intampinam o piesa
            {
                if((Tabla[ikb][j].piesa==4||Tabla[ikb][j].piesa==5)&&Tabla[ikb][j].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        if(jkb-1>=0){
        for(int j=jkb-1;j>=0;j--)
        {
            if(Tabla[ikb][j].piesa)//daca intampinam o piesa
            {
                if((Tabla[ikb][j].piesa==4||Tabla[ikb][j].piesa==5)&&Tabla[ikb][j].culoare!=cine_muta) return 1;
                else break;//am gasit o alta piesa
            }
        }}
        //nebun(+regina): if((i0+j0==ix+jx||i0-j0==ix-jx)&&valid_nebun(n,Tabla,i0,j0,ix,jx))
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(valid_nebun(n,Tabla,ikb,jkb,i,j))//daca gaseste o piesa conectata in relatie directa nebun cu regele returneaza 1, sper, altfel iar as coda ca la tura, desi si acolo cred ca mergea asa
                {
                    if((i+j==ikb+jkb||i-j==ikb-jkb)&&Tabla[i][j].culoare!=cine_muta&&Tabla[i][j].culoare!=2&&(Tabla[i][j].piesa==3||Tabla[i][j].piesa==5)) return 1;
                }
            }
        }
        //pion alb(cel nwgru nu ne va ataca)
        if((Tabla[ikb-1][jkb+1].piesa==1&&Tabla[ikb-1][jkb+1].culoare!=cine_muta)||(Tabla[ikb-1][jkb-1].piesa==1&&Tabla[ikb-1][jkb-1].culoare!=cine_muta)) return 1;
        break;
    default:
        break;
    }
    return 0;
}

int move_valid(int n, patrat Tabla[n][n], int i0,int j0, int ix,int jx,int cine_muta,patrat toate_miscarile[1200][n][n],int ctrmisc)//inca nu verifica sahurile 
{
    if(i0==ix&&j0==jx) return 0;//nu ai facut o miscare
    if(i0>=n||j0>=n||ix>=n||jx>=n||i0<0||j0<0||ix<0||jx<0) return 0;//seg fault, ajungi in afara tablei
    if(Tabla[ix][jx].culoare==cine_muta) return 0;//can't eat your own pieces, but you can eat empty spaces(en passant) or go to them without a capture
    if(Tabla[i0][j0].culoare!=cine_muta||Tabla[i0][j0].culoare==2) return 0;//can't move opponent's pieces or empty spaces
    //if(isincheck(n,Tabla,cine_muta,ikw,jkw,ikb,jkb)) return 0;//nu poti intra sau ramane in sah
        switch (Tabla[i0][j0].piesa)
            {
            case 0://nu poti muta un gol
                return 0;
                break;
            case 1://pion: cei albi merg progresiv in i si cei negri regresiv
                switch (Tabla[i0][j0].culoare)
                {
                case 0://pion alb
                    if(i0==4&&ix==5&&(jx==j0+1||jx==j0-1))
                    {
                        if((toate_miscarile[ctrmisc][4][jx].piesa==1&&toate_miscarile[ctrmisc][4][jx].culoare!=cine_muta&&toate_miscarile[ctrmisc][6][jx].piesa==0&&toate_miscarile[ctrmisc-1][6][jx].piesa==1&&toate_miscarile[ctrmisc-1][6][jx].culoare!=cine_muta&&toate_miscarile[ctrmisc-1][4][jx].piesa==0))//||(toate_miscarile[ctrmisc][4][jx+1].piesa==1&&toate_miscarile[ctrmisc][4][jx+1].culoare!=cine_muta&&toate_miscarile[ctrmisc-1][6][jx+1].piesa==1&&toate_miscarile[ctrmisc-1][6][jx+1].culoare!=cine_muta))//aici credeam ca jx-1 si jx+1
                        {
                            return 3;//en passant
                        }
                    }
                    if((j0==jx)&&(ix==i0+1)&&!Tabla[ix][jx].piesa)
                    {
                        if(ix==7&&i0==6) return 2;//daca pionul trebuie promovat functia returneaza 2(fara captura)
                        return 1;
                    }
                    if((i0==1&&(ix==3))&&(j0==jx)&&!Tabla[ix][jx].piesa&&!Tabla[ix-1][jx].piesa) return 1;//poate misca 2 patrate la inceput
                    if((jx==j0+1||jx==j0-1)&&(Tabla[ix][jx].culoare!=cine_muta&&Tabla[ix][jx].culoare!=2)&&(ix==i0+1))
                    {
                        if(ix==7&&i0==6) return 2;//daca pionul trebuie promovat functia returneaza 2(fara captura)
                        return 1;
                    }
                    break;
                case 1://pion negru
                    if(i0==3&&ix==2&&(jx==j0+1||jx==j0-1))
                    {
                        if((toate_miscarile[ctrmisc][3][jx].piesa==1&&toate_miscarile[ctrmisc][3][jx].culoare!=cine_muta&&toate_miscarile[ctrmisc][1][jx].piesa==0&&toate_miscarile[ctrmisc-1][1][jx].piesa==1&&toate_miscarile[ctrmisc-1][1][jx].culoare!=cine_muta&&toate_miscarile[ctrmisc-1][3][jx].piesa==0))//||(toate_miscarile[ctrmisc][4][jx+1].piesa==1&&toate_miscarile[ctrmisc][4][jx+1].culoare!=cine_muta&&toate_miscarile[ctrmisc-1][6][jx+1].piesa==1&&toate_miscarile[ctrmisc-1][6][jx+1].culoare!=cine_muta))//aici credeam ca jx-1 si jx+1
                        {
                            return 3;//en passant
                        }
                    }
                    if((j0==jx)&&(ix==i0-1)&&!Tabla[ix][jx].piesa)
                    {
                        if(ix==0&&i0==1) return 2;//daca pionul trebuie promovat functia returneaza 2(fara captura)
                        return 1;
                    }
                    if((i0==6&&(ix==4))&&(j0==jx)&&!Tabla[ix][jx].piesa&&!Tabla[ix+1][jx].piesa) return 1;//poate misca 2 patrate la inceput
                    if((jx==j0-1||jx==j0+1)&&(Tabla[ix][jx].culoare!=cine_muta&&Tabla[ix][jx].culoare!=2)&&(ix==i0-1))
                    {
                        if(ix==0&&i0==1) return 2;//daca pionul trebuie promovat functia returneaza 2(fara captura)
                        return 1;
                    }
                    break;
                default://am verificat deja sa nu mutam un gol, e ok
                    break;
                }
                return 0;
                break;
            case 2://cal
                if((ix==i0+1&&jx==j0-2)||(ix==i0+2&&jx==j0-1)||(ix==i0+2&&jx==j0+1)||(ix==i0+1&&jx==j0+2)||(ix==i0-1&&jx==j0+2)||(ix==i0-2&&jx==j0+1)||(ix==i0-2&&jx==j0-1)||(ix==i0-1&&jx==j0-2))return 1;
                return 0;
                break;
            case 3://nebun
                if((i0+j0==ix+jx||i0-j0==ix-jx)&&valid_nebun(n,Tabla,i0,j0,ix,jx))return 1;
                return 0;
                break;
            case 4://tura
                if((i0==ix||j0==jx)&&valid_tura(n,Tabla,i0,j0,ix,jx)) return 1;//puteam pune si conditia initiala in functie daca tot am facut una dar na
                return 0;
                break;
            case 5://regina
                if(((i0+j0==ix+jx||i0-j0==ix-jx)&&valid_nebun(n,Tabla,i0,j0,ix,jx))||((i0==ix||j0==jx)&&valid_tura(n,Tabla,i0,j0,ix,jx))) return 1;
                return 0;
                break;
            case 6://rege
                if((ix==i0+1&&jx==j0-1)||(ix==i0-1&&jx==j0+1)||(ix==i0+1&&jx==j0+1)||(ix==i0-1&&jx==j0-1)||(ix==i0&&jx==j0+1)||(ix==i0&&jx==j0-1)||(ix==i0+1&&jx==j0)||(ix==i0-1&&jx==j0))return 1;//fiecare patrat din jurul sau
                return 0;
                break;
            default:
                break;
            }
    //return 0;
}

void afisare_negru(int n, patrat Tabla[n][n])
{
    printf("\n\nBlack to play:\n   h  g  f  e  d  c  b  a\n");
                for(int i=0;i<8;i++)
                {
                    printf("%d",i+1);
                    for(int j=7;j>=0;j--)//for inversat
                    {
                        switch(Tabla[i][j].piesa)
                        {
                            case 0:
                            //printf(" . ");
                            if(i%2==j%2) printf(" . ");// alternativ: ■
                            else printf(" . ");// alternativ: □
                            break;
                            case 1:
                            if(Tabla[i][j].culoare)
                            printf(" .♟");
                            else
                            printf(" .♙");
                            break;
                            case 2:
                            if(Tabla[i][j].culoare)
                            printf(" .♞");
                            else
                            printf(" .♘");
                            break;
                            case 3:
                            if(Tabla[i][j].culoare)
                            printf(" .♝");
                            else
                            printf(" .♗");
                            break;
                            case 4:
                            if(Tabla[i][j].culoare)
                            printf(" .♜");
                            else
                            printf(" .♖");
                            break;
                            case 5:
                            if(Tabla[i][j].culoare)
                            printf(" .♛");
                            else
                            printf(" .♕");
                            break;
                            case 6:
                            if(Tabla[i][j].culoare)
                            printf(" .♚");
                            else
                            printf(" .♔");
                            break;
                        }
                        if(j==0)printf(" .\n");
                    }
                }
    printf("\n");
}


void afisare_alb(int n, patrat Tabla[n][n])
{
    printf("\n\nWhite to play:\n   a  b  c  d  e  f  g  h\n");
                for(int i=7;i>=0;i--)//for inversat
                {
                    printf("%d",i+1);
                    for(int j=0;j<8;j++)
                    {
                        switch(Tabla[i][j].piesa)
                        {
                            case 0:
                            //printf(" . ");
                            if(i%2==j%2) printf(" . ");// alternativ: ■
                            else printf(" . ");// alternativ: □
                            break;
                            case 1:
                            if(Tabla[i][j].culoare)
                            printf(" .♟");
                            else
                            printf(" .♙");
                            break;
                            case 2:
                            if(Tabla[i][j].culoare)
                            printf(" .♞");
                            else
                            printf(" .♘");
                            break;
                            case 3:
                            if(Tabla[i][j].culoare)
                            printf(" .♝");
                            else
                            printf(" .♗");
                            break;
                            case 4:
                            if(Tabla[i][j].culoare)
                            printf(" .♜");
                            else
                            printf(" .♖");
                            break;
                            case 5:
                            if(Tabla[i][j].culoare)
                            printf(" .♛");
                            else
                            printf(" .♕");
                            break;
                            case 6:
                            if(Tabla[i][j].culoare)
                            printf(" .♚");
                            else
                            printf(" .♔");
                            break;
                        }
                        if(j==7)printf(" .\n");
                    }
                }
    printf("\n");
}

int main()
{
    patrat Tabla[MAX][8][8];
    int opt=-1 ,contor=0,cul=-1;
    do{
        meniu();
        scanf("%d",&opt);
        switch (opt)
        {
        case 0:
            //return 0;
        break;
        case 1:
            clearr(2);
            instructions();
            char c;//poate trebuie int
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    switch (j)
                    {
                    case 0:
                        printf("Pe pozitia a%d: ",i+1);
                        break;
                    case 1:
                        printf("Pe pozitia b%d: ",i+1);
                        break;
                    case 2:
                        printf("Pe pozitia c%d: ",i+1);
                        break;
                    case 3:
                        printf("Pe pozitia d%d: ",i+1);
                        break;
                    case 4:
                        printf("Pe pozitia e%d: ",i+1);
                        break;
                    case 5:
                        printf("Pe pozitia f%d: ",i+1);
                        break;
                    case 6:
                        printf("Pe pozitia g%d: ",i+1);
                        break;
                    case 7:
                        printf("Pe pozitia h%d: ",i+1);
                        break;
                    default:
                        eroare();
                        break;
                    }
                    char enter='\n';
                    scanf("%c",&enter);
                    scanf("%c",&c);
                    switch(c)
                    {
                        case 'O':
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                        break;
                        case 'o':
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                        break;
                        case 'P':
                        Tabla[contor][i][j].piesa=1;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=1;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'p':
                        Tabla[contor][i][j].piesa=1;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=1;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'N':
                        Tabla[contor][i][j].piesa=2;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=3;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'n':
                        Tabla[contor][i][j].piesa=2;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=3;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'B':
                        Tabla[contor][i][j].piesa=3;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=3;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'b':
                        Tabla[contor][i][j].piesa=3;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=3;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'R':
                        Tabla[contor][i][j].piesa=4;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=5;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'r':
                        Tabla[contor][i][j].piesa=4;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=5;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'Q':
                        Tabla[contor][i][j].piesa=5;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=9;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'q':
                        Tabla[contor][i][j].piesa=5;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=9;
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'K':
                        Tabla[contor][i][j].piesa=6;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=2097151;//2^21-1
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        case 'k':
                        Tabla[contor][i][j].piesa=6;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=2097151;//2^21-1
                        printf("Culoarea (0=alb 1=negru): ");
                        scanf("%d", &cul);
                        if(cul==1||cul==0) Tabla[contor][i][j].culoare=cul;
                        break;
                        default:
                        printf("Wrong input!\n");
                        return 0;
                    }
                }
            }
            contor++;
        break;
        case 2:
        {
            clearr(2);
            if(!contor) {printf("\nNu aveti ce sa afisati\n\n");break;}
            for(int k=0;k<contor;k++)
            {
                printf("\n\nTabla cu numarul %d:\nBlack's view:\n   h  g  f  e  d  c  b  a\n",k+1);
                for(int i=0;i<8;i++)
                {
                    printf("%d",i+1);
                    for(int j=7;j>=0;j--)
                    {
                        switch(Tabla[k][i][j].piesa)
                        {
                            case 0:
                            printf(" . ");
                            break;
                            case 1:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♟");
                            else
                            printf(" .♙");
                            break;
                            case 2:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♞");
                            else
                            printf(" .♘");
                            break;
                            case 3:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♝");
                            else
                            printf(" .♗");
                            break;
                            case 4:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♜");
                            else
                            printf(" .♖");
                            break;
                            case 5:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♛");
                            else
                            printf(" .♕");
                            break;
                            case 6:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♚");
                            else
                            printf(" .♔");
                            break;
                        }
                        if(j==0)printf(" .\n");
                    }
                }
                printf("\nWhite's view:\n   a  b  c  d  e  f  g  h\n");
                for(int i=7;i>=0;i--)//for inv
                {
                    printf("%d",i+1);
                    for(int j=0;j<8;j++)
                    {
                        switch(Tabla[k][i][j].piesa)
                        {
                            case 0:
                            printf(" . ");
                            break;
                            case 1:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♟");
                            else
                            printf(" .♙");
                            break;
                            case 2:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♞");
                            else
                            printf(" .♘");
                            break;
                            case 3:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♝");
                            else
                            printf(" .♗");
                            break;
                            case 4:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♜");
                            else
                            printf(" .♖");
                            break;
                            case 5:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♛");
                            else
                            printf(" .♕");
                            break;
                            case 6:
                            if(Tabla[k][i][j].culoare)
                            printf(" .♚");
                            else
                            printf(" .♔");
                            break;
                        }
                        if(j==7)printf(" .\n");
                        if(i==7&&j==7&&k<contor-1)printf("\n\nTabla cu numarul %d:\n",k+2);
                    }
                }
            }
        }
        break;
        case 3:
        clearr(5);
        //aici hardcodez matricea cu piesele pe pozitiile de start
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    switch (j)
                    {
                    case 0://a
                        switch (i+1)
                        {
                            case 1:
                            //white rook
                                Tabla[contor][i][j].piesa=4;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=5;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black rook
                                Tabla[contor][i][j].piesa=4;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=5;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                            break;
                        }
                    break;
                    case 1://b
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white knight
                                Tabla[contor][i][j].piesa=2;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black knight
                                Tabla[contor][i][j].piesa=2;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                    break;
                    case 2://c
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white bishop
                                Tabla[contor][i][j].piesa=3;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black bishop
                                Tabla[contor][i][j].piesa=3;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                    break;
                    case 3://d
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white Queen
                                Tabla[contor][i][j].piesa=5;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=9;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black Queen
                                Tabla[contor][i][j].piesa=5;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=9;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                    break;
                    case 4://e
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white King
                                Tabla[contor][i][j].piesa=6;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=2097151;//2^21-1
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black King
                                Tabla[contor][i][j].piesa=6;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=2097151;//2^21-1
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                        break;
                    case 5://f
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white bishop
                                Tabla[contor][i][j].piesa=3;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black bishop
                                Tabla[contor][i][j].piesa=3;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                    break;
                    case 6://g
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white knight
                                Tabla[contor][i][j].piesa=2;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black knight
                                Tabla[contor][i][j].piesa=2;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=3;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                    break;
                    case 7://h
                        switch (i+1)//sa se potriveasca cu pozitia 1-8 in loc de 0-7
                        {
                            case 1:
                            //white rook
                                Tabla[contor][i][j].piesa=4;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=5;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 2:
                            //white pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=0;
                            break;
                            case 3:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 4:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 5:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 6:
                        Tabla[contor][i][j].piesa=0;
                        Tabla[contor][i][j].pozitia_i=i;
                        Tabla[contor][i][j].pozitia_j=j;
                        Tabla[contor][i][j].valoarea=0;
                        Tabla[contor][i][j].culoare=2;
                            break;
                            case 7:
                            //black pawn
                                Tabla[contor][i][j].piesa=1;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=1;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            case 8:
                            //black rook
                                Tabla[contor][i][j].piesa=4;
                                Tabla[contor][i][j].pozitia_i=i;
                                Tabla[contor][i][j].pozitia_j=j;
                                Tabla[contor][i][j].valoarea=5;
                                Tabla[contor][i][j].culoare=1;
                            break;
                            default:
                            printf("CIUDATA EROARE!!!\n");
                            return 0;
                        }
                    break;
                    default://err
                        eroare();
                    break;
                    }
                }
            }
        contor++;
        break;


        case 4:
        clearr(4);
        printf("\nAlege o tabla din cele salvate(numerotate de la 1): ");
        int tbl=-1;
        scanf("%d",&tbl);
        if(tbl>contor||tbl<1)//tablele vor fi numerotate mai natural, de la 1 la contor-1
        {
            printf("\nNu aveti aceasta tabla\n");
            break;
        }
        tbl-=1;//ca sa reglez indexarea
        printf("\nCine muta? Daca acum incepe jocul este normal sa inceapa alb. \nSelecteaza 0 pt alb 1 pt negru: ");
        int cine_muta=-1;
        scanf("%d",&cine_muta);
        if(cine_muta!=0&&cine_muta!=1)
        {
            printf("\nNu ati ales o optiune valida\n");
            break;
        }
        int isnotover=1,wrong=0,won=-3000,kapa=0;//voi prelucra pe viitor variabilele in functie de posibilele finaluri de meci: agree to draw, stalemate, insufficient material, resign, 3 fold repetition, 50 move rule si ultima dar nu cea din urma sah mat
        int ikw=-1,jkw=-1,ikb=-1,jkb=-1;//coord regelui jucatorului alb/negru
        int fiftymoverule=0;

        //urmatorul concept va fi folositor pt rocada, en-passant si 3-fold reppetition etc
        patrat toate_miscarile[12000][8][8];//cel mai lung meci de sah posibil are ~<=6000 de miscari, dar noi tinem minte si alb si negru=>12000
        int ctrmisc=0;//pt primul index de mai sus
        // //pe index ^ par voi incerca sa tin minte alb, iar impar negru, (am lasat ideea nu ma ajuta mai mult ma incurca)
        // //practic ctrmisc%2==cine_muta

        // if(cine_muta){//daca incepe negru indexul 0 va avea si el acelasi lucru ca indexul 1
        //     for(int i=0; i<8;i++){for(int j=0;j<8;j++){toate_miscarile[ctrmisc][i][j]=Tabla[tbl][i][j];}}ctrmisc++;//tin minte miscarile
        // }
        // else{
        for(int i=0; i<8;i++){for(int j=0;j<8;j++){toate_miscarile[ctrmisc][i][j]=Tabla[tbl][i][j];}}ctrmisc++;//tin minte miscarea 0 practic tabla de la care s-a inceput
        char posin[2],posout[2];//ex e4 d5
        char draw_resign[10];//'d' pe index 0 inseamna ca se ofera draw, 'r' inseamna ca se lasa jucatorul
        patrat white_inventory[15];
        patrat black_inventory[15];//max 15 piese pot fi capturate
        int kwhite=0,kblack=0;//nr de piese de pana acum, pt index la vectori
        int valwhite=0,valblack=0;//suma valorilor pieselor capturate
        while(isnotover)
        {
            clearr(3);
            if(!wrong&&isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb))//verificam in urma unei miscari corecte daca e sah mat
            {
                patrat AUX[2][8][8];//construim doua table
                for(int i=0; i<8;i++){for(int j=0;j<8;j++){AUX[0][i][j]=Tabla[tbl][i][j];}}
                for(int i00;i00<8;i00++)
                {
                    for(int j00;j00<8;j00++)
                    {
                        for(int ixx;ixx<8;ixx++)
                        {
                            for(int jxx;jxx<8;jxx++)
                            {
                                switch (move_valid(8,AUX[0],i00,j00,ixx,jxx,cine_muta,toate_miscarile,ctrmisc-1))
                                {
                                case 1://miscare oarecare
                                    patrat plecare0,destinatie0;
                                    destinatie0=AUX[1][ixx][jxx];
                                    plecare0=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx]=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx].pozitia_i=ixx;
                                    AUX[1][ixx][jxx].pozitia_j=jxx;
                                    AUX[1][i00][j00].piesa=0;
                                    AUX[1][i00][j00].valoarea=0;
                                    AUX[1][i00][j00].culoare=2;
                                    if(!isincheck(8,AUX[1],cine_muta,ikw,jkw,ikb,jkb)){//iese din sah
                                        break;//switch case
                                        break;break;break;break;//toate for-urile
                                    }
                                    break;
                                case 2://promo, mutam pionul pe ultimul rank ca nu are importanta la ce piesa promovam atata timp cat ne scoate din sah
                                    patrat plecare1,destinatie1;
                                    destinatie1=AUX[1][ixx][jxx];
                                    plecare1=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx]=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx].pozitia_i=ixx;
                                    AUX[1][ixx][jxx].pozitia_j=jxx;
                                    AUX[1][i00][j00].piesa=0;
                                    AUX[1][i00][j00].valoarea=0;
                                    AUX[1][i00][j00].culoare=2;
                                    if(!isincheck(8,AUX[1],cine_muta,ikw,jkw,ikb,jkb)){//iese din sah
                                        break;//switch case
                                        break;break;break;break;//toate for-urile
                                    }
                                    break;
                                case 3://en passant
                                    patrat plecare2,destinatie2,pion_mancat2;//le tinem minte sa le punem inapoi daca este sah dupa miscare
                                    destinatie2=AUX[1][ixx][jxx];
                                    plecare2=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx]=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx].pozitia_i=ixx;
                                    AUX[1][ixx][jxx].pozitia_j=jxx;
                                    AUX[1][i00][j00].piesa=0;
                                    AUX[1][i00][j00].valoarea=0;
                                    AUX[1][i00][j00].culoare=2;
                                    pion_mancat2=AUX[1][i00][jxx];
                                    AUX[1][i00][jxx].culoare=2;
                                    AUX[1][i00][jxx].piesa=0;
                                    AUX[1][i00][jxx].valoarea=0;
                                    if(!isincheck(8,AUX[1],cine_muta,ikw,jkw,ikb,jkb))
                                    {//iese din sah
                                        break;//switch case
                                        break;break;break;break;//toate for-urile
                                    }
                                    break;
                                default://rocada sau miscare invalida, nici care nu ne scoate din sah

                                    break;
                                }
                                if(i00==7&&ixx==7&&j00==7&&jxx==7)//a incercat toate miscarile posibile fara sa iasa din sah=>mat
                                {
                                    printf("CHECKMATE!");
                                    isnotover=0;
                                    won=!cine_muta;//sper ca face din 0 1 si din 1 0
                                }
                            }
                        }
                    }
                }
            }
            
            //verificare pt draw by insufficient material:
            int insufalb[2],insufnegru[2];//putea fi pe 6 fiindca nu numaram golurile la index 0
            for(int i=0;i<2;i++){insufalb[i]=0;insufnegru[i]=0;}//daca gasim piesa: cal 0 nebun 1
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(Tabla[tbl][i][j].piesa==1||Tabla[tbl][i][j].piesa==4||Tabla[tbl][i][j].piesa==5) {break;break;} //am gasit pion(poate fi promovat) tura sau regina, jocul continua avem material de sah mat
                    if(Tabla[tbl][i][j].culoare==0)//alb
                    {
                        if(Tabla[tbl][i][j].piesa==2) insufalb[0]++;
                        if(Tabla[tbl][i][j].piesa==3) insufalb[1]++;
                    }
                    if(Tabla[tbl][i][j].culoare==1)//negru
                    {
                        if(Tabla[tbl][i][j].piesa==2) insufnegru[0]++;
                        if(Tabla[tbl][i][j].piesa==3) insufnegru[1]++;
                    }
                }
            }/*
            //king vs king
            if(!insufalb[0]&&!insufalb[1]&&!insufnegru[0]&&!insufnegru[1]){printf("\nRege vs rege\n"); won=-2;isnotover=0;break;}
            //king + minor piece vs king
            if((insufalb[0]==1&&!insufalb[1]&&!insufnegru[0]&&!insufnegru[1])||(!insufalb[0]&&!insufalb[1]&&insufnegru[0]==1&&!insufnegru[1])){printf("\nRege vs rege cu un cal\n"); won=-2;isnotover=0;break;}
            if((!insufalb[0]&&insufalb[1]==1&&!insufnegru[0]&&!insufnegru[1])||(!insufalb[0]&&!insufalb[1]&&!insufnegru[0]&&insufnegru[1]==1)){printf("\nRege vs rege cu un nebun\n"); won=-2;isnotover=0;break;}
            //king + minor piece vs king + minor piece:
            if((!insufalb[0]&&insufalb[1]==1&&insufnegru[0]==1&&!insufnegru[1])||(insufalb[0]==1&&!insufalb[1]&&!insufnegru[0]&&insufnegru[1]==1)){printf("\nRege cu un cal vs rege cu un nebun\n"); won=-2;isnotover=0;break;}
            if(!insufalb[0]&&insufalb[1]==1&&!insufnegru[0]&&insufnegru[1]==1){printf("\nRege cu un nebun vs rege cu un nebun\n"); won=-2;isnotover=0;break;}
            if(insufalb[0]==1&&!insufalb[1]&&insufnegru[0]==1&&!insufnegru[1]){printf("\nRege cu un cal vs rege cu un cal\n"); won=-2;isnotover=0;break;}
// rege cu doi cai vs rege matul e posibil dar nu fortabil, eu il las sa continue jocul
*/


            if(!wrong&&!isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb))//verificam in urma unei miscari corecte daca e stalemate
            {
                patrat AUX[2][8][8];//construim doua table
                for(int i=0; i<8;i++){for(int j=0;j<8;j++){AUX[0][i][j]=Tabla[tbl][i][j];}}
                for(int i00;i00<8;i00++)
                {
                    for(int j00;j00<8;j00++)
                    {
                        for(int ixx;ixx<8;ixx++)
                        {
                            for(int jxx;jxx<8;jxx++)
                            {
                                switch (move_valid(8,AUX[0],i00,j00,ixx,jxx,cine_muta,toate_miscarile,ctrmisc-1))
                                {
                                case 1://miscare oarecare
                                    patrat plecare3,destinatie3;
                                    destinatie3=AUX[1][ixx][jxx];
                                    plecare3=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx]=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx].pozitia_i=ixx;
                                    AUX[1][ixx][jxx].pozitia_j=jxx;
                                    AUX[1][i00][j00].piesa=0;
                                    AUX[1][i00][j00].valoarea=0;
                                    AUX[1][i00][j00].culoare=2;
                                    if(!isincheck(8,AUX[1],cine_muta,ikw,jkw,ikb,jkb)){//iese din sah
                                        break;//switch case
                                        break;break;break;break;//toate for-urile
                                    }
                                    break;
                                case 2://promo, mutam pionul pe ultimul rank ca nu are importanta la ce piesa promovam atata timp cat ne scoate din sah
                                    patrat plecare4,destinatie4;
                                    destinatie4=AUX[1][ixx][jxx];
                                    plecare4=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx]=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx].pozitia_i=ixx;
                                    AUX[1][ixx][jxx].pozitia_j=jxx;
                                    AUX[1][i00][j00].piesa=0;
                                    AUX[1][i00][j00].valoarea=0;
                                    AUX[1][i00][j00].culoare=2;
                                    if(!isincheck(8,AUX[1],cine_muta,ikw,jkw,ikb,jkb)){//iese din sah
                                        break;//switch case
                                        break;break;break;break;//toate for-urile
                                    }
                                    break;
                                case 3://en passant
                                    patrat plecare5,destinatie5,pion_mancat5;//le tinem minte sa le punem inapoi daca este sah dupa miscare
                                    destinatie5=AUX[1][ixx][jxx];
                                    plecare5=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx]=AUX[1][i00][j00];
                                    AUX[1][ixx][jxx].pozitia_i=ixx;
                                    AUX[1][ixx][jxx].pozitia_j=jxx;
                                    AUX[1][i00][j00].piesa=0;
                                    AUX[1][i00][j00].valoarea=0;
                                    AUX[1][i00][j00].culoare=2;
                                    pion_mancat5=AUX[1][i00][jxx];
                                    AUX[1][i00][jxx].culoare=2;
                                    AUX[1][i00][jxx].piesa=0;
                                    AUX[1][i00][jxx].valoarea=0;
                                    if(!isincheck(8,AUX[1],cine_muta,ikw,jkw,ikb,jkb))
                                    {//iese din sah
                                        break;//switch case
                                        break;break;break;break;//toate for-urile
                                    }
                                    break;
                                default://rocada sau miscare invalida, nici care nu ne scoate din sah







//aici e discutabil las liber sa completez poate ca o rocada te scoate din stalemate, dar oricum at trebui ca tura aia sa fie miscabila deci nu prea conteaza








                                    break;
                                }
                                if(i00==7&&ixx==7&&j00==7&&jxx==7)//a incercat toate miscarile posibile fara sa iasa din sah=>mat
                                {
                                    won=-1;
                                    isnotover=0;
                                }
                            }
                        }
                    }
                }
            }
            kapa=0;//pt o mica optimizare
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(Tabla[tbl][i][j].piesa==6) 
                    {
                        if(Tabla[tbl][i][j].culoare==0)
                        {
                            ikw=i;
                            jkw=j;
                            kapa++;
                        }
                        if(Tabla[tbl][i][j].culoare==1)
                        {
                            ikb=i;
                            jkb=j;
                            kapa++;
                        }
                        if(kapa==2){break;break;}//odata ce a gasit ambii regi iese din for-uri
                    }
                }
            }
            if(wrong==1) printf("Ati gresit miscarea, nu este legala! mai aveti sansa sa va reparati greseala:\n\n");
            if(isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb)) printf("ATENTIE! Sunteti in sah!\n");
            if(cine_muta)
            afisare_negru(8,Tabla[tbl]);
            else
            afisare_alb(8,Tabla[tbl]);
            printf("\nPUNCTE DE MATERIAL CAPTURATE:\nAlb:%d   Negru:%d\n",valwhite,valblack);
            if(valwhite>valblack)
            {
                if(cine_muta) printf("Atentie! Sunteti pe minus cu %d punct(e)!\n",valwhite-valblack);//mi-e lene sa printez diferit pt mai multe puncte, daca depaseste 20 sa pun "de" samd
                else printf("Sunteti pe plus cu %d punct(e)!\n",valwhite-valblack);
            }
            if(valwhite<valblack)
            {
                if(cine_muta) printf("Sunteti pe plus cu %d punct(e)!\n",valblack-valwhite);
                else printf("Atentie! Sunteti pe minus cu %d punct(e)!\n",valblack-valwhite);
            }
            if(valwhite==valblack)
            {
                printf("Egalitate de puncte\n\n");
            }

/*


            char drawresign;
            printf("Daca doriti sa oferiti o egalitate sperand ca oponentul sa accepte tastati 'd'(de la draw)\ndaca doriti sa va dati batut tastati 'r' de la resign(skip=enter):\n");
            scanf("%c",&drawresign);

*/




            
            printf("Pozitia la care se afla piesa pe care doriti sa o mutati\n(litera si cifra impreuna: 2 caractere): ");
            scanf("%s",&posin[0]);
            printf("Unde doriti sa o mutati(acelasi format): ");
            scanf("%s",&posout[0]);
            //printf("\n%c%c  ->  %c%c\n",posin[0],posin[1],posout[0],posout[1]);//am verificat si merge citirea
            //Tabla[tbl]=makemove(8,Tabla[tbl],posin,posout);
            //patrat tblnxt[8][8];
    int i0=-1,j0=-1,ix=-1,jx=-1;
    // i0=atoi(posin[1])-1;
    // ix=atoi(posout[1])-1;
    i0=posin[1]-48-1;
    ix=posout[1]-48-1;//ca sa reglez ascii(48) si indexarea(1)
    j0=posin[0]-97;
    jx=posout[0]-97;
            if(move_valid(8,Tabla[tbl],i0,j0,ix,jx,cine_muta,toate_miscarile,ctrmisc-1)==1)//pt a optimiza as putea numi o variabila cu acea functie
            {
            wrong=0;
            patrat plecare,destinatie;//le tinem minte sa le punem inapoi daca este sah dupa miscare
            destinatie=Tabla[tbl][ix][jx];
            plecare=Tabla[tbl][i0][j0];
            Tabla[tbl][ix][jx]=Tabla[tbl][i0][j0];
            Tabla[tbl][ix][jx].pozitia_i=ix;
            Tabla[tbl][ix][jx].pozitia_j=jx;
            Tabla[tbl][i0][j0].piesa=0;
            Tabla[tbl][i0][j0].valoarea=0;
            Tabla[tbl][i0][j0].culoare=2;
            if(isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb)){//anulez miscarea
                wrong=1;
                Tabla[tbl][i0][j0]=plecare;
                Tabla[tbl][ix][jx]=destinatie;
            }else{//daca nu e in sah fac schimbarea jucatorului
            if(plecare.piesa==1||(destinatie.culoare!=cine_muta&&destinatie.piesa)) fiftymoverule=0;
            else {if(fiftymoverule++>=100) {isnotover=0;won=-5;}}
            for(int i=0; i<8;i++){for(int j=0;j<8;j++){toate_miscarile[ctrmisc][i][j]=Tabla[tbl][i][j];}}ctrmisc++;//tin minte miscarile
            if(cine_muta){
            if(destinatie.culoare==0){black_inventory[kblack++]=destinatie;valblack+=destinatie.valoarea;}
            cine_muta=0;}//urm randul lui alb
            else{
            if(destinatie.culoare==1){white_inventory[kwhite++]=destinatie;valwhite+=destinatie.valoarea;}
            cine_muta=1;}//urm randul lui negru
            }}
            else
            { 
                if(move_valid(8,Tabla[tbl],i0,j0,ix,jx,cine_muta,toate_miscarile,ctrmisc-1)==2)
                {
                wrong=0;
                int gresit=1;
                printf("Ai promovat pionul! ce piesa vrei sa devina?\nQ/q Regina\nR/r Tura\nN/n Cal\nB/b Nebun\nAlegerea: ");
                while(gresit)
                {
                char promo='\0';
                scanf("%c",&promo);
                if(promo=='Q'||promo=='q'||promo=='R'||promo=='r'||promo=='N'||promo=='n'||promo=='B'||promo=='b')
                {
                    gresit=0;
                    if(promo=='Q'||promo=='q')
                    {
                        Tabla[tbl][ix][jx].culoare=cine_muta;
                        Tabla[tbl][ix][jx].piesa=5;
                        Tabla[tbl][ix][jx].valoarea=9;
                        if(cine_muta) valblack+=8;//1 era pionul deja
                        else valwhite+=8;
                    }
                    if(promo=='R'||promo=='r')
                    {
                        Tabla[tbl][ix][jx].culoare=cine_muta;
                        Tabla[tbl][ix][jx].piesa=4;
                        Tabla[tbl][ix][jx].valoarea=5;
                        if(cine_muta) valblack+=4;//1 era pionul deja
                        else valwhite+=4;
                    }
                    if(promo=='N'||promo=='n')
                    {
                        Tabla[tbl][ix][jx].culoare=cine_muta;
                        Tabla[tbl][ix][jx].piesa=2;
                        Tabla[tbl][ix][jx].valoarea=3;
                        if(cine_muta) valblack+=2;//1 era pionul deja
                        else valwhite+=2;
                    }
                    if(promo=='B'||promo=='b')
                    {
                        Tabla[tbl][ix][jx].culoare=cine_muta;
                        Tabla[tbl][ix][jx].piesa=3;
                        Tabla[tbl][ix][jx].valoarea=3;
                        if(cine_muta) valblack+=2;//1 era pionul deja
                        else valwhite+=2;
                    }
                }//mai sus din cate se vede nu mai aveam chef de switch case
                else
                {
                    printf("Nu este una din variantele sugerate!\n Mai incearca: ");
                }
                }
                patrat plecare,destinatie;//le tinem minte sa le punem inapoi daca este sah dupa miscare
                destinatie=Tabla[tbl][ix][jx];
                plecare=Tabla[tbl][i0][j0];
                Tabla[tbl][ix][jx].pozitia_i=ix;
                Tabla[tbl][ix][jx].pozitia_j=jx;
                Tabla[tbl][i0][j0].piesa=0;
                Tabla[tbl][i0][j0].valoarea=0;
                Tabla[tbl][i0][j0].culoare=2;
                if(isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb)){//anulez miscarea
                wrong=1;
                Tabla[tbl][i0][j0]=plecare;
                Tabla[tbl][ix][jx]=destinatie;
            }else{//daca nu e in sah fac schimbarea jucatorului
                for(int i=0; i<8;i++){for(int j=0;j<8;j++){toate_miscarile[ctrmisc][i][j]=Tabla[tbl][i][j];}}ctrmisc++;//tin minte miscarile
                if(plecare.piesa==1||(destinatie.culoare!=cine_muta&&destinatie.piesa)) fiftymoverule=0;
                else {if(fiftymoverule++>=100) {isnotover=0;won=-5;}}
                if(cine_muta){
                if(destinatie.culoare==0){black_inventory[kblack++]=destinatie;valblack+=destinatie.valoarea;}
                cine_muta=0;}//urm randul lui alb
                else{
                if(destinatie.culoare==1){white_inventory[kwhite++]=destinatie;valwhite+=destinatie.valoarea;}
                cine_muta=1;}//urm randul lui negru
                }}
                else
                { 
                    if(move_valid(8,Tabla[tbl],i0,j0,ix,jx,cine_muta,toate_miscarile,ctrmisc-1)==3)//en passant
                    {       
                        wrong=0;
                        patrat plecare,destinatie,pion_mancat;//le tinem minte sa le punem inapoi daca este sah dupa miscare
                        destinatie=Tabla[tbl][ix][jx];
                        plecare=Tabla[tbl][i0][j0];
                        Tabla[tbl][ix][jx]=Tabla[tbl][i0][j0];
                        Tabla[tbl][ix][jx].pozitia_i=ix;
                        Tabla[tbl][ix][jx].pozitia_j=jx;
                        Tabla[tbl][i0][j0].piesa=0;
                        Tabla[tbl][i0][j0].valoarea=0;
                        Tabla[tbl][i0][j0].culoare=2;
                        pion_mancat=Tabla[tbl][i0][jx];
                        Tabla[tbl][i0][jx].culoare=2;
                        Tabla[tbl][i0][jx].piesa=0;
                        Tabla[tbl][i0][jx].valoarea=0;
                        if(isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb)){//anulez miscarea
                            wrong=1;
                            Tabla[tbl][i0][j0]=plecare;
                            Tabla[tbl][ix][jx]=destinatie;
                            Tabla[tbl][i0][jx]=pion_mancat;
                        }else{//daca nu e in sah fac schimbarea jucatorului
                        if(plecare.piesa==1||(destinatie.culoare!=cine_muta&&destinatie.piesa)) fiftymoverule=0;//nu trebuie modificata pt en passant deoarece pionul oricum se misca si restarteaza variabila fiftymoverule
                        else {if(fiftymoverule++>=100) {isnotover=0;won=-5;}}
                        for(int i=0; i<8;i++){for(int j=0;j<8;j++){toate_miscarile[ctrmisc][i][j]=Tabla[tbl][i][j];}}ctrmisc++;//tin minte miscarile
                        if(cine_muta){
                        black_inventory[kblack++]=pion_mancat;valblack+=pion_mancat.valoarea;
                        cine_muta=0;}//urm randul lui alb
                        else{
                        white_inventory[kwhite++]=pion_mancat;valwhite+=pion_mancat.valoarea;
                        cine_muta=1;}//urm randul lui negru
                        }
                    }
                    else 
                    {
                        if(move_valid(8,Tabla[tbl],i0,j0,ix,jx,cine_muta,toate_miscarile,ctrmisc-1)==4)//rocada
                        {   
                            if(isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb)) wrong=1;//nu poti iesi din sah prin rocada
                            else{
                            wrong=0;
                            patrat plecare,destinatie;//le tinem minte sa le punem inapoi daca este sah dupa miscare
                            destinatie=Tabla[tbl][ix][jx];
                            plecare=Tabla[tbl][i0][j0];
                            Tabla[tbl][ix][jx]=Tabla[tbl][i0][j0];
                            Tabla[tbl][ix][jx].pozitia_i=ix;
                            Tabla[tbl][ix][jx].pozitia_j=jx;
                            Tabla[tbl][i0][j0].piesa=0;
                            Tabla[tbl][i0][j0].valoarea=0;
                            Tabla[tbl][i0][j0].culoare=2;
                            Tabla[tbl][i0][jx].culoare=2;
                            Tabla[tbl][i0][jx].piesa=0;
                            Tabla[tbl][i0][jx].valoarea=0;
                            if(isincheck(8,Tabla[tbl],cine_muta,ikw,jkw,ikb,jkb)){//anulez miscarea


                                //aici voi verifica si sa nu treaca regele prin sah
                                

                                wrong=1;
                                Tabla[tbl][i0][j0]=plecare;
                                Tabla[tbl][ix][jx]=destinatie;
                            }else{//daca nu e in sah fac schimbarea jucatorului
                            if(plecare.piesa==1||(destinatie.culoare!=cine_muta&&destinatie.piesa)) fiftymoverule=0;//nu trebuie modificata pt en passant deoarece pionul oricum se misca si restarteaza variabila fiftymoverule
                            else {if(fiftymoverule++>=100) {isnotover=0;won=-5;}}
                            for(int i=0; i<8;i++){for(int j=0;j<8;j++){toate_miscarile[ctrmisc][i][j]=Tabla[tbl][i][j];}}ctrmisc++;//tin minte miscarile
                            if(cine_muta){
                            cine_muta=0;}//urm randul lui alb
                            else{
                            cine_muta=1;}//urm randul lui negru
                        }
                    }
                        }else wrong=1;//nu mai facem schimbarea jucatorului nici miscarea in sine daca nu e una valida
                    }
                }
            }
        }
        clearr(2);
        if(won==1)
            {printf("Black won!\n\n");}
        if(won==0)
            {printf("White won!\n\n");}
        if(won==-1)
            {printf("Draw by stalemate!\n\n");}
        if(won==-2)
            {printf("Draw by insufficient material!\n\n");}//DONE!
        if(won==-3)
            {printf("Draw by agreement!\n\n");}
        if(won==-4)
            {printf("Draw by 3 fold repetition!\n\n");}
        if(won==-5)
            {printf("Draw by 50 move rule!\n\n");}//DONE!
        char enter='\n';
        printf("press enter to continue and exit this match");//ca sa apuce sa vada cum si de ce s-a terminat meciul
        scanf("%c",&enter);
        break;
        default:
            printf("Optiune invalida!\n");
        break;
        }
    }while(opt!=0);//initial pusesem while opt dar am facut asa ca sa fiu sigur 100% ca nu va cauza probleme
    return 0;
}