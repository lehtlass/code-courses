#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


const int GT = 1;  // your guess is greater than the guessed number
const int ST = 2; // your guess is smaller than the guessed number
const int EQUAL = 3; // success!!  your guess is equal to the guessed number

const int _n = 1000;


int *_a, *_b, *_gcd, _i;
const int minimum = 1;
const int maximum = 1000;
int guessCount;

/*
int round(double toRound){
	return (int)floor(toRound + 0.5);
}*/

int uniformRandom(int a, int b){
	return round(a + (b - a) * (((double)rand())/RAND_MAX));
}

int gcd_naive(int a, int b);

int guess_a(int guess){
	guessCount++;
	if (guess == _a[_i]){
		return EQUAL;
	}else if (guess < _a[_i]){
		return ST;
	}else return GT;
}

int guess_b(int guess){
	guessCount++;
	if (guess == _b[_i]){
		return EQUAL;
	}else if (guess < _b[_i]){
		return ST;
	}else return GT;
}

bool verify(int a, int b, int gcd){
	bool ok = true;
	if (a != _a[_i]){
		printf("Guessed a incorrect!!  Your guess (%d) is not equal to %d\n", a, _a[_i]);
		ok = false;
	}
	if (b != _b[_i]){
		printf("Guessed b incorrect!!  Your guess (%d) is not equal to %d\n", b, _b[_i]);
		ok = false;
	}
	if (gcd != _gcd[_i]){
		printf("Calculated GCD is incorrect!!  Your value (%d) is not equal to %d = GCD(%d, %d)\n", gcd, _gcd[_i], _a[_i], _b[_i]);
		ok = false;
	}
	return ok;
}

void initialize(){
	//printf("Generating %d pair(s) of random numbers...", _n);
	//srand(2008);
	srand(1000*time(0));
	_a = new int[_n];
	_b = new int[_n];
	_gcd = new int[_n];
	for (int i=0; i!=_n; i++){
		_a[i] = uniformRandom(minimum, maximum);
		_b[i] = uniformRandom(minimum, maximum);
		_gcd[i] = gcd_naive(_a[i], _b[i]);
		//printf("%4d %4d %4d\n", _a[i], _b[i], _gcd[i]);
	}
	_i = 0;
	guessCount = 0;
	//printf("done!\n");
}

void terminate(){
	delete _a; delete _b; delete _gcd;
}

int guess_naive(bool a){
	for (int i=minimum; i<=maximum; i++){
		if (a){
			if (guess_a(i) == EQUAL) return i;
		}else{
			if (guess_b(i) == EQUAL) return i;
		}
	}
	return -1; // this statement will never be reached
}

int gcd_naive(int a, int b){
	int _min, _max;
	if (a < b){
		_min = a;
		_max = b;
	}else{
		_min = b;
		_max = a;
	}
	for (int i=_min; i>=1; i--){
		if (((_min % i) == 0) && ((_max % i) == 0)){
			return i;
		}
	}
	return 1;
}

int guess_fast(bool a);

int gcd_fast(int a, int b);


void main(){

	// BEGIN INITIALIZATION CODE *********************************************
	initialize();
	_i = 0;
	printf("Press any key to start\n"); 
	getchar();	
	bool all_ok = true;
	int a, b, gcd;
	clock_t start_time = clock();
	// END INITIALIZATION CODE ***********************************************
	
	/*
	// NAIVE CODE -- these are correct (but slow) versions.  
	a = guess_naive(true); // call the naive guessing function to obtain the value of mystery number a
	b = guess_naive(false); // call the naive guessing function to obtain the value of mystery number b
	gcd = gcd_naive(a, b);
	*/	
	
	for (;_i!=_n; _i++){
		// this is the code to test your procedures.  				
		a = guess_fast(true); b = guess_fast(false);  // ECHTE PROCEDURES
		//a = guess_naive(true); b = guess_naive(false);
		
		gcd = gcd_fast(a, b); // ECHTE PROCEDURE
		//gcd = gcd_naive(a, b);

		
			// THIS CODE WILL CHECK WHETHER THE VALUES YOU HAVE CALCULATED ARE CORRECT **
		bool ok = verify(a, b, gcd);
		if (!ok){ 
			all_ok = false;	
			break;
		}//else printf("%d OK\n", _i);
	}
	
	// BEGIN FINALIZATION CODE ************************************************ 
	double iTime = ((double)(clock() - start_time)/CLK_TCK);	
	terminate();	
	if (all_ok) printf("All values correct.\n");
	else printf("Not all values were correct.\n");
	printf("Computation time: %.3f seconds.\nAverage #guesses per number: %.2f\n", iTime, (double) guessCount/(2*_n));
	printf("Press any key to exit\n");
	getchar();
	// END FINALIZATION CODE $$$***********************************************
}
