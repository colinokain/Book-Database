#pragma once


//BookRecord class, function implementations in BookRecord.cpp
class BookRecord {
private:
	char m_sName[128];
	long m_lStockNum;
	int m_iClassification;
	double m_dCost;
	int m_iCount;
	BookRecord *m_pNext;

public:
	
	//Constructor
	BookRecord();

	//Constructor
	BookRecord(const char *name, long sn, int cl, double cost);

	//Deconstructor
	~BookRecord();

	//Function: Function copies value of m_sName to a pointer
	//Pre: Record has been initialized
	//Post: Value of pointer passed in has been set to the value of the name of the record
	void getName(char *name);

	//Function: Function sets the name of the record using a pointer
	//Pre: Record has been initialized
	//Post: Name of record has been set
	void setName(const char *name);

	//Function: Gets the stock number of the record
	//Pre: Record has been initialized
	//Post: Stock number of record returned to caller
	long getStockNum();

	//Function: Sets the stock number of the record using a passed in variable
	//Pre: Record has been initialized
	//Post: Stock number for record has been set
	void setStockNum(long sn);

	//Function: Passes a variable by reference and sets the value to the classification
	//Pre: Record has been initialized
	//Post: The value of the variable passed in by reference has been set to the classification
	int getClassification();

	//Function: Sets the classification of the record to the value of a passed in variable
	//Pre: Record has been initialized
	//Post: Classification of record has been set
	void setClassification(int cl);

	//Function: Sets the value passed in to the cost of the record
	//Pre: Record has been initialized
	//Post: Sets the value of the passed in pointer to the cost of the book record
	double getCost();

	//Function: Sets the cost of the record to the value passed in
	//Pre: Record has been initialized
	//Post: Cost for record has been set
	void setCost(double c);

	//Function: Gets the number in stock
	//Pre: Record has been initialized
	//Post: Directly returns the number in stock
	int getNumberInStock();

	//Function: Sets the number in stock using the passed in value
	//Pre: Record has been initialized
	//Post: NumberInStock has been set for record
	void setNumberInStock(int count);

	//Function: Prints the record to the console
	//Pre: Record has been initialized
	//Post: Values are output to console
	void printRecord();

	void setNext(BookRecord *next);

	BookRecord *getNext();

};
