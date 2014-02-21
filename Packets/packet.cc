/*Name: Nick McIntyre-Wyma
Program: This program simulates grabbing packets from a device and decoding their contents. Grabs from a file instead of a device, however. */
#include <pcap.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>  	// needed for exit
#include <arpa/inet.h>	// needed for socket address struct

using namespace std;

const char *FILENAME = "/home/rappleto/pub/Classes/CS442/Assignments/PacketSniffer/packets.db";

/* ethernet headers are always exactly 14 bytes [1] */
#define SIZE_ETHERNET 14

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct sniff_ethernet {
        u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
        u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
        u_short ether_type;                     /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        #define IP_RF 0x8000            /* reserved fragment flag */
        #define IP_DF 0x4000            /* dont fragment flag */
        #define IP_MF 0x2000            /* more fragments flag */
        #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};
#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
        u_short th_sport;               /* source port */
        u_short th_dport;               /* destination port */
        tcp_seq th_seq;                 /* sequence number */
        tcp_seq th_ack;                 /* acknowledgement number */
        u_char  th_offx2;               /* data offset, rsvd */
#define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
        u_char  th_flags;
        #define TH_FIN  0x01
        #define TH_SYN  0x02
        #define TH_RST  0x04
        #define TH_PUSH 0x08
        #define TH_ACK  0x10
        #define TH_URG  0x20
        #define TH_ECE  0x40
        #define TH_CWR  0x80
        #define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
        u_short th_win;                 /* window */
        u_short th_sum;                 /* checksum */
        u_short th_urp;                 /* urgent pointer */
};


int checkEthernet (const unsigned char *packet)
{
	struct sniff_ethernet *eth = (struct sniff_ethernet *)packet;		//Ethernet packet structure
	cout << endl << "Ethernet Info------" << endl;
	cout << "Destination Address: ";
	for (int i=0; i < 6; i++)	//Prints the MAC address
	{
		if ((int)*(packet+i) < 15)	//Filling in zeros if need be
			cout << "0";
		cout << std::hex <<(int)*(packet+i);
		if (i != 5)
			cout <<":";
	}
	cout<< endl <<"Source Address: ";
	for (int i=6; i < 12; i++)
	{
		if ((int)*(packet+i) < 15)
			cout << "0";
		cout << std::hex <<(int)*(packet+i);
		if (i != 11)
			cout <<":";
	}
	cout << endl << "Ethernet Type: ";
	if  (*(packet + 12) == 8 && *(packet + 13) == 0)
		cout << "IPv4"<<endl;
	else if  (*(packet + 12) == 8 && *(packet + 13) == 6)
		cout << "ARP"<<endl; 
	else
		cout << "Other (" << ntohs(eth->ether_type) <<") " <<endl;
	return sizeof(eth);
}

void checkTCP (const unsigned char *packet, int length, int totallength)
{
	const struct sniff_tcp *tcp = (struct sniff_tcp *)(packet+length) ; //TCP header structure
	cout << endl << "TCP Info------" << endl;
	cout << "Length: " << TH_OFF(tcp)*4 << endl;
	cout << std::dec << "Source Port: " << ntohs(tcp->th_sport) <<  endl;	//th_sport and th_dport are source port and destination port. Refer to the structure above to confirm.
	cout << std::dec << "Dest Port: " << ntohs(tcp->th_dport) <<  endl;
	cout << std::dec << "Sequence #: " << ((int)*(packet+length+4)*4294967296) + ((int)*(packet+length+5)*65536) + (256*(int)*(packet+length+6)) + (int)*(packet+length+7) << endl;
	cout << std::dec << "Ack #: " << ((int)*(packet+length+8)*4294967296) + ((int)*(packet+length+9)*65536) + (256*(int)*(packet+length+10)) + (int)*(packet+length+11) << endl;
	cout << std::dec << "Window Size: " << ((int)*(packet+length+18))*256 + (int)*(packet+length+19) << endl;
	cout << std::dec << "Checksum: " << ((int)*(packet+length+20))*256 + (int)*(packet+length+21) << endl;
	cout << std::dec << "Urgent Pointer: " << ntohs(tcp->th_urp) << endl;
	cout << "SYN Flag: " << (((int)*(packet+length+13) & 0x2) >> 1) << endl;	// &'ing with binary 0000 0010(hex is just 2) since the second bit is the SYN flag.
	cout << "ACK Flag: " << (((int)*(packet+length+13) & 0x10) >> 4) << endl;	// &'ing with binary 0001 0000(hex is 10) since the fifth bit is the ACK flag.
	cout << "FIN Flag: " << (((int)*(packet+length+13) & 0x1)) << endl << endl;	// &'ing with binary 0000 0001(hex is just 1) since the first bit is the FIN flag.
	cout << endl;
	return;
}

void checkUDP (const unsigned char *packet, int length, int totallength)	//If it is UDP, spits out the Source and Destination Port #s
{
	cout << endl << "UDP Info------" << endl;
	cout << std::dec << "Source Port: " << ((int)*(packet+length)*256) + ((int)*(packet+length+1)) << endl;
	cout << std::dec << "Destination Port: " << ((int)*(packet+length+2)*256) + ((int)*(packet+length+3)) << endl;

}

void checkIP (const unsigned char *packet)
{
	struct sniff_ip *ip = (struct sniff_ip *)(packet+14);	//IP starts after the ethernet stuff, which is always 14 bytes.
	int length = ntohs(ip->ip_len);
	cout << endl;
	cout << "IP Info------" << endl;
	cout << "Destination Address: " << inet_ntoa(ip->ip_dst) << endl;
	cout << "Source Address: " << inet_ntoa(ip->ip_src) << endl;
	cout << "Header Length: " << IP_HL(ip) << endl;
	cout << "Version: " << IP_V(ip)  << endl;
	cout << std::dec << "Length: "<< length << endl;
	cout << std::dec << "Time To Live: " <<(int)*(packet+22)<<endl;
	cout << std::dec << "Protocol: " << (int)*(packet+23) << endl;
	cout << std::dec << "CRC: " << ((int)*(packet+24))*256 + (int)*(packet+25) << endl;
	cout << std::dec << "ID: " << ((int)*(packet+19))*256 + (int)*(packet+20) << "("<<((int)*(packet+19)) <<"."<< (int)*(packet+20) <<")"<< endl;
	cout << "Fragment Offset: " << ntohs(ip->ip_off) << endl;
	if ((int)*(packet+23) == 6)	//This is checking the Protocol section, if it equals 6 then the protocol is TCP and 17 is UDP.
		checkTCP(packet, 14+(IP_HL(ip)*4), length);
	else if ((int)*(packet+23) == 17)
		checkUDP(packet, 13+(IP_HL(ip)*4), ntohs(ip->ip_len )+14);
}

int main()
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct pcap_pkthdr pheader;
	const unsigned char *packet;

	handle = pcap_open_offline(FILENAME, errbuf);	//Set to offline so we grab from a file "FILENAME", instead of a device.
	if (handle == NULL)								//If it comes back NULL, something went wrong. 
	{	
		cout << errbuf << endl;
		exit(1);
	}
	int count = 0;
	while ((packet = pcap_next(handle, &pheader)) != NULL)	//if pcap_next returns NULL, then there are no more packets to read.
	{	
		count++;
		cout <<endl<< std::dec <<"Packet Number " << count << ":"<<endl;
		checkEthernet(packet);
		if  (*(packet + 12) == 8 && *(packet + 13) == 0)
				checkIP(packet);
		if  (*(packet + 12) == 8 && *(packet + 13) == 6)
		cout << endl;
	}
}