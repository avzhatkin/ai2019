#include "BulletParams.hpp"

BulletParams::BulletParams() { }
BulletParams::BulletParams(double speed, double size, int damage) : speed(speed), size(size), damage(damage) { }
BulletParams BulletParams::readFrom(InputStream& stream) {
    BulletParams result;
    result.speed = stream.readDouble();
    result.size = stream.readDouble();
    result.damage = stream.readInt();
    return result;
}
void BulletParams::writeTo(OutputStream& stream) const {
    stream.write(speed);
    stream.write(size);
    stream.write(damage);
}
static std::string kv(const std::string&k,const std::string&v){return "\""+k+"\":"+v;}
std::string BulletParams::toString() const {
  #define F(NAME)kv(#NAME,std::to_string(NAME))
  #define G(NAME)kv(#NAME,NAME.toString())
  return "{"+
    F(speed) + "," +
    F(size) + "," +
    F(damage) +
  "}";
}
