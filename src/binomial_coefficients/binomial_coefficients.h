#include <vector>
#include <iostream>

/*
* The binomial coefficient indexed by n and k denoted by ( n chooses k ) is the
* coefficient if the x^k term in the polynomial expansion of the binomial power (1+x)^n.
* The value of this coefficient can be determined by (n!/(k!(n-k)!)), but factorials are 
* generally resource-intense to calculate and don't offer caching mechanisms.
*
* The task is implement a function below in a more efficient way:
*
* unsigned int bin(unsigned int n, unsigned int k)
*
* ==========
*
* Solution
*
* The beauty of this solution resides in the Pascal's Triangle, which tabulates the
* binomial coefficients, which can be iteratively computed as 
* (n chooses k) = ((n-1) chooses k) + ((n-1) chooses (k-1))
*
* 0:									1								
* 1:								1		1							
* 2:							1		2		1						
* 3:						1		3		3		1					
* 4:					1		4		6		4		1				
* 5:				1		5		10		10		5		1			
* 6:			1		6		15		20		15		6		1		
*
* Where n is the row and k is the column (both zero-indexed). Also one has to note that
* there are as many columns as the value of the row (k goes from 0 to n) with exception of
* the row 0 which is (0 chooses 0) = 1.
*/
