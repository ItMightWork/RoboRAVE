int get_int_from_twos_complement(int source, int lenght){
	int result;

	if ((source & (1 << (lenght-1))) != 0)
	  result = source | ~((1 << lenght) - 1);
	else
	  result = source;
	return result;
}
