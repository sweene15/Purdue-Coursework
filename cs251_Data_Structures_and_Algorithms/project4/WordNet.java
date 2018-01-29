import java.util.Scanner;
import java.io.FileReader;
import java.io.FileNotFoundException;

public final class WordNet {

  public static final int MAX_SIZE = 81426;
  public String sys;
  public SAP s;
  public int[] indexA;
  public int[] indexB;
  public int countA;
  public int countB;
  public WordNet(String sysnets, String hypernyms){

	sys = sysnets;
  	//BUILD DIGRAPH
	Digraph x = new Digraph(MAX_SIZE);
	try{
	Scanner in = new Scanner(new FileReader(hypernyms));
	for(int i = 0; i < MAX_SIZE; i++){
		String line = in.nextLine();
		String[] tokens = line.split(",");
		for(int j = 1; j < tokens.length; j++){
			int a, b;
			a = Integer.parseInt(tokens[0]) - 1;
			b = Integer.parseInt(tokens[j]) - 1;
			x.addEdge(a,b);
		}
	}
	s = new SAP(x);

	} catch (FileNotFoundException e){
		e.printStackTrace();	}
  }
  //THIS FUNCTION IS NOT USED AT ALL IN THIS PROGRAM.
  public boolean isNoun(String word){
	try{
	Scanner in = new Scanner(new FileReader(sys));
	for(int i = 0; i < MAX_SIZE; i++){
		String line = in.nextLine();
		String[] tokens = line.split(",");
		String[] nouns = tokens[1].split(" ");
		for(int j = 0; j < nouns.length; j++){
			if(nouns[j].equals(word))
				return true;
		}
	}
	} catch (FileNotFoundException e){
		e.printStackTrace();}

	return false;
  }


  public void printSap(String nounA, String nounB){

	//Find Index of Strings
  	countA = 0;
	countB = 0;
	indexA = new int[]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	indexB = new int[]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	try{
	Scanner in = new Scanner(new FileReader(sys));

	for(int i = 0; i < MAX_SIZE; i++){
		String line = in.nextLine();
		String[] tokens = line.split(",");
		String[] nouns = tokens[1].split(" ");
		for(int j = 0; j < nouns.length; j++){
			if(nouns[j].equals(nounA)){
				indexA[countA] = i;
				countA++;
			}
			if(nouns[j].equals(nounB)){
				indexB[countB] = i;
				countB++;
			}
		}
	}
	} catch (FileNotFoundException e){
		e.printStackTrace();}
	//BUILD SAP AND READ INPUT FROM .INPUT FILE, PRINT RESULT
	int c = 100;
	int d = -1;
	String result = "null";
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(indexA[i] != -1 && indexB[j] != -1){
				if(c > s.length(indexA[i], indexB[j])){
					c = s.length(indexA[i], indexB[j]);
					d = s.ancestor(indexA[i], indexB[j]);
					try{
					Scanner in = new Scanner(new FileReader(sys));
					String blah = "";
					for(int k = 0; k <= d; k++){
						blah = in.nextLine();
					}
					String [] temp = blah.split(",");
					result = temp[1];
					} catch (FileNotFoundException e){
						e.printStackTrace();}
				}
			}
		}
	}
	if(c == 100)
		c = -1;
	System.out.printf("sap = " + c + ", ancestor = " + result + "\n");
  }
  public static void main(String[] args){
		
	WordNet w = new WordNet(args[0], args[1]);
	String a, b;
	try{
	Scanner in = new Scanner(new FileReader(args[2]));
	while(in.hasNextLine()){
		String blah = "";
		blah = in.nextLine();
		String []temp = blah.split(" ");
		w.printSap(temp[0], temp[1]);
	}
	} catch (FileNotFoundException e){
		e.printStackTrace();}
/*	
	while(!(StdIn.isEmpty())){
		a = StdIn.readString();
		b = StdIn.readString();
		w.printSap(a, b);
	}
*/
  }
}
