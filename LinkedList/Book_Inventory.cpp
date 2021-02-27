//-----------------------------------------------------------------------------
// File: Book_Inventory.cpp
// Implementation file for the Book_Inventory class
//-----------------------------------------------------------------------------

#include "Book_Inventory.h"


//Book_Inventory Class Constructor
Book_Inventory::Book_Inventory() {
	m_pHead = nullptr;
}

//Book_Inventory Class Destructor
Book_Inventory::~Book_Inventory() {
	ClearList();
}

//--------------------------------------------
// Function: clearList()
// Purpose: Deletes all items in list from 
//		memory.
//--------------------------------------------
void Book_Inventory::ClearList() {
	BookRecord *tempPtr;

	while (m_pHead != nullptr) {
		tempPtr = m_pHead;
		m_pHead = m_pHead->getNext();
		delete tempPtr;
	}
}

//--------------------------------------------
// Function: readInventory()
// Purpose: Read the inventory data file and
//		build the list.
// Returns: True if successful read
//--------------------------------------------
bool Book_Inventory::readInventory(const char *filename)
{
	char line[128];
	int numBooks;

	m_InFile.open(filename, ifstream::in);

	if (!m_InFile.is_open())
	{
		// m_InFile.is_open() returns false if the file could not be found or
		//    if for some other reason the open failed.
		cout << "Unable to open file" << filename << "\nProgram terminating...\n";
		return false;
	}

	// Read number of books
	getNextLine(line, 128);
	numBooks = atoi(line);

	for (int i = 0; i < numBooks; i++)
	{
		BookRecord *newRecord = new BookRecord();

		getNextLine(line, 128);
		newRecord->setStockNum(atol(line));

		getNextLine(line, 128);
		newRecord->setName(line);

		getNextLine(line, 128);
		newRecord->setClassification(atoi(line));

		getNextLine(line, 128);
		newRecord->setCost(atof(line));

		getNextLine(line, 128);
		newRecord->setNumberInStock(atoi(line));

		addBook(newRecord);
	}
	return true;
}


//--------------------------------------------
// Function: addBook()
// Returns: True if successfully added book
// Pre: Book record is initialized
//		List has been initialized
// Post: Adds book to Book_Inventory List
//--------------------------------------------
bool Book_Inventory::addBook(BookRecord *br) {

	BookRecord *previousRecord;
	BookRecord *location;
	bool moreToSearch;

	location = m_pHead;
	previousRecord = nullptr;
	moreToSearch = (location != nullptr);

	while (moreToSearch) {
		if (br->getStockNum() > location->getStockNum()) {
			previousRecord = location;
			location = location->getNext();
			moreToSearch = (location != nullptr);
		}
		else if (br->getStockNum() < location->getStockNum()) {
			moreToSearch = false;
		}
	}

	if (previousRecord == nullptr) {
		br->setNext(m_pHead);
		m_pHead = br;
	}
	else {
		br->setNext(location);
		previousRecord->setNext(br);
	}

	return true;
}
//--------------------------------------------
// Function: removeBook()
// Returns: BookRecord removed from list
// Pre: List has been initialized
// Post: Book has been unlinked from list
//--------------------------------------------
BookRecord *Book_Inventory::removeBook(long stockNum) {
	BookRecord *tempPtr = m_pHead;
	BookRecord *predLoc = nullptr;

	while (tempPtr->getStockNum() != stockNum) {
		predLoc = tempPtr;
		tempPtr = tempPtr->getNext();

		if (tempPtr == nullptr) {
			cout << "Could not remove book: Book was not found." << endl;
			return nullptr;
		}
	}

	if (predLoc != nullptr) {
		predLoc->setNext(tempPtr->getNext());
	}
	else {
		m_pHead = tempPtr->getNext();
	}

	cout << "Book with stock number " << tempPtr->getStockNum() << " successfully removed." << endl;

	return tempPtr;
}

//-----------------------------------------------
// Function: searchByStockNumber()
// Returns: BookRecord with stock num passed in
// Pre: List has been initialized
// Post: BookRecord returned, else null returned
//-----------------------------------------------
BookRecord *Book_Inventory::searchByStockNumber(long stockNum) {
	BookRecord *next = m_pHead;

	while (next != nullptr) {
		if (stockNum == next->getStockNum()) {
			return next;
		}

		next = next->getNext();
	}

	return NULL;
}

