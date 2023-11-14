package Assignment_A2.JAVA;

public class Main {
    public static void main(String[] args) {
        Pass1 pass1 = new Pass1( "Assignment_A2/testcase1.txt" ) ; 
        pass1.perform();
        System.out.println();
        System.out.println();
        Pass2 pass2 = new Pass2( "Assignment_A2/JAVA/MNT.dat", "Assignment_A2/JAVA/KPDTAB.dat", "Assignment_A2/JAVA/PNTAB.dat", "Assignment_A2/JAVA/MDT.dat" ) ; 
        pass2.processCall( "INCR(A,B,REG=AREG)" );
    }
}
