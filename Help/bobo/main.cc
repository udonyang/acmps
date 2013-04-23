//refer to the paper <<Suffix Array--a powerful tool for manipulating strings>>---Suiqian.Luo
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<map>
#include<fstream>
using namespace std;
const char readme[] = "\n\
kpattern ver 0.25\n\n\
usage:\n\
    kpattern -L=minimum number of occurences\
 -K=minimum pattern\
 length FILE\n\n\
Function:\n\
    finds all exact patterns that have at least k\
occurrences in a given sequence, S.\
We are interested in patterns that occur at least k times in S.\n\n\
OUTPUT:\n\
    Four columns.\n\
    pattern length, number of unique patterns, average occurrence\
frequency, and percent coverage of the input sequence by this pattern length.\
\n\n\
";
const int maxn = 100010;
int a[maxn],b[maxn];
int next[maxn];
namespace SuffixArray {
	int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
	int sa[maxn];

	bool cmp(int *r,int a,int b,int l)
	{
		return r[a]==r[b]&&r[a+l]==r[b+l];
	}
	//da function use doubling algorithm in suffix array, to create sa[].
	void da(int  *r,int n,int m)//n represent the number of integers in sequence s,includeing the end a[n]=0;
	//m represent the value range of sequence s.after discretization, m equal to the number of unique integers in a[] plus 1.
	{
		int i,j,*x=wa,*y=wb,*t,p;
		for(i=0;i<m;i++)
			ws1[i]=0;
		for(i=0;i<n;i++)
			ws1[x[i]=r[i]]++;
		for(i=1;i<m;i++)
			ws1[i]+=ws1[i-1];
		for(i=n-1;i>=0;i--)
			sa[--ws1[x[i]]]=i;//suffix array sa[i] contains the starting positions of the sorted suffix.
		//for example,sa[2]=5 refers to the rank 2 suffix starting at position 5 in a[].

		for(j=1,p=1;p<n;m=p,j*=2)//doubling algorithm,time complexity is o(nlogn).
			//the main idea of doubling algorithm: the rank of s[i...i+pow(2,k)-1] is calculated through the ranks of s[i...i+pow(2,k-1)-1] and s[i+pow(2,k-1)...i+pow(2,k)-1].
		{
			for(i=n-j,p=0;i<n;i++)
				y[p++]=i;
			for(i=0;i<n;i++)
			{
				if(sa[i]>=j)
					y[p++]=sa[i]-j;
			}
			for(i=0;i<n;i++)
				wv[i]=x[y[i]];
			for(i=0;i<m;i++)
				ws1[i]=0;
			for(i=0;i<n;i++)
				ws1[wv[i]]++;
			for(i=1;i<m;i++)
				ws1[i]+=ws1[i-1];
			for(i=n-1;i>=0;i--)
				sa[--ws1[wv[i]]]=y[i];
			for(t=x,x=y,y=t,i=1,p=1,x[sa[0]]=0;i<n;i++)
				x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;//x[] is used to store the rank of every pattern(from the key position to the end of a[] 
			//e.g.in a[]={1,2,3,4...n},if the key position is the third element in a[],the pattern should 
			//be {4...n}).if two patterns are the same,the left pattern ranks lower in sa[].however,the ranks
			//of two same patterns should be the same in x[],ohterwise,when p==n,the recycle is stopped.
		}
	}
	int h[maxn],crank[maxn];

