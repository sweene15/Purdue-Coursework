import java.util.*;

public class PercolationStats {
	public int[] opencount;
	public long[] timeList;
	public int n;
	public int t;
	public String type;
	public PercolationQuick q;
	public Percolation p;
	public PercolationStats(int x, int y, String s){
		n = x;
		t = y;
		type = s;
		opencount = new int[t];
		timeList = new long[t];
	}
	public void percolator(int n) {
		
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
		
	}
	
	public void quickPercolator(int n){
		
		for(int i = 0; i < n; i++){						//Fill any open in top row
			if(q.isOpen(n-1, i)){
				q.fill(n-1, i);
			}
		}
		
		
		for(int i = n-1; i >= 0; i--){
			for(int j = 0; j < n; j++){
				if(q.grid[i][j] == 2){
					if(i + 1 < n && i + 1 >= 0){							//FILL NORTH IF POSSIBLE
						if(q.grid[i+1][j] == 1){
							q.fill(i + 1 , j);
						}
					}
					if(i - 1 < n && i - 1 >= 0){							//FILL SOUTH IF POSSIBLE
						if(q.grid[i-1][j] == 1){
							q.fill(i - 1 , j);
						}
					}
					if(j + 1 < n && j + 1 >= 0){							//FILL EAST IF POSSIBLE
						if(q.grid[i][j + 1] == 1){
							q.fill(i, j + 1);
						}
					}
					if(j - 1 < n && j - 1 >= 0){							//FILL WEST IF POSSIBLE
						if(q.grid[i][j - 1] == 1){
							q.fill(i, j - 1);
						}
					}
					
				}
			}
		}
		
		
		for(int i = 0; i < n; i++){
			for(int j = n - 1; j >= 0; j--){
				if(q.grid[i][j] == 2){
					if(i + 1 < n && i + 1 >= 0){							//FILL NORTH IF POSSIBLE
						if(q.grid[i+1][j] == 1){
							q.fill(i + 1 , j);
						}
					}
					if(i - 1 < n && i - 1 >= 0){							//FILL SOUTH IF POSSIBLE
						if(q.grid[i-1][j] == 1){
							q.fill(i - 1 , j);
						}
					}
					if(j + 1 < n && j + 1 >= 0){							//FILL EAST IF POSSIBLE
						if(q.grid[i][j + 1] == 1){
							q.fill(i, j + 1);
						}
					}
					if(j - 1 < n && j - 1 >= 0){							//FILL WEST IF POSSIBLE
						if(q.grid[i][j - 1] == 1){
							q.fill(i, j - 1);
						}
					}
					
				}
			}
		}	
	
	}
	
	
	
	
	public static void main(String[] args){
		int inputOne = Integer.parseInt(args[0]);
		int inputTwo = Integer.parseInt(args[1]);
		String inputThree = args[2];
		
		PercolationStats stats = new PercolationStats(inputOne, inputTwo, inputThree);
		
		//FAST AND SLOW generation and percolation
		long startTotalTime = System.nanoTime();
		if(stats.type.equals("slow")){
			for(int i = 0; i < stats.t; i++) {
				long startAvgTime = System.nanoTime();
				stats.q = new PercolationQuick(stats.n);
				while(stats.q.percolates() == false){
					Random rand = new Random();
					int  x = rand.nextInt(stats.n);
					int  y = rand.nextInt(stats.n); 
					if(stats.q.isOpen(x, y) || stats.q.isFull(x, y)){
						continue;
					}
					stats.q.open(x,y);
					stats.opencount[i]++;
					stats.quickPercolator(stats.n);
				}
				stats.timeList[i] = System.nanoTime() - startAvgTime;
			}
		} else if(stats.type.equals("fast")){
			for(int i = 0; i < stats.t; i++) {
				long startAvgTime = System.nanoTime();
				stats.p = new Percolation(stats.n);
				while(stats.p.percolates() == false){
					Random rand = new Random();
					int  x = rand.nextInt(stats.n);
					int  y = rand.nextInt(stats.n); 
					if(stats.p.isOpen(x, y) || stats.p.isFull(x, y)){
						continue;
					}
					stats.p.open(x,y);
					stats.opencount[i]++;
					stats.percolator(stats.n);
				}
				stats.timeList[i] = System.nanoTime() - startAvgTime;
			}
		} else {
			System.out.println("Invalid Input (TYPE)");
		}
		
		//DATA PROCESSING
		
		//TOTAL TIME
		long totalTime = System.nanoTime() - startTotalTime;
		
		//AVERAGE TIME
		long meanTime;
		long timeSum = 0;
		for(int i = 0; i < stats.timeList.length; i++) {
			timeSum += stats.timeList[i];
		}
		meanTime = timeSum / stats.timeList.length;
		
		//STND DEV TIME
		long[] deviationTime = new long[stats.timeList.length];
	    double timeDevsum = 0;
	    double timeStndev;
	    for(int i = 0; i < stats.timeList.length; i++) {
	    	deviationTime[i] = stats.timeList[i] - meanTime;
	    	timeDevsum += Math.abs(deviationTime[i]);
	    }
	    timeStndev = Math.sqrt(timeDevsum);
		
		//MEAN
		double mean;
		double sum = 0;
	    for(int i = 0; i < stats.opencount.length; i++) {
	        sum += stats.opencount[i];
	    }
	    mean = sum / stats.opencount.length;
		
		//STND DEV
	    double[] deviation = new double[stats.opencount.length];
	    double devsum = 0;
	    double stndev;
	    for(int i = 0; i < stats.opencount.length; i++) {
	    	deviation[i] = stats.opencount[i] - mean;
	    	devsum += Math.abs(deviation[i]);
	    }
	    stndev = Math.sqrt(devsum);
		
	    
	    System.out.println("mean threshold= " + mean + "\n");
	    System.out.println("std dev= " + stndev + "\n");
	    System.out.println("time= " + totalTime + "\n");
	    System.out.println("mean time= " + meanTime + "\n");
	    System.out.println("stddev time= " + timeStndev + "\n");

	}
}
