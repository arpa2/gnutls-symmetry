/*
 *      Copyright (C) 2000 Nikos Mavroyanopoulos
 *
 * This file is part of GNUTLS.
 *
 * GNUTLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GNUTLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <stdio.h>
#include <stdlib.h>
#include "gnutls_int.h"
#include "gnutls_errors.h"

#ifdef DEBUG

void _gnutls_dump_mpi(char* prefix, MPI a)
{
	char buf[400];
	size_t n = sizeof buf;
	
	if (gcry_mpi_print(GCRYMPI_FMT_HEX, buf, &n, a))
		strcpy(buf, "[can't print value]"); /* Flawfinder: ignore */
	_gnutls_log( "MPI: length: %d\n\t%s%s\n", (n-1)/2, prefix, buf);
}


char *_gnutls_bin2hex(const unsigned char *old, const size_t oldlen)
{
	unsigned char *new = NULL;
	int i, j;

	new = calloc(1, oldlen * 2 * sizeof(char) + 1);
	if (!new)
		return (new);

	for (i = j = 0; i < oldlen; j+=2) {
		sprintf(&new[j], "%.2x", old[i]); /* Flawfinder: ignore */
		i++;
	}
	new[j] = '\0';

	return (new);
}

void _gnutls_print_state(GNUTLS_STATE state)
{

	_gnutls_log( "GNUTLS State:\n");
	_gnutls_log( "Connection End: %d\n",
		state->security_parameters.entity);
	_gnutls_log( "Cipher Algorithm: %d\n",
		state->security_parameters.read_bulk_cipher_algorithm);
	_gnutls_log( "MAC algorithm: %d\n",
		state->security_parameters.read_mac_algorithm);
	_gnutls_log( "Compression Algorithm: %d\n",
		state->security_parameters.read_compression_algorithm);
	_gnutls_log( "\n");

}

const char* _gnutls_alert2str( int alert) {
static char str[512];

	switch(alert) {
		case GNUTLS_A_CLOSE_NOTIFY:
			strcpy(str, "Close Notify");
			break;
		case GNUTLS_A_UNEXPECTED_MESSAGE:
			strcpy(str, "Unexpected message");
			break;
		case GNUTLS_A_BAD_RECORD_MAC:
			strcpy(str, "Bad record MAC");
			break;

		case GNUTLS_A_DECRYPTION_FAILED:
			strcpy(str, "Decryption Failed");
			break;
		case GNUTLS_A_RECORD_OVERFLOW:
			strcpy(str, "Record Overflow"); 
			break;

		case GNUTLS_A_DECOMPRESSION_FAILURE:
			strcpy(str, "Decompression Failed");
			break;

		case GNUTLS_A_HANDSHAKE_FAILURE:
			strcpy(str, "Handshake failed");
			break;
		case GNUTLS_A_BAD_CERTIFICATE:
			strcpy(str, "Certificate is bad");
			break;
		case GNUTLS_A_UNSUPPORTED_CERTIFICATE:
			strcpy(str, "Certificate is not supported");
			break;
		case GNUTLS_A_CERTIFICATE_REVOKED:
			strcpy(str, "Certificate was revoked");
			break;
		case GNUTLS_A_CERTIFICATE_EXPIRED:
			strcpy(str, "Certificate is expired");
			break;
		case GNUTLS_A_CERTIFICATE_UNKNOWN:
			strcpy(str, "Unknown Certificate");
			break;
		case GNUTLS_A_ILLEGAL_PARAMETER:
			strcpy(str, "Illegal Parameter");
			break;
		case GNUTLS_A_UNKNOWN_CA:
			strcpy(str, "CA is not known");
			break;
		case GNUTLS_A_ACCESS_DENIED:
			strcpy(str, "Access was denied");
			break;
		case GNUTLS_A_DECODE_ERROR:
			strcpy(str, "Decode error");
			break;
		case GNUTLS_A_DECRYPT_ERROR:
			strcpy(str, "Decrypt error");
			break;
		case GNUTLS_A_EXPORT_RESTRICTION:
			strcpy(str, "Export Restriction");
			break;
		case GNUTLS_A_PROTOCOL_VERSION:
			strcpy(str, "Error in protocol version");
			break;
		case GNUTLS_A_INSUFFICIENT_SECURITY:
			strcpy(str, "Insufficient Security");
			break;
		case GNUTLS_A_USER_CANCELED:
			strcpy(str, "User Canceled");
			break;
		case GNUTLS_A_NO_RENEGOTIATION:
			strcpy(str, "No renegotiation is allowed");
			break;
		default:
			strcpy(str, "Unknown Alert");
			
	}	
	return str;	
	
}


char* _gnutls_packet2str( int packet) {
static char str[512];

	switch(packet) {
		case GNUTLS_CHANGE_CIPHER_SPEC:
			strcpy(str, "Change Cipher Spec");
			break;		
		case GNUTLS_ALERT:
			strcpy(str, "Alert");
			break;		
		case GNUTLS_HANDSHAKE:
			strcpy(str, "Handshake");
			break;
		case GNUTLS_APPLICATION_DATA:
			strcpy(str, "Application Data");
			break;

		default:
			strcpy(str, "Unknown Packet");
			
	}	
	return str;	
	
}

char* _gnutls_handshake2str( int handshake) {
static char str[512];

	switch(handshake) {
		case GNUTLS_HELLO_REQUEST:
			strcpy(str, "HELLO REQUEST");
			break;		
		case GNUTLS_CLIENT_HELLO:
			strcpy(str, "CLIENT HELLO");
			break;		
		case GNUTLS_SERVER_HELLO:
			strcpy(str, "SERVER HELLO");
			break;
		case GNUTLS_CERTIFICATE:
			strcpy(str, "CERTIFICATE");
			break;
		case GNUTLS_SERVER_KEY_EXCHANGE:
			strcpy(str, "SERVER KEY EXCHANGE");
			break;
		case GNUTLS_CERTIFICATE_REQUEST:
			strcpy(str, "CERTIFICATE REQUEST");
			break;
		case GNUTLS_SERVER_HELLO_DONE:
			strcpy(str, "SERVER HELLO DONE");
			break;
		case GNUTLS_CERTIFICATE_VERIFY:
			strcpy(str, "CERTIFICATE VERIFY");
			break;
		case GNUTLS_CLIENT_KEY_EXCHANGE:
			strcpy(str, "CLIENT KEY EXCHANGE");
			break;
		case GNUTLS_FINISHED:
			strcpy(str, "FINISHED");
			break;
		default:
			strcpy(str, "Unknown Handshake");
			
	}	
	return str;	
	
}

int gnutls_x509pki_extract_certificate_dn( const gnutls_datum*, gnutls_dn*);

const char* GET_CN( gnutls_datum cert) {
static gnutls_dn dn;

	if (gnutls_x509pki_extract_certificate_dn( &cert, &dn) >= 0)
		return &dn.common_name[0]; /* FIXME */
	else 
		return NULL;

}

#endif
