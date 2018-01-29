import java.io.BufferedWriter;
import java.util.Arrays;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;

public class Fast {

	public Point[] pointArray;
	public int n;
	public Point[] temp;
	public Point[][] listArray;
	public Point[][] finalArray;
	public int listArrayCount = 0;
	public int finalArrayCount = 0;
	
	public static void main(String[] args){
		Fast f = new Fast();
		f.build();
		f.listArray = new Point[f.n*f.n][f.n];
		f.temp = new Point[f.n - 1];
		f.finalArray = new Point[f.n*f.n][f.n];
		
        //Fast It Up
		for(int i = 0; i < f.n; i++) {
			int k = 0;
			for(int j = 0; j < f.n; j++){
				if(j != i){
					f.temp[k] = f.pointArray[j];
					k++;
				}
			}
			Arrays.sort(f.temp, f.pointArray[i].BY_SLOPE_ORDER);
	
			f.isLine(f.temp, i);
		}
		f.prepIt();
        f.writeIt();
	}

	
	private void prepIt() {
		//SORT IT LEXI
				for(int i = 0; i < listArrayCount; i++){
					int j, k;
					Point a;
					for (j = 0; j < arrayCounter(listArray[i]); j++)
				    {
				        for (k = j + 1; k < arrayCounter(listArray[i]); k++)
				        {
				            if (listArray[i][j].compareTo(listArray[i][k]) == 1)
				            {
				                a =  listArray[i][j];
				                listArray[i][j] = listArray[i][k];
				                listArray[i][k] = a;
				            }
				        }
				    }
				}
				//DELETE DUPLI
				Point[][] tempArray = new Point[n*n][n];
				int tempArrayCount = 0;
				boolean checkForMatch = false;
				for(int i = 0; i < listArrayCount; i++){
					for(int j = 0; j <= tempArrayCount ; j++){
						if(Arrays.equals(listArray[i], tempArray[j])){
							checkForMatch = true;
						}
					}
					if(!checkForMatch){
						tempArray[tempArrayCount] = listArray[i];
						tempArrayCount++;
					} else {
						checkForMatch = false;
					}
				}
				//DELETE INNERS
				for(int i = 0; i < tempArrayCount; i++){
					for(int j = 0; j < tempArrayCount; j++){
						if(tempArray[i] != null && tempArray[j] != null && i != j){
							if(Arrays.asList(tempArray[i]).containsAll(Arrays.asList(tempArray[j]))){
								tempArray[j] = null;
							}
						}
					}
				}
				int k = 0;
				for (int c = 0; c < tempArrayCount; c ++){
				    if (tempArray[c] != null){
				    	finalArray[k] = tempArray[c];
				    	finalArrayCount++;
				    	k++;
				    }
				}			
	}


	private void writeIt() {
		try (Writer output = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("visualPoints.txt"), "utf-8"))) {
				for(int i = 0; i < finalArrayCount; i++){
					if(arrayCounter(finalArray[i]) != 0){
						System.out.print(arrayCounter(finalArray[i]) + ":");
						output.write(arrayCounter(finalArray[i]) + ":");
					}
					for(int j = 0; j < arrayCounter(finalArray[i]); j++){
						System.out.print("(" + finalArray[i][j].getX() + ", " + finalArray[i][j].getY() + ")");
						output.write("(" + finalArray[i][j].getX() + ", " + finalArray[i][j].getY() + ")");
						if(j < arrayCounter(finalArray[i]) - 1){
							System.out.print(" -> ");
							output.write(" -> ");
						} else {
							System.out.print("\n");
							output.write("\n");
						}
					}
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

	private void isLine(Point[] x, int a) {
		int count = 1;
		int j;
		for(j = 0; j < arrayCounter(x); j++){
			if(j < arrayCounter(x) - 1){
				if(pointArray[a].getAngle(x[j]) == pointArray[a].getAngle(x[j+1])){
					count++;
				} else {
					if(count >= 3){
						for(int i = 0, k = count; k >= 1; i++, k--){
							listArray[listArrayCount][i] = x[j - k + 1];
						}
						listArray[listArrayCount][arrayCounter(listArray[listArrayCount])] = pointArray[a];
						listArrayCount++;
					}
					count = 1;
				}
			}
		}
		if(count >= 3){
			for(int i = 0, k = count; k >= 1; i++, k--){
				listArray[listArrayCount][i] = x[j - k];
			}
			listArray[listArrayCount][arrayCounter(listArray[listArrayCount])] = pointArray[a];
			listArrayCount++;
		}
		
	}
	private int arrayCounter(Point[] x) {
		int counter = 0;
		for (int c = 0; c < x.length; c ++)
		    if (x[c] != null)
		        counter ++;
		return counter;
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
