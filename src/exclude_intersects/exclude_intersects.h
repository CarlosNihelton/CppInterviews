#include <vector>
#include <iostream>

/*
* http://leetcode.libaoj.in/remove-interval.html
*
* 1272. Remove Interval

Description
Given a sorted list of disjoint intervals, each interval intervals[i] = [a, b] represents the set of real numbers x such that a <= x < b.

We remove the intersections between any interval in intervals and the interval toBeRemoved.

Return a sorted list of intervals after all such removals.

 

Example 1:

Input: intervals = [[0,2],[3,4],[5,7]], toBeRemoved = [1,6]
Output: [[0,1],[6,7]]
Example 2:

Input: intervals = [[0,5]], toBeRemoved = [2,3]
Output: [[0,2],[3,5]]
Example 3:

Input: intervals = [[-5,-4],[-3,-2],[1,2],[3,5],[8,9]], toBeRemoved = [-1,4]
Output: [[-5,-4],[-3,-2],[4,5],[8,9]]

Hints
Solve the problem for every interval alone.
Divide the problem into cases according to the position of the two intervals.


vector<pair<int,int>> removeInterval(vector<pair<int,int>> intervals, pair<int,int> toBeRemoved){
 // your code goes here.
}


Solution Article
Approach 1: Sweep Line, One Pass.
Best Possible Time Complexity

What is the best possible time complexity here?

The input is sorted, that usually means at least linear time complexity. Is it possible to do O(logN)O(log⁡N)? No, because to copy input elements into output still requires O(N)O(N) time.

Sweep Line

Sweep Line algorithm is a sort of geometrical visualisation. Let's imagine a vertical line which is swept across the plane, stopping at some points. That could create various situations, and the decision to make depends on the stop point.



* */
