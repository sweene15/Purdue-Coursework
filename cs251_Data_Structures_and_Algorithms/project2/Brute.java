import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;

public class Brute {
	
	public Point[] pointArray;
	public int n;
	public Point[][] listArray;
	public int listArrayCount = 0;
	
	public Brute(){
		
	}
	
	public static void main(String[] args){
		Brute b = new Brute();
		b.build();
		b.listArray = new Point[b.n*b.n][5];
		
        //Brute it up
        for(int i = 0; i < b.n; i++){
        	for(int j = 0; j < b.n; j++){
        		if(i != j){
        			for(int k = 0; k < b.n; k++){
        				if(i != k && j != k){
        					for(int l = 0; l < b.n; l++){
    							if(i != l && j != l && k!= l){
    								if(Point.areCollinear(b.pointArray[i], b.pointArray[j], b.pointArray[k], b.pointArray[l])){
        								b.isLine(b.pointArray[i], b.pointArray[j], b.pointArray[k], b.pointArray[l]);
        							}
    							}
    						}
        				}
        			}
        		}
        	}
        }
        b.writeIt();
	}

	private void writeIt() {
		try (Writer output = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("visualPoints.txt"), "utf-8"))) {
			for(int i = 0; i < listArrayCount; i++){
				System.out.println("4" + ":" + "(" + listArray[i][0].getX() + ", " + listArray[i][0].getY() + ") -> " + "(" + listArray[i][1].getX() + ", " + listArray[i][1].getY() + ") -> " + "(" + listArray[i][2].getX() + ", " + listArray[i][2].getY() + ") -> " + "(" + listArray[i][3].getX() + ", " + listArray[i][3].getY() + ")");
				output.write(4 + ":" + "(" + listArray[i][0].getX() + ", " + listArray[i][0].getY() + ") -> " + "(" + listArray[i][1].getX() + ", " + listArray[i][1].getY() + ") -> " + "(" + listArray[i][2].getX() + ", " + listArray[i][2].getY() + ") -> " + "(" + listArray[i][3].getX() + ", " + listArray[i][3].getY() + ")\n");
			}
				
		} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
		} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
		} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
		}
			
	}

	private void isLine(Point point, Point point2, Point point3, Point point4) {
		
		
		
		Point tmp;
		if (point.compareTo(point2) == 1) { tmp = point; point = point2; point2 = tmp; }
		if (point3.compareTo(point4) == 1) { tmp = point3; point3 = point4; point4 = tmp; }
		if (point.compareTo(point3) == 1) { tmp = point; point = point3; point3 = tmp; }
		if (point2.compareTo(point4) == 1) { tmp = point2; point2 = point4; point4 = tmp; }
		if (point2.compareTo(point3) == 1) { tmp = point2; point2 = point3; point3 = tmp; }
		
		boolean checkForMatch = false;
		
		for(int i = 0; i < listArrayCount; i++){
			if((point.compareTo(listArray[i][0]) == 0 && point2.compareTo(listArray[i][1]) == 0 && point3.compareTo(listArray[i][2]) == 0 && point4.compareTo(listArray[i][3]) == 0)){
				checkForMatch = true;
			}
		}
		if(!checkForMatch){
			listArray[listArrayCount][0] = point;
			listArray[listArrayCount][1] = point2;
			listArray[listArrayCount][2] = point3;
			listArray[listArrayCount][3] = point4;
			listArrayCount++;
		}
	}

	private void build() {
		// read in the input, mostly ripped from Point Plotter
		n = StdIn.readInt();
        pointArray = new Point[n];
        int count = 0;
        while (!StdIn.isEmpty()) 
        {
            int x = StdIn.readInt();
            int y= StdIn.readInt();
            //create point and add to the array
            Point p = new Point(x, y);
            pointArray[count] = p;
            count++;
        }
		
	}
}
