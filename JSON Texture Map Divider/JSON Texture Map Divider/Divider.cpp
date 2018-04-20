#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	string fileName;
	cout << "Please enter the filename of the JSON File " << endl;
	cin >> fileName;
	//fileName = "c:\\Users\\where44444\\Desktop\\Glass_Door.json";
	int size;
	cout << "Input Texture Dimension (One Integer - Has to be a square texture) " << endl;
	cin >> size;
	size /= 16;

	char cfileName[100];
	for (int i = 0; i < 100; i++)
		cfileName[i] = '\0';

	int TempNumOne = fileName.size();
	for (int a = 0; a <= TempNumOne; a++)
	{
		cfileName[a] = fileName[a];
	}


	ifstream input;
	input.open(cfileName);

	if (input.fail())
		return -1;

	int i = 0;
	int j = 0;
	char Txt[512][256];
	char Line[1024];
	//FILLS THE FIRST ARRAYS WITH NULLS TO MAKE SPACE
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 256; j++)
			Txt[i][j] = NULL;

	for (int i = 0; i < 1024; i++)
			Line[i] = NULL;
	//INPUTS FROM THE JSON FILE INTO A BIG 2D ARRAY
	while (input.getline(Line, 1024))
	{
		while (Line[j])
		{
			Txt[i][j] = Line[j];
			j++;
		}
		j = 0;
		i++;
	}
	input.close();
	int UVS = 0;
	char UV1[5];
	char UV2[5];
	char UV3[5];
	char UV4[5];
	char UV1c[5];
	char UV2c[5];
	char UV3c[5];
	char UV4c[5];
	int Position1 = 0;
	int Position2 = 0;
	int Position3 = 0;
	int Position4 = 0;
	bool unfinished = true;
	int marker = 0; //Tells which position was last set


	for (int i = 0; i < 512; i++)
	{
		for (int c = 0; c < 5; c++)
		{
			UV1[c] = NULL;
			UV2[c] = NULL;
			UV3[c] = NULL;
			UV4[c] = NULL;
			UV1c[c] = NULL;
			UV2c[c] = NULL;
			UV3c[c] = NULL;
			UV4c[c] = NULL;
		}
		for (int j = 0; j < 256; j++)
		{
			//RUNS ONCE EVERY TIME A UV SET IS FOUND
			if (Txt[i][j] == 'u' && Txt[i][j + 1] == 'v' && Txt[i][j + 2] == '"'
				&& Txt[i][j + 3] == ':'&& Txt[i][j + 4] == ' '&& Txt[i][j + 5] == '['&& Txt[i][j + 6] == ' ')
			{
				UVS++;
				Position1 = j + 7;
					for (int m = 0; m < 5; m++)
						if (Txt[i][Position1 + m] != ',' && Txt[i][Position1 + m] != ' ')
							UV1[m] = Txt[i][Position1 + m];
						else
							UV1[m] = NULL;

				marker = 1;
				//Puts each number into a UV Char Array
				for (int k = j + 7; Txt[i][k]; k++)
					if (Txt[i][k] == ' ')
						if (marker == 1)
						{
							Position2 = k + 1;
								for (int m = 0; m < 5; m++)
									if (Txt[i][Position2 + m] != ',' && Txt[i][Position2 + m] != ' ')
										UV2[m] = Txt[i][Position2 + m];
									else
										UV2[m] = NULL;

							marker = 2;
						}
						else if (marker == 2)
						{
							Position3 = k + 1;
								for (int m = 0; m < 5; m++)
									if (Txt[i][Position3 + m] != ',' && Txt[i][Position3 + m] != ' ')
										UV3[m] = Txt[i][Position3 + m];
									else
										UV3[m] = NULL;

							marker = 3;
						}
						else if (marker == 3)
						{
							Position4 = k + 1;
								for (int m = 0; m < 5; m++)
									if (Txt[i][Position4 + m] != ',' && Txt[i][Position4 + m] != ' ')
										UV4[m] = Txt[i][Position4 + m];
									else
										UV4[m] = NULL;

							marker = 4;
						}
				for (int n = 0; n < 5; n++)
					if (to_string(atof(UV1) / size)[n])
						UV1c[n] = to_string(atof(UV1) / size)[n];

				for (int n = 0; n < 5; n++)
					if (to_string(atof(UV2) / size)[n])
						UV2c[n] = to_string(atof(UV2) / size)[n];

				for (int n = 0; n < 5; n++)
					if (to_string(atof(UV3) / size)[n])
						UV3c[n] = to_string(atof(UV3) / size)[n];

				for (int n = 0; n < 5; n++)
					if (to_string(atof(UV4) / size)[n])
						UV4c[n] = to_string(atof(UV4) / size)[n];

				//Space taken from Position1 to space before ] is 27
				//Expands Texture Slot to make room for 4 5-digit numbers
				unfinished = true;
				for (int n = Position4; n < 256 && unfinished; n++)
					if (Txt[i][n] == ']')
					{
						unfinished = false;
						marker = 27 - (n - Position1);
						for (int b = 255 - marker; b > Position3; b--)
							Txt[i][b + marker] = Txt[i][b];
					}

				for (int n = 0; n < 5; n++)
					Txt[i][Position1 + n] = UV1c[n];
				Txt[i][Position1 + 5] = ',';
				Txt[i][Position1 + 6] = ' ';
				for (int n = 0; n < 5; n++)
					Txt[i][Position1 + n + 7] = UV2c[n];
				Txt[i][Position1 + 12] = ',';
				Txt[i][Position1 + 13] = ' ';
				for (int n = 0; n < 5; n++)
					Txt[i][Position1 + n + 14] = UV3c[n];
				Txt[i][Position1 + 19] = ',';
				Txt[i][Position1 + 20] = ' ';
				for (int n = 0; n < 5; n++)
					Txt[i][Position1 + n + 21] = UV4c[n];
				Txt[i][Position1 + 26] = ' ';
					
						
			}

		}
	}
	cout << "FOUND " << UVS << " UV's" << endl;

	
	//OUTPUTS THE TXT ARRAY
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (Txt[i][j])
				cout << Txt[i][j];
		}
		if (Txt[i][0])
		cout << endl;
	}

	string fileName2;
	cout << "Writing JSON to output.json" << endl;
	//cin >> fileName2;
	//fileName2 = "c:\\Users\\where44444\\Desktop\\output.json";
	fileName2 = "output.json";
	char cfileName2[100];
	for (int i = 0; i < 100; i++)
		cfileName2[i] = '\0';

	TempNumOne = fileName2.size();
	for (int a = 0; a <= TempNumOne; a++)
	{
		cfileName2[a] = fileName2[a];
	}
	ofstream fout;
	fout.open(cfileName2);

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (Txt[i][j])
				fout << Txt[i][j];
		}
		fout << endl;
	}
	fout.close();
	cout << "Json written successfully\n";

	int value;
	cin >> value;

}