//-------------------------------------------------------------
// Function: searchByStockNumber()
// Pre: List has been initialized
// Post: BookRecords with classification passed in are printed
//-------------------------------------------------------------
void Book_Inventory::searchByClassification(int cl) {

	BookRecord *next = m_pHead;
	int ct = 0;

	cout << "--- Search results for classification ---" << endl;

	while (next != nullptr) {
		if (cl == next->getClassification()) {
			char name[128];
			next->getName(name);

			ct++;
			cout << "BOOK " << ct  << ": " << name << '\t' << next->getStockNum() 
				<< '\t' << next->getClassification() << '\t' << next->getCost() 
				<< '\t' << next->getNumberInStock() << endl;
		}
		next = next->getNext();
	}

	if (ct) {
		cout << "No more books found." << endl;
	}
	else {
		cout << "No books found." << endl;
	}
}

//-----------------------------------------------
// Function: searchByCost()
// Pre: List has been initialized
// Post: BookRecords in cost range are printed
//-----------------------------------------------
void Book_Inventory::searchByCost(double min, double max) {
	BookRecord *next = m_pHead;
	int ct = 0;

	cout << "--- Search results for cost between $" << min << " and $" << max << "---" << endl;

	while (next != nullptr) {

		double cost = next->getCost();

		if (min <= cost && max >= cost) {
			char name[128];
			next->getName(name);

			ct++;

			cout << "BOOK " << ct << ": " << name << '\t' << next->getStockNum()
				<< '\t' << next->getClassification() << '\t' << cost
				<< '\t' << next->getNumberInStock() << endl;
		}
		next = next->getNext();
	}

	if (ct) {
		cout << "No more books found." << endl;
	}
	else {
		cout << "No books found." << endl;
	}
}

//--------------------------------------------------------------------
// Function: getNumberInStock()
// Returns: Number of book records in stock for given stock number
// Pre: List has been initialized
// Post: Number of book records in stock returned for given stock num
//--------------------------------------------------------------------
int Book_Inventory::getNumberInStock(long sn) {

	BookRecord *rec = searchByStockNumber(sn);

	if (rec != nullptr)
		return searchByStockNumber(sn)->getNumberInStock();
	else
		return -1;

}

//-----------------------------------------------
// Function: printAll()
// Pre: List has been initialized
// Post: All book records printed to console
//-----------------------------------------------
void Book_Inventory::printAll() {
	BookRecord *next = m_pHead;

	cout << "*********************************************************" << endl;
	cout << '\t' << "Title" << "\t\t" << "Stk #" << '\t' << "Class" << '\t' << "Cost" << '\t' << "In Stock" << endl;
	cout << "*********************************************************" << endl;

	while (next != nullptr) {
		char name[128];
		next->getName(name);

		cout << name << '\t' << next->getStockNum() << '\t' << next->getClassification() << '\t' << next->getCost() << '\t' << next->getNumberInStock() << endl;

		next = next->getNext();
	}
	cout << "*********************************************************" << endl;
}

//--------------------------------------------
// Function: getNextLine() 
// Purpose:  Read a line from a data file.
//   The next non-comment line read from file
//   is stored in line char array.
//   An empty string is stored if the end of
//   file is reached.
// Returns: bool - true if a valid line was
//   read, false if end of file is reached. 
//--------------------------------------------
bool Book_Inventory::getNextLine(char *line, int lineLen)
{
	int done = false;
	while (!done)
	{
		m_InFile.getline(line, lineLen);

		if (m_InFile.good())    // If a line was successfully read
		{
			if (strlen(line) == 0)  // Skip any blank lines
				continue;
			else if (line[0] == '#')  // Skip any comment lines
				continue;
			else return true;    // Got a valid data line so return with this line
		}
		else // No valid line read, meaning we reached the end of file
		{
			strcpy(line, ""); // Copy empty string into line as sentinal value
			return false;
		}
	} // end while
	return false; // Cannot reach this point but include a return to avoid compiler warning
				  //   that not all paths return a value.
}