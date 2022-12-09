#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

struct S {
	int Int;
	char Char;
	float Float;
};

char randChar();
int rngSeed(int);
S** randomValues(int);
void deleteArray(S**, int);
void sortArray(S**, int);
int countChars(S**, int, char);
bool openFile(string, int&, char&);

int main() {

	srand(time(NULL));

	int N, charFlag;
	char X;
	clock_t begin, end;
	double time_spent;

	if (!openFile("data.txt", N, X)) {
		cerr << "Error\n";
		return 0;
	}

	S** A;

	begin = clock();

	A = randomValues(N);

	sortArray(A, N);

	for (int i = 0; i < 20; i++) {
		cout << "A[" << i
			<< "]:  Int: " << A[i]->Int
			<< "   Char: " << A[i]->Char
			<< "   Float: " << A[i]->Float
			<< endl;
	}

	charFlag = countChars(A, N, X);

	cout << "\nChars found: " << charFlag << endl;

	deleteArray(A, N);

	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "\nTime spent: " << time_spent << endl;

	return 0;
}

char randChar() {
	int rng = rand() % 18;
	char rngChar = (char)(rng + 66);
	return rngChar;
}

int rngSeed(int i) {
	return rand() % i;
}

S** randomValues(int N) {
	S** A;
	A = new S * [N];

	int rngA[10001];
	for (int i = -1000; i <= 9000; i++) {
		rngA[i + 1000] = i;
	}
	random_shuffle(begin(rngA), end(rngA), rngSeed);

	for (int i = 0; i < N; i++) {
		A[i] = new S[N];
		A[i]->Int = rngA[i];
		A[i]->Char = randChar();
		A[i]->Float = 1000 + (i + 1);
	}

	return A;
}

void deleteArray(S** A, int N) {
	for (int i = 0; i < N; i++) {
		delete A[i];
	}
	delete[] A;
}

void sortArray(S** A, int N) {
	bool flag;

	for (int i = 0; i < N; i++) {
		flag = false;
		for (int j = 0; j < N - i - 1; j++) {
			if (A[j]->Int > A[j + 1]->Int) {
				swap(A[j], A[j + 1]);
				flag = true;
			}
		}
		if (!flag) {
			break;
		}
	}
}

int countChars(S** A, int N, char X) {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		if (A[i]->Char == X) {
			ret++;
		}
	}

	return ret;
}

bool openFile(string file, int& N, char& X) {
	ifstream ifs(file);

	if (!ifs) {
		return false;
	}
	else {
		ifs >> N >> X;
		ifs.close();
		return true;
	}
}