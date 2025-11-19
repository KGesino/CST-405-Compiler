int main() {

    int i;
    int j;
    int k;
    float x;
    float y;

    i = 10;
    j = 2;
    k = i * j;   /* expect 20 */
    print(k);

    k = i / j;   /* expect 5 */
    print(k);

    /* =======================================================
     * SWAP TEST (NEW)
     * ======================================================= */
    i = 5;
    j = 9;
    swap(i, j);      /* after swap: i = 9, j = 5 */
    print(i);        /* expect 9 */
    print(j);        /* expect 5 */

    /* Mixed-type: multiply int and float */
    x = i * 2.5;    /* expect 25.0 */
    print(x);

    y = 7.5 * i;    /* expect 75.0 */
    print(y);

    return 0;
}
