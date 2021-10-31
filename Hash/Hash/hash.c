#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 541
#define NAME_SIZE 20
typedef struct hash {
	char name[NAME_SIZE];
	unsigned short collison;
}hash;

hash Hash_Table[TABLE_SIZE];
int Random_a[10];

void Init_Random() {
	for (int i = 0; i < 10; i++) 
		Random_a[i] = rand() % TABLE_SIZE;
}

void Init_Table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		Hash_Table[i].collison = 0;
		strcpy(Hash_Table[i].name, "");
	}
}

int Hash1(char* arr) {
	int val = 0;
	for (int i = 0; i < strlen(arr); i++) 
		val = ((int)arr[i] + val) % TABLE_SIZE;
	return val;
}

void Hashing_1(char *names) {
	int idx = Hash1(names);
	int Counter = 0;
	while (strcmp(Hash_Table[idx].name, "")) {
		Hash_Table[idx].collison++;
		Counter++;
		idx = (idx + Counter) % TABLE_SIZE;
	}
	strcpy(Hash_Table[idx].name, names);
}

int Ex2_Hash2(char* arr) {
	int val = 0;
	for (int i = 0; i < strlen(arr); i++)
		val = ((int)arr[i] * Random_a[i] + val) % TABLE_SIZE;
	return val;
}

void Hashing_2(char* names) {
	int idx = Ex2_Hash2(names);
	int Counter = 0;
	while (strcmp(Hash_Table[idx].name, "")) {
		Hash_Table[idx].collison++;
		Counter++;
		idx = (idx + Counter * Counter) % TABLE_SIZE;
	}
	strcpy(Hash_Table[idx].name, names);
}

int main() {
	srand(time(NULL));
	Init_Random();
	Init_Table();
	
	char File_name[NAME_SIZE];
	FILE* fp1 = NULL, *fp2 = NULL;
	fp1 = fopen("names.txt", "r");
	if (fp1 == NULL) printf("Error!\n");
	while (fscanf(fp1, "%s", File_name) != EOF) {
		Hashing_1(File_name);
	}

	int Total_Collison_Hashing1 = 0;
	puts("Go Print Using Hash_1");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (!strcmp(Hash_Table[i].name, "")) printf("Hash_Table[ %d ] : EMPTY , %d \n", i, Hash_Table[i].collison);
		else {
			printf("Hash_Table[ %d ] : %s, %d\n", i, Hash_Table[i].name, Hash_Table[i].collison);
			Total_Collison_Hashing1 += Hash_Table[i].collison;
		}
	}
	printf("--------------------------------------------------------------------------------------\n");
	Init_Table();
	fp2 = fopen("names.txt", "r");
	if (fp2 == NULL) printf("Error!\n");
	while (fscanf(fp2, "%s", File_name) != EOF) {
		Hashing_2(File_name);
	}

	int Total_Collison_Hashing2 = 0;
	puts("Go Print Using Hash_2");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (!strcmp(Hash_Table[i].name, "")) printf("Hash_Table[ %d ] : EMPTY , %d \n", i, Hash_Table[i].collison);
		else {
			printf("Hash_Table[ %d ] : %s, %d\n", i, Hash_Table[i].name, Hash_Table[i].collison);
			Total_Collison_Hashing2 += Hash_Table[i].collison;
		}
	}
	
	printf("Using Hash_1 method Total Collison is %d\n", Total_Collison_Hashing1);
	printf("Using Hash_2 method Total Collison is %d\n", Total_Collison_Hashing2);

	return 0;
}