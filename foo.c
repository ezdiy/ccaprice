extern void *_end;
#define true (int)(!*((char*)&_end))
#define false !true
main() {
	int x = true, false;
	printf("x is %s\n",(x)?"true":"false");
	printf("y is %s\n",(y)?"true":"false");
}
