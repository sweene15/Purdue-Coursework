
public class PercolationQuick {
	public int[][] grid;
	public int size;
	public QuickUnionUF openSpaces;
	public QuickUnionUF fullSpaces;
	public PercolationQuick(int n){
		grid = new int[n][n];								//CREATES GRID STRUCTURE, 2D ARRAY
		openSpaces = new QuickUnionUF(n*n);			//CREATES EMPTY UF, of size n^2 for Open
		fullSpaces = new QuickUnionUF(n*n);			//Creates EMPTY UF, of size n^2 for Full
		size = n;
	}
	public void open(int x, int y){
		grid[x][y] = 1;											//Sets Grid value
		openSpaces.status[x*size + y] = 1;						//sets UF value
		for(int i = 0; i < grid.length*grid.length; i++){		//finds other UF node with similar status value and not connected, and unions the two. Cannot union w/ self.
			if(openSpaces.status[i] == 1 && !openSpaces.connected(i, x*size + y)){
				openSpaces.union(i, x*size + y);
				continue;
			}
		}
	}
	
	public void fill(int x, int y){
		grid[x][y] = 2;											//Sets Grid value
		fullSpaces.status[x*size + y] = 2;						//sets UF value
		for(int i = 0; i < grid.length*grid.length; i++){		//finds other UF node with similar status value and not connected, and unions the two. Cannot union w/ self.
			if(fullSpaces.status[i] == 1 && !fullSpaces.connected(i, x*size + y)){
				fullSpaces.union(i, x*size + y);
				continue;
			}
		}
		
	}
	
	
	public boolean isOpen(int x, int y){					//Checks if Open (equal to 1)
		if(grid[x][y] == 1){
			return true;
		} else {
			return false;
		}
	}
	public boolean isFull(int x, int y){					//Checks if Full (equal to 2)
		if(grid[x][y] == 2){
			return true;
		} else {
			return false;
		}
	}
	public boolean percolates(){				 			//Checks if Percolates (one in the bottom row is full)
		for(int i = 0; i < size; i++){
			if(isFull(0,i)){
				return true;
			}
		}
		return false;
	}
	public static void main(String[] args){
		int n = StdIn.readInt();							//Read Size
		int a, b;
		Percolation p = new Percolation(n);					//Create Object
		while (!(StdIn.isEmpty())) {						//Pull values from stdin, set valid array spaces to 1
            a = StdIn.readInt();
            b = StdIn.readInt();
            p.open(a,b);
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
		
		System.out.println(p.percolates());
	}
}
