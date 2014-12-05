#include <stdio.h>

void Series_Sum( double sum[]  );
 
int main()
{
	int i;
	double x, sum[3001];
			   
	Series_Sum( sum  );
				 
	x = 0.0;
	for (i=0; i<3001; i++)
	printf("%6.2lf %16.12lf\n", x + (double)i * 0.10, sum[i]);
						 
	return 0;

}

void Series_Sum( double sum[]  ){
	
	double x = 0;
	
	double k;
	int i;
	for(i = 0; i < 3001; i += 20){
		x = i/10.0;
		sum[i] = 0;
		for(k = 10000000; k >= 1; k--){
			sum[i] += 1.0/((k+1.0)*k*(k+x));
		}
		sum[i] *= (1.0 - x);
		sum[i] += 1;
	}
	

	return ;
}
