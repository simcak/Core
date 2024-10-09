## Cheat scheet
|Group size|Subnet|CIDR|3rd Octet|2nd Octet|1st Octet|
|    -     |   -  |  - |    -    |    -    |    -    |
|   128    |  128 | \25|   \17   |   \9    |   \1    |
|    64    |  192 | \26|   \18   |   \10   |   \2    |
|    32    |  224 | \27|   \19   |   \11   |   \3    |
|    16    |  240 | \28|   \20   |   \12   |   \4    |
|    8     |  248 | \29|   \21   |   \13   |   \5    |
|    4     |  252 | \30|   \22   |   \14   |   \6    |
|    2     |  254 | \31|   \23   |   \15   |   \7    |
|    1     |  255 | \32|   \24   |   \16   |   \8    |











## Reserved IP addresses
| Address block  | Address range              | Number of addresses | Scope           | Description |
|       -        |        -                   |         -           |   -             |      -      |
| 0.0.0.0/8      | 0.0.0.0–0.255.255.255      | 16777216            | Software        | Current (local, "this") network[1]
| 10.0.0.0/8     | 10.0.0.0–10.255.255.255    | 16777216            | Private network | Used for local communications within a private network[3]
| 100.64.0.0/10  | 100.64.0.0–100.127.255.255 | 4194304             | Private network | Shared address space[4] for communications between a service provider and its subscribers when using a carrier-grade NAT
| 127.0.0.0/8    | 127.0.0.0–127.255.255.255  | 16777216            | Host            | Used for loopback addresses to the local host[1]
| 169.254.0.0/16 | 169.254.0.0–169.254.255.255| 65536               | Subnet          | Used for link-local addresses[5] between two hosts on a single link when no IP address is otherwise specified, such as would have normally been retrieved from a DHCP server
| 172.16.0.0/12  | 172.16.0.0–172.31.255.255  | 1048576             | Private network | Used for local communications within a private network[3]
| 192.0.0.0/24   | 192.0.0.0–192.0.0.255      | 256                 | Private network | IETF Protocol Assignments, DS-Lite (/29)[1]
| 192.0.2.0/24   | 192.0.2.0–192.0.2.255      | 256                 | Documentation   | Assigned as TEST-NET-1, documentation and examples[6]
| 192.88.99.0/24 | 192.88.99.0–192.88.99.255  | 256                 | Internet        | Reserved.[7] Formerly used for IPv6 to IPv4 relay[8] (included IPv6 address block 2002::/16).
| 192.168.0.0/16 | 192.168.0.0–192.168.255.255| 65536               | Private network | Used for local communications within a private network[3]
| 198.18.0.0/15  | 198.18.0.0–198.19.255.255  | 131072              | Private network | Used for benchmark testing of inter-network communications between two separate subnets[9]
| 198.51.100.0/24| 198.51.100.0–198.51.100.255| 256                 | Documentation   | Assigned as TEST-NET-2, documentation and examples[6]
| 203.0.113.0/24 | 203.0.113.0–203.0.113.255  | 256                 | Documentation   | Assigned as TEST-NET-3, documentation and examples[6]
| 224.0.0.0/4    | 224.0.0.0–239.255.255.255  | 268435456           | Internet        | In use for multicast[10] (former Class D network)
| 233.252.0.0/24 | 233.252.0.0–233.252.0.255  | 256                 | Documentation   | Assigned as MCAST-TEST-NET, documentation and examples (Note that this is part of the above multicast space.)[10][11]
| 240.0.0.0/4    | 240.0.0.0–255.255.255.254  | 268435455           | Internet        | Reserved for future use[12] (former Class E network)
| 255.255.255.255/32 | 255.255.255.255        | 1                   | Subnet          | Reserved for the "limited broadcast" destination address[1]








## Subnet Mask Chart
|  Subnet Mask  | CIDR | Binary Notation| Network Bits| Host Bits| Available Addresses|
| -             |  -   |                   -                   | -  | -  | -          | 
|255.255.255.255|   /32|  11111111.11111111.11111111.11111111  | 32 | 0  |  1         |
|255.255.255.254|   /31|  11111111.11111111.11111111.11111110  | 31 | 1  |  2         |
|255.255.255.252|   /30|  11111111.11111111.11111111.11111100  | 30 | 2  |  4         |
|255.255.255.248|   /29|  11111111.11111111.11111111.11111000  | 29 | 3  |  8         |
|255.255.255.240|   /28|  11111111.11111111.11111111.11110000  | 28 | 4  |  16        |
|255.255.255.224|   /27|  11111111.11111111.11111111.11100000  | 27 | 5  |  32        |
|255.255.255.192|   /26|  11111111.11111111.11111111.11000000  | 26 | 6  |  64        |
|255.255.255.128|   /25|  11111111.11111111.11111111.10000000  | 25 | 7  |  128       |
|255.255.255.0|     /24|  11111111.11111111.11111111.00000000  | 24 | 8  |  256       |		
|255.255.254.0|     /23|  11111111.11111111.11111110.00000000  | 23 | 9  |  512       |
|255.255.252.0|     /22|  11111111.11111111.11111100.00000000  | 22 | 10 |  1024      |
|255.255.248.0|     /21|  11111111.11111111.11111000.00000000  | 21 | 11 |  2048      |
|255.255.240.0|     /20|  11111111.11111111.11110000.00000000  | 20 | 12 |  4096      |
|255.255.224.0|     /19|  11111111.11111111.11100000.00000000  | 19 | 13 |  8192      |
|255.255.192.0|     /18|  11111111.11111111.11000000.00000000  | 18 | 14 |  16384     |
|255.255.128.0|     /17|  11111111.11111111.10000000.00000000  | 17 | 15 |  32768     |
|255.255.0.0|       /16|  11111111.11111111.00000000.00000000  | 16 | 16 |  65536     |
|255.254.0.0|       /15|  11111111.11111110.00000000.00000000  | 15 | 17 |  131072    |
|255.252.0.0|       /14|  11111111.11111100.00000000.00000000  | 14 | 18 |  262144    |
|255.248.0.0|       /13|  11111111.11111000.00000000.00000000  | 13 | 19 |  524288    |
|255.240.0.0|       /12|  11111111.11110000.00000000.00000000  | 12 | 20 |  1048576   |
|255.224.0.0|       /11|  11111111.11100000.00000000.00000000  | 11 | 21 |  2097152   |
|255.192.0.0|       /10|  11111111.11000000.00000000.00000000  | 10 | 22 |  4194304   |
|255.128.0.0|        /9|  11111111.10000000.00000000.00000000  | 9  | 23 |  8388608   |
|255.0.0.0|          /8|  11111111.00000000.00000000.00000000  | 8  | 24 |  16777216  |










### Example
```
Address:   192.168.0.1           11000000.10101000.00000000 .00000001
Netmask:   255.255.255.0 = /24   11111111.11111111.11111111 .00000000
Wildcard:  0.0.0.255             00000000.00000000.00000000 .11111111
=>
Network:   192.168.0.0/24        11000000.10101000.00000000 .00000000 (Class C)
Broadcast: 192.168.0.255         11000000.10101000.00000000 .11111111
HostMin:   192.168.0.1           11000000.10101000.00000000 .00000001
HostMax:   192.168.0.254         11000000.10101000.00000000 .11111110
Hosts/Net: 254                   (Private Internet)
```



## Resources
- [Subnet training webside](https://subnetipv4.com/)
- [Subnet YT video](https://www.youtube.com/watch?v=s_Ntt6eTn94)