int divide(int dividend, int divisor) {
    // Handle the only positive overflow case
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    // Determine the sign of the answer
    int negative = (dividend < 0) != (divisor < 0);

    // Convert to positive magnitudes safely
    long long a = dividend;
    long long b = divisor;

    if (a < 0) a = -a;
    if (b < 0) b = -b;

    long long quotient = 0;

    while (a >= b) {
        long long temp = b;
        long long multiple = 1;

        // Double the divisor while it still fits
        while (a >= temp + temp) {
            temp = temp + temp;
            multiple = multiple + multiple;
        }

        // Subtract the largest fitting multiple
        a = a - temp;
        quotient = quotient + multiple;
    }

    if (negative) {
        quotient = -quotient;
    }

    return (int)quotient;
}
