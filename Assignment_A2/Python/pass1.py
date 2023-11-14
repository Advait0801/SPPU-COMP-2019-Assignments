class MNTableEntry:
    def __init__(self, name) -> None:
        self.name = name
        self.num_kpd = 0
        self.num_pp = 0
        self.mdtab_ptr = 0
        self.kpdtab_ptr = 0


class MDTableEntry:
    def __init__(self, mnemonic_name) -> None:
        self.mnemonic = mnemonic_name
        self.operand1 = ""
        self.operand2 = ""
        self.op1_index = -1
        self.op2_index = -1


mntab: list[MNTableEntry] = []
mdtab: list[MDTableEntry] = []
kpdtab: list[tuple[str, str]] = []
list_of_pntabs: dict[str, list[str]] = {}

source_path = input("Enter file path: ")
with open(source_path, 'r') as file:
    source_lines = file.read().split('\n')
    source_tokens = [line.split() for line in source_lines]

mdtab_pointer = 0
kpdtab_pointer = 0
name = ""

for i in range(1, len(source_tokens)):
    line_tokens = source_tokens[i]

    if source_tokens[i-1][0] == 'MACRO':
        name = line_tokens[0]
        parameters = line_tokens[1:]
        pntab: list[str] = []
        kpd_counter = 0
        pp_counter = 0
        p_name = ''

        for parameter in parameters:
            if '=' in parameter:
                p_name, val = parameter.split('=')
                kpdtab.append((p_name, val))
                kpd_counter += 1
            else:
                p_name = parameter
                pp_counter += 1
            pntab.append(p_name)

        mntab_entry = MNTableEntry(name=name)
        mntab_entry.num_kpd = kpd_counter
        mntab_entry.num_pp = pp_counter
        mntab_entry.kpdtab_ptr = kpdtab_pointer
        mntab_entry.mdtab_ptr = mdtab_pointer
        mntab.append(mntab_entry)

        list_of_pntabs[name] = pntab
        kpdtab_pointer += kpd_counter

    elif line_tokens[0] != 'MEND' and line_tokens[0] != 'MACRO':
        mdtab_entry = MDTableEntry(mnemonic_name=line_tokens[0])
        pntab: list[str] = list_of_pntabs[name]

        parameter = line_tokens[1]
        if parameter in pntab:
            mdtab_entry.op1_index = pntab.index(parameter)
        mdtab_entry.operand1 = parameter

        parameter = line_tokens[2]
        if parameter in pntab:
            mdtab_entry.op2_index = pntab.index(parameter)
        mdtab_entry.operand2 = parameter

        mdtab.append(mdtab_entry)
        mdtab_pointer += 1

    elif line_tokens[0] == 'MEND':
        mdtab_entry = MDTableEntry('MEND')
        mdtab_pointer += 1
        mdtab.append(mdtab_entry)


print( "------------ MNTAB ----------------")   
print( "Name".ljust( 10 ) , "#PP".ljust( 5 ) , "#KP".ljust( 5 ) , "KPDTAB_PTR".ljust( 10 ) , "MDTAB_PTR".ljust( 10 ) )  
for entry in mntab:
    print( 
        entry.name.ljust( 10 ) , 
        str(entry.num_pp).ljust( 5 ) , 
        str(entry.num_kpd).ljust( 5 ) , 
        str(entry.kpdtab_ptr).ljust( 10 ) , 
        str(entry.mdtab_ptr).ljust( 10 )
    )

print( "------------ MDTAB ----------------")   
for entry in mdtab:
    print( 
        entry.mnemonic.ljust( 10 ) , 
        (entry.operand1 if entry.op1_index == -1 else f"(P,{entry.op1_index})").ljust(10) , 
        (entry.operand2 if entry.op2_index == -1 else f"(P,{entry.op2_index})").ljust(10) ,  
    )
    
print( "------------ KPDTAB ----------------")   
print( "Name".ljust( 10 ) , "Default Value".ljust( 15 ) )
for param in kpdtab:
    print( param[0].ljust( 10 ) , param[1].ljust( 15 ) )

print( "------------- PNTAB -----------------")
for ( name , pntab ) in list_of_pntabs.items():
    print( "PNTAB for macro" , name ) 
    for param in pntab:
        print( param )