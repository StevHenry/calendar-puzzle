#include "util.h"
#include <stdio.h>


void writeResults(char *path, ComputationResult *results) {
	FILE* fp;
	char row[500];

	//TODO: Retreive file path from program argument
	int err = fopen_s(&fp, path, "w");

	if (err != 0) { //Check for file errors
		perror("Cannot write into file: %s !", path);
		return;
	}
	fprintf(fp, "mois; quantieme (0=SUNDAY, 6=SATURDAY); jour; #solutions; secondes CPU\n");
	for (char index = 0; index < 31; index++) {
		fprintf(fp, "%d; %d; %d; %d; %.2f\n", results[index].month, results[index].day,
			results[index].dayNumber, results[index].resultCount, results[index].computationTime);
	}
	fclose(fp);
}