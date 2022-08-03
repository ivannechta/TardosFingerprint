#pragma once
#ifndef TARDOS_H_INCLUDED
#define TARDOS_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.1415926


class Tardos {
private:
	int CodeLength;
	int N;
	char **Code;
	int c;
	double *P;
	double k;


private:
	template <typename T>
	void swap(T&a, T &b) {
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}
	void Clear() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < CodeLength; j++) {
				Code[i][j] = '0';
			}
		}
	}
	double getRND(double a, double b) {
		return 1.0l*(rand() % 10000)*(b - a) / 10000.0l + a;
	}
	double sqr(double x) {
		return x * x;
	}
	char GenOne(double prob) {
		return (rand() % 1000 < 1000.0l*prob) ? '1' : '0';
	}

	int CalcScore(int i, char *y) {
		double score = 0, U;
		for (int j = 0; j < CodeLength; j++) {
			U = (Code[i][j] == '1') ? sqrt((1 - P[j])/P[j]) : -sqrt(P[j] / (1 - P[j]));
			score += (y[j] - '0')*U;
		}
		return score;
	}

public:

	Tardos(int CNT, double c0, double eps) {
		srand(time(NULL));
		N = CNT;
		k = ceil(log(1 / eps));
		c = c0;
		CodeLength = 100 * c*c*k;
		P = new double[CodeLength];
		Code = new char*[CNT];
		for (int i = 0; i < CNT; i++) {
			Code[i] = new char[CodeLength];
		}
		Clear();
	}

	void ShowCodeTable() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < CodeLength; j++) {
				printf("%c", Code[i][j]);
			}
			printf("\n\n");
		}
		printf("Length=%d\n", CodeLength);
	}
	void ShowCodeWord(int i) {
		for (int j = 0; j < CodeLength; j++) {
			printf("%c ", Code[i][j]);
		}
	}
	void Info() {
		printf("Total %d users.\nCodeLength %d bits.\n", N, CodeLength);
		printf("Collision limit = %d users.\n", c);
	}
	void BuildCode() {
		double t = 1.0l / (300.0l*c);
		double t_ = asin(sqrt(t));
		double r;

		for (int j = 0; j < CodeLength; j++) {
			r = getRND(t_, PI / 2 - t_);
			P[j] = sqr(sin(r));
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < CodeLength; j++) {
				Code[i][j] = GenOne(P[j]);
			}
		}
	}
	char * Collide2(int a, int b) {
		char *y = new char[CodeLength];
		for (int j = 0; j < CodeLength; j++) {
			y[j] = (Code[a][j] != Code[b][j]) ? '0' + rand() % 2 : Code[a][j];
		}
		return y;
	}
	void Detect(char *y, int collide_users) {
		double *score = new double[N];
		int *user = new int[N];
		for (int i = 0; i < N; i++) {
			score[i] = CalcScore(i, y);
			user[i] = i;
		}
		// sort
		int flag = 1;
		while (flag) {
			flag = 0;
			for (int i = 0; i < N - 1; i++) {
				if (score[i] < score[i + 1]) {
					flag = 1;
					swap<double>(score[i], score[i + 1]);
					swap<int>(user[i], user[i + 1]);
				}
			}
		}
		// show
		for (int i = 0; i < collide_users; i++) {
			printf("[%d %.4f] ", user[i], score[i]);
		}
		printf("\n");
		delete user;
		delete score;


	}
};

#endif // TARDOS_H_INCLUDED


