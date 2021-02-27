//-----------------------------------------------------------------------------
// Book_Database.h
// Header file for a book database program implemented as a binary search tree
//
// Note: All functions which print data on a book must print an appropriate
//       message if it fails to find any book(s) meeting the search criteria
//-----------------------------------------------------------------------------
#pragma once;
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "BookRecord.h"

using namespace std;

class Book_Database
{
   private:
      BookRecord *m_pRoot;                         		// Pointer to root of the tree
      ifstream   m_InFile;                         		// File containing inventory


   public:
      Book_Database ();                            		// Class constructor
      ~Book_Database ();                           		// Class destuctor
      bool readDatabase(const char *filename);           		// Read database from file
      bool addBook(BookRecord *br);                		// Add the given book to the list
      BookRecord *removeBook(long stockNum);              	// Remove a book from the list
      BookRecord *searchByStockNumber(long stockNum);    	// Search for a book by stock number
      void searchByClassification(int cl);         		// Search for all books of the given classification
      void searchByCost(double min, double max);   		// Search for all books whose cost is within the given range
      int getNumInStock(long sn);				// Get number of books of given stock number in stock
      void PrintAll();                             		// Print all items in the database
   private:
      void ClearList(BookRecord *rt);              		// Recursively remove any items from the list
      bool getNextLine(char *line, int lineLen);   		// Read next line from a file
      void searchByClassification(int cl, BookRecord *rt);	// Recursive search by classification
      void searchByCost(double min, double max, BookRecord *rt);// Recursive search by cost range
      void PrintAll(BookRecord *rt);               		// Recursive print all
};
