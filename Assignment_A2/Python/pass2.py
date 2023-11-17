class MNTableEntry:
    def __init__(self) -> None:
        self.name = ''
        self.num_kpd = 0
        self.num_pp = 0
        self.mdtab_ptr = 0
        self.kpdtab_ptr = 0


class MDTableEntry:
    def __init__(self) -> None:
        self.mnemonic = ''
        self.operand1 = ''
        self.operand2 = ''
        self.op1_index = -1
        self.op2_index = -1


#Taking MDTAB entries
print( "MDTAB entries........" )
num_entries = int( input( "Enter number of entries in MDTAB: " ) )
mdtab = []
for _ in range( num_entries ):
    entry = MDTableEntry()
    entry.mnemonic = input( "Enter mnemonic: " )
    if entry.mnemonic != 'MEND':
        entry.operand1 = input( "Enter operand 1: " )
        if entry.operand1.isdigit():
            entry.op1_index = int( entry.operand1 )
        entry.operand2 = input( "Enter operand 2: " )
        if entry.operand2.isdigit():
            entry.op2_index = int( entry.operand2 )
    mdtab.append( entry )
    print()
print()
print()

#Taking KPDTAB entries
print( "KPDTAB entries............" )
num_entries = int( input( "Enter number of entries in KPDTAB: " ) )
kpdtab = []
for _ in range( num_entries ):
    kpdtab.append( ( 
        input( "Enter parameter name: " ) , 
        input( "Enter parameter default value: " )
    ) )
    print()
print()
print()

#Taking MNTAB entries
print( "MNTAB entries..........." )
num_entries = int( input( "Enter number of entries in MNTAB: " ) )
mntab = []
for _ in range( num_entries ):
    entry = MNTableEntry()
    entry.name = input( "Enter macro name: " )
    entry.num_kpd = int( input( "Enter number of keyword parameters: " ) )
    entry.num_pp = int( input( "Enter number of positional parameters: " ) )
    entry.mdtab_ptr = int( input( "Enter mdtab ptr: " ) )
    entry.kpdtab_ptr = int( input( "Enter kpdtab ptr: " ) )
    mntab.append( entry )
    print()
print()
print()

#Taking PNTAB entries
print( "PNTAB entries........." )
pntab_map = {}
for macro in mntab:
    print( f"Enter parameter for macro {macro.name}: " )
    pntab = []
    for _ in range( macro.num_kpd + macro.num_pp ):
        pntab.append( input( "Enter parameter name: " ) )
    pntab_map[ macro.name ] = pntab
    print()
print()
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


