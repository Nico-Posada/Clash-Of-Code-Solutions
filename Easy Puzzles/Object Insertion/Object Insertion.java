import java.util.*;
import java.io.*;
import java.math.*;

class ObjectFiller {
    // vars to externally fill
    private int obj_x, obj_y, grid_x, grid_y;
    private ArrayList<char[]> to_insert, grid;

    // vars to internally fill
    private int count = 0;

    public ObjectFiller(ArrayList<char[]> to_insert, ArrayList<char[]> grid)
    {
        this.obj_x = to_insert.get(0).length;
        this.obj_y = to_insert.size();

        this.grid_x = grid.get(0).length;
        this.grid_y = grid.size();

        this.to_insert = to_insert;
        this.grid = grid;
    }

    private Boolean isValid(int x, int y)
    {
        for (int i = 0; i < obj_y; i++)
        {
            for (int j = 0; j < obj_x; j++)
            {
                if (to_insert.get(i)[j] == '.') continue;
                if (grid.get(y+i)[x+j] == '#') return false;
            }
        }

        return true;
    }

    public void solve()
    {
        Boolean first_solve = true;
        for (int y = 0; y <= grid_y - obj_y; y++)
        {
            for (int x = 0; x <= grid_x - obj_x; x++)
            {
                Boolean valid = isValid(x, y);
                if (valid && first_solve)
                {
                    for (int i = 0; i < obj_y; i++) 
                    {
                        for (int j = 0; j < obj_x; j++) 
                        {
                            if (to_insert.get(i)[j] == '.') {continue;}
                            grid.get(y+i)[x+j] = '*';
                        }
                    }

                    this.count++;
                    first_solve = false;
                }
                else if (valid)
                    this.count++;
            }
        }
    }

    public int getCount()
    {
        return this.count;
    }

    public String toString()
    {
        String result = "";
        for (int i = 0; i < grid.size(); i++)
        {
            for (char c : grid.get(i))
                result += c;

            result += "\n";
        }

        return result;
    }
}

class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);

        int a = in.nextInt();
        in.nextInt();
        ArrayList<char[]> grid = new ArrayList<char[]>();
        ArrayList<char[]> to_insert = new ArrayList<char[]>();

        if (in.hasNextLine()) in.nextLine();
        for (int i = 0; i < a; i++) to_insert.add(in.nextLine().toCharArray());
        int c = in.nextInt();
        in.nextInt();
        if (in.hasNextLine()) in.nextLine();
        for (int i = 0; i < c; i++) grid.add(in.nextLine().toCharArray());

        ObjectFiller filler = new ObjectFiller(to_insert, grid);
        filler.solve();
        int count = filler.getCount();
        System.out.println(count);
        if (count == 1) System.out.println(filler);
    }
}
