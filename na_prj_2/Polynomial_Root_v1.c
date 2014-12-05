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
		//TEST
		//printf("The value of f(1), f(2) are %lf, %lf\n", evalPoly(n, c, 1), evalPoly(n, c, 2));
	}


	return 0;

}
double Polynomial_Root(int n, double c[], double a, double b, double EPS){
	double derivative [MAXN];
	int i;
	for(i = 0; i <= n; i++){
		derivative[i] = 0;
	}

	//TEST for derivative[]
	for(i = n - 1; i >= 0; i--){
		derivative[i] = c[i+1]*(i+1);	
		printf("The c for x^%d is : %lf\n", i, derivative[i]);
	}
	double tmp;
	if(a > b){
		tmp = a, a = b, b = tmp;
	}
	//Get a smaller range of (a, b)
	decideBinaryRange(n, c, &a, &b);

	//Make sure that f(a) < 0 and f(b) > 0
	if(evalPoly(n, c, a) > 0){
		tmp = a, a = b, b = tmp;
	}
	
	if(fabs(evalPoly(n, c, a)) < ZERO)
		return fabs(a);
	if(fabs(evalPoly(n, c, b)) < ZERO)
		return fabs(b);

	//Pre-Calculate using the binary method.
	double binResult = b;
	binResult = binary(n, c, a, b);
	printf("The binary result is %lf\n", binResult);

	//Calculate using the Newton's method.
	double result = newton(n, c, derivative, EPS, binResult);
	printf("The Newton's method's result is %16.12lf\n", result);

	if(fabs(result) < ZERO)
	  result = 0;

	return result;
}

double newton(int n, double f[], double df[], double EPS, double x){
	long long i;
	const long long MAX_NEWTON_ITER = 100000000;

	double lastX = x;
	for(i = 0; i < MAX_NEWTON_ITER; i++){
		x = lastX - evalPoly(n, f, lastX)/ evalPoly(n-1, df, lastX);	
		if(fabs(x - lastX) < EPS/10 && fabs(evalPoly(n, f, x)) < ZERO){
			printf("x = %lf, lastX = %lf, diff = %16.12lf\n", x, lastX, x - lastX);
			printf("Newton's method run for %lld times\n", i+1);
			return x;
		}
		lastX = x;
	}
	printf("Accuracy didn't reach demand!\n");
	return x;
}

void decideBinaryRange(int n, double c[], double *a, double *b){
	int i;
	const int MAX_DIV_NUM = 10000;

	int tmp;
	if(*a > *b){
		tmp = *a, *a = *b, *b = tmp;
	}
	printf("Before dicide binary range, (a,b) = (%lf, %lf)\n", *a, *b);

	double step = (*b - *a)/ MAX_DIV_NUM;
	double lastX = *a;
	double x = lastX + step;
	// smallest[0] is smaller then smallest[1]
	double smallest[2] = {evalPoly(n, c, lastX), evalPoly(n, c, x)};
	double smallestIndex[2] = {lastX, x};
	int testCount = 0;
	for(i = 0; i < MAX_DIV_NUM ; i++)
	{
		//If a range with a root is found then, change the range.
		if(evalPoly(n, c, x)*evalPoly(n, c, lastX) < 0){
			*a = lastX;
			*b = x;
			printf("Binary-solution range FOUND! From %.4lf to %.4lf\n", *a, *b);
			return;
		}
		//Keep trace of the x of smallest f(x)
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
	printf("testCOunt = %d\n", testCount);
	printf("Binary-solution range NOT FOUNT! Use an alternative solution. From %.4lf to %.4lf\n", *a, *b);
	
}

double binary(int n, double c[], double a, double b){
	const int MAX_BIN_ITER = 5;
	double mid;

	if( evalPoly(n, c, a) * evalPoly(n, c, b) > 0 )
	{
		printf("Unable to binary!\n");
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
