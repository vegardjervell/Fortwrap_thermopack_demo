#include "wrappers/NotIdGas.h"
#include "wrappers/Variant1.h"
#include "wrappers/Variant2.h"
#include <iostream>
#include <vector>

int main(){


    float T = 300.;
    float V = 1.;
    std::vector<float> n;
    n.push_back(1.);
    n.push_back(2.);
    float Fres;
    float Ft;
    float Fv;
    float p_ideal;
    float p_real;
    std::vector<float> Fn(2, 0.0);


    NotIdGas nid = NotIdGas(0, 2, 100., 50.);
    nid.Fres(T, V, &n, &Fres, &Ft, &Fv, &Fn);
    std::cout << "Not Ideal Fres is : " << Fres << std::endl;
    nid.Fideal(T, V, &n, &Fres, &Ft, &p_ideal, &Fn);
    std::cout << "Ideal pressure at T, V = " << T << " " << V << " is : " << -p_ideal << std::endl;
    nid.pressure(T, V, &n, &p_real);
    std::cout << "Not Ideal pressure is : " << p_real << std::endl;

    Variant1 v1 = Variant1(1, 2, 100., 50., 2, 5.);
    v1.Fres(T, V, &n, &Fres, &Ft, &Fv, &Fn);
    std::cout << "\nVariant1 Fres is : " << Fres << std::endl;
    v1.pressure(T, V, &n, &p_real);
    std::cout << "Variant1 pressure is : " << p_real << std::endl;
    Variant2 v2 = Variant2(3, 2, 100., 50., 2, 5.);
    v2.Fres(T, V, &n, &Fres, &Ft, &Fv, &Fn);
    std::cout << "\nVariant2 Fres is : " << Fres << std::endl;
    v2.pressure(T, V, &n, &p_real);
    std::cout << "Variant2 pressure is : " << p_real << std::endl;

    return 0;
}