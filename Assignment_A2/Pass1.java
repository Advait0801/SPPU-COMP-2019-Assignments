package Assignment_A2;

import java.util.*;
import java.io.*;

public class Pass1 implements Serializable{
    class MNTableEntry implements Serializable{
        public String macroName;
        public int numKPD = 0;
        public int numPP = 0;
        public int MDTabPtr = 0;
        public int kpdTabPtr = 0;

        public MNTableEntry(){}

        public MNTableEntry(String name,int k,int p,int mPtr,int kPtr){
            this.macroName = name;
            this.numKPD = k;
            this.numPP = p;
            this.MDTabPtr = mPtr;
            this.kpdTabPtr = kPtr;
        }
    }

    class MDTableEntry implements Serializable{
        public String mnemonic;
        public String operand1;
        public String operand2;
        public int op1Index = -1;
        public int op2Index = -1;
    }

    private ArrayList<String[]> tokens = new ArrayList<>() ;
    private ArrayList<String[]> KDPTAB = new ArrayList<>() ;
    private ArrayList<String> PNTAB = new ArrayList<>() ;  
    private ArrayList<MNTableEntry> MNT = new ArrayList<>() ; 
    private ArrayList<MDTableEntry> MDT = new ArrayList<>() ; 
    private String currentMacroName ; 
    private HashMap<String , List<String>> pnTabHashMap = new HashMap<>();

    public Pass1( String sourceFilepath ) {
        ArrayList<String> lines = readLines( sourceFilepath ) ; 
        for( String line : lines ) {
            tokens.add( line.split(" ") ) ; 
        }
    }

    public void perform() {
        int mdtabPtr = 0 ;
        int kpdtabPtr = 0 ;
        for( int i = 1 ; i < tokens.size() ; i++ ) { 
            String[] lineTokens = tokens.get( i ) ; 
            System.out.println( Arrays.toString( lineTokens ) ) ;
            if( tokens.get( i - 1 )[0].equals( "MACRO" ) )  {
                currentMacroName = lineTokens[ 0 ] ; 
                int numKPD = 0 ; 
                int numPP = 0 ; 
                PNTAB.clear();
                for( int j = 1 ; j < lineTokens.length ; j++ ) {
                    String parameter = lineTokens[ j ] ; 
                    if( parameter.contains( "=" ) ) {
                        KDPTAB.add( parameter.split( "=" ) ); 
                        numKPD++ ; 
                    }
                    else {
                        numPP++ ; 
                    }
                    System.out.println( "Parameter added : " + parameter ) ; 
                    PNTAB.add( parameter.split("=")[0] ) ; 
                }
                MNT.add( new MNTableEntry( currentMacroName , numKPD , numPP , mdtabPtr , kpdtabPtr ) ) ;
                System.out.println( "Added to map : " + currentMacroName ) ; 
                kpdtabPtr += numKPD ; 
                pnTabHashMap.put( currentMacroName , PNTAB ) ;  
            }
            else if( !lineTokens[0].equals( "MACRO" ) &&
             !lineTokens[0].equals( "MEND" ) ) {
                MDTableEntry entry = new MDTableEntry(); 
                entry.mnemonic = lineTokens[0] ;   
                List<String> currentPNTAB = pnTabHashMap.get( currentMacroName ) ; 
                if( lineTokens[1].startsWith( "&" ) ) {
                    int index = currentPNTAB.indexOf(lineTokens[1]) ; 
                    entry.operand1 = lineTokens[1] ;
                    if( index >= 0 ) { 
                        entry.op1Index = index ; 
                    }
                }
                if( lineTokens[2].startsWith( "&" ) ) {
                    int index = currentPNTAB.indexOf(lineTokens[2]) ; 
                    entry.operand2 = lineTokens[2] ;
                    if( index >= 0 ) { 
                        entry.op2Index = index ; 
                    }
                }
                MDT.add( entry ) ; 
            }
            else if( lineTokens[0].equals( "MEND" ) ) {
                MDTableEntry entry = new MDTableEntry(); 
                entry.mnemonic = "MEND" ;
                MDT.add(entry) ;    
            }
            mdtabPtr++ ; 
        }

        saveTable( MNT , "Assignment_A2/MNT.dat" ) ;
        saveTable( KDPTAB , "Assignment_A2/KPDTAB.dat" ) ;
        saveTable( pnTabHashMap , "Assignment_A2/PNTAB.dat" ) ;
        saveTable( MDT , "Assignment_A2/MDT.dat" ) ;

        printPNTAB();
        printMNTAB();
        printKPDTAB();
        
    }

    private static void saveTable( Object table , String filepath ) {
        try {
            FileOutputStream fos = new FileOutputStream( new File( filepath ) ) ; 
            ObjectOutputStream outputStream = new ObjectOutputStream(fos) ; 
            outputStream.writeObject( table );
            outputStream.flush();
            outputStream.close();
            fos.close();
        }
        catch( FileNotFoundException e ){
            e.printStackTrace();
        }
        catch( IOException e ) {
            e.printStackTrace(); 
        }
    }

    private static ArrayList<String> readLines( String filePath ) {
        File textFile = new File( filePath ) ;
        ArrayList<String> lines = new ArrayList<>();  
        try {
            FileInputStream inputStream = new FileInputStream( textFile ) ; 
            BufferedReader reader = new BufferedReader( new InputStreamReader( inputStream ) ) ; 
            while( reader.ready() ) {
                lines.add( reader.readLine() ) ; 
            }
            inputStream.close();
        }
        catch( FileNotFoundException e ) {
            e.printStackTrace();
        }
        catch( IOException e ) {
            e.printStackTrace();
        }
        return lines ; 
    }

    private void printMNTAB() {
        for( MNTableEntry entry : MNT ) {
            System.out.println( 
                entry.macroName + " " + 
                entry.numKPD + " " + 
                entry.numPP + " " + 
                entry.MDTabPtr + " " + 
                entry.kpdTabPtr );
        }
    }

    private void printKPDTAB() {
        for( String[] entry : KDPTAB ) {
            System.out.println( entry[0] + " " + entry[1] );
        }
    }

    private void printPNTAB() {
        Iterator<String> it = pnTabHashMap.keySet().iterator() ; 
        while( it.hasNext() ) {
            String macroName = it.next() ; 
            System.out.println( "Macro Name: " + macroName ) ; 
            List<String> params = pnTabHashMap.get( macroName ) ; 
            for( String param : params ) {
                System.out.println( param ) ; 
            }
        }
    }
}
