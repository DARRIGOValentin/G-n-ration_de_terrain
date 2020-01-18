#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

//PARAMETRE
int OCTAVES = 6; //6
float PERSISTENCE = 0.4; //0.5
float LACUNARITY = 5; //3
int BASE = 22;

int RINGS = 250;    // 1000
int SEGMENTS = 500; // 2000 pour haute résolution mais long à calculer 

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
grad3(const int hash, const float x, const float y, const float z)
{
    const int h = hash & 15;
    return x * GRAD3[h][0] + y * GRAD3[h][1] + z * GRAD3[h][2];
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
    int kk = (int)fmodf(k + 1, repeatz);
    i = (i & 255) + base;
    j = (j & 255) + base;
    k = (k & 255) + base;
    ii = (ii & 255) + base;
    jj = (jj & 255) + base;
    kk = (kk & 255) + base;

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

    return lerp(fz,lerp(fy,    lerp(fx,     grad3(PERM[AA+k], x, y, z),
                                            grad3(PERM[BA+k], x - 1, y, z)),
                                lerp(fx,    grad3(PERM[AB+k], x, y - 1, z),
                                            grad3(PERM[BB+k], x - 1, y - 1, z))),
                    lerp(fy,    lerp(fx,    grad3(PERM[AA+kk], x, y, z - 1),
                                            grad3(PERM[BA+kk], x - 1, y, z - 1)),
                                lerp(fx,    grad3(PERM[AB+kk], x, y - 1, z - 1),
                                            grad3(PERM[BB+kk], x - 1, y - 1, z - 1))));
}

float
betternoise3(float x, float y, float z, const int octaves, const float persistence, const float lacunarity, const float repeatx, const float repeaty, const float repeatz, const int base)
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


class Vector3
{
	public:
	    float coords[3];

	public:
	    Vector3(float a, float b, float c);

	    float operator[](int i);

};

Vector3::Vector3(float x, float y, float z)
{
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
}

float Vector3::operator[](int i){
	return coords[i];
}

vector<vector<Vector3>> getPoints(int segments, int rings){
    vector<vector<Vector3>> points;

    vector<Vector3> foo;
    foo.push_back(Vector3(0, 1, 0));
    
    points.push_back(foo);

    for(int i = 1; i < rings - 1 ; i++){
        float y = sin( (M_PI/2) -     (  (i*M_PI)/(rings-1)  )    );
        float radius = cos( (M_PI/2) -     (  (i*M_PI)/(rings-1)  )    );

        vector<Vector3> ring;
        for(int j = 0; j < segments; j++){
            float x = radius * cos( (j*2*M_PI)/segments );
            float z = radius * sin( (j*2*M_PI)/segments );
            ring.push_back(Vector3(x, y, z));
        }

        points.push_back(ring);
    }

    vector<Vector3> bar;
    bar.push_back(Vector3(0, -1, 0));
    points.push_back(bar);

    return points;
}

void set_color(float t, float &r, float &g, float &b){
    
    if (t >= 0.3){
        r = 0.8;
        g = 0.8;
        b = 0.8;
    }
    else if (t >= 0.2){
        r = 0.45;
        g = 0.40;
        b = 0.34;
    }else if(t >= 0){
        r = 0.0;
        g = 0.8;
        b = 0.0;
    }
    else if (t >= -0.1){
        r = 0.;
        g = 0.;
        b = 0.8;
    }
    else{
        r = 0.;
        g = 0.;
        b = 0.2;
    }
    
}

void writeVertex(Vector3 vertex, ofstream& myfile){
    float xp = vertex[0];
	float yp = vertex[1];
	float zp = vertex[2];
    float t = betternoise3(xp, yp, zp, OCTAVES, PERSISTENCE, LACUNARITY, 1024, 1024, 1024, BASE);

    float h = 1+t/5.;
    xp *= h;
    yp *= h;
    zp *= h;

	myfile << "v " << xp << " " << yp << " " << zp;  

	float r, g, b;
            
	set_color(t, r, g, b);
	myfile << " " << r << " " << g << " " << b << endl;
}

void writeUVSphere(vector<vector<Vector3>> points, string fileName){
	ofstream myfile;
	myfile.open (fileName);

	int rings = points.size();
	int segments = points[1].size();

    writeVertex(points[0][0], myfile);

	for(int y = 1; y < rings-1; y++){
		for(int x = 0; x < segments; x++){
            writeVertex(points[y][x], myfile);
		}
	}

    writeVertex(points[rings-1][0], myfile);

    //ecriture des faces
    int counter = 2;
    for(int i = 1; i < rings-2; i++){
        for(int j = 0; j < segments-1; j++){
           int v1 = counter;
           int v2 = v1 +1;
           int v3 = v1 + segments;
           int v4 = v3 + 1;

            myfile << "f " << v1 << " " << v2 << " " <<  v3 << endl;
            myfile << "f " << v3 << " " << v2 << " " <<  v4 << endl;

           counter ++;
        }

        int v1 = counter;
        int v2 = v1 - segments + 1;
        int v3 = v1 + segments;
        int v4 = v2 + segments;

        myfile << "f " << v1 << " " << v2 << " " <<  v3 << endl;
        myfile << "f " << v3 << " " << v2 << " " <<  v4 << endl;

        counter ++;
   }
    
    //faces pole nord
    for(int i = 0; i < segments-1; i++){
        myfile << "f " << i+2 << " " << 1 << " " << i+3 << endl;
    }
    myfile << "f " << 1 << " " << 2 << " " << segments+1 << endl;

   
    //faces pole sud
   int last = 2 + (rings-2) * segments;
   for(int i = 0; i < segments-1; i++){
        int index = 2 + i + (rings-3) * (segments);
        myfile << "f " << last << " " << index << " " << index+1 << endl;
    }
    myfile << "f " << last << " " << last-1 << " " << last-segments << endl;

	myfile.close();
}

int main() 
{
	
    cout << "création de planètte ..." << endl;
    vector<vector<Vector3>> p = getPoints(SEGMENTS, RINGS);
    writeUVSphere(p, "test.obj");
    cout << "fin" << endl;
  	return 0;
}