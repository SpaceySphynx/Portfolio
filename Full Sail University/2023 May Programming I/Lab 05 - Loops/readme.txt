Test 1 – How many multiples
public static int Test1(int start, int end, int factor)
Given three int's, start, end and factor, using a loop, count how multiples of factor occur
between start and end (inclusive). A multiple is a number that is the factor multiplied by a whole number.

Example Input	Example Output
11,8,4	5


Test 2 – Factorial
public static int Test2(int number)
Given an int, number, calculate the factorial for number. A factorial is the result of multiplying all integers between 1 and the target (number) (so 3 factorial, 3!, is 3 X 2 X 1 = 6)

Example Input	Example Output
4

24

Test 3 – Raise to a power
public static int Test3(int root, int exponent)
Given two int's, root and exponent, use a loop to raise root to exponent. You are not allowed to use Math.Pow to compute the answer – you must use a loop. Additionally, exponent will be greater than or equal to 0 (no negative exponents)

Example Input	Example Output
6,3

216

   

Test 4 – Consumable
public static int Test4(double onHand, double consume)
Given two doubles (onHand and consume) that represent the amount of an on-hand resource (onHand) and the amount of the resource that is consumed per cycle (think a time period). You are to determine how many cycles (time periods) are before the on-hand amount is used up. For example, if you have 1 gallon of milk (onHand) and use 1 quart (1/4 gallon) per day (consume), determine when you expect to run out of milk (4 days). 



Return the number of cycles completed when the on-hand amount is no longer enough to satisfy the consume condition. You may find it necessary to use the Round method from the Math class to avoid floating-point errors. It is suggested to round the results of each computation to 3 decimal places.

Example Input	Example Output
47.7, 0.9

53

Test 5 – Prime number
public static bool Test5(int number)
Given an int, number, determine if number is a prime number. Recall prime numbers are numbers that are divisible on by 1 and themselves. Negative values, 0 and 1 are not prime numbers (2 is the smallest prime number). If number is prime, return true, otherwise return false. You must check all values.

Example Input	Example Output
41

true

Note: Some ‘facts’ regarding prime numbers:
The smallest prime number is 2
2 is the only even prime number
One way to determine if a number is prime is to divide it by every value greater than one but that is less than the given number divided by 2. If the remainder of the division is 0, the number is not prime
Test 6 – Build a string
public static string Test6(char starter, int number)
Given a char, starter, and an int, number, create a string of sequential characters that begins with starter and is number of characters long. For example, if starter is 'A' and number is 5, the string should be ABCDE (the starting value of A followed by the next 4 characters, in order)

Example Input	Example Output
g, 3

ghi

Notes:

You need to start with an empty string ("" or string.Empty)
This test relies on using the character encoding values for each char you need. The character encoding is defined by the ASCII or UTF-8 encoding scheme (i.e. ‘A’ is encoded using the decimal value 65, ‘B’ is encoded using the decimal 66 and so on). If you add an int to a char, the char is converted to its decimal equivalent and the result is an int. To add the result to the string you are building, you have to cast that int back to a char.

Here’s a brief example:
char char1 = ‘k’;
char char2 = (char)(char1+1); // first char1 and 1 are added, the resulting int is cast to char
 

Test 7 – Making change
public static int Test7(double amount)
Given a double, amount, that represents an amount of US money, determine the minimum number of coins required to equal that amount. Use on quarters, dimes, nickels and pennies. There are two approaches to this problem. The first uses division and the second uses loops. You are not allowed to solve using division. 



For example, given 2.63, you would need 10 quarters, 1 dime and 3 pennies, for a total of 14 coins. You will probably find it necessary to use the Round method from the Math class to avoid floatingpoint errors. Since you are dealing with US currency/coins, it is suggested to round the results of each computation to 2 decimal places.

Example Input	Example Output
0.41

4

Test 8 – Return the multiples
public static string Test8(int factor, int qty)
Given two int's factor and qty, find the first qty multiples of factor (including factor as the first multiple) and add (concatenate) each to a string (each multiple will be followed by a single space to separate the multiples). 



For example, given 5 (factor) and 7 (qty), the resulting string would be "5 10 15 20 25 30 35"

Example Input	Example Output
7,4

7 14 21 28


Notes:

You need to start with an empty string ("" or string.Empty)
This test is a series of multiples of a given factor. Each multiple must be followed by a space. If the factor is 3 and there 7 multiples, the resulting string should be:

“3 6 9 12 15 18 21 “ // note there is a space after the final multiple


Test 9 – Sum of values
public static int Test9(int start, int end)
Given two int's start and end, find the sum of all values between start and end (inclusive). 



For example, given 11 (start) and 19 (end), the result is 135 (11+12+13+14+15+16+17+18+19)


Example Input	Example Output
5, 9

35

Test 10 – Sum of values
public static int Test9(Random gener, int min, int max, int qty)
Given an instance of the Random class, gener, use it to generate qty number of random integers in the range min (inclusive) to max (exclusive). Find and return the sum of the random numbers you generate.

For example, given gener, 3, 7, 5, you will generate 5 random numbers between 3 and 7 (actually 3 and 6 because 7 is excluded) and find the sum of those 5 numbers. Return the sum.

Additional resources:

Random Class: https://www.youtube.com/watch?v=7ZJ1v5hKxs8
Example Input	Example Output
gener, 3, 7, 5

23

Note: This test does not require that you define an instance of a Random object – it is provided (gener). You can call gener’s methods to generate the random int values you are adding.
