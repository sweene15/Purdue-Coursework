import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.lang.String;
import java.util.Comparator;

public class BurrowsWheeler {

    // apply Burrows-Wheeler encoding, reading from standard input and writing to standard output
    public static void encode()
     { 
    	String s = BinaryStdIn.readString();
	//int[] indices = new int[s.length()];
	//System.out.println("Length: " + s.length());
	/*
	for(int i = 0; i < s.length(); i++){
		indices[i] = i;
 	}
	*/
	//sort(indices, s);
	Integer[] index = new Integer[s.length()];
	for(int i = 0; i < s.length(); i++)
		index[i] = i;
	
	Arrays.sort(index, new Comparator<Integer>(){
		public int compare(Integer a, Integer b){
			int x = a.intValue();
			int y = b.intValue();
			int r = 0;
			for(int i = 0; i < s.length(); i++){
				if(x > s.length() - 1)
					x = 0;
				if(y > s.length() - 1)
					y = 0;
				if(s.charAt(x) > s.charAt(y)){
					//System.out.println("test1");
					r = 1;
					return r;
					}
				else if(s.charAt(x) < s.charAt(y)){
					//System.out.println("test2");
					r = -1;
					return r;
					}
				x++;
				y++;
			}
			return r;
		}
	});

	for(int i = 0; i < s.length(); i++){
		if(index[i] == 0){
			BinaryStdOut.write(i);
		}
	}
	char[] result = new char[s.length()];
	for(int i = 0; i < s.length(); i++)
		result[i] = getString(index[i], s).charAt(s.length() - 1);
	String strR = new String(result);
	BinaryStdOut.write(strR);
	BinaryStdOut.close();
     }
/*
    public static int array[];
    public static int length;
    public static int count;
    public static void sort(int[] in, String s) {  
    	if(in == null || in.length == 0)
		return;
	array = in;
	length = in.length;
	quickSort(0, length - 1, s);
    }
    public static void quickSort(int lo, int hi, String s){
	int i = lo;
	int j = hi;
	int p = array[lo+(hi-lo)/2];
	while(i <= j){
		while(getString(array[i], s).compareTo(getString(p, s)) < 0)
			i++;
		while(getString(array[j], s).compareTo(getString(p, s)) > 0)
			j--;
		if(i <= j){
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if(lo < j)
		quickSort(lo, j, s);
	if(i < hi)
		quickSort(i, hi, s);
    }
*/
    public static String getString(int n, String s){
	char[] temp = new char[s.length()];
	for(int count = 0; count < s.length(); count++){
		int c = count + n;
		if(c >= s.length())
			c = c - s.length();
		temp[count] = s.charAt(c);
	}
	String result = new String(temp);
	return result;
    }

    // apply Burrows-Wheeler decoding, reading from standard input and writing to standard output
    public static void decode()
    {
	int n = BinaryStdIn.readInt();
	String s = BinaryStdIn.readString();
	char[] sArray = s.toCharArray();
	int l = sArray.length;
	int next[] = new int[l];
	HashMap<Character, Queue<Integer>> m = new HashMap<Character, Queue<Integer>>();
	for(int i = 0; i < l; i++){
		if(!m.containsKey(sArray[i]))
			m.put(sArray[i], new Queue<Integer>());
		m.get(sArray[i]).enqueue(i);
	}
	Arrays.sort(sArray);
	for(int i = 0; i < l; i++){
		next[i] = m.get(sArray[i]).dequeue();
	}
	char[] resultArray  = new char[l];
	for(int i = 0, count = n; i < l; i++, count = next[count])
		resultArray[i] = sArray[count];
	
	String result = new String(resultArray);
	BinaryStdOut.write(result);
	BinaryStdOut.close();
    }


    public static void main(String[] args)
    {
    	if	(args[0].equals("-")) encode();
	else if (args[0].equals("+")) decode();
	else throw new RuntimeException("Illegal command line argument");
    }
}
