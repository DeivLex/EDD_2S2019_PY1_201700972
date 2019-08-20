#include <iostream>
#include <stdlib.h>

using namespace std;

int main ()
{
	int a;
	do{
		cout<< "\n";
		cout<< "1. Insert image\n";
		cout<< "2. Select image\n";
		cout<< "3. Apply filrtes\n";
		cout<< "4. Manual editing\n";
		cout<< "5. Export image\n";
		cout<< "6. Reports\n";
		cout<< "7. Exit \n\n";
		cout<<"Option to select: "; 
		cin >> a ;
		cout<< "\n";
		
		switch (a)
		{
			case 1:
				cout<< "Opcion1\n";
				break;
			case 2:
				cout<< "Opcion2\n";
				break;
			case 3:
				cout<< "Opcion3\n";
				break;
			case 4:
				cout<< "Opcion4\n";
				break;
			case 5:
				cout<< "Opcion5\n";
				break;
			case 6:
				cout<< "Opcion6\n";
				break;				
			case 7:
				return 0;
				break;
			default:
				return main();
				break;
		}
	}
	while(a != 3);
	return main();
}
