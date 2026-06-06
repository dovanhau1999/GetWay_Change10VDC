#include "PROTOCAL_Kalman.h"

void Kalman_Init(Kalman_t *k,
                 float q,
                 float r,
                 float initial_value)
{
    k->Q = q;
    k->R = r;
    k->P = 1.0f;
    k->x = initial_value;
}

float Kalman_Update(Kalman_t *k, float measurement)
{
    // Predict
    k->P = k->P + k->Q;

    // Update
    k->K = k->P / (k->P + k->R);
    k->x = k->x + k->K * (measurement - k->x);
    k->P = (1.0f - k->K) * k->P;

    return k->x;
}

