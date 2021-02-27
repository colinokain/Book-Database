//-----------------------------------------------------------------------------
// File: Book_Inventory.h
// Header file for a book inventory program implemented as a sorted linked list
//
// Note: All functions which print data on a book must print an appropriate
//       message if it fails to find any book(s) meeting the search criteria
//-----------------------------------------------------------------------------
#pragma once;

#include<iostream>  // This header lets you use cout and cin
#include<fstream>   // This header gives you all the file I/O functions
#include<string.h>
#include<stdlib.h>
#include "BookRecord.h"

using namespace std; // This command lets you use all the I/O function and include headers w/o the ".h"

class Book_Inventory
{
private:
	BookRecord *m_pHead;                		// Pointer to the head of the list
	ifstream m_InFile;                		// File containing the inventory

public:
	Book_Inventory();                       		// Class constructor
	~Book_Inventory();                      		// Class destructor. Must free all list memory
	void ClearList();                       		// Remove all items from the list
	bool readInventory(const char *filename);     	// Read inventory file and build the list
	bool addBook(BookRecord *br);           		// Add the given book to the list 
	BookRecord *removeBook(long stockNum);  		// Remove a book from the list or print message if not found
	BookRecord *searchByStockNumber(long stockNum);	// Search by stock number return pointer to node or NULL if not found
	void searchByClassification(int cl);   			// Search for all books given classification, print all data
	void searchByCost(double min, double max);		// Search for all books within the given cost range
	int getNumberInStock(long sn);          		// Get number of books in stock for the given stock number 
	void printAll();                        		// Print all information on all books in the inventory.
private:
	bool getNextLine(char *line, int lineLen);   	// read next line from a file
};