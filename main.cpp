#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

//======================================Bubble algortimas ir Merge sort algoritmas===========================================
// =====SKAICIUOTUVAI====
long long compBubble, swapBubble;
long long compMerge;

//----------------Merge sort------------------

void merge(int arr[], int left, int mid, int right) { // Sujungiame dvi jau surikiotos masyvo dalis
    int sau [50000];

    int i = left; // pradzia kaires dalies
    int j = mid + 1; // pradzia desines dalies
    int k = left; // iraso elementus i laikina masyva (sau)

    while (i <= mid && j <= right) { // Kol yra elementu abiejose dalyse
        compMerge++;
        if (arr[i] <= arr[j]) { // Parenkame mazesni elementa
            sau[k] = arr[i];
            i++; // pereiname prie kito keireje
        }else {
            sau[k] = arr[j];
            j++; // pereiname prie kito desineje
        }
        k++; // judame i prieki sau masyve
    }
    while (i <= mid) { // Jei liko elementu kaireje puseje - perkeliame juos
        sau[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) { // Jei liko elementu desineje puseje, taip pat perkeliame juos
        sau[k] = arr[j];
        j++;
        k++;
    }
    // Perrasome rezultatus atgal i pagrindini masyva
    for (int t = left; t <= right; t++) {
        arr[t] = sau[t];
    }
}
// Dalinsim masyva i dalis
void mergeSort(int arr[], int left, int right) {
    // Jei masyve daugiau nei vienas elementas - daliname
    if (left < right) { // Jei yra ka dalinti
        int mid = (left + right) / 2; //viduri

        mergeSort(arr, left, mid); // keire
        mergeSort(arr, mid + 1, right); // desine

        merge(arr, left, mid, right); // sujungimas
    }
}
// ------------Bubble sort----------------

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Atlikti n - 1 perejimu, kiekviena karta vienas elementas atsistoja i vieta
        for (int j = 0; j < n - i - 1; j++) {
            compBubble++;
            // Lyginame elementus tik iki nesurikiuotos dalies ir neeiname uz ribu (arr[j+1])
            if (arr[j] > arr[j + 1]) {
                swapBubble++;
                int sau = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = sau;
            }
        }
    }
}

    // TESTAVIMAS
void runTest(int n, int type) {
    int original[50000];
    int arr1[50000];
    int arr2[50000];

    //type: 0 = random, 1 = sorted, 2 = reversed
    // Sukuriame duomenis
    for (int i = 0; i < n; i++) {
        if (type == 0) original[i] = rand() % n; // random
        if (type == 1) original[i] = i; // jau surikiuoti
        if (type == 2) original[i] = n - i; // atvirkstiniai

        arr1[i] = original[i];
        arr2[i] = original[i];
    }

    double timeB = 0, timeM = 0;

    // KARTOJAME 5 KARTUS!!
    for (int t = 0; t < 5; t++) {

        // ---Bubble---
        compBubble = 0;
        swapBubble = 0;

        for (int i = 0; i < n; i++) arr1[i] = original[i];

        clock_t start1 = clock();
        bubbleSort(arr1, n);
        clock_t end1 = clock();

        // Laikas mikrosekundemis
        timeB += double(end1 - start1) * 1000000.0 / CLOCKS_PER_SEC;

        // ---Merge---
        compMerge = 0;

        for (int i = 0; i < n; i++) arr2[i] = original[i];
        clock_t start2 = clock();
        mergeSort(arr2, 0, n - 1);
        clock_t end2 = clock();

        timeM += double(end2 - start2) * 1000000.0 / CLOCKS_PER_SEC;

    }

    // VIDURKIS
    timeB /= 5;
    timeM /= 5;
    cout << "n = " << n << " | ";

    if (type == 0) cout << "random | ";
    if (type == 1) cout << "sorted | ";
    if (type == 2) cout << "reversed | ";

    cout << "Bubble: " << fixed << setprecision(0) << timeB << " mikrosekundes, comp=" << compBubble
    << ", swap=" << swapBubble << " | ";

    cout << "Merge: " << fixed << setprecision(0) << timeM << " mikrosekundes, comp=" << compMerge << endl;

}
int main() {

    int sizes[] = {5000, 10000, 50000};

    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        runTest(n, 0); // random
        runTest(n, 1); // sorted
        runTest(n, 2); // reversed

        cout << "-------------------------------" << endl;
    }

    return 0;
}