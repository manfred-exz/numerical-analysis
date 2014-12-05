#include <stdio.h>
#include <math.h>
 
#define ZERO 0.000000001 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11   /* Max Polynomial Degree + 1 */
 
double binary(int n, double c[], double a, double b);
double newton(int n, double c[], double derivative [], double EPS, double x);
double evalPoly(int n, double c[], double x);
double Polynomial_Root(int n, double c[], double a, double b, double EPS);
void decideBinaryRange(int n, double c[], double *a, double *b);
 
int main()
{
	int n;
	double c[MAXN], a, b;
	double EPS = 0.00005;
	int i;

	while (scanf("%d", &n)!= EOF){
		for (i=n; i>=0; i--)
			scanf("%lf", &c[i]);
		scanf("%lf %lf", &a, &b);

		printf("%.4lf\n", Polynomial_Root(n, c, a, b, EPS));
	}


	return 0;

}
double Polynomial_Root(int n, double c[], double a, double b, double EPS){
	double derivative [MAXN];
	int i;
	for(i = 0; i <= n; i++){
		derivative[i] = 0;
	}

	for(i = n - 1; i >= 0; i--){
		derivative[i] = c[i+1]*(i+1);	
	}
	double tmp;
	if(a > b){
		tmp = a, a = b, b = tmp;
	}

	decideBinaryRange(n, c, &a, &b);


	if(evalPoly(n, c, a) > 0){
		tmp = a, a = b, b = tmp;
	}
	
	if(fabs(evalPoly(n, c, a)) < ZERO)
		return fabs(a);
	if(fabs(evalPoly(n, c, b)) < ZERO)
		return fabs(b);


	double binResult = b;
	binResult = binary(n, c, a, b);


	double result = newton(n, c, derivative, EPS, binResult);

	if(fabs(result) < ZERO)
	  result = 0;

	return result;
}

double newton(int n, double f[], double df[], double EPS, double x){
	int i;
	const int MAX_NEWTON_ITER = 100000;

	double lastX = x;
	for(i = 0; i < MAX_NEWTON_ITER; i++){
		x = lastX - evalPoly(n, f, lastX)/ evalPoly(n-1, df, lastX);	
		if(fabs(x - lastX) < EPS/10 && fabs(evalPoly(n, f, x)) < ZERO){
			return x;
		}
		lastX = x;
	}
	return x;
}

void decideBinaryRange(int n, double c[], double *a, double *b){
	int i;
	const int MAX_DIV_NUM = 10000;

	int tmp;
	if(*a > *b){
		tmp = *a, *a = *b, *b = tmp;
	}

	double step = (*b - *a)/ MAX_DIV_NUM;
	double lastX = *a;
	double x = lastX + step;

	double smallest[2] = {evalPoly(n, c, lastX), 1.7976931348623158e+308};
	double smallestIndex[2] = {lastX, 1.7976931348623158e+308};
	int testCount = 0;
	for(i = 0; i < MAX_DIV_NUM ; i++)
	{

		if(evalPoly(n, c, x)*evalPoly(n, c, lastX) < 0){
			*a = lastX;
			*b = x;
			return;
		}

		if(fabs(evalPoly(n, c, x)) <= smallest[1]){
			testCount++;
			if(fabs(evalPoly(n, c, x)) < smallest[0]){
				smallest[1] = smallest[0];
				smallestIndex[1] = smallestIndex[0];
				smallest[0] = fabs(evalPoly(n, c, x));
				smallestIndex[0] = x;
			}
			else{ 
				smallest[1] = fabs(evalPoly(n, c, x));
				smallestIndex[1] = x;
			}
		}
		lastX = x;
		x += step;
	} 
	*a = smallestIndex[0];
	*b = smallestIndex[1];
	
}

double binary(int n, double c[], double a, double b){
	const int MAX_BIN_ITER = 5;
	double mid;

	if( evalPoly(n, c, a) * evalPoly(n, c, b) > 0 )
	{
		return b;
	}

	double valMid = 0;
	int i;
	for(i = 0; i < MAX_BIN_ITER; i++){
		mid = (a+b)/2;
		valMid = evalPoly(n, c, mid);
		if(valMid < 0){
			a = mid;
		}
		else if(valMid > 0){
			b = mid;
		}
		else{
			return mid;
		}
	}
	
	return mid;
}

double evalPoly(int n, double c[], double x){
	double sum = 0;
	double powOfX = 1;
	int i;
	for(i = 0; i <= n; i++)
	{
		sum += c[i]*powOfX;
		powOfX *= x;
	}
	return sum;	
}
