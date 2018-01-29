import java.util.LinkedList;
import java.util.List;
public class MoveToFront {
	// apply move-to-front encoding, reading from standard input and writing to standard output
	public static void encode()
	{
		char[] asciiTable = new char[256];
		for(int i = 0; i < asciiTable.length; i++)
			asciiTable[i] = (char) i;
		String alphabet = new String(asciiTable);


		String in = BinaryStdIn.readString();
		char[] inArray = in.toCharArray();
		List<Integer> output = new LinkedList<Integer>();
		StringBuilder s = new StringBuilder(alphabet);

		for(int i = 0; i < inArray.length; i++){
			int id = s.indexOf("" + inArray[i]);
			output.add(id);
			s = s.deleteCharAt(id).insert(0, inArray[i]);
		}

		char[] result = new char[inArray.length];
		for(int i = 0; i < result.length; i++){
			//System.out.println("GET");
			result[i] = (char)(int)output.get(i);
			BinaryStdOut.write(result[i]);
		}

		BinaryStdOut.close();
	}

	// apply move-to-front decoding, reading from standard input and writing to standard output
	public static void decode()
	{
		char[] asciiTable = new char[256];
		for(int i = 0; i < asciiTable.length; i++)
			asciiTable[i] = (char) i;
		String alphabet = new String(asciiTable);


		String in = BinaryStdIn.readString();
		char[] inArray = in.toCharArray();
		LinkedList<Integer> input = new LinkedList<Integer>();

		for(int i = 0; i < inArray.length; i++){
			input.add((int)inArray[i]);
		}

		StringBuilder out = new StringBuilder();
		StringBuilder s = new StringBuilder(alphabet);
		for(int i = 0; i < input.size(); i++){
			char c = s.charAt(input.get(i));
			out = out.append(c);
			s = s.deleteCharAt(input.get(i)).insert(0, c);
		}

		BinaryStdOut.write(out.toString());
		BinaryStdOut.close();
	}

	// if args[0] is '-', apply move-to-front encoding
	// if args[0] is '+', apply move-to-front decoding
	public static void main(String[] args)
	{
		if	(args[0].equals("-")) encode();
		else if	(args[0].equals("+")) decode();
		else throw new RuntimeException("Illegal command line argument");
	}
}
