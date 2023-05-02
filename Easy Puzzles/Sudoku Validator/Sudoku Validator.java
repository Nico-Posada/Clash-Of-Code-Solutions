import java.util.*;
import java.io.*;
import java.math.*;

class Solution {
    public static Boolean check(int val)
    {
        if (val != 1)
            System.out.println(false);

        return val == 1;
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int[][] grid = new int[9][9];

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                grid[i][j] = in.nextInt();

        
        for (int[] row : grid)
        {
            int val = 0;
            for (int num : row)
                val ^= num;

            if (!check(val))
                return;
        }

        for (int x = 0; x < 9; x++)
        {
            int val = 0;
            for (int y = 0; y < 9; y++)
                val ^= grid[y][x];

            if (!check(val))
                return;
        }

        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                int val = 0;
                for (int a = 0; a < 3; a++)
                    for (int b = 0; b < 3; b++)
                        val ^= grid[y*3+a][x*3+b];

                if (!check(val))
                    return;
            }
        }

        System.out.println(true);
    }
}
