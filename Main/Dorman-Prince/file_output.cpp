#include "file_output.h"

#include <fstream>

#define FILE "output.txt"

void Dorman_to_file(const TMatrix &Result, const TDormanPrince &Integrator){
	ofstream fout/*, ftest("test.txt")*/;
	fout.open(FILE);
	if (!fout.is_open())
	{
		cout << "File couldn't been created";
		system("pause");
		exit;
	}

	for (int i = 0; i < Result.getRowCount(); i++)
	{
		for (int j = 0; j < Result.getColCount(); j++)
		{
			fout << Result[i][j] << "	";
		}
		fout << "\n";
	}

	fout.close();

	// ------------------------------------------------------------ Èםעונפויס
	cout << "\n\nProcess have been ended. \n	Number of iterations: "
		<< Integrator.get_iter()
		<< "\n	Global Eps: " << Integrator.getEps_Global()
		<< "\n\nNow would be opened result file\n";
	Sleep(DELAY);
	// ------------------------------------------------------------ Èםעונפויס

	ShellExecute(NULL, TEXT("open"), TEXT(FILE), NULL, NULL, SW_RESTORE);
}