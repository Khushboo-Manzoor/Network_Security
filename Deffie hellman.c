#include <stdio.h>
#include <math.h>

long long int power(long long int a, long long int b, long long int P) {
    if (b == 1)
        return a;
    else {
        long long int result = 1;
        a = a % P;
        while (b > 0) {
            if (b & 1) 
                result = (result * a) % P;
            a = (a * a) % P;
            b /= 2;
        }
        return result;
    }
}

int main() {
    long long int prime_num, generator, alice_private, alice_public, bob_private, bob_public, alice_secret, bob_secret;

    
    prime_num = 23;  
    printf("Public Prime Number (prime_num): %lld\n", prime_num);

    generator = 9;   
    printf("Public Generator (generator): %lld\n", generator);

    
    alice_private = 4; 
    printf("Alice's Private Key (alice_private): %lld\n", alice_private);

    alice_public = power(generator, alice_private, prime_num); 
    printf("Alice's Public Key (alice_public): %lld\n", alice_public);


    bob_private = 3;  
    printf("Bob's Private Key (bob_private): %lld\n", bob_private);

    bob_public = power(generator, bob_private, prime_num); 
    printf("Bob's Public Key (bob_public): %lld\n", bob_public);


    alice_secret = power(bob_public, alice_private, prime_num); 
    bob_secret = power(alice_public, bob_private, prime_num);

    printf("Alice's Secret Key (alice_secret): %lld\n", alice_secret);
    printf("Bob's Secret Key (bob_secret): %lld\n", bob_secret);

    return 0;
}

