import math

def is_prime(n):
    # check to see if a number is prime
    if n < 2:
        # not considering 0 or 1
        return False
    
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
        
    return True