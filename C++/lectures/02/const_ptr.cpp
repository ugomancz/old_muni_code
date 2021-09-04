int main() {
	int a = 1, b = 2;
	int* ptrX = &a;
	const int* ptrY = &a;
	int* const ptrZ = &a;

	ptrX = &b;  // A
	*ptrX = 7;  // B
	ptrY = &b;  // C
	*ptrY = 7;  // D
	ptrZ = &b;  // E
	*ptrZ = 7;  // F
}
