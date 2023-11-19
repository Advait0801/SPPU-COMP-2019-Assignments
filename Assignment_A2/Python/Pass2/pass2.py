class MNTableEntry:
    def __init__( self ):
        self.macro_name = ""
        self.num_kpd = 0
        self.num_pp = 0
        self.mdtab_ptr = 0 
        self.kpdtab_ptr = 0 

class MDTableEntry:
    def __init__( self ):
        self.mnemonic = ""
        self.operand1 = ""
        self.operand2 = ""
        self.op1_index = -1
        self.op2_index = -1


#Taking MDTAB entries through a text file
mdtab = []
mdt_filepath = input( "Enter MDT filepath: " )
with open( mdt_filepath , "r" ) as file:
    mdt_contents = file.read()
    mdt_lines: list[str] = mdt_contents.split( "\n" ) 
    mdt_line_tokens: list[list[str]] = [ line.split() for line in mdt_lines ]

for line_tokens in mdt_line_tokens:
    entry = MDTableEntry()
    entry.mnemonic = line_tokens[0]
    if len( line_tokens ) == 3:
        entry.operand1 = line_tokens[1]
        if entry.operand1[3].isdigit():
            entry.op1_index = int( entry.operand1[3] )
        entry.operand2 = line_tokens[2]
        if entry.operand2[3].isdigit():
            entry.op2_index = int( entry.operand2[3] )
    mdtab.append( entry )

#Taking KPDTAB entries
print( "KPDTAB entries........." )
num_entries = int( input( "Enter number of entries in KPDTAB: " ) )
kpdtab = []
for _ in range( num_entries ):
    kpdtab.append( ( 
        input( "Enter parameter name: " ) , 
        input( "Enter parameter default value: " )
    ) )
    print()
print()

#Taking MNTAB entries
print( "MNTAB entries.........." )
num_entries = int( input( "Enter number of entries in MNTAB: " ) )
mntab = []
for _ in range( num_entries ):
    entry = MNTableEntry()
    entry.macro_name = input( "Enter macro name: " )
    entry.num_kpd = int( input( "Enter num. of keyword parameters: " ) )
    entry.num_pp = int( input( "Enter num. of positional parameters: " ) )
    entry.mdtab_ptr = int( input( "Enter mdtab ptr: " ) )
    entry.kpdtab_ptr = int( input( "Enter kpdtab ptr: " ) )
    mntab.append( entry )
    print()
print()

print( "Enter PNTAB entries:" )
pntab_map = {}
for macro in mntab:
    print( f"Enter parameters for macro {macro.macro_name}: " )
    pntab = []
    for _ in range( macro.num_kpd + macro.num_pp ):
        pntab.append( input( "Enter parameter name: " ) )
    pntab_map[ macro.macro_name ] = pntab
print()

#Macro Call
call_statement = input( "Enter call statement: " )
call_tokens: list[str] = call_statement.split()

name = call_tokens[0]
pntab: list[str] = pntab_map[ name ]
actual_parameters: list[str] = call_tokens[ 1: ] 

mdtab_pointer = 0
kpdtab_pointer = 0
kpd_counter = 0
for entry in mntab:
    if entry.name == name:
        mdtab_pointer = entry.mdtab_ptr
        kpdtab_pointer = entry.kpdtab_ptr
        kpd_counter = entry.num_kpd
        break

aptab: dict[ str , str ] = {}
for name , val in kpdtab[ kpdtab_pointer: kpdtab_pointer + kpd_counter ]:
    aptab[ name ] = val
for i , parameter in enumerate(actual_parameters):
    if "=" in parameter:
        def_parameter , val = parameter.split( "=" )
        aptab[ def_parameter ] = val
    else:
        aptab[ pntab[i] ] = parameter

print()
print( "--------------- EXPANDED CODE -------------------" )
curr_entry = mdtab[ mdtab_pointer ]
while curr_entry.mnemonic != "MEND":
    op1: str = ""
    if curr_entry.op1_index != -1:
        op1 = aptab[ pntab[ curr_entry.op1_index] ]
    else:
        op1 = curr_entry.operand1
    
    op2: str = ""
    if curr_entry.op2_index != -1:
        op2 = aptab[ pntab[ curr_entry.op2_index] ]
    else:
        op2 = curr_entry.operand2

    print( 
        " + " , 
        curr_entry.mnemonic.ljust( 10 ) , 
        op1.ljust(10) , 
        op2.ljust(10) ,  
    )

    mdtab_pointer += 1
    curr_entry = mdtab[ mdtab_pointer ]

print()
print()
print( "---------- APTAB --------------" )
for ( name , val ) in aptab.items():
    print( name , val )
print()