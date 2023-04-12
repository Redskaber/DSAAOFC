#include<stdio.h>
#include<stdlib.h>


int* shell_sort(int arrlen, int* arr)
{

    int rpInd, lpInd, tmp, incre;
    for (incre = arrlen / 2; incre > 0; incre /= 2){        // incre: [5, 2, 1]
        for (rpInd = incre; rpInd < arrlen; rpInd++){       // rpInd: [5, 2, 1]
            tmp = arr[rpInd];
            for (
                lpInd = rpInd - incre;                      // lpInd: [0, 0, 0]
                lpInd >= 0 && arr[lpInd] > tmp;             // ±È½Ï
                lpInd = lpInd - incre                       // -5, -2, -1
                )
            {
                arr[lpInd + incre] = arr[lpInd];            // right
            }
            arr[lpInd + incre] = tmp;                       // left
        }
    }
    for (int i = 0; i < arrlen; i++) printf("%d ", arr[i]); printf("\n");
    return arr;
}

