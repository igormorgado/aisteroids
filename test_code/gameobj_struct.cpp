class GameObj
{
    public:
        //constructors/functions
        GameObj(float _size = 1);
        GameObj(const Point3f &_p,
                const float _angle,
                const Point3f &_v);
        virtual void Draw(){}
        virtual void Init();
        virtual void Update(float t);
        virtual bool IsColliding(GameObj *obj);
        virtual void DoCollision(GameObj *obj) {}
        virtual void Explode() {}
        //unit vector in facing direction
        Point3f UnitVectorFacing();
        Point3f UnitVectorVelocity();
        enum //collision flags/object types
        {
            OBJ_NONE = 0x00000001,
            OBJ_ASTEROID = 0x00000010,
            OBJ_SHIP = 0x00000100,
            OBJ_BULLET = 0x00001000,
            OBJ_EXP = 0x00010000,
            OBJ_POWERUP = 0x00100000,
            OBJ_TARGET = 0x01000000
        };
        //data
        Point3f m_position;
        Point3f m_axis;
        float m_angle;
        Point3f m_velocity;
        float m_angVelocity;
        bool m_active;
        float m_size;
        Sphere3f m_boundSphere;
        int m_type;
        unsigned int m_collisionFlags;
        int m_lifeTimer;
};
