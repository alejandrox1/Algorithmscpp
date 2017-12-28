void f(int * restrict a, int * restrict b, int * restrict x) {
	*a += *x;
	*b += *x;
}
