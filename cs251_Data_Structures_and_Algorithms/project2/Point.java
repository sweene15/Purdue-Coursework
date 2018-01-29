/*************************************************************************
 * Compilation:  javac Point.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/

import java.util.Comparator;

public class Point implements Comparable<Point>{
    // compare points by slope
    public final Comparator<Point>  BY_SLOPE_ORDER = new Comparator<Point>(){

		@Override
		public int compare(Point a, Point b) {
			if(this.getAngle(a) > this.getAngle(b)){
				return 1;
			} else if(this.getAngle(a) == this.getAngle(b)){
				return 0;
			}
			return -1;
		}
		

		private float getAngle(Point a) {
			return (float) Math.toDegrees(Math.atan2(a.x - x, a.y - y));		}
    	
    };
    private final int x;                              // x coordinate
    private final int y;                              // y coordinate

    // constructor
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // are the 3 points p, q, and r collinear?
    public static boolean areCollinear(Point p, Point q, Point r) {
        if((p.x * (q.y - r.y)+ q.x * (r.y - p.y) + r.x *(p.y - q.y)) == 0){
        	return true;
        }
        return false;	
    }

    // are the 4 points p, q, r, and s collinear?
    public static boolean areCollinear(Point p, Point q, Point r, Point s) {
    	if(areCollinear(p, q, r) && areCollinear(q, r, s)){
        	return true;
        }
        return false;	
    }

    // is this point lexicographically smaller than that one?
    public int compareTo(Point that) {
		if(this.getX() > that.getX() || (this.getX() == that.getX() && this.getY() > that.getY())){
			return 1;
		}
		if(this.getX() == that.getX() && this.getY() == that.getY()){
			return 0;
		}
		return -1;
        /* YOUR CODE HERE */
    }

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}
	
	//GET ANGLE Between two points
	public float getAngle(Point target) {
	    return (float) Math.abs(Math.toDegrees(Math.atan2(target.x - x, target.y - y)));
	}

}
