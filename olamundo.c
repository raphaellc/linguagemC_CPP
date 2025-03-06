#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int iOp1, iOp2, iSoma, iSub;
    float fOp1, fOp2, fSoma, fSub;
    
    scanf("%d %d", &iOp1, &iOp2);
    scanf("%f %f", &fOp1, &fOp2);
    iSoma = iOp1 + iOp2;
    iSub = iOp1 - iOp2;
    fSoma = fOp1 + fOp2;
    fSub = fOp1 - fOp2;
    
    printf("%d %d\n", iSoma, iSub);
    printf("%.1f %.1f\n", fSoma, fSub);

    
    return 0;
}


