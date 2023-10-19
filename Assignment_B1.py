import math

def dec_to_bin(n):
    b = bin(n)[2:]
    output = b.rjust(8 , '0')
    return [int(i) for i in output]

def bin_to_dec(num):
    num = [str(i) for i in num]
    b = ''.join(num)
    return int(b,2)

def boolean_and(num1 , num2):
    ans = []
    for i in range(len(num1)):
        ans.append(int(num1[i] == 1 and num2[i] == 1))
    return ans

def cidr_subnet_generation(cidr_number):
    subnet = '1'*cidr_number
    output = subnet.ljust(32 , '0')
    return [int(i) for i in output]

def ip_decimal_generation(ip_address):
    ans = ""
    for i in range(0,len(ip_address),8):
        ans += str(bin_to_dec(ip_address[i : i+8])) + '.'
    return ans

def ip_octet_generation(ip_address):
    ans = []
    for i in range(0,len(ip_address),8):
        ans.append(bin_to_dec(ip_address[i : i+8]))
    return ans

def ip_address_generation(starting_ip_octets , n):
    c0 = starting_ip_octets[3]
    c1 = starting_ip_octets[2]
    c2 = starting_ip_octets[1]
    c3 = starting_ip_octets[0]
    i = 0
    addresses = []

    for c3 in range(starting_ip_octets[0] , 256):
        for c2 in range(starting_ip_octets[1] , 256):
            for c1 in range(starting_ip_octets[2] , 256):
                for c0 in range(starting_ip_octets[3] , 256):
                    if i>=n:
                        break
                    addresses.append((c3 , c2 , c1 , c0))
                    i += 1

    return addresses

input_ip_str = input( "Enter an IPv4 address: " ) 
octets = list(map( int , input_ip_str.split( "." )))
ip_bin = []
ip_class = ""
for octet in octets:
    ip_bin += dec_to_bin( octet ) 
if octets[0] >= 0 and octets[0] <= 126:
    ip_class = "A"
    print( "Class of given IP: Class A" )
    print( "Default subnet mask: 255.0.0.0" )
elif octets[0] >= 128 and octets[0] <= 191:
    ip_class = "B"
    print( "Class of given IP: Class B" )
    print( "Default subnet mask: 255.255.0.0" )
elif octets[0] >= 192 and octets[0] <= 223:
    ip_class = "C"
    print( "Class of given IP: Class C" )
    print( "Default subnet mask: 255.255.255.0" )
elif octets[0] >= 224 and octets[0] <= 239:
    print( "Class of given IP: Class D" )
elif octets[0] >= 240 and octets[0] <= 254:
    print( "Class of given IP: Class E" )


print("""
    Options: 
    1. CIDR Number (ex. 27)
    2. Number of subnets (ex. 8)
    """)
option = int( input( "Enter option: " ) )
if option == 1:
    cidr_num = int( input( "Enter CIDR Number: ") )
    subnet_mask = cidr_subnet_generation( cidr_num ) 
    result = boolean_and( ip_bin , subnet_mask )
    num_hosts = 2**(32-cidr_num)
    print( "Number of hosts available: " , num_hosts )
    print( "Subnet mask: " , ip_decimal_generation( subnet_mask ) , "/" , cidr_num )
    print( "Starting address of subnet: " , ip_decimal_generation( result ) )
    result_octets = ip_octet_generation( result )
    ip_addresses = ip_address_generation( result_octets , num_hosts )
    print( "Network address: " , ip_addresses[0] )
    print( "Broadcast address: " , ip_addresses[-1] ) 
elif option == 2:
    num_subnets = int( input( "Enter number of subnets: " ) )
    num_hosts_per_class = {
        "A": 256 * 256 * 256 , 
        "B": 256 * 256 , 
        "C": 256
    }
    num_hosts_per_subnet = num_hosts_per_class[ ip_class ] // num_subnets
    num_host_bits = int( math.log2( num_hosts_per_subnet ) )
    num_network_bits = 32 - num_host_bits
    subnet_mask = cidr_subnet_generation( num_network_bits )
    print( "Maximum hosts possible in this IP class: " , num_hosts_per_class[ ip_class ] )
    print( "Number of hosts per subnet (all): " , num_hosts_per_subnet ) 
    print( "Number of hosts per subnet (usable): " , num_hosts_per_subnet - 2 ) 
    print( "Subnet mask required: " , ip_decimal_generation( subnet_mask ) , "/" , num_network_bits )

    result = boolean_and( ip_bin , subnet_mask )
    result_octets = ip_octet_generation( result )
    ip_addresses = ip_address_generation( result_octets , num_hosts_per_subnet * num_subnets )
    print( "Subnet ranges are: " )
    subnets = []
    for i in range( 0 , len(ip_addresses) , num_hosts_per_subnet ):
        print( ip_addresses[i] , " - " , ip_addresses[i+num_hosts_per_subnet-1] ) 
        subnets.append( ip_addresses[ i : i+num_hosts_per_subnet ] )
    self_ip = tuple( octets )
    
    while True:
        input_dst_ip_str = input( "Command: " ) 
        dst_ip = tuple(map( int , input_dst_ip_str.split()[1].split( "." )))
        
        if self_ip == dst_ip:
            print( "PING SUCCESS (Both IPs are same)" )
            continue
        for subnet in subnets:
            is_found_1 = self_ip in subnet
            is_found_2 = dst_ip in subnet
            if is_found_1 and is_found_2:
                print( "PING SUCCESS (Both IPs are in same subnet)" )
                break
        else:
            print( "PING FAILED (Network is unreachable)" )
