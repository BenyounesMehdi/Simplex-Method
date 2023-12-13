#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

int variablesNumber, constainsNumber, colPivotIndex, linPivotIndex;
float pivot  ;
vector<vector<float>> table;
vector<vector<float>> newTable; 
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
}

void getUserInputs()
{
    cout << "\nEnter The Number of Variables : ";
    cin >> variablesNumber;
    cout << "Enter The Number of Constrains : ";
    cin >> constainsNumber;

    float temp;
    int turn = 0 ;

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
            
        for( int k = 0 ; k < constainsNumber ; k++ ) {
            if( k == turn ) {
                temp  = 1 ;
            }
            else {
                temp = 0 ;
            }
            coefficients.push_back(temp) ;
        }
        turn++ ;
        cout << "\tEnter bi Value : ";
        cin >> temp;
        BIcoefficients.push_back(temp);
        cout << endl;
    }
    reverse(coefficients.begin(), coefficients.end());
    reverse(BIcoefficients.begin(), BIcoefficients.end());

    getZequation();
    for( int g = 0 ; g < constainsNumber ; g++ ) {
        Zequation.push_back(0) ;
    }
}

void filleArray()
{
    string x;
    int i;
    for (i = 1; i < constainsNumber + 1; i++)
    {
        x = "e" + to_string(i);
        eArray.push_back(x);  
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

    for( i = 0 ; i < eArray.size()-1 ; i++ ) {

        xArray.push_back(eArray[i]) ;
    }

    for( i = 0 ; i < eArray.size()-1 ; i++ ) {
        Zequation.push_back(0) ;
    }
    xArray.push_back("Bi");

    reverse(coefficients.begin(), coefficients.end()) ;
    reverse(coefficients.begin(), coefficients.end()) ;

}


void fillTable(vector<vector<float>> &table, vector<float> t, vector<float> bi, vector<float> Zequation)
{
    float temp;
    constainsNumber = constainsNumber + 1 ;
    variablesNumber = variablesNumber + eArray.size()  ;
    reverse(Zequation.begin(), Zequation.end());
    newTable.resize(constainsNumber, vector<float>(variablesNumber));
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
    pivot = table[linIndex][colIndex] ;
    cout << "\nPivot in Linge: " << linIndex+1 << ", Pivot in Column: " << colIndex+1 ;
    cout << "\nPivot = " << pivot ;
}

bool checkTable() {
    int i , j ;
    float maxElement = table[constainsNumber][0] ;

    for( i = 0  ; i < variablesNumber ; i++ ) {
        if( maxElement < table[constainsNumber][i] ) {
            maxElement = table[constainsNumber][i] ;
        }
    }

    if( maxElement > 0 ) {
        return true ;
    }
    return false ;
}

void calculateNewTable() {
    int i, j ;

      newTable.resize(constainsNumber, vector<float>(variablesNumber, 0));

    colPivotIndex = getPivotCol(Zequation) ;
    linPivotIndex = getPivotLin(Zequation, BIcoefficients, table) ; 
    eArray[linPivotIndex] = xArray[colPivotIndex] ;
    
    pivot = table[linPivotIndex][colPivotIndex];

    for( i = 0 ; i < constainsNumber ; i++ ) {
        for( j = 0 ; j < variablesNumber ; j++ ) {
            if( j == colPivotIndex ) {
                if( i == linPivotIndex ) {
                    newTable[i][j] = 1 ;
                }
                else {
                    newTable[i][j] = 0 ;
                }
            }
            else if( i == linPivotIndex ) {
                newTable[i][j] = table[i][j] / pivot ;
            }
            
            else {
                newTable[i][j] = (table[i][j] - ((table[i][colPivotIndex] * table[linPivotIndex][j]) / pivot)) ;
            }
        }
    }

    for( i = 0 ; i < constainsNumber ; i++ ) {
        for( j = 0 ; j < variablesNumber ; j++ ) {
            table[i][j] = newTable[i][j] ;
        }
    }
}

void finishProgramm() {
    while( !checkTable() ) {
        calculatePivot(Zequation) ;
        calculateNewTable() ;
        cout << endl ;
        displayTable(xArray, eArray, table); 
    }
}

int main()
{

    getUserInputs();
    filleArray();
    fillxArray();
    
    fillTable(table, coefficients, BIcoefficients, Zequation);
    displayTable(xArray, eArray, table);
    cout << endl ;

        calculatePivot(Zequation) ;
        calculateNewTable() ;
        cout << endl ;
        displayTable(xArray, eArray, table); 

    return 0;
}
