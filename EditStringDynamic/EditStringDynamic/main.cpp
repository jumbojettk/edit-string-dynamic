// Napon Krassner (Jett)
// CSC 3430
// Lab 6 Final Exam
// Name: EditStringDynamic
// Description: Dynamic Programming solution to compute the “minimum editing
//				distance” between two strings and shows the operations necessary
//				to transform the first string into the second string.
//******************************************************************************

// Includes
#include <iostream>
#include <string>
#include <stack>


using namespace std;

// Function Declaration
int min(int, int, int);
int editDist(string, string, int, int);
int editDistDP(int[][50], string, string, int, int);
void printMemTable(int[][50], string, string, int, int);
void detOperation(int[][50], string, string, int, int, stack<char>&, stack<char>&, stack<char>&);


// Driver program
int main()
{
	int M[50][50];					// Memoization table
	stack<char> alignSourceStk;		// stack to store aligned source
	stack<char> opMapStk;			// stack to store mapping for operation
	stack<char> alignTargetStk;		// stack to store aligned target

	// Declare strings
	string str1;
	string str2;
	int minEdits;

	// Program header
	cout << "Welcome to Dynamic Programming for Minimum Editing Distance between 2 strings by Napon Krassner (Jett)\n\n";

	// Prompt for input
	cout << "Enter initial string: ";
	cin >> str1;

	cout << "Enter targer  string: ";
	cin >> str2;
	cout << endl;

	// dynamic programming edit dist
	minEdits = editDistDP(M, str1, str2, str1.length(), str2.length());

	// Print Memoization table
	printMemTable(M, str1, str2, str1.length(), str2.length());

	// find out the operation from source to target with map
	detOperation(M, str1, str2, str1.length(), str2.length(), alignSourceStk, opMapStk, alignTargetStk);


	// print source stack
	cout << endl << "From: ";
	while (!alignSourceStk.empty())
	{
		// print the char and pop it off
		cout << alignSourceStk.top();
		alignSourceStk.pop();
	}
	cout << endl;

	// print map stack
	cout << " map: ";
	while (!opMapStk.empty())
	{
		// print the char and pop it off
		cout << opMapStk.top();
		opMapStk.pop();
	}
	cout << "    : i)nsertions, d)eletions, r)eplacements" << endl;

	// print target stack
	cout << "  To: ";
	while (!alignTargetStk.empty())
	{
		// print the char and pop it off
		cout << alignTargetStk.top();
		alignTargetStk.pop();
	}
	cout << endl;

	// print status
	cout << "\nMinimum edits required to convert sunday into saturday is " << minEdits << "\n\n";

	return 0;
}

//********Function Definition********

// Parameters:	int - first number
//				int - second number
//				int - third number
// Return:	int - minimum number
// Description:	finds the minimum number out of the given 3 numbers
int min(int x, int y, int z)
{
	if (x < y && x < z)
	{
		return x;
	}
	else if (y < x && y < z)
	{
		return y;
	}
	else
	{
		return z;
	}
}


// Parameters:	int - memoization array
//				string - first string
//				string - second string
// Return:	int - minimum number operation
// Description: dynamic programming function to find the minimum
//				number of operation to edit the first string into
//				the second string.
int editDistDP(int M[][50], string str1, string str2, int m, int n)
{
	// Create a table to store results of sub problems
	// M[][] asume 50 char for lab and is global

	// Fill in bottom up manner
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			// If first string is empty
			// insert all chars of second string
			if (i == 0)
			{
				M[i][j] = j;	// Min op = j
			}

			// If second string is empty
			// remove all chars of sec string
			else if (j == 0)
			{
				M[i][j] = i;	// Min op = i
			}

			// If last char are same, ignore last char
			// recur from remaining string
			else if (str1[i - 1] == str2[j - 1])
			{
				M[i][j] = M[i - 1][j - 1];
			}
			// If last character are different
			// find possibilities and minimum
			else
			{

				M[i][j] = 1 + min(M[i][j - 1],		// insert
								M[i - 1][j],		// remove
								M[i - 1][j - 1]);	// replace
			}
		}
	}

	return M[m][n];
}


// Parameters:	int[][] - Memoization table
//				string - string 1
//				string - string 2 (target)
//				int - size of string 1
//				int - size of string 2 (target)
// Return:	nothing
// Description:	prints the memoization table in formatting
void printMemTable(int M[][50], string str1, string str2, int m, int n)
{	
	// print the index row for string 2 (target)
	cout << "    ";
	for (int i = 0; i <= n; i++)
	{
		if (i < 10)
			cout << "  ";
		else
			cout << " ";

		cout << i;
	}

	cout << "\n";

	// print the letters for string 2 (target)
	cout << "    ";
	for (int i = 0; i < n; i++)
	{
		cout << "  " << str2.at(i);
	}
	cout << "  " << " \n";

	// print the letter from string 1 while printing rows from Mem table
	for (int i = 0; i <= m; i++)
	{
		if (i < m)
		{
			if (i < 10)
				cout << " ";
			cout << i << " " << str1.at(i);
		}
		else
		{
			if (i < 10)
				cout << " ";
			cout << i << "  ";
		}
		
		for (int j = 0; j <= n; j++)
		{
			if (M[i][j] < 10)
				cout << "  ";
			else
				cout << " ";

			cout << M[i][j];
		}
		cout << "\n";
	}
	
}

// Parameters:	int[][] - memoization table
//				string - string1
//				string - string2 (target)
//				int - size of string 1
//				int - size of string 2
//				stack<char> - stack to store the aligned string1
//				stack<char> - stack to store the operation
//				stack<char> - stack to store the aligned string2
// Return: nothing
// Description: determine the operation done to transform string 1 to string 2
//				then store the transformed string1 into stack and
//				store operartion mapping into another stack
void detOperation(int M[][50], string str1, string str2, int m, int n, stack<char>& alignSourceStk, stack<char>& opMapStk, stack<char>& alignTargetStk)
{
	int i = m;
	int j = n;

	while (i >= 0 && j >= 0)
	{
		// base case to not fall off the table at last op
		if (i == 0 && j == 0)
		{
			break;
		}
		// if the diagonal val is less than the current val
		// means replace occured
		else if (M[i-1][j-1] < M[i][j] && i != 0 && j != 0)
		{
			alignSourceStk.push(str1.at(i - 1));
			opMapStk.push('r');
			alignTargetStk.push(str2.at(j - 1));
			i--;
			j--;
		}

		// if the top val is less than the current val
		// means delete occured
		else if (M[i-1][j] < M[i][j] && i != 0)
		{
			alignSourceStk.push(str1.at(i - 1));
			opMapStk.push('d');
			alignTargetStk.push(' ');
			i--;
		}

		// if the left val is less than cur val
		// means insert occured
		else if (M[i][j - 1] < M[i][j] && j != 0)
		{
			alignSourceStk.push(' ');
			opMapStk.push('i');
			alignTargetStk.push(str2.at(j - 1));
			j--;
		}

		// means same char
		else
		{
			alignSourceStk.push(str1.at(i - 1));
			opMapStk.push(' ');
			alignTargetStk.push(str2.at(j - 1));
			i--;
			j--;
		}
	}
}