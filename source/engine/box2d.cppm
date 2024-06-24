module;
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

export module atom.engine:box2d;

export
{
    using ::b2Body;
    using ::b2BodyDef;
    using ::b2BodyType;
    using ::b2Fixture;
    using ::b2FixtureDef;
    using ::b2PolygonShape;
    using ::b2Vec2;
    using ::b2World;
}
