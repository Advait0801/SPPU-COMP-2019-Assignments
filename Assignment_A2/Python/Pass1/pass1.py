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

mntab: list[MNTableEntry] = []
mdtab: list[MDTableEntry] = []
kpdtab: list[tuple[str,str]] = []
pntab_map: dict[ str , list[str] ] = {}

source_path = input( "Enter source path: " )
with open( source_path , "r" ) as file:
    source_contents = file.read()
    source_lines: list[str] = source_contents.split( "\n" )
    source_tokens: list[list[str]] = [ line.split() for line in source_lines ]

mdtab_pointer = 0
kpdtab_pointer = 0
curr_macro_name = ""
is_macro_reading = False

for i in range( 1 , len( source_tokens ) ):
    line_tokens = source_tokens[i]

    if source_tokens[i-1][0] == "MACRO":
        curr_macro_name = line_tokens[0]
        parameters = line_tokens[1:]
        pntab: list[str] = []
        kpd_count = 0 
        pp_count = 0
        for parameter in parameters:
            if "=" in parameter:
                parameter_name , def_val = parameter.split( "=" )
                kpdtab.append( ( parameter_name , def_val ) )
                kpd_count += 1
            else:
                parameter_name = parameter
                pp_count += 1
            pntab.append( parameter_name )
   
        mntab_entry = MNTableEntry()
        mntab_entry.macro_name = curr_macro_name
        mntab_entry.num_kpd = kpd_count
        mntab_entry.num_pp = pp_count
        mntab_entry.kpdtab_ptr = kpdtab_pointer
        mntab_entry.mdtab_ptr = mdtab_pointer

        pntab_map[ curr_macro_name ] = pntab
        kpdtab_pointer += kpd_count

        mntab.append( mntab_entry )

        is_macro_reading = True
        
    elif is_macro_reading and line_tokens[0] != "MEND" and line_tokens[0] != "MACRO":
        mdtab_entry = MDTableEntry()
        mnemonic = line_tokens[0]
        mdtab_entry.mnemonic = mnemonic
        pntab = pntab_map[ curr_macro_name ]

        param = line_tokens[1]
        if param in pntab:
            mdtab_entry.op1_index = pntab.index( param )
        mdtab_entry.operand1 = param

        param = line_tokens[2]
        if param in pntab:
            mdtab_entry.op2_index = pntab.index( param )
        mdtab_entry.operand2 = param

        mdtab.append( mdtab_entry )
        mdtab_pointer += 1

    elif line_tokens[0] == "MEND":
        mdtab_entry = MDTableEntry()
        mdtab_entry.mnemonic = "MEND"
        mdtab.append( mdtab_entry )
        mdtab_pointer += 1
        is_macro_reading = False

print( "------------ MNTAB ----------------")   
print( "Name".ljust( 10 ) , "#PP".ljust( 5 ) , "#KP".ljust( 5 ) , "KPDTAB_PTR".ljust( 10 ) , "MDTAB_PTR".ljust( 10 ) )  
for entry in mntab:
    print( 
        entry.macro_name.ljust( 10 ) , 
        str(entry.num_pp).ljust( 5 ) , 
        str(entry.num_kpd).ljust( 5 ) , 
        str(entry.kpdtab_ptr).ljust( 10 ) , 
        str(entry.mdtab_ptr).ljust( 10 )
    )
print()

print( "------------ MDTAB ----------------")   
for entry in mdtab:
    print( 
        entry.mnemonic.ljust( 10 ) , 
        (entry.operand1 if entry.op1_index == -1 else f"(P,{entry.op1_index})").ljust(10) , 
        (entry.operand2 if entry.op2_index == -1 else f"(P,{entry.op2_index})").ljust(10) ,  
    )
print()
    
print( "------------ KPDTAB ----------------")   
print( "Name".ljust( 10 ) , "Default Value".ljust( 15 ) )
for param in kpdtab:
    print( param[0].ljust( 10 ) , param[1].ljust( 15 ) )
print()

print( "------------- PNTAB -----------------")
for ( macro_name , pntab ) in pntab_map.items():
    print( "PNTAB for macro" , macro_name ) 
    for param in pntab:
        print( param[1:] )