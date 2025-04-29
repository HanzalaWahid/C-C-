// Print a pattern with number in descending order
// # include <stdio.h>

// int main(){
//     int i , j ;
//     // int n = 3;
//     for (i = 1 ; i <= n ; i++){
//         for ( j = 1 ; j<= i ; j++){
//             printf("%d ", j);
//         }
//         printf("\n");
//     }
    
//     return 0;
// }

# include <stdio.h>
int main (){
    int i , j;
    // int n = 5;
    for (i = 1 ; i <= 5 ; i++ ){
        for ( j = 1 ; j <= i ; j++){
            printf("%d", i );
    
        }
        printf("\n");
    }

    return 0 ; 
}