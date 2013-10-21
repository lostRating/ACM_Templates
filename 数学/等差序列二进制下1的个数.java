import java.io.*;
import java.util.*;

public class Main {
    final static int LENGTH = 55;

    long countBit(int a, long b, long n, int k) {
        long ret = 0;
        long now = b;
        long mod = 1L << k;
        while (n > 0) {
            long need = mod - (now % mod);
            long step = Math.min((need + a - 1) / a, n);
            if ((now >> k & 1) == 1) {
                ret += step;
            }
            n -= step;
            now += step * a;
        }
        return ret;
    }

    long solve(int a, long b, long n) {
        long ret = 0;
        for (int k = 0; k < LENGTH; ++ k) {
            long period = 1L << k + 1;
            ret += countBit(a, b, period, k) * (n / period);
            ret += countBit(a, b, n % period, k);
        }
        return ret;
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        int testCount = scanner.nextInt();
        for (int t = 1; t <= testCount; ++ t) {
            int a = scanner.nextInt();
            long b = scanner.nextLong();
            long n = scanner.nextLong();
            System.out.println("Case #" + t + ": " + solve(a, b + a, n));
        }
    }

    public static void main(String[] args) {
        new Main().run();
    }
}
