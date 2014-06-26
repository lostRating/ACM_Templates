import java.util.*;
import java.io.*;
import java.math.*;

public class Main{
	public static void main(String args[]){
	    Scanner in = new Scanner(System.in);
	    while (in.hasNextInt())
        {
            int t = in.nextInt();
            int a = in.nextInt();
            int b = in.nextInt();
            System.out.print("(" + t + "^" + a + "-1)/");
            System.out.print("(" + t + "^" + b + "-1) ");
            if (t == 1)
            {
                System.out.println("is not an integer with less than 100 digits.");
            }
            else if (a % b != 0)
            {
                System.out.println("is not an integer with less than 100 digits.");
            }
            else if (a == b)
            {
                System.out.println("1");
            }
            else
            {
                BigInteger ans = new BigInteger("1", 10);
                BigInteger tmp = new BigInteger("1", 10);
                BigInteger fff = new BigInteger(Integer.toString(t), 10);
                BigInteger gxx = new BigInteger("1", 10);
                String s = "";
                for (int i = 0; i < 100; ++i)
                    s += "9";
                BigInteger lim = new BigInteger(s, 10);
                for (int i = 0; i < b; ++i)
                {
                    gxx = gxx.multiply(fff);
                    if (gxx.compareTo(lim) > 0) break;
                }
                //System.out.println(gxx);
                if (gxx.compareTo(lim) > 0)
                {
                    System.out.println("is not an integer with less than 100 digits.");
                    continue;
                }
                int tt = b;
                b += tt;
                while (b <= a)
                {
                    tmp = tmp.multiply(gxx);
                    ans = ans.add(tmp);
                    if (b == a) break;
                    b += tt;
                }
                if (ans.compareTo(lim) > 0)
                    System.out.println("is not an integer with less than 100 digits.");
                else
                    System.out.println(ans);
            }
        }
	}
}
