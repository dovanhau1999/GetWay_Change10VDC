#ifndef _KALMAN_FILTER_H
#define _KALMAN_FILTER_H

typedef struct
{
    float x; // giá trị lọc
    float P; // sai số ước lượng
    float Q; // nhiễu hệ thống
    float R; // nhiễu đo
    float K; // Kalman gain
} Kalman_t;

void Kalman_Init(Kalman_t *k,
                 float q,
                 float r,
                 float initial_value);
float Kalman_Update(Kalman_t *k, float measurement);

#endif /*_KALMAN_FILTER_H*/
