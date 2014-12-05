#include <stdio.h>

int main(){
	double i;
	double sum = 0;
	for(i = 5000000; i >= 1; i--){
		sum += 1.0/((i+1)*i*(i+0));
	}
	sum += 1;
	printf("The first sum: %16.12lf\n", sum);

	double x;
	for(i = 1; i < 3001; i++){
		x = i/10.0;
		printf("The next sum: %16.12lf\n", sum*(1-x)/(1-x+0.1));
	}

	return 0;
}
