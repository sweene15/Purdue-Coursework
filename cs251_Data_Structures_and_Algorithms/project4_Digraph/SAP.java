import java.util.Scanner;
import java.io.FileReader;
import java.io.FileNotFoundException;

public class SAP{
  //constructor
  public Digraph di;
  public SAP(Digraph G){
	di = new Digraph(G);	
  }
  public int length(int v, int w){
    	BreadthFirstDirectedPaths a = new BreadthFirstDirectedPaths(di, v);
	BreadthFirstDirectedPaths b = new BreadthFirstDirectedPaths(di, w);
  	int pathLength = di.V();
	for(int i = 0; i < di.V(); i ++){
		if(a.hasPathTo(i) && b.hasPathTo(i)){
			if(a.distTo(i) + b.distTo(i) < pathLength)
				pathLength = a.distTo(i) + b.distTo(i);
		}
	}
	if(pathLength == di.V())
		return -1;
	return pathLength;

  }
  public int ancestor(int v, int w){
  	BreadthFirstDirectedPaths a = new BreadthFirstDirectedPaths(di, v);
	BreadthFirstDirectedPaths b = new BreadthFirstDirectedPaths(di, w);
  	int pathLength = di.V();
	int temp = -1;
	for(int i = 0; i < di.V(); i ++){
		if(a.hasPathTo(i) && b.hasPathTo(i)){
			if(a.distTo(i) + b.distTo(i) < pathLength) {
				pathLength = a.distTo(i) + b.distTo(i);
				temp = i;
			}
		}
	}
	if(pathLength == di.V())
		return -1;
	return temp;
  }
  public static void main(String[] args){
  	Digraph x = new Digraph(0);
	try{
	Scanner in = new Scanner(new FileReader(args[0]));
	String vector = in.nextLine();
	int vec = Integer.parseInt(vector);
	x = new Digraph(vec);
	String edge = in.nextLine();
	int edg = Integer.parseInt(edge);
	for (int i = 0; i < edg; i++){
		//String blah = "";
		//blah = in.nextLine();
		//String []temp = blah.split(" ");
		//int v = Integer.parseInt(temp[0]);
		//int w = Integer.parseInt(temp[1]);
		int v = in.nextInt();
		int w = in.nextInt();
		x.addEdge(v, w);
	}
	} catch (FileNotFoundException e){
		e.printStackTrace();}
/*
	int vector = StdIn.readInt();
  	Digraph x = new Digraph(vector);
	int edge = StdIn.readInt();
	for (int i = 0; i < edge; i ++) {
		int v = StdIn.readInt();
		int w = StdIn.readInt();
		x.addEdge(v,w);
	}
*/
	SAP s = new SAP(x);
	try{
	int a, b, c, d;
	Scanner in = new Scanner(new FileReader(args[1]));
	while(in.hasNextLine()){
		String blah = "";
		blah = in.nextLine();
		String []temp = blah.split(" ");
		a = Integer.parseInt(temp[0]);
		b = Integer.parseInt(temp[1]);
		c = s.length(a, b);
		d = s.ancestor(a, b);
		System.out.printf("sap = " + c + ", ancestor = " + d + "\n");
	}
	} catch (FileNotFoundException e){
		e.printStackTrace();}
/*	
	int a, b, c, d;
	while(!(StdIn.isEmpty())){
		a = StdIn.readInt();
		b = StdIn.readInt();
		c = s.length(a,b);
		d = s.ancestor(a,b);
		System.out.printf("sap = " + c + ", ancestor = " + d + "\n");

	}
*/
  }
}
