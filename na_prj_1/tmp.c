#include <stdio.h>

int main(){
	double k;
	double sum1 = 0;
	double sum2 = 0;
	for(k = 5000000; k >= 20001; k--){
		sum1 += 1.0/((k+1)*k*k);
		sum2 += 1.0/((k+1)*k*(k+300));
	}
	printf("Sum 1 = %16.12lf\n", sum1);
	printf("Sum 2 = %16.12lf\n", sum2);

	
}
