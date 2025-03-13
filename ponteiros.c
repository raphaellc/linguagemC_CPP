#include <stdio.h>
#include <math.h>

int a, b;
int variave_global;
void update(int *a,int *b) {
    printf("Update %d %d\n", *a, *b);
    *a = 100;
    *b = 200;
    // Complete this function    
    
    /*int sum = *a + *b;
    int sub = *a - *b;
    *a = sum;
    *b = abs(sub);*/
    
}

int main() {
    
    
    int *pa = &a, *pb = &b;
    a = 10;
    b = 15;
    *pa = 20;
    *pb = 30;
    
    printf("%d %d\n", a, b);

    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}