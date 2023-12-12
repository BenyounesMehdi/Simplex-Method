#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

int variablesNumber, constainsNumber;
vector<vector<float>> table;  // Change to 2D vector
vector<float> coefficients;
vector<float> BIcoefficients;
vector<float> Zequation;
vector<string> xArray;
vector<string> eArray;

void getZequation()
{
    float temp;
    cout << "\nPlease,Enter The Coefficients of Z Equation : " << endl;
    for (int i = 1; i < variablesNumber + 1; i++)
    {
        cout << "\tEnter The Value of X" << i << ": ";
        cin >> temp;
        Zequation.push_back(temp);
    }
    reverse(Zequation.begin(), Zequation.end());
}

void getUserInputs()
{
    cout << "\nEnter The Number of Variables : ";
    cin >> variablesNumber;
    cout << "Enter The Number of Constrains : ";
    cin >> constainsNumber;

    float temp;

    for (int i = 1; i <= constainsNumber; i++)
    {
        cout << "Please, Enter The Coefficients Of Constain N° " << i << " : ";
        cout << endl;
        for (int j = 1; j <= variablesNumber; j++)
        {

            cout << "\tEnter The Value of X" << j << " : ";
            cin >> temp;
            coefficients.push_back(temp);
        }
        cout << "\tEnter bi Value : ";
        cin >> temp;
        BIcoefficients.push_back(temp);
        cout << endl;
    }
    reverse(coefficients.begin(), coefficients.end());
    reverse(BIcoefficients.begin(), BIcoefficients.end());

    getZequation();
}

void filleArray()
{
    string x;
    int i;
    for (i = 1; i < constainsNumber + 1; i++)
    {
        x = "e" + to_string(i);
        eArray.push_back(x);  // Change to eArray
    }
    eArray.push_back("Z");

}

void fillxArray()
{
    string x;
    int i;
    for (i = 1; i < variablesNumber + 1; i++)
    {
        x = "X" + to_string(i);
        xArray.push_back(x);
    }
    xArray.push_back("Bi");
}



void fillTable(vector<vector<float>> &table, vector<float> t, vector<float> bi, vector<float> Zequation)
{
    float temp;
    constainsNumber = constainsNumber + 1 ;
    variablesNumber = variablesNumber + 1 ;
    table.resize(constainsNumber, vector<float>(variablesNumber));  // Resize the table
    int i, j;

    cout << endl;

    for (i = 0; i < constainsNumber; i++)
    {

        for (j = 0; j < variablesNumber; j++)
        {

            if (j == variablesNumber-1)
            {

                temp = bi.back();
                bi.pop_back();
                table[i][j] = temp;
            }

            else if (i == constainsNumber-1)
            {
                temp = Zequation.back();
                Zequation.pop_back();
                table[i][j] = temp;
            }

            else
            {
                temp = t.back();
                t.pop_back();
                table[i][j] = temp;
            }
        }
        cout << endl;
    }
    table[constainsNumber-1][variablesNumber-1] = 0;
}

void displayTable(vector<string> xArray, vector<string> eArray, vector<vector<float>> &table)
{
    int k, i, j;
    int f = 0 ;
    for (k = 0; k < xArray.size(); k++)
    {
        cout << "\t" << xArray[k];
    }

    cout << endl;

    for (i = 0; i < constainsNumber ; i++)
    {

        for (j = 0; j < variablesNumber ; j++)
        {
            if (j == 0)
            {
                cout << eArray[f] << "\t" << table[i][j] << " ";
                f++;
            }
            else
            {
                cout << "\t" << table[i][j];
            }
        }
        cout << endl;
    }
}

int getPivotCol (vector<float> Zequation) {
    int i, index ;
    float max = Zequation[0] ;
    for( i = 0 ; i < Zequation.size() ; i++ ) {
        if( Zequation[i] > max ) {
            max = Zequation[i] ;
            index = i ;
        }
    }

    return index ;
}

int getPivotLin (vector<float> Zequation, vector<float> BIcoefficients, vector<vector<float>> &table) {
    vector<float>divsion ;
    float temp, min ;
    int linIndex ;
    int index = getPivotCol(Zequation) ;
    for( int i = 0 ; i < constainsNumber-1 ; i++ ) {
         temp  = table[i][variablesNumber-1] / table[i][index] ;
         //cout << table[i][index]  << " ";
         
        divsion.push_back(temp) ;
    }

    min = divsion[0] ;
    for( int j = 0 ; j < divsion.size() ; j++ ) {
        if( min > divsion[j] ) {
            min = divsion[j] ;
            linIndex = j ;
        }
    }

    return linIndex ;
}

void calculatePivot (vector<float> Zequation) {
    int colIndex = getPivotCol(Zequation) ;
    int linIndex = getPivotLin(Zequation, BIcoefficients, table) ;
    cout << "\nPivot in Linge: " << linIndex+1 << ", Pivot in Column: " << colIndex+1 ;
    cout << "\nPivot = " << table[linIndex][colIndex] ;
}

void calculateNewTable(vector<vector<float>> &table) {
    int i, j ;
    float temp ;
    int colIndex = getPivotCol(Zequation) ;
    int linIndex = getPivotLin(Zequation, BIcoefficients, table) ; 

    for( i = 0 ; i < constainsNumber ; i++ ) {
        for( j = 0 ; j < variablesNumber ; j++ ) {
            temp = table[i][j] - ((table[i][colIndex] * table[linIndex][j]) / table[linIndex][colIndex]) ;
            table[i][j] = temp ;
        }
    }
}

int main()
{

    getUserInputs();
    filleArray();
    fillxArray();
    fillTable(table, coefficients, BIcoefficients, Zequation);
    displayTable(xArray, eArray, table);
    calculatePivot(Zequation) ;
    calculateNewTable(table) ;
    cout << endl ;
    displayTable(xArray, eArray, table);

    return 0;
}
