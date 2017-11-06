#include <stdio.h>
#include <stdlib.h>
#define n 4
#define nfac 24

void inverse(int p[], int pinv[]) {
  int i;
  for(i = 0; i < n*n+1; i++) pinv[p[i]]=i;
}

int numtoperm(int num, int perm[]) {
  int x[n]; 
  int taken[n];
  int i;
  int count;
  int index;
  int tmp;
  int place;
  x[n-1] = 0;
  place = 2;
  tmp = num;
  for(i = n-2; i >= 0; i--) {
    x[i] = tmp%place;
    tmp = (tmp-x[i])/place;
    place++;
  }  
  for(i = 0; i < n; i++) taken[i] = 0;
  for(i = 0; i < n; i++) {
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

int leftmost(int perm[], int trans_perms[][n*n+1], int inv_perms[][n*n+1]) {
  int i;
  int max, ind, mid;
  int pnum;
  int *symp;
  int *sympinv;
  int p,q;
  max = n*n+1;
  for(pnum = 0; pnum < nfac-1; pnum++) {
    symp = trans_perms[pnum];
    sympinv = inv_perms[pnum];
    for(i = 1; i < max; i++) {
      p = perm[i];
      if(p == 0) break;
      ind = sympinv[i];
      mid = perm[ind];
      if(mid == 0) break;
      q = symp[mid];
      if(p < q) break;
      if(p > q) return 0;
    }
  }
  return 1;
}

void upperlower(int p[], int upper[], int lower[]) {
  int a,b,c;
  upper[0] = 0;
  lower[0] = 0;
  for(a = 0; a < n; a++) {
    for(b = 0; b < n; b++) {
      for(c = 0; c < n; c++) {
        if(p[n*a+b+1] == 0) upper[n*n*a+n*b+c+1] = 0;
        else upper[n*n*a+n*b+c+1] = n*(p[n*a+b+1]-1)+c+1;
        if(p[n*b+c+1] == 0) lower[n*n*a+n*b+c+1] = 0;
        else lower[n*n*a+n*b+c+1] = n*n*a+p[n*b+c+1];
      }
    }
  }
}

int ok(int p[]) {
  int a[n*n*n+1];
  int b[n*n*n+1];
  int i;
  int x,y;
  upperlower(p, a, b);
  for(i = 0; i <= n*n*n; i++) {
    x = a[b[a[i]]];
    y = b[a[b[i]]];
    if(x != 0 && y != 0 && x != y) return 0;
  }
  return 1;
}

void printperm(int p[]) {
  int i;
  for(i = 1; i < n*n; i++) printf("%d ", p[i]-1);
  printf("%d\n", p[n*n]-1);
}

void perm(int code[], int p[]) {
  int taken[n*n+1];
  int index;
  int i;
  int count;
  for(i = 0; i <= n*n; i++) {
    taken[i] = 0;
    p[i] = 0;
  }
  i = 1;
  while(i <= n*n && code[i-1] != 0) {
    count = 0;
    index = 1;
    while(count < code[i-1]) {
      if(taken[index] == 0) count++;
      index++;
    }
    index--;
    taken[index] = 1;
    p[i] = index;
    i++;
  }
}

void dfs(int code[], int depth, int trans_perms[][n*n+1], int inv_perms[][n*n+1]) {
  int i,j;
  int p[n*n+1];
  perm(code, p);
  if(ok(p)) {
    if(leftmost(p, trans_perms, inv_perms)) {
      if(depth == n*n-1) printperm(p);
      else {
        for(i = 1; i < n*n+1-depth; i++) {
          code[depth] = i;
          for(j = depth+1; j < n*n-1; j++) code[j] = 0;
          dfs(code, depth+1, trans_perms, inv_perms);
        }
      }
    }
  }
}

int main() {
  int code[n*n];
  int i, j;
  int j0, j1;
  int trans_perms[nfac-1][n*n+1];
  int inv_perms[nfac-1][n*n+1];
  int miniperm[n];
  for(i = 0; i < n*n-1; i++) code[i] = 0; 
  code[n*n-1] = 1;
  for(i = 1; i < nfac; i++) { //i=0 is identity permutation
    trans_perms[i-1][0] = 0;
    numtoperm(i, miniperm);
    for(j = 1; j < n*n+1; j++) {
      j0 = (j-1)%n;
      j1 = (j-1-j0)/n;
      trans_perms[i-1][j] = n*miniperm[j1]+miniperm[j0]+1;
    }
    inverse(trans_perms[i-1], inv_perms[i-1]);
  }
  dfs(code, 0, trans_perms, inv_perms);
  return EXIT_SUCCESS;
}
