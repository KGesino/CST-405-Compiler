int sumArray(int arr[], int size) {
    int sum;
    int i;

    sum = 0;
    i = 0;

    while (i < size) {
        sum = sum + arr[i];
        i = i + 1;
    }

    return sum;
}

void testArrayOperations(int arr[], int size) {
    int i;

    /* Initialize array */
    i = 0;
    while (i < size) {
        arr[i] = i * 2;
        i = i + 1;
    }

    /* Modify array elements */
    i = 0;
    while (i < size) {
        arr[i] = arr[i] + 1;
        i = i + 1;
    }
}

int main() {

    int testArray[10];
    int testArray2[10];
    int i;
    int result;
    int a;
    int b;
    int choice;

    testArrayOperations(testArray, 10);
    result = sumArray(testArray, 10);
    write(result);

    return 0;
}
