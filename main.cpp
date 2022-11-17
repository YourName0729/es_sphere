#include <iostream>
#include <random>
#include <string>
#include <array>

using namespace std;

float sqrt_sum(const array<float, 10>& x) {
    float re = 0;
    for (auto e : x) re += e * e;
    return re;
}

int es1c1(float sigma) {
    random_device rd;
    default_random_engine rng(rd());
    normal_distribution<float> dis(0, sigma);
    array<float, 10> x = {1,1,1,1,1,1,1,1,1,1};
    int i = 0;
    for (; i < 10000000 && sqrt_sum(x) >= 0.005; ++i) {
        // auto y = x;
        for (auto& e : x) {
            e += dis(rng);
        }
    }
    return i;
}

int es1p1(float sigma) {
    random_device rd;
    default_random_engine rng(rd());
    normal_distribution<float> dis(0, sigma);
    array<float, 10> x = {1,1,1,1,1,1,1,1,1,1};
    float ss_x = sqrt_sum(x);
    int i = 0;
    for (; i < 10000000 && ss_x >= 0.005; ++i) {
        auto y = x;
        for (auto& e : y) {
            e += dis(rng);
        }
        float ss_y = sqrt_sum(y);
        if (ss_y < ss_x) x = y, ss_x = ss_y;
    }
    return i;
}

int unc_es1c1(float sigma) {
    random_device rd;
    default_random_engine rng(rd());
    normal_distribution<float> dis(0, 1);
    float eps_0 = 1e-6;
    float tau = 0.01 / sqrt(2 * 10);
    float tau_p = 0.01 / sqrt(2 * sqrt(10));
    array<float, 10> x = {1,1,1,1,1,1,1,1,1,1};
    float ss_x = sqrt_sum(x);
    array<float, 10> sig;
    fill(sig.begin(), sig.end(), sigma);
    int i = 0;
    for (; i < 10000000 && ss_x >= 0.005; ++i) {
        // auto y = x;
        for (int i = 0; i < 10; ++i) {
            sig[i] = sig[i] * exp(tau_p * dis(rng) + tau * dis(rng));
            sig[i] = max(sig[i], eps_0);
            x[i] += sig[i] * dis(rng);
        }
        ss_x = sqrt_sum(x);
    }
    // float mx = sig[0];
    // for (auto v : sig) mx = max(mx, v);
    // cout << mx << ' ' << ss_x << '\n';
    return i;
}

int unc_es1p1(float sigma) {
    random_device rd;
    default_random_engine rng(rd());
    normal_distribution<float> dis(0, 1);
    float eps_0 = 1e-6;
    float tau = 0.01 / sqrt(2 * 10);
    float tau_p = 0.01 / sqrt(2 * sqrt(10));
    array<float, 10> x = {1,1,1,1,1,1,1,1,1,1};
    float ss_x = sqrt_sum(x);
    array<float, 10> sig;
    fill(sig.begin(), sig.end(), sigma);
    int i = 0;
    for (; i < 10000000 && sqrt_sum(x) >= 0.005; ++i) {
        auto y = x;
        for (int i = 0; i < 10; ++i) {
            sig[i] = sig[i] * exp(tau_p * dis(rng) + tau * dis(rng));
            sig[i] = max(sig[i], eps_0);
            y[i] += sig[i] * dis(rng);
            float ss_y = sqrt_sum(y);
            if (ss_y < ss_x) x = y, ss_x = ss_y;
        }
    }
    return i;
}

int fifth_es1c1(float sigma) {
    random_device rd;
    default_random_engine rng(rd());
    normal_distribution<float> dis(0, 1);
    float a = 0.85;
    int G = 10;
    int Gs = 0;
    
    array<float, 10> x = {1,1,1,1,1,1,1,1,1,1};
    float ss_x = sqrt_sum(x);
    int i = 0;
    for (; i < 10000000 && ss_x >= 0.005; ++i) {
        // auto y = x;
        if (i % G == 9) {
            if (Gs > 2) sigma /= a;
            else if (Gs < 2) sigma *= a;
            Gs = 0;
        }
        
        for (auto& e : x) {
            e += sigma * dis(rng);
        }
        float ss_y = sqrt_sum(x);
        if (ss_y < ss_x) ++Gs;
        ss_x = ss_y;
    }
    return i;
}

int fifth_es1p1(float sigma) {
    random_device rd;
    default_random_engine rng(rd());
    normal_distribution<float> dis(0, 1);
    float a = 0.85;
    int G = 10;
    int Gs = 0;
    array<float, 10> x = {1,1,1,1,1,1,1,1,1,1};
    float ss_x = sqrt_sum(x);
    int i = 0;
    for (; i < 10000000 && ss_x >= 0.005; ++i) {
        if (i % G == 9) {
            if (Gs > 2) sigma /= a;
            else if (Gs < 2) sigma *= a;
            Gs = 0;
        }

        auto y = x;
        for (int i = 0; i < 10; ++i) {
            // sig[i] = sig[i] * exp(tau_p * dis(rng) + tau * dis(rng));
            // sig[i] = max(sig[i], eps_0);
            y[i] += sigma * dis(rng);
            float ss_y = sqrt_sum(y);
            if (ss_y < ss_x) x = y, ss_x = ss_y, ++Gs;
        }
    }
    return i;
}

int main() {
    float sigma[] = {0.01, 0.1, 1.0};
    cout << "unc_es1c1" << endl;
    for (int i = 0; i < 10; ++i) {
        for (auto sig : sigma) {
            cout << unc_es1c1(sig) << '\t';
        }
        cout << endl;
    }

    cout << "unc_es1p1" << endl;
    for (int i = 0; i < 10; ++i) {
        for (auto sig : sigma) {
            cout << unc_es1p1(sig) << ' ';
        }
        cout << endl;
    }
}