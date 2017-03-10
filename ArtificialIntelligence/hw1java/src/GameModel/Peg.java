package GameModel;

public class Peg {
	private int row = 0;
    private int column = 0;
    
    //bool exists if this peg has not been eaten during the game

    private int f = 0; // needed for A*

    public Peg(int row, int column) {
        this.row = row;
        this.column = column;
    }

    public boolean equals(Peg other) {
        if ( this.row == other.row && this.column == other.column ) 
            return true;
        return false;
    }

    public int getRow() {
        return this.row;
    }

    public int getCol() {
        return this.column;
    }
    
    public String toString() {
        return "(" + this.row + "," + this.column + ")";
    }
    
    public int manhattandistance() {
        return Math.abs(this.column - 3) + Math.abs(this.row - 3);
    }

    //given a peg in an old position, move it in some direction
    public Peg move(int[][] grid, char direction) { // (3,4) to n
        int r = this.row;
        int c = this.column;
        if ( direction == 'n' ) {
            if ( grid[r - 1][c] == 0 ) {
                r = this.row-1;
                c = this.column;
            }
            else {  // move north, eating peg
                r = this.row-2;
                c = this.column;
                grid[r - 2][c] = 1;
            }
        }
        else if( direction == 'e') {
            if ( grid[r][c + 1] == 0 ) {
                r = this.row;
                c = this.column + 1;
            }
            else {
                r = this.row;
                c = this.column+2;
            }
        }
        else if ( direction == 's' ) {
            if ( grid[r + 1][c] == 0 ) {
                r = this.row+1;
                c = this.column;
            }
            else {
                r = this.row+2;
                c = this.column;
            }
        }
        else {  // direction == 'w'
            if ( grid[r][c - 1] == 0 ) {
                c = this.column-1;
                r = this.row;
            }
            else {
                c = this.column - 2;
                r = this.row;
            }
        }
        return new Peg(r,c);
    }
    
}
