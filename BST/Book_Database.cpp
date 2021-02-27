//-----------------------------------------------------------------------------
// File: Book_Database.cpp
// Implementation file for the Book_Database class
//-----------------------------------------------------------------------------

#include "Book_Database.h"

//Book_Database Class Constructor
Book_Database::Book_Database() {
	m_pRoot = nullptr;
}

//Book_Database Class Destructor
Book_Database::~Book_Database() {
	ClearList(m_pRoot);
}

//--------------------------------------------
// Function: ClearList()
// Purpose: Deletes all items in list from
//		memory.
//--------------------------------------------
void Book_Database::ClearList(BookRecord *rt) {
  if (rt != nullptr){
    ClearList(rt->getLeft());
    ClearList(rt->getRight());
    delete rt;
  }
}

//--------------------------------------------
// Function: readDatabase()
// Purpose: Read the inventory data file and
//		build the list.
// Returns: True if successful read
//--------------------------------------------
bool Book_Database::readDatabase(const char *filename)
{
     char     line[128];
     int      numBooks;
     // define other variables here as needed

    m_InFile.open(filename, ifstream::in);
    if(!m_InFile.is_open())
    {
        // m_InFile.is_open() returns false if the file could not be found or
        //    if for some other reason the open failed.
        cout << "Unable to open file" << filename << "\nProgram terminating...\n";
        return false;
    }
    // Read number of books
    getNextLine(line, 128);
    numBooks = atoi(line);
    for(int i=0; i<numBooks; i++)
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
//		Tree has been initialized
// Post: Adds book to Book_Database Tree
//--------------------------------------------
bool Book_Database::addBook(BookRecord *br) {
    BookRecord *nodePtr = m_pRoot;
    BookRecord *parentPtr = nullptr;
    bool found = false;
    if (m_pRoot == nullptr){
        m_pRoot = br;
		return true;
    }
    else{
        while (nodePtr != nullptr && !found){
            if (br->getStockNum() < nodePtr->getStockNum())
            {
              parentPtr = nodePtr;
              nodePtr = nodePtr->getLeft();
            }
            else if (br->getStockNum() > nodePtr->getStockNum())
            {
              parentPtr = nodePtr;
              nodePtr = nodePtr->getRight();
            }
            else
              found = true;
        }
        if(br->getStockNum() > parentPtr->getStockNum()){
            parentPtr->setRight(br);
			return true;
        }else if (br->getStockNum() < parentPtr->getStockNum()) {
			parentPtr->setLeft(br);
			return true;
		}
		else {
			return false;
		}
    }

}


//--------------------------------------------
// Function: removeBook()
// Returns: BookRecord removed from tree
// Pre: tree has been initialized
// Post: Book has been unlinked from tree
//--------------------------------------------
BookRecord *Book_Database::removeBook(long stockNum) {
	BookRecord *node = m_pRoot;
	BookRecord *parent = nullptr;
	BookRecord *temp;
	if (node == nullptr) {
		return nullptr;
	}

	while (node != nullptr && stockNum != node->getStockNum()) {
		if (stockNum > node->getStockNum()) {
			parent = node;
			node = node->getRight();
		}
		else if (stockNum < node->getStockNum()) {
			parent = node;
			node = node->getLeft();	
		}
	}

	if (node == nullptr) {
		return nullptr;
	}

	temp = node; 

	if (node->getRight() == nullptr) {
		if (parent == nullptr) {
			node = node->getLeft();
		}
		if (parent->getLeft() == node) {
			node = node->getLeft();
			parent->setLeft(node);
		}
		else {
			node = node->getLeft();
			parent->setRight(node);
		}
		return temp;
	}
	else if (node->getLeft() == nullptr) {
		if (parent == nullptr) {
			node = node->getRight();
		}
		if (parent->getLeft() == node) {
			node = node->getRight();
			parent->setLeft(node);
		}
		else {
			node = node->getRight();
			parent->setRight(node);
		}
		return temp;
	}
	else {
		temp = node->getLeft();
		BookRecord *newParent = nullptr;


		while (temp->getRight() != nullptr) {
			newParent = temp;
			temp = temp->getRight();
		}
		if (newParent != nullptr) {
			newParent->setRight(nullptr);
		}
		
		if (node->getLeft() != temp) {
			temp->setLeft(node->getLeft());
			temp->setRight(node->getRight());
		}
		else {
			temp->setRight(node->getRight());
		}
		if (parent != nullptr) {
			if (parent->getLeft() == node) {
				parent->setLeft(temp);
			}
			else {
				parent->setRight(temp);
			}
		}
		if (m_pRoot == node) {
			m_pRoot = temp;
		}
		return node;
	}
}


//-----------------------------------------------
// Function: searchByStockNumber()
// Returns: BookRecord with stock num passed in
// Pre: tree has been initialized
// Post: BookRecord returned, else null returned
//-----------------------------------------------
BookRecord *Book_Database::searchByStockNumber(long stockNum) {
	BookRecord *nodePtr = m_pRoot;
	BookRecord *parentPtr = nullptr;
	bool found = false;
	while (nodePtr != nullptr && !found){
		if (stockNum < nodePtr->getStockNum()){
		
			parentPtr = nodePtr;
			nodePtr = nodePtr->getLeft();
		}
		else if (stockNum > nodePtr->getStockNum()){
		
			parentPtr = nodePtr;
			nodePtr = nodePtr->getRight();
		}
		else
			found = true;
	}
	return nodePtr;
}

//-------------------------------------------------------------
// Function: searchByClassification()
// Pre: tree has been initialized
// Post: BookRecords with classification passed in are printed
//-------------------------------------------------------------
void Book_Database::searchByClassification(int cl) {
	searchByClassification(cl, m_pRoot);

}

//-----------------------------------------------
// Function: searchByCost()
// Pre: tree has been initialized
// Post: BookRecords in cost range are printed
//-----------------------------------------------
void Book_Database::searchByCost(double min, double max) {
	searchByCost(min, max, m_pRoot);
}

//--------------------------------------------------------------------
// Function: getNumInStock()
// Returns: Number of book records in stock for given stock number
// Pre: tree has been initialized
// Post: Number of book records in stock returned for given stock num
//--------------------------------------------------------------------
int Book_Database::getNumInStock(long sn) {

	BookRecord *rec = searchByStockNumber(sn);

	if (rec != nullptr)
		return rec->getNumberInStock();
	else
		return -1;

}

//-----------------------------------------------
// Function: printAll()
// Pre: tree has been initialized
// Post: All book records printed to console
//-----------------------------------------------
void Book_Database::PrintAll() {
	cout << "***************************************************************" << endl;
	cout << "\t\t" << "Title" << "\t\t" << "Stk #" << '\t' << "Class" << '\t' << "Cost" << '\t' << "In Stock" << endl;
	cout << "***************************************************************" << endl;
	PrintAll(m_pRoot);
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
bool Book_Database::getNextLine(char *line, int lineLen)
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


//-------------------------------------------------------------------------
// Function: searchByClassification()
// Pre: tree has been initialized
// Post: BookRecords with classification passed in are printed recursively
//-------------------------------------------------------------------------
void Book_Database::searchByClassification(int cl, BookRecord *rt) {

	if (rt != nullptr){

		char name[128];
		rt->getName(name);
		searchByClassification(cl, rt->getLeft());   // Print left subtree.

		if (cl == rt->getClassification()) {
			rt->printRecord();
		}

		searchByClassification(cl, rt->getRight());  // Print right subtree.
	}

}	
//-----------------------------------------------------------------------------------
// Function: searchByCost()
// Pre: tree has been initialized
// Post: BookRecords with cost between min and max passed in are printed recursively
//-----------------------------------------------------------------------------------
void Book_Database::searchByCost(double min, double max, BookRecord *rt) {
	if (rt != nullptr) {

		char name[128];
		rt->getName(name);
		searchByCost(min, max , rt->getLeft());   // Print left subtree.

		if (min <= rt->getCost() && max >= rt->getCost()) {
			rt->printRecord();
		}

		searchByCost(min, max, rt->getRight());  // Print right subtree.
	}
}

//------------------------------------------------------
// Function: PrintAll()
// Pre: tree has been initialized
// Post: Recursively prints data for all nodes in tree
//------------------------------------------------------
void Book_Database::PrintAll(BookRecord *rt) {
	if (rt != nullptr){

		PrintAll(rt->getLeft());   // Print left subtree.
		char name[128];
		rt->getName(name);
		cout  << left << setw(30) << name << '\t' << rt->getStockNum() << '\t' << rt->getClassification() << '\t' << rt->getCost() << '\t' << rt->getNumberInStock() << endl;
		PrintAll(rt->getRight());  // Print right subtree.
	}
}