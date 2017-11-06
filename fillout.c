#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//interprets a permutation in list form as an operation on two pents
void truthtable(int P[], int tt[][4], int n) {
  int i;
  int ai,bi,aj,bj;
  for(i = 0; i < n*n; i++) {
    bi = i%n;
    ai = (i - bi)/n;
    bj = P[i]%n;
    aj = (P[i] - bj)/n;
    tt[i][0] = ai;
    tt[i][1] = bi;
    tt[i][2] = aj;
    tt[i][3] = bj;
  }
}

void printtt(int tt[][4], int n) {
  int i;
  for(i = 0; i < n*n; i++) printf("%d%d|%d%d\n", tt[i][0], tt[i][1], tt[i][2], tt[i][3]);
}

int factorial(int x) {
  if(x == 0) return 1;
  return x*factorial(x-1);
}

int numtoperm(int num, int perm[], int size) {
  int x[6]; //we assume we never need permutations bigger than size 6
  int taken[6];
  int i;
  int count;
  int index;
  int tmp;
  int place;
  x[size-1] = 0;
  place = 2;
  tmp = num;
  for(i = size-2; i >= 0; i--) {
    x[i] = tmp%place;
    tmp = (tmp-x[i])/place;
    place++;
  }  
  for(i = 0; i < size; i++) taken[i] = 0;
  for(i = 0; i < size; i++) {
    count = 0;
    index = 0;
    while(count < x[i]+1) {
      if(taken[index] == 0) count++;
      index++;
    }
    index--;
    taken[index] = 1;
    perm[i] = index;
  }
}

void printarray(int arr[], int length) {
  int i;
  for(i = 0; i < length-1; i++) printf("%d ", arr[i]);
  printf("%d\n", arr[length-1]);
}

void trans(int perm[], int permout[], int symp[], int n) {
  int i,p0,p1,i0,i1;
  for(i = 0; i < n*n; i++) {
    p0 = perm[i]%n;
    p1 = (perm[i]-p0)/n;
    i0 = i%n;
    i1 = (i - i0)/n;
    permout[n*symp[i1] + symp[i0]] = n*symp[p1]+symp[p0];
  }
}

int matchperm(int p1[], int p2[], int length) {
  int i;
  for(i = 0; i < length; i++) if(p1[i] != p2[i]) return 0;
  return 1;
}

void copyperm(int p1[], int p2[], int length) {
  int i;
  for(i = 0; i < length; i++) p2[i] = p1[i];
}

int main(int argc, char *argv[]) {
  FILE *in;
  char *line;
  char *remainder;
  char *cur;
  int perm[36];
  int allperms[1000000][36];
  int permout[36];
  int i,j,k;
  size_t nbytes = 512;
  int bytes_read;
  int n;
  int symp[6];
  int total;
  int found;
  if(argc != 2) {
    printf("Usage: cycles filename.txt\n");
    return EXIT_SUCCESS;
  }
  in = fopen(argv[1], "r");
  if(in == NULL) {
    printf("Unable to open %s.\n", argv[1]);
    return EXIT_SUCCESS;
  }
  line = malloc(512*sizeof(char));
  if(line == NULL) {
    printf("Memory allocation error.\n");
    return EXIT_SUCCESS;
  }
  total = 0;
  do {
    bytes_read = getline(&line, &nbytes, in);
    n = 0;
    if(bytes_read == 65 || bytes_read == 66) n = 5;
    if(bytes_read == 38 || bytes_read == 39) n = 4;
    if(bytes_read == 18 || bytes_read == 19) n = 3;
    if(bytes_read == 8 || bytes_read == 9) n = 2;
    remainder = line;
    if(n != 0) {
      cur = strtok(line, " ");
      sscanf(cur, "%d", &perm[0]);
      for(i = 1; i < n*n; i++) {
        cur = strtok(NULL, " "); 
        sscanf(cur, "%d", &perm[i]);
      }
      for(j = 0; j < factorial(n); j++) {
        numtoperm(j, symp, n);
        trans(perm, permout, symp, n);
        found = 0;
        for(k = 0; k < total; k++) if(matchperm(permout, allperms[k], n*n)) found = 1;
	if(!found) { 
	  copyperm(permout, allperms[total++], n*n);
          printarray(permout, n*n);
	}
      }
    }
  }while(n > 0);
  fclose(in);
  free(line);
  return EXIT_SUCCESS;
}


/*int main() {
  int i,j;
  int perm[6];
  for(j = 3; j < 7; j++) {
    for(i = 0; i < factorial(j); i++) {
      numtoperm(i, perm, j);
      printarray(perm, j);
    }
  }
  return EXIT_SUCCESS;
}*/
