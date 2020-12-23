#ifndef MATHHELPER_H
#define MATHHELPER_H

#define FLIPH_TILE(n) (n | (1 << 10))
#define FLIPV_TILE(n) (n | (1 << 11))
#define FLIPHV_TILE(n) (n | (3 << 10))

struct Vector2{
    int x,y;

    Vector2(int _x = 0,int _y = 0){
        x = _x;
        y = _y;
    }

    Vector2& operator +=(const Vector2& v2) {
		x += v2.x;
		y += v2.y;
		return *this;
	}
};

inline Vector2 operator +(const Vector2& v1, const Vector2& v2) {
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

const Vector2 VEC2_ZERO = {0,0};

struct Rect{
private:
    Vector2 mCorners[4];/// Los vertices del rectangulo estan enumerados en el sentido de las manecillas del reloj y empezando por la esquina superior izquierda
public:
    Rect(){
        for(int i=0; i<4; i++){
            mCorners[i] = VEC2_ZERO;
        }
    }

    Rect(Vector2 _esqSI, int _width, int _height){
        mCorners[0] = _esqSI;
        mCorners[1] = _esqSI+Vector2(_width-1,0);
        mCorners[2] = _esqSI+Vector2(_width-1,_height-1);
        mCorners[3] = _esqSI+Vector2(0,_height-1);
    }

    int width(){
        return (mCorners[2].x-mCorners[0].x)+1;
    }

    int height(){
        return (mCorners[2].y-mCorners[0].y)+1;
    }

    Vector2 topLeftCorner(){
        return mCorners[0];
    }

    Vector2 bottomRightCorner(){
        return mCorners[2];
    }

    Vector2 getCorner(int index){
        if(index <0 || index>3) return VEC2_ZERO;
        return mCorners[index];
    }

    void moveBy(int xOffset,int yOffset){
        Vector2 vecOffset(xOffset,yOffset);
        for(int i=0; i<4; i++){
            mCorners[i] += vecOffset;
        }
    }

    void moveTLTo(Vector2 pos){
        int ancho = width(),largo = height();
        mCorners[0] = pos;
        mCorners[1] = pos+Vector2(ancho-1,0);
        mCorners[2] = pos+Vector2(ancho-1,largo-1);
        mCorners[3] = pos+Vector2(0,largo-1);
    }
};


inline int anguloAEntero32B(int angulo){
    float res = angulo;
    res /= 360;
    res *= 32767;

    return res;
}

inline int offsetDeMapa(int x,int y, int width){ ///Regresa el offset que se debe añadir al puntero inicial de un mapa con anchura "width"  en la posicion (x,y)
    return (y*width) + x;
}

inline int Clamp(const int& value, const int& nMin, const int& nMax) {
	if (value > nMax) {
		return nMax;
	}
	if (value < nMin) {
		return nMin;
	}
	return value;
}

/*inline bool PointInRect(Rect rect,Vector2 point){
    return(point.x == Clamp(point.x,rect.topLeftCorner().x,rect.bottomRightCorner().x) && point.y == Clamp(point.y,rect.topLeftCorner().y,rect.bottomRightCorner().y));
}*/

inline bool RectRectCollision(Rect R1,Rect R2){ ///Esta funcion checa si dos rectangulos estan colicionando, NOTA: No funciona en rectangulos rotados
    if(R1.getCorner(0).x > R2.getCorner(2).x) return false;
    if(R1.getCorner(2).x < R2.getCorner(0).x) return false;
    if(R1.getCorner(0).y > R2.getCorner(2).y) return false;
    if(R1.getCorner(2).y < R2.getCorner(0).y) return false;
    return true;
}

#endif // MATHHELPER_H
