#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int KMPMatcher(char* haystack, char* needle) {
	
	int haystackLen , needleLen;
	
	unsigned int  *next;

	int k;
	int pos;
	if (needle==NULL)
		return 0;
	if (haystack==NULL)
		return -1;

	haystackLen = strlen(haystack);
	needleLen = strlen(needle);

	if (needleLen == 0)
		return 0;
	next = (unsigned int*)malloc(sizeof(unsigned int)*needleLen);
	if (next == NULL)
		return -1;

	//preprocess
	next[0] = 0;
	k = 0;
	for (pos = 1; pos < needleLen; pos++)
	{
		if (k>0 && needle[k] != needle[pos])
			k = next[k - 1];
		if (needle[k] == needle[pos])
			k++;
		next[pos] = k;
	}
	
	//match
	k = 0;
	for (pos = 0; pos < haystackLen; pos++)
	{
		while (k>0 && haystack[pos] != needle[k])
			k = next[k - 1];
		if (haystack[pos] != needle[k])
			k++;
		if (k == needleLen)
			return pos + 1 - k;
	}
	return -1;
}

int RabinKarpMatcher(char *T, char *P, int d, int q)
{
	int TLen, PLen;
	int h;
	int i;
	int p=0, t=0;
	if (!P)
		return 0;
	if (!T)
		return -1;


	TLen = strlen(T);
	PLen = strlen(P);
	if (PLen == 0)
		return 0;

	h = 1;
	for (i = 0; i < PLen - 1; i++)
		h = (h*d) % q;

	//preprocessing
	for (i = 0; i < PLen; i++)
	{
		t = (d*t + T[i]) % q;
		p = (d*p + P[i]) % q;
	}

	for (i = 0; i <= TLen - PLen; i++)
	{
		if (t == p)
			if (!strncmp(T + i, P, PLen))
				return i;
		t = ((t - (h*T[i]) % q + q)*d + T[i + PLen]) % q;
	}
	return -1;
}

int Matcher(char* haystack, char* needle)
{
	return RabinKarpMatcher(haystack, needle, 128, 6999997);
}

int KMPMatcher2(char * T, char *P)
{
	int TLen, PLen,pos;
	int * next;
	int k;

	if (NULL == P)
		return 0;
	if (NULL == T)
		return -1;

	TLen = strlen(T);
	PLen = strlen(P);

	if (0 == PLen)
		return 0;

	//preprocessing
	next = (int*)malloc(PLen*sizeof(int));
	if (NULL == next)
		return -1;

	next[0] = 0;
	k = 0;
	for (pos = 1; pos < PLen; pos++)
	{
		while (k>0 && P[k] != P[pos])
			k = next[k - 1];
		if (P[k] == P[pos])
			k++;
		next[pos] = k;
	}

	//matching
	k = 0;
	for (pos = 0; pos < TLen; pos++)
	{
		while (k>0 && P[k] != T[pos])
			k = next[k - 1];
		if (P[k] == T[pos])
			k++;
		if (k == PLen)
		{
			free(next);
			return pos + 1 - k;
		}
			
	}

	free(next);
	return -1;
}

int moveback(char *P, int len, char target)
{
	int ret = 1;
	while (len > 0)
	{
		if (P[len - 1] != target)
			ret++;
		else 
			return ret;
		len--;
	}
	return ret;
}
int SundayMatcher(char *T, char *P)
{
	int TLen, PLen, pos;
	if (NULL == P)
		return 0;
	if (NULL == T)
		return -1;

	TLen = strlen(T);
	PLen = strlen(P);

	if (0 == PLen)
		return 0;
	
	pos = 0;
	while (pos <=TLen-PLen)
	{
		if (strncmp(T + pos, P, PLen))
		{
			if (pos == TLen - PLen)
				return -1;
			pos += moveback(P, PLen, T[pos + PLen]);
		}
		else
			return pos;
	}
	return -1;
}
int main(void)
{
	int ret = KMPMatcher2("mississippi", "issip");
	printf("ret %x\n", ret);
	return 0;
}