import random

def dec_to_bin(n):
    b = bin(n)[2:]
    return [int(i) for i in b]

def bin_to_dec(num):
    num = [str(i) for i in num]
    b = ''.join(num)
    return int(b,2)

def calculate_redundant_bits(message):
    m = len(message)
    for i in range(1,m):
        if 2**i >= m + i + 1:
            return i

def even_parity(sequence):
    total = sum(sequence)
    if total % 2 != 0:
        return int(True)
    return int(False)

def odd_parity(sequence):
    total = sum(sequence)
    if total % 2 == 0:
        return int(True)
    return int(False)

def sender(message,p):
    redundant_bits = calculate_redundant_bits(message)
    parity = even_parity if p == 'even' else odd_parity
    code_word = [0 for i in range(len(message) + redundant_bits)]
    parity_positions = [2**i - 1 for i in range(redundant_bits)]
    data_positions = [i for i in range(len(message) + redundant_bits) if i not in parity_positions]

    for i,j in enumerate(data_positions):
        code_word[j] = int(message[i])

    for i,j in enumerate(parity_positions):
        parity_sequence = []
        take = True
        take_count = 2**i
        for k in range(j,len(code_word)):
            if take:
                parity_sequence.append(code_word[k])
                take_count -= 1
            else:
                take_count += 1
            
            if take_count == 0:
                take = False
            elif take_count == 2**i:
                take = True

        code_word[j] = parity(parity_sequence)

    return code_word,redundant_bits

def reciever(code_word,p,r):
    parity = even_parity if p == 'even' else odd_parity
    parity_positions = [2**i - 1 for i in range(r)]
    parity_bits = []

    for i,j in enumerate(parity_positions):
        parity_sequence = []
        take = True
        take_count = 2**i
        for k in range(j,len(code_word)):
            if take:
                parity_sequence.append(code_word[k])
                take_count -= 1
            else:
                take_count += 1
            
            if take_count == 0:
                take = False
            elif take_count == 2**i:
                take = True

        parity_bits.append(parity(parity_sequence))

    return parity_bits

p = input("Press e for even parity and o for odd parity: ")
p = 'even' if p == 'e' else 'odd'
print( "---------- Transmitter -----------" )
input_message_str = input( "Enter message: " )
input_chars = list( input_message_str )
input_chars_ascii = [ ord( c ) for c in input_chars ]
bin_repr_lists = []
print( "Data on transmitter side is -> " )
for ( char , ascii ) in zip( input_chars , input_chars_ascii ):
    bin_repr = dec_to_bin( ascii )
    bin_repr_lists.append( bin_repr )
    print( f"{char} -> {ascii} -> { ''.join([str(i) for i in bin_repr]) }" )
code_word_lists = []
num_r_bits = None
print( "Code words on transmitter side ->" ) 
for ( char , bin_repr ) in zip( input_chars , bin_repr_lists ):
    code_word , num_r_bits = sender( bin_repr , p )
    code_word_lists.append( code_word )
    print( f"{char} -> { ''.join([str(i) for i in code_word]) }" )
print( "Number of redundant bits => r = " , num_r_bits )
print( "Number of bits in message => m = " , len( code_word_lists[0] ) - num_r_bits )

print( "---------- Channel / Transmission Medium -----------" )
error = input( "Press y to enduce error else press n: " ) 
if error == "yes":
    for code_word in code_word_lists:
        random_position = random.randint( 0 , len( code_word ) - 1 ) 
        code_word[ random_position ] = 0 if code_word[random_position] == 1 else 1
        print( "For code word {}, error induced at position={}".format( ''.join([str(i) for i in code_word]) , random_position ) )

print( "---------- Receiver -----------" )
decoded_message: str = ""
for code_word in code_word_lists:
    code_word_str = ''.join([str(i) for i in code_word])
    parity_bits = reciever( code_word , 'even', num_r_bits )
    if sum( parity_bits ) == 0:
        parity_positions = [ 2**i - 1 for i in range(num_r_bits) ]
        char_bin_repr = [ c for (pos , c) in enumerate(code_word) if pos not in parity_positions ]
        char = chr(bin_to_dec( char_bin_repr )) 
        print( f"Code {code_word_str} received without any error." , 
              f"Decoded character => { char }" )
    else:
        error_position = bin_to_dec( parity_bits[::-1] ) - 1
        print( f"Code {code_word_str} received with any error." , 
              f"Error is at index={ error_position }"
               )
        code_word[error_position] = 0 if code_word[error_position] == 1 else 1
        parity_positions = [ 2**i - 1 for i in range(num_r_bits) ]
        char_bin_repr = [ c for (pos , c) in enumerate(code_word) if pos not in parity_positions ]
        char = chr(bin_to_dec( char_bin_repr )) 
        print( f"Decoded character after correcting error => {char}" )
    decoded_message += char

print( "Message on receiver side =>" , decoded_message )

    
    








