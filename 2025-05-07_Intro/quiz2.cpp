bool is_Prime (long n){
    for (long ii = 2; ii*ii <= n;++ii)
        if (n%ii == 0) return false;
    return true;
}

void nth_twin_primes (int n){
    long count = 0;
    for (long ii = 2;;++ii){
        if (is_Prime(ii) and is_Prime(ii+2)){
            count++;
            if (count == n){
                std::cout << "(" << ii << "," << ii+2 << ")\n";
                break;
            }
        }

    }
        
}