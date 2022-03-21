using System.Text.RegularExpressions;

Test1();
Test2();
Test3();

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
    for (int i = 3; i * i <= number; i += 2)
    {
        if (number % i == 0) return false;
    }
    return true;
}
void Test1()
{
    Console.WriteLine("-----Test1-----");
    string _fileName = "test1.txt";
    List<List<int>> _numbers = ReadDocument(_fileName);
    MaximumSumOfNumbers(_numbers);
}

void Test2()
{
    Console.WriteLine("-----Test2-----");
    string _fileName = "test2.txt";
    List<List<int>> _numbers = ReadDocument(_fileName);
    MaximumSumOfNumbers(_numbers);
}
void Test3()
{
    Console.WriteLine("-----Test3-----");
    string _fileName = "test3.txt";
    List<List<int>> _numbers = ReadDocument(_fileName);
    MaximumSumOfNumbers(_numbers);
}
List<List<int>> ReadDocument(string fileName)
{
    string contents = File.ReadAllText(fileName);
    List<string> array = contents.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();

    List<List<int>> matrixList = new List<List<int>>();
    int i = 0;
    foreach (string item in array)
    {
        List<int> rowList = new List<int>();
        matrixList.Add(rowList);
        var matches = Regex.Matches(item, @"\d+");
        foreach (var match in matches)
        {
            string? s = match.ToString();
            if (!String.IsNullOrEmpty(s))
            {
                rowList.Add(int.Parse(s));
            }
        }
        i++;
    }
    return matrixList;
}


void MaximumSumOfNumbers(List<List<int>> numbers)
{
    int cost = MaximumSumOfNumbersRecursive(numbers, 0, 0);
    Console.WriteLine("Maximum Sum of the Numbers: {0}", cost);
}

int MaximumSumOfNumbersRecursive(List<List<int>> numbers, int i, int j)
{
    int EndPoint = numbers.Count;
    if (i == EndPoint - 1 && j == EndPoint - 1) return 0;

    int downCost = 0;
    if (i + 1 <= EndPoint - 1) if (!isPrime(numbers[i + 1][j])) downCost = MaximumSumOfNumbersRecursive(numbers, i + 1, j);

    int rightCost = 0;
    if (i + 1 <= EndPoint - 1 && j + 1 <= EndPoint - 1) if (!isPrime(numbers[i + 1][j + 1])) rightCost = MaximumSumOfNumbersRecursive(numbers, i + 1, j + 1);

    int leftCost = 0;
    if (i + 1 <= EndPoint - 1 && j - 1 >= 0) if (!isPrime(numbers[i + 1][j - 1])) leftCost = MaximumSumOfNumbersRecursive(numbers, i + 1, j - 1);

    int ailem = new[] { downCost, leftCost, rightCost }.Max();
    return numbers[i][j] + ailem;
}
