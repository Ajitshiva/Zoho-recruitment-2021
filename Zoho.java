import static java.lang.System.out;
import java.io.*;
import java.util.*;
class Zoho
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		String s = sc.nextLine();
		int len = s.length();
		int mid = len / 2;
		for(int row = 0; row < s.length(); row++)
		{
			for(int space = 0; space < len - row - 1; space++)
			{
				out.print("  ");
			}
			for(int col = 0; col <= row; col++)
			{
				out.print(s.charAt((col + mid) % len) + " ");
			}
			out.println();
		}

	}
}