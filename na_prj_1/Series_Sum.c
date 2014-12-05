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
	for(k = 500000; k >= 20001; k--){
		pre_sum += 1.0/((k+1)*k*k);
	}
	int i, count;
	double ref_x = 1;
	double ref_value = 1;
	for(i = 0, count = 0; i < 3001; i++, count++){
		x = i/10.0;
		sum[i] = 0;
		for(k = 20000; k >= 1; k--){
			sum[i] += 1.0/((k+ref_x)*k*(k+x));
		}
		sum[i] += pre_sum;
		sum[i] *= (ref_x - x);
		sum[i] += ref_value;
		/*
		if(count == 3){
			count = 0;
			ref_x = i/10.0;
			ref_value = sum[i];
		}
		*/
	}

	
	

	return ;
}
