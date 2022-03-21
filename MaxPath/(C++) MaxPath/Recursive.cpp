#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> ReadDocument(string fileName);
void MaximumSumOfNumbers(vector<vector<int>> numbers);
int MaximumSumOfNumbersRecursive(vector<vector<int>> numbers, int i, int j);
bool isPrime(int number);
void Test1();
void Test2();

int main()
{
    Test1();
    Test2();
    return 0;
}

bool isPrime(int number)
{
    if (number == 0 || number == 1)
    {
        return false;
    }
    if (number % 2 == 0)
    {
        return false;
    }
    for (int i = 3; i * i <= number; i = i + 2)
    {
        if (number % i == 0) return false;
    }
    return true;
}

void Test1()
{
    cout << "-----Test1-----" << endl;
    string _fileName = "test1.txt";
    vector<vector<int>> _numbers = ReadDocument(_fileName);
    MaximumSumOfNumbers(_numbers);
}

void Test2()
{
    cout << "-----Test2-----" << endl;
    string _fileName = "test2.txt";
    vector<vector<int>> _numbers = ReadDocument(_fileName);
    MaximumSumOfNumbers(_numbers);
}

vector<vector<int>> ReadDocument(string fileName)
{
    std::ifstream testFile;
    testFile.open(fileName, ios::in);
    if (testFile.is_open())
    {
        vector<int> row;
        vector<vector<int>> numbers;
        char ch;
        string number = "";
        while (testFile >> std::noskipws >> ch)
        {
            if (ch == ' ' || ch == '\n')
            {
                row.push_back(stoi(number));
                number.clear();
                if (ch == '\n')
                {
                    numbers.push_back(row);
                    row.clear();
                }
            }
            else
            {
                number += ch;
            }
        }
        row.push_back(stoi(number));
        numbers.push_back(row);

        testFile.close();
        return numbers;
    }
    else
    {
        cerr << "File cannot opened!" << endl;
        return vector<vector<int>>();
    }

}


void MaximumSumOfNumbers(vector<vector<int>> numbers)
{
    int cost = MaximumSumOfNumbersRecursive(numbers, 0, 0);
    cout << "Maximum Sum of the Numbers: " << cost << endl;
}

int MaximumSumOfNumbersRecursive(vector<vector<int>> numbers, int i, int j)
{
    size_t EndPoint = numbers.size();
    if (i == EndPoint - 1 && j == EndPoint - 1) return 0;

    int downCost = 0;
    if (i + 1 <= EndPoint - 1)	if (!isPrime(numbers[i + 1][j])) downCost = MaximumSumOfNumbersRecursive(numbers, i + 1, j);

    int rightCost = 0;
    if (i + 1 <= EndPoint - 1 && j + 1 <= EndPoint - 1) if (!isPrime(numbers[i + 1][j + 1])) rightCost = MaximumSumOfNumbersRecursive(numbers, i + 1, j + 1);

    int leftCost = 0;
    if (i + 1 <= EndPoint - 1 && j - 1 >= 0) if (!isPrime(numbers[i + 1][j - 1])) leftCost = MaximumSumOfNumbersRecursive(numbers, i + 1, j - 1);

    int maxCorner = max(leftCost, rightCost);
    return numbers[i][j] + max(maxCorner, downCost);
}
