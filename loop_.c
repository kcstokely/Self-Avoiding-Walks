#include <time.h>
#include <stdio.h>

#define D 2
#define L 12

unsigned long long int count;

void tree(int);

int main(){

  time_t intro;
  time(&intro);

  count=0;
  tree(2);
  count*=2*D;

  printf("%d %d %llu %d\n",D,L,count,(int)difftime(time(NULL),intro));

  return 0;
}

void tree(int level)
{

  // there is a 2*D degeneracy in the direction of the first step
  // so we fix that direction (hence not all disps start at zero)
  // and call the first tree at level 2, multiplying output by 2D
 
  static int Y[L][D] = {-1};  // displacement in D since L
  static int Z[L]    = {1};   // number Ds nonzero since L

  int i,j,k,l;

    for(i=0;i<D;i++){
      for(j=-1;j<2;j+=2){

        // update all displacements
        for(k=level;k--;){
          Y[k][i]+=j;
          if(Y[k][i]==j)
            Z[k]++;
          if(Y[k][i]==0){
            Z[k]--;
            if(Z[k]==0)
              goto end;
          }
        }

        // if here, no loops
        if(level<L)
          tree(level+1);
        else
          count++;

        // undo displacements
        end:
        for(l=level-1;l>=k;l--){
          Y[l][i]-=j;
          if(Y[l][i]==0)
              Z[l]--;
          if(Y[l][i]==-j)
              Z[l]++;
          }

      }
    }

  return;
}






