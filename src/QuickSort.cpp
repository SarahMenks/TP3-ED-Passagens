// #include "QuickSort.hpp"
// #include "Flight.hpp"

// // media de 3 inteiros
// int media3(int a, int b, int c) {
//     if ((a <= b) && (b <= c)) return b;  // a b c
//     if ((a <= c) && (c <= b)) return c;  // a c b
//     if ((b <= a) && (a <= c)) return a;  // b a c
//     if ((b <= c) && (c <= a)) return c;  // b c a
//     if ((c <= a) && (a <= b)) return a;  // c a b
//     return b;                            // c b a
// }

// /*
// void Partition(Flight *flights, int first, int end, int *left, int *right) {
//     int indices[end+1];
    
//     if(first >= end)
//         return;

//     //implementação do quick sort com mediana de 3    
//     *left = first;
//     *right = end;

//     std::string pivo = media3(indices[first], indices[(first+end)/2],indices[end]);

//     while(left <= right){

//         while((indices[*left]) < pivo){
//             (*left)++;
//         }
        
//         while(RetornaChave(indices[*right]) > pivo){
//            (*right)--;
//         }

//         if(left <= right){
//             int temp = indices[*left];
//             indices[*left] = indices[*right];
//             indices[*right] = temp;
            
//             (*left)++;
//             (*right)--;
//         }
//     } 
// }
// */

// void QuickSort(Flight *flights, int l, int r) { 
//   int i, j;
//   Partition(flights, l, r, &i, &j);

//   if(l < j){
//     QuickSort(flights, l, j);
//   }
//   if(i < r){
//     QuickSort(flights, i, r);
//   }
// }