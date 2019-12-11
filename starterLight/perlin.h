#ifndef PERLIN_H
#define PERLIN_H

#include "math.h"
#include <QVector3D>
#include <vector>
#include <QDebug>

using namespace std;


#define lerp(t, a, b) ((a) + (t) * ((b) - (a)))

const float GRAD3[][3] = {
    {1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
    {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
    {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1},
    {1,0,-1},{-1,0,-1},{0,-1,1},{0,1,1}};

const unsigned char PERM[] = {
  151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
  36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
  234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
  88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
  134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
  230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
  1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
  116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
  124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
  47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
  154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
  108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
  242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
  239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
  50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
  141, 128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131,
  13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37,
  240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
  219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125,
  136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158,
  231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245,
  40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187,
  208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198,
  173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
  255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223,
  183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167,
  43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185,
  112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179,
  162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199,
  106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236,
  205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156,
  180};

static inline float
grad2(const int hash, const float x, const float y)
{
    const int h = hash & 15;
    return x * GRAD3[h][0] + y * GRAD3[h][1];
}

static inline float
grad3(const int hash, const float x, const float y, const float z)
{
    const int h = hash & 15;
    return x * GRAD3[h][0] + y * GRAD3[h][1] + z * GRAD3[h][2];
}

float
noise2(float x, float y, const float repeatx, const float repeaty, const int base)
{
    float fx, fy;
    int A, AA, AB, B, BA, BB;
    int i = (int)floorf(fmodf(x, repeatx));
    int j = (int)floorf(fmodf(y, repeaty));
    int ii = (int)fmodf(i + 1, repeatx);
    int jj = (int)fmodf(j + 1, repeaty);
    i = (i & 255) + base;
    j = (j & 255) + base;
    ii = (ii & 255) + base;
    jj = (jj & 255) + base;

    x -= floorf(x); y -= floorf(y);
    fx = x*x*x * (x * (x * 6 - 15) + 10);
    fy = y*y*y * (y * (y * 6 - 15) + 10);

    A = PERM[i];
    AA = PERM[A + j];
    AB = PERM[A + jj];
    B = PERM[ii];
    BA = PERM[B + j];
    BB = PERM[B + jj];

    return lerp(fy, lerp(fx, grad2(PERM[AA], x, y),
                             grad2(PERM[BA], x - 1, y)),
                    lerp(fx, grad2(PERM[AB], x, y - 1),
                             grad2(PERM[BB], x - 1, y - 1)));
}


float
noise3(float x, float y, float z, const float repeatx, const float repeaty, const float repeatz, const int base)
{
    float fx, fy, fz;
    int A, AA, AB, B, BA, BB;
    int i = (int)floorf(fmodf(x, repeatx));
    int j = (int)floorf(fmodf(y, repeaty));
    int k = (int)floorf(fmodf(z, repeatz));
    int ii = (int)fmodf(i + 1, repeatx);
    int jj = (int)fmodf(j + 1, repeaty);
    int kk = (int)fmodf(z + 1, repeatz);
    i = (i & 255) + base;
    j = (j & 255) + base;
    ii = (ii & 255) + base;
    jj = (jj & 255) + base;

    x -= floorf(x); y -= floorf(y); z -= floorf(z);
    fx = x*x*x * (x * (x * 6 - 15) + 10);
    fy = y*y*y * (y * (y * 6 - 15) + 10);
    fz = z*z*z * (z * (z * 6 - 15) + 10);

    A = PERM[i];
    AA = PERM[A + j];
    AB = PERM[A + jj];
    B = PERM[ii];
    BA = PERM[B + j];
    BB = PERM[B + jj];

    return lerp(fz,lerp(fy,    lerp(fx,    grad3(PERM[AA], x, y, z),
                                            grad3(PERM[BA], x - 1, y, z)),
                                lerp(fx,    grad3(PERM[AB], x, y - 1, z),
                                            grad3(PERM[BB], x - 1, y - 1, z))),
                    lerp(fy,    lerp(fx,    grad3(PERM[AA], x, y, z - 1),
                                            grad3(PERM[BA], x - 1, y, z - 1)),
                                lerp(fx,    grad3(PERM[AB], x, y - 1, z - 1),
                                            grad3(PERM[BB], x - 1, y - 1, z - 1))));
}

float
py_noise2(float x, float y, const int octaves, const float persistence, const float lacunarity, const float repeatx, const float repeaty, const int base)
{


    if (octaves == 1) {
        // Single octave, return simple noise
        return noise2(x, y, repeatx, repeaty, base);
    } else if (octaves > 1) {
        int i;
        float freq = 1.0f;
        float amp = 1.0f;
        float max = 0.0f;
        float total = 0.0f;

        for (i = 0; i < octaves; i++) {
            total += noise2(x * freq, y * freq, repeatx * freq, repeaty * freq, base) * amp;
            max += amp;
            freq *= lacunarity;
            amp *= persistence;
        }
        return (total / max);
    }

    return 0;
}

float
py_noise3(float x, float y, float z, const int octaves, const float persistence, const float lacunarity, const float repeatx, const float repeaty, const float repeatz, const int base)
{


    if (octaves == 1) {
        // Single octave, return simple noise
        return noise3(x, y, z, repeatx, repeaty, repeatz, base);
    } else if (octaves > 1) {
        int i;
        float freq = 1.0f;
        float amp = 1.0f;
        float max = 0.0f;
        float total = 0.0f;

        for (i = 0; i < octaves; i++) {
            total += noise3(x * freq, y * freq, z * freq, repeatx * freq, repeaty * freq, repeatz * freq, base) * amp;
            max += amp;
            freq *= lacunarity;
            amp *= persistence;
        }
        return (total / max);
    }

    return 0;
}

vector<vector<QVector3D>> genereTerrain(int rows, int cols, int step, int octaves, float persistence, float lacunarity ) {

    vector<vector<QVector3D>> grid;
    vector<QVector3D> line;


    for(int y = 0;  y < rows*step; y++){
        line.clear();

        for(int x = 0; x < cols*step; x++){

            float xp = (float)x/step;// - (cols*scale)/2;
            float yp = (float)y/step;// - (rows*scale)/2;


            //float zp = noise2(xp, yp, 1024, 1024, 0);
            float zp = py_noise2(xp, yp,  octaves, persistence, lacunarity, 1024, 1024, 0);


            //line.push_back(Vector3(xp- (scale/step)/2, yp- (scale/step)/2, zp));
            line.push_back(QVector3D(xp-cols/2, yp-rows/2, zp));


        }
        grid.push_back(line);
    }

    return grid;
}

/*vector<vector<QVector3D>> generePlanete(int meridien, int parallele) {

    vector<vector<QVector3D>> grid;
    vector<QVector3D> line;

    int octaves = 6;
    float persistence = 0.5;
    float lacunarity = 2.0;


    for(int y = 0;  y < rows; y++){
        line.clear();

        for(int x = 0; x < cols; x++){

            float xp = (float)x/step;// - (cols*scale)/2;
            float yp = (float)y/step;// - (rows*scale)/2;


            //float zp = noise2(xp, yp, 1024, 1024, 0);
            float zp = py_noise2(xp, yp,  8, 0.5, 2.0f, 1024, 1024, 0);


            //line.push_back(Vector3(xp- (scale/step)/2, yp- (scale/step)/2, zp));
            line.push_back(QVector3D(xp-cols/2, yp-rows/2, zp));


        }
        grid.push_back(line);
    }

    return grid;
}*/





#endif // PERLIN_H
