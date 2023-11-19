ic_file_path = input( "Enter IC file path: " )
with open( ic_file_path , "r" ) as file:
    ic_contents = file.read()
    ic_lines: list[str] = ic_contents.split( "\n" ) 
    ic_line_tokens: list[list[str]] = [ line.split() for line in ic_lines ]

sym_tab: list[tuple[str,int]] = []
sym_tab_filepath = input( "Enter symbol table filepath: " )
with open( sym_tab_filepath , "r" ) as file:
    sym_tab_contents = file.read()
    sym_tab_lines: list[str] = sym_tab_contents.split("\n")
    for line in sym_tab_lines:
        name , addr = line.split()
        sym_tab.append( ( name , int(addr) ) )

lit_tab: list[tuple[str,int]] = []
lit_tab_filepath = input( "Enter literal table filepath: " )
if lit_tab_filepath != "":
    with open( lit_tab_filepath , "r" ) as file:
        lit_tab_contents = file.read()
        lit_tab_lines: list[str] = lit_tab_contents.split("\n")
        for line in lit_tab_lines:
            name , addr = line.split()
            lit_tab.append( ( name , int(addr) ) )

for line_tokens in ic_line_tokens:
    if len( line_tokens ) == 4:
        lc = line_tokens[0]
        mnemonic_opcode = line_tokens[1].strip( "(" ).strip( ")" ).split( "," )[1]
        
        operand1_tokens = line_tokens[2].strip( "(" ).strip( ")" ).split( "," )
        operand1 = ""
        if len( operand1_tokens ) == 2:
            if operand1_tokens[0] == "S":
                sym_tab_index = int( operand1_tokens[1] )
                _ , sym_addr = sym_tab[ sym_tab_index ]
                operand1 = str(sym_addr)
        else:
            operand1 = operand1_tokens[0]

        operand2_tokens = line_tokens[3].strip( "(" ).strip( ")" ).split( "," )
        operand2 = ""
        if operand2_tokens[0] == "S":
            sym_tab_index = int( operand2_tokens[1] )
            _ , sym_addr = sym_tab[ sym_tab_index ]
            operand2 = str(sym_addr)
        elif operand2_tokens[0] == "L":
            lit_tab_index = int( operand2_tokens[1] )
            _ , lit_addr = lit_tab[ lit_tab_index ]
            operand2 = str(lit_addr)
        elif operand2_tokens[0] == "C":
            value = operand2_tokens[1]
            if "'" in value:
                value = value.strip( "'" )
            operand2 = value
        
        print( lc , mnemonic_opcode , operand1 , operand2 )

    elif len( line_tokens ) == 2:

        if line_tokens[0].isdigit():
            lc = line_tokens[0]
            mnemonic_opcode = line_tokens[1].strip( "(" ).strip( ")" ).split( "," )[1]
            print( lc , mnemonic_opcode )
        else:
            mnemonic_opcode = line_tokens[0].strip( "(" ).strip( ")" ).split( "," )[1]
            operand1_tokens = line_tokens[1].strip( "(" ).strip( ")" ).split( "," )
            operand1 = ""
            if len( operand1_tokens ) == 2:
                if operand1_tokens[0] == "S":
                    sym_tab_index = int( operand1_tokens[1] )
                    _ , sym_addr = sym_tab[ sym_tab_index ]
                    operand1 = str(sym_addr)
            else:
                operand1 = operand1_tokens[0]
            print( mnemonic_opcode , operand1 )
