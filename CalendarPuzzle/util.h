#pragma once
#ifndef UTIL_H
#define UTIL_H

typedef enum {
	SUNDAY = 0,
	MONDAY = 1, 
	TUESDAY = 2, 
	WEDNESDAY = 3,
	THURSDAY = 4,
	FRIDAY = 5,
	SATURDAY = 6
	
} Day;


typedef enum {
	JANUARY = 1, FEBRUARY = 2, MARCH = 3, APRIL = 4, MAY = 5, JUNE = 6, 
	JULY = 7, AUGUST = 8, SEPTEMBER = 9, OCTOBER = 10, NOVEMBER = 11, DECEMBER = 12
} Month;


typedef struct {
	char dayNumber;
	Day day;
	Month month;
	int resultCount;
	double computationTime;
} ComputationResult;


void writeResults(char* path, ComputationResult *results);

#endif
