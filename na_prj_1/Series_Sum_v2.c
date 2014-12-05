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
	double pre_sum = 0;	
	double k;

	for(k = 500000; k>= 18001; k--){
		pre_sum += 1.0/(k*(k+1)*(k+2)*(k+200));
	}
	int i;
	for(i = 0; i < 3001; i++ ){
		x = i/10.0;
		sum[i] = 0;
		for(k = 18000; k >= 1; k--){
			sum[i] += 1.0/((k+1)*(k+2)*k*(k+x));
		}

		sum[i] += pre_sum;
		if(x == 1){
			sum[i] = 1;
			continue;
		}
		else if(x == 2){
			sum[i] = 0.75;
			continue;
		}
		sum[i] = sum[i] + 1/(1-x) - 0.75/(2-x);
		sum[i] *= (1-x)*(2-x);
	}

	
	

	return ;
}
