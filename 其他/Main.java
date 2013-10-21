import java.util.*;
import java.io.*;
import java.math.*;

class Task{
	
	InputReader in;
	PrintWriter out;


	Task(InputReader in, PrintWriter out){
		this.in = in;
		this.out = out;
	}

	void run(){
	}

}

class InputReader {
	public BufferedReader reader;
	public StringTokenizer tokenizer;

	public InputReader(InputStream stream) {
		reader = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}

	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

	public int nextInt() {
		return Integer.parseInt(next());
	}

	public int nextHex() {
		return Integer.parseInt(next(), 16);
	}

	public long nextLong() {
		return Long.parseLong(next());
	}

	public double nextDouble() {
		return Double.parseDouble(next());
	}

	public BigInteger nextBigInteger(){
		return new BigInteger(next(), 10);
	}

}


public class Main{
	public static void main(String args[]){
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);
		Task solver = new Task(in, out);	
		solver.run();
		out.close();
	}
}