	//calheight function use greedy algorithm,to create height array--h[].time complexity is o(2n).
	void calheight(int *r,int n)
	{
		int i,j,k=0;
		for(i=1;i<=n;i++)
		{		
			crank[sa[i]]=i;	//calculate the rank of every pattern,crank[] is the opposite operation to sa[].
			//e.g.crank[i]=4 represent the pattern, which use the (i-1)th element in a[] as the starting position, rank 4.
		}
		for(i=0;i<n;h[crank[i++]]=k)
		{
			for(k?k--:0,j=sa[crank[i]-1];r[i+k]==r[j+k];k++);//h[i] represent the number of common prefix bits between sa[i] and sa[i-1].
			//e.g. a[]={1,2,3,4,5,1,2,3,4,5,0},sa[1] refers to the string{1,2,3,4,5,0},
			//sa[2] refers to the string{1,2,3,4,5,1,2,3,4,5,0},there are 5 common prefix bits 
			//between sa[1] and sa[2], hence,h[2]=5.
		}
	}
}
using namespace SuffixArray;
int val[maxn];
int mark[maxn];
int m[maxn];
bool makermq(int l,int k,int n)
{
	int i,ans=0,sum=1,z=0,g,sum1,j;
	double sum2,ssum;
	//count the total number of patterns(length = L, minimun occurence = K)
	//use height array to decide whether the length of common prefix satisfy the requirement or not.if satisfy,sum+=1.
	//as h[i] is obtained from Suffix(sa[i]) and Suffix(sa[i-1]), the initial value of sum equal to 1.
	//the preparation of three output could be excuted in one recycle for(,,).time complexity is O(n) in most situations.
	for(i=1;i<=n;i++)
	{
		if(h[i]>=l)
		{
			sum++;
		}
		if(sum>=k&&z==0)
		{
			ans++;//ans is the number of occurences of all patterns(length=l,occurence>=k)
			z=1;
		}
		if(h[i]<l)
		{
			if(sum>=k)
			{
				val[ans]=sum;//val array is used for recording the number of occurences of every pattern(length=l,occurence>=k),
							//prepared for calculating average occurence frequency.
				mark[ans]=i-1;//mark array is used for marking the ending postion of a common prefix(length=l,occurence>=k) in h[],
							//prepared for calculating percent coverage with val[].
			}
			sum=1;
			z=0;
		}
	}
	if(sum>=k)
	{
		val[ans]=sum;
		mark[ans]=n;
	}
	printf("%6d %6d", l, ans);
	//count the average occurence frequency of certain pattern length(occurence>=k)
	if(ans!=0)
	{
		ssum=n-l+1;//total number of patterns(length=l)
	    sum2=0;
	    for(i=1;i<=ans;i++)
		{
		   sum2+= double (val[i]) /  ssum;//the value of element in val[] divide by the number of patterns(length=l) equal to 
										//the occurence frequency of one pattern(length=l)
		}
		printf(" %6f",sum2/ans);//sum2 divide by ans equal to the average occurence frequency of one pattern length
	}
	else
	{
		printf(" %6f", 0.0);
	}
	//count the percent coverage of certain pattern length(occurence>=k)
	if(ans!=0)
	{
		g=0;
		sum1=0;
		for(i=1;i<=ans;i++)
		{
			for(j=mark[i];j>=mark[i]-val[i]+1;j--)//mark[i]-val[i] get the rank of certain pattern
			{
				m[++g]=sa[j];//get the starting position in a[] through sa[], record in m[].
			}
		}
		sort(m+1,m+g+1);
		//in sort(), if L is larger, g will be smaller.
		//however,in the worst situation,all elements in a[] are the same and K=L=1, time complexity would be o(nlogn).
		for(i=2;i<=g;i++)
		{
			if(m[i]-m[i-1]>l)
				sum1+=l;
			else
				sum1+=m[i]-m[i-1];
			//get the coverage length between two patterns
			//if m[i]-m[i-1]>l,there is no coverage between two patterns,coverage length add L
			//if m[i]-m[i-1]<l,there is coverage between two patterns,coverage length add m[i]-m[i-1]
		}
		sum1+=l;
		printf(" %6d/%d\n", sum1 , n );
	}
	else
	{
		printf(" %6d\n", 0);
	}
	return 0 < ans;
}
map<int ,int >maps;
//Convert a string to corresponding integer if it's possible.
int StringToInteger(char *s)
{
	int result = 0;
	for (s += 3 ; *s; s++) {
		if (*s < '0' || '9' < *s) {
			return -1;
		}
		result = result * 10 + *s - '0';
	}
	return result;
}
//main function 
//argc as the amount of arguments(or parameters) which argv stores them.
//e.g. Run the command like "main .exe -L=2 -K=2 test1".
//We would have
//argc = 4,
//argv = {"main.exe", "-L=2", "-K=2", "test1"}
int main(int argc, char **argv)
{
#if 1
	for (int i = 0; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	puts("");
#endif
	int i,
		l = 1 < argc? StringToInteger(argv[1]): -1,
		k = 2 < argc? StringToInteger(argv[2]): -1,
		n = 0,
		m = 1;
	//Parameters check
	//Check if argv[]'s format is legal.
	if (argc != 4 ||
			argv[1][0] != '-' || argv[1][1] != 'L' || argv[1][2] != '=' ||
			argv[2][0] != '-' || argv[2][1] != 'K' || argv[2][2] != '=' ||
			l < 0 || k <0) {
		puts(readme);
		return 1;
	}
	//Redirect stdin to the file which argv[3] represents.
	if (!freopen(argv[3], "r", stdin)) {
		printf("File can't be opened.\n");
		return 1;
	}
	//Load FILE, read a[] from stdin
	for ( ; ~scanf("%d", a + n); n++) {}
	//Make a backup for a[].
	memcpy(b, a, sizeof(a));
	//as the maximum value of int is larger than 100000, it's needed to discretize a[] before using suffix array, which is based on radix sort. 
	//sort before discretization, time complexity is o(nlogn) 
	sort(b, b + n);
	//map a[] <-> b[]. before discretiztion, if a[]={1,1000,1000,1000000,...}, after discretization, a[]={1,2,2,3,...}
	maps[b[0]] = m++;
	for(i = 1; i < n; i++) {
		if(b[i] != b[i - 1]) {
			maps[b[i]] = m++;
		}
	}
	for(i = 0; i < n; i++) {
		a[i]=maps[a[i]];
	}
	a[n]=0;	//set boundary value, in order to set sa[0]=n
	//Construct SuffixArray
	da(a, n + 1, m + 1);
	calheight(a, n);
	//Enumerate the length of subsequences from l to n (included)
	//which appear at least k times in a[].
	for (i = l; i <= n; i++) {
		if (!makermq(i, k, n)) {
			//break;
		}
	}

	fclose(stdin);

	return 0;
}
