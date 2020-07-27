//Ivannechta<at>gmail.com

#include <iostream>
#include "Tardos.h"


int main()
{
	// Example:
	Tardos *T = new Tardos(10, 2, 0.1); //Prepare code. Params are (10- Total users/fingerprints, 2- collision size, 0.1- detection_error_probability).
	T->BuildCode();  //Build CodeTable
	//T->ShowCodeTable();
	T->Info(); //Show some information about code
	
	//Example detecyion
	char *y = T->Collide2(5, 6); // Coalition with two intruders(№5,6) creates mutual fingerprint by randomly changing differing bits in their fingerprints
	// after interception corruped fingerprint we  try to detect the coalition
	T->Detect(y, 2); // y- intercepted fingerprint, 2 - coaltion size
	// Result: Scores and users numbers would be shown. 
	
	delete y;
	delete T;

	return 0;
}
