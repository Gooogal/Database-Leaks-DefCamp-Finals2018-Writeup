#include <stdio.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char CNP[15];
char CON[] = "279146358279";
char RES[32];

unsigned char *getMd5Hash(unsigned char *data, size_t dataLen, int *mdLen) {
    unsigned char *md = NULL;
    EVP_MD_CTX *ctx = NULL;
    const EVP_MD *mdType = EVP_md5();
    
    *mdLen = EVP_MD_size(mdType);
    
    md = (unsigned char *) malloc(*mdLen);
    ctx = EVP_MD_CTX_create();
    
    EVP_MD_CTX_init(ctx);
    EVP_DigestInit_ex(ctx, mdType, NULL);
    EVP_DigestUpdate(ctx, data, dataLen);
    EVP_DigestFinal_ex(ctx, md, NULL);
    //EVP_MD_CTX_cleanup(ctx);
    //EVP_MD_CTX_destroy(ctx);
    return md;
}

int main (int argc, char* argv[]) {
	char* ZZ = argv[1];
	char* LL = argv[2];
	char* sex = argv[3];
	char* hash = argv[4];
	char* salt = argv[5];
	CNP[0] = salt[0];
	CNP[1] = salt[1];

	for (int AA = 99; AA >= 30; AA--) {
		char S = '2';
		
		if (sex[0] == '0')
			S = '1';
		
		for(int JJ = 1; JJ < 53; JJ++){
			for(int NNN = 0; NNN < 1000; NNN++){
				CNP[2] = S;
				CNP[3] = '0' + (AA / 10);
				CNP[4] = '0' + (AA % 10);
				CNP[5] = LL[0];
				CNP[6] = LL[1];
				CNP[7] = ZZ[0];
				CNP[8] = ZZ[1];
				CNP[9] = '0' + (JJ / 10);
				CNP[10] = '0' + (JJ % 10);
				CNP[11] = '0' + (NNN / 100);
				CNP[12] = '0' + ((NNN / 10) % 10);
				CNP[13] = '0' + (NNN % 10);
				
				int res = 0;
				for(int i = 0; i < 12; i++){
					res += (CNP[i+2] - '0') * (CON[i] - '0');
				}
				res %= 11;
				if (res == 10)
					res = 1;
				
				CNP[14] = '0' + res;
				
				int mdLen = 0;
				unsigned char *md = getMd5Hash((unsigned char *)CNP, 15, &mdLen);
    				
    				for(int i = 0; i < mdLen; i++) {
        				sprintf(RES + 2 * i, "%02x", md[i]);
    				}
				
				if (!strcmp(RES, hash)) {
					printf ("%s\n", CNP);
					return 0;
				}
			}
		}
	}

	fflush(stdout);
	return 0;
}