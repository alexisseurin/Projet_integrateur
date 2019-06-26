#include <stdio.h>
#include <stdlib.h>
#define INF 9999
#define V 16

int findMin(int x, int y) {
  if (x < y) {
    return x;
  }
  return y;
}

/**
* this function will check if the vertex is marked
*/
int isMarked(int v, int markedVertices[], int markedVerticesIdx) {
  for (int i = 0; i < markedVerticesIdx; i++) {
    if (v == markedVertices[i]) {
      return 1;
    }
  }

  return 0;
}

/**
* this function will find shortest path between source and destination vertex
*/
void dijkstra(int map[V][V], int src, int dest) {

  //variables
  int i, r, c,
    tmpC,
    min,
    currVertex,
    edgeWt = 0,
    destValue = 0,
    markedValue = 0,
    wtTableR = 0,
    markedVerticesIdx = 0;

  /**
   * array containing vertices in the shortest path
   */
  int shortestPathVertices[V] = {-1};
  int shortestPathVerticesIdx = 0;

  /**
   * this table will hold the weight
   */
  int weightTable[V][V];
  for (r = 0; r < V; r++) {
    for (c = 0; c < V; c++) {
      weightTable[r][c] = INF;
    }
  }
  weightTable[wtTableR++][src] = 0;

  /**
   * vertices that are marked
   */

  int markedVertices[V] = {-1};
  markedVertices[markedVerticesIdx++] = src;
  currVertex = src;

  /**
  * find shortest path
   */
  while(currVertex != dest) {

    /**
     * copy marked values to the next row of weightTable
     */
    for (i = 0; i < markedVerticesIdx; i++) {
      c = markedVertices[i];
      weightTable[wtTableR][c] = weightTable[wtTableR - 1][c];
    }

    /**
     * find the weight from the current vertex to all the other
     * vertices that are directly connected and not yet marked
     */
    for (c = 0; c < V; c++) {

      if (c != currVertex && !isMarked(c, markedVertices, markedVerticesIdx)) {

        edgeWt = map[currVertex][c];
        destValue = weightTable[wtTableR - 1][c];
        markedValue = weightTable[wtTableR][currVertex];

        min = findMin(destValue, markedValue + edgeWt);

        weightTable[wtTableR][c] = min;

      }

    }

    /**
     * find minimum unmarked vertices in current row
     */
    min = INF;
    for (c = 0; c < V; c++) {

      if (!isMarked(c, markedVertices, markedVerticesIdx)) {
        if (weightTable[wtTableR][c] < min) {
          min = weightTable[wtTableR][c];
          tmpC = c;
        }
      }

    }

    /**
     * found a new vertex for marking
     */
    markedVertices[markedVerticesIdx++] = tmpC;
    currVertex = tmpC;

    /**
     * variables update
     */
    wtTableR++;

  }

  /**
   * compute shortest path vertices
   */
  c = dest;
  shortestPathVertices[shortestPathVerticesIdx++] = c;
  markedValue = weightTable[wtTableR - 1][dest];
  for (r = wtTableR - 2; r >= 0; r--) {

    if (weightTable[r][c] != markedValue) {
      c = markedVertices[r];
      markedValue = weightTable[r][c];
      shortestPathVertices[shortestPathVerticesIdx++] = c;
    }

  }

  /**
   * display the weight and shortest path
   */
   int then = src+1 , now = src+1, after;
  //printf("Shortest Path between %d and %d\n", src, dest);

  for (i = shortestPathVerticesIdx-1; i >= 0; i--) {
        after = shortestPathVertices[i]+1;
        tourner(then, now, after);
        then = now;
        now = shortestPathVertices[i]+1;
    }
// printf("\n");
// printf("Weight of the path: %d\n", weightTable[wtTableR-1][dest]);

}

void tourner(int c, int a, int b){
    a--;
    b--;
    c--;
    int coo[16][16] = {{0,0,0,0,1,1,3,3,4,5,5,4,4,1,1,5}, //=x
                     {0,2,4,5,5,4,4,5,5,5,2,2,1,1,0,0}}; //=y

    int xa,ya,xb,yb,xc,yc,turn;

    xa = coo[0][a];
    ya = coo[1][a];

    xb = coo[0][b];
    yb = coo[1][b];

    xc = coo[0][c];
    yc = coo[1][c];



  if(a != b || b!= a){
   printf(" de %d a %d\n ", a+1, b+1);
 }
//---------------------------------------------------------
    if ((xb-xa)!=0 && (yb-ya)!=0)
    {
        printf("impossible"); //A SUPPRIMER
    }

    if(((xc-xa)!=0) &&((xb-xa)==0))
       {
           turn = 1;
       }

    if(((yc-ya)!=0) &&((yb-ya)==0))
       {
           turn = 1;
       }
    if(((yb-ya>0) || (yb-ya<0)) && turn==0)
    {
        printf("avancer");  //REMPLACER PAR AVANCER
    }

    if(((xb-xa>0) || (xb-xa<0)) && turn==0)
    {
        printf("avancer");  //REMPLACER PAR AVANCER
    }
    // REMPLACER LES TOURNANTS PAR LA METHODE ADEQUATE

    if((xb>xa)&&(turn == 1) && (yc<ya)){
    printf("tourner droite");
    }

    if((xb>xa)&&(turn == 1) && (yc>ya)){
    printf("tourner gauche");
    }

    if((xb<xa)&&(turn == 1) && (yc<ya)){
    printf("tourner gauche");
    }

    if((xb<xa)&&(turn == 1) && (yc>ya)){
    printf("tourner droite");
    }


    if((yb<ya)&&(turn == 1) && (xc>xa)){
    printf("tourner gauche");
    }

    if((yb<ya)&&(turn == 1) && (xc<xa)){
    printf("tourner droite");
    }

    if((yb>ya)&&(turn == 1) && (xc<xa)){
    printf("tourner gauche");
    }

    if((yb>ya)&&(turn == 1) && (xc>xa)){
    printf("tourner droite");
    }
    printf("\n");
    turn = 0;
}

int main(void) {
  int map[V][V] = {{INF,2,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1,INF},
                       {2,INF,2,INF,INF,INF,INF,INF,INF,INF,INF,4,INF,INF,INF,INF},
                       {INF,2,INF,1,INF,1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                       {INF,INF,1,INF,1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                       {INF,INF,INF,1,INF,1,INF,2,INF,INF,INF,INF,INF,INF,INF,INF},
                       {INF,INF,1,INF,1,INF,2,INF,INF,INF,INF,INF,INF,INF,INF,INF},
                       {INF,INF,INF,INF,INF,2,INF,1,INF,INF,INF,INF,INF,INF,INF,INF},
                       {INF,INF,INF,INF,2,INF,1,INF,1,INF,INF,INF,INF,INF,INF,INF},
                       {INF,INF,INF,INF,INF,INF,INF,1,INF,1,INF,3,INF,INF,INF,INF},
                       {INF,INF,INF,INF,INF,INF,INF,INF,1,INF,3,INF,INF,INF,INF,INF},
                       {INF,INF,INF,INF,INF,INF,INF,INF,INF,3,INF,1,INF,INF,INF,2},
                       {INF,4,INF,INF,INF,INF,INF,INF,3,INF,1,INF,1,INF,INF,INF},
                       {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1,INF,3,INF,INF},
                       {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,3,INF,1,INF},
                       {1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1,INF,4},
                       {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,2,INF,INF,INF,4,INF}};

  int depart = 4;
  int destination = 12;
 printf("Le plus court chemin entre %d et %d :\n", depart, destination);
  dijkstra(map, depart-1, destination-1);
  return 0;
}
