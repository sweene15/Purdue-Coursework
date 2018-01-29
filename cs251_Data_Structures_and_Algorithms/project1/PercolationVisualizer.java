import java.io.*;

public class PercolationVisualizer {

	public static void main(String[] args) {
		int n = StdIn.readInt();							//Read Size
		int a, b;
		Percolation p = new Percolation(n);					//Create Object
		while (!(StdIn.isEmpty())) {						//Pull values from stdin, set valid array spaces to 1
            a = StdIn.readInt();
            b = StdIn.readInt();
            p.open(a,b);
            //System.out.println(a + " " + b);
        }
				
		//PERCOLATION SUB-ROUTINE
		
		for(int i = 0; i < n; i++){						//Fill any open in top row
			if(p.isOpen(n-1, i)){
				p.fill(n-1, i);
			}
		}
		
		for(int i = n-1; i >= 0; i--){
			for(int j = 0; j < n; j++){
				if(p.grid[i][j] == 2){
					if(i + 1 < n && i + 1 >= 0){							//FILL NORTH IF POSSIBLE
						if(p.grid[i+1][j] == 1){
							p.fill(i + 1 , j);
						}
					}
					if(i - 1 < n && i - 1 >= 0){							//FILL SOUTH IF POSSIBLE
						if(p.grid[i-1][j] == 1){
							p.fill(i - 1 , j);
						}
					}
					if(j + 1 < n && j + 1 >= 0){							//FILL EAST IF POSSIBLE
						if(p.grid[i][j + 1] == 1){
							p.fill(i, j + 1);
						}
					}
					if(j - 1 < n && j - 1 >= 0){							//FILL WEST IF POSSIBLE
						if(p.grid[i][j - 1] == 1){
							p.fill(i, j - 1);
						}
					}
					
				}
			}
		}
		
		
		for(int i = 0; i < n; i++){
			for(int j = n - 1; j >= 0; j--){
				if(p.grid[i][j] == 2){
					if(i + 1 < n && i + 1 >= 0){							//FILL NORTH IF POSSIBLE
						if(p.grid[i+1][j] == 1){
							p.fill(i + 1 , j);
						}
					}
					if(i - 1 < n && i - 1 >= 0){							//FILL SOUTH IF POSSIBLE
						if(p.grid[i-1][j] == 1){
							p.fill(i - 1 , j);
						}
					}
					if(j + 1 < n && j + 1 >= 0){							//FILL EAST IF POSSIBLE
						if(p.grid[i][j + 1] == 1){
							p.fill(i, j + 1);
						}
					}
					if(j - 1 < n && j - 1 >= 0){							//FILL WEST IF POSSIBLE
						if(p.grid[i][j - 1] == 1){
							p.fill(i, j - 1);
						}
					}
					
				}
			}
		}
		
		try (Writer output = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("visualMatrix.txt"), "utf-8"))) {
			output.write(n+"\n\n");
			for(int i = n-1; i >= 0; i--){
				for(int j = 0; j < n; j++){
					output.write(p.grid[i][j] + " ");
				}
				output.write("\n");
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

}
