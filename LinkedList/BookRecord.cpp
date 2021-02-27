//Implementation of BookRecord.h

#include "BookRecord.h"
#include <cstring>
#include <iostream>

//BookRecord Default Class Constructor
BookRecord::BookRecord() {
	//Setting m_sName value to an empty string
	strcpy_s(m_sName, "");

	//Initializing values
	m_lStockNum = 0;
	m_iClassification = 0;
	m_dCost = 0.0;
	m_iCount = 0;
}

//BookRecord Class Constructor with predefined values
BookRecord::BookRecord(const char *name, long sn, int cl, double cost) {
	strcpy_s(m_sName, name);
	m_lStockNum = sn;
	m_iClassification = cl;
	m_dCost = cost;
	m_iCount = 1;
}

//BookRecord Class Deconstructor
BookRecord::~BookRecord() {

}

//Pre: Record has been initialized
//Post: Value of pointer passed in has been set to the value of the name of the record
void BookRecord::getName(char *name) {
	strcpy_s(name, 128, m_sName);
}

//Pre: Record has been initialized
//Post: Name of record has been set
void BookRecord::setName(const char *name) {
	strcpy_s(m_sName, name);
}

//Pre: Record has been initialized
//Post: Stock number of record returned to caller
long BookRecord::getStockNum() {
	return m_lStockNum;
}

//Pre: Record has been initialized
//Post: Stock number for record has been set
void BookRecord::setStockNum(long sn) {
	m_lStockNum = sn;
}

//Pre: Record has been initialized
//Post: The value of the variable passed in by reference has been set to the classification
int BookRecord::getClassification() {
	return m_iClassification;
}

//Pre: Record has been initialized
//Post: Classification of record has been set
void BookRecord::setClassification(int cl) {
	m_iClassification = cl;
}

//Pre: Record has been initialized
//Post: Sets the value of the passed in pointer to the cost of the book record
double BookRecord::getCost() {
	return m_dCost;
}

//Pre: Record has been initialized
//Post: Cost for record has been set
void BookRecord::setCost(double c) {
	m_dCost = c;
}

//Pre: Record has been initialized
//Post: Directly returns the number in stock
int BookRecord::getNumberInStock() {
	return m_iCount;
}

//Pre: Record has been initialized
//Post: NumberInStock has been set for record
void BookRecord::setNumberInStock(int count) {
	m_iCount = count;
}

//Pre: Record has been initialized
//Post: Values are output to console
void BookRecord::printRecord() {
	std::cout << "Name: " << m_sName << " - Stock Number: " << m_lStockNum << " - Classification: " 
		      << m_iClassification << " - Cost: " << m_dCost << " - Count: " << m_iCount << std::endl;
}

void BookRecord::setNext(BookRecord *next) {
	m_pNext = next;
}

BookRecord *BookRecord::getNext(){
	return m_pNext;
}