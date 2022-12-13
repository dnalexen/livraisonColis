#include "colisB.h"

ColisB::ColisB(int hauteur, int largeur,
               int longueur, QString nom,
               QString pays, int poids):
        Colis(hauteur, largeur,
              longueur, nom,
              pays, poids)
{
    mType = 'B';
}
