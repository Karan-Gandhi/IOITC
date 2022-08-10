ll int mod_pow(int n, int pow, int mod) {
	if (pow <= 0) return 1;
	if (pow == 1) return n;
	if (pow % 2 == 0) {
		ll int res = mod_pow(n, pow / 2, mod);

		return (res * res) % mod;
	} else {
		ll int res = mod_pow(n, pow / 2, mod);

		return (res * res * n) % mod;
	}
}