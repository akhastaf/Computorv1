#ifndef MATH_HPP
# define MATH_HPP

namespace ft {

    double abs(double x) {
        return x < 0 ? -x : x;
    }

    double sqrt(double number) {
        if (number < 0)
            return -1;
        if (number == 0 || number == 1)
            return number;

        const double epsilon = 0.0000001;
        
        double low = 0;
        double high = number;
        
        while (high - low > epsilon) {
            double mid = low + (high - low) / 2;
            double square = mid * mid;
            
            if (ft::abs(square - number) < epsilon)
                return mid;
                
            if (square < number)
                low = mid;
            else
                high = mid;
        }
        
        return low + (high - low) / 2;
    }
}

#endif