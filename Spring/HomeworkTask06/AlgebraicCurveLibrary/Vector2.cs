using System;

namespace AlgebraicCurveLibrary
{
    public class Vector2
    {
        float x;
        float y;

        public float X
        {
            get
            {
                return x;
            }
        }

        public float Y
        {
            get
            {
                return y;
            }
        }

        public float Length
        {
            get
            {
                return (float)Math.Sqrt(x * x + y * y);
            }
        }

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public void Normalize()
        {
            float length = Length;
            x /= length;
            y /= length;
        }

        public static Vector2 operator +(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x + b.x, a.y + b.y);
        }

        public static Vector2 operator -(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x - b.x, a.y - b.y);
        }

        public static Vector2 operator *(Vector2 p, float scale)
        {
            return new Vector2(p.x * scale, p.y * scale);
        }

        public static Vector2 operator *(float scale, Vector2 p)
        {
            return new Vector2(p.x * scale, p.y * scale);
        }

        public static Vector2 operator /(Vector2 p, float scale)
        {
            return new Vector2(p.x / scale, p.y / scale);
        }
    }
}
