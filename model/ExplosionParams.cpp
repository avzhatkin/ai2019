#include "ExplosionParams.hpp"

ExplosionParams::ExplosionParams() { }
ExplosionParams::ExplosionParams(double radius, int damage) : radius(radius), damage(damage) { }
ExplosionParams ExplosionParams::readFrom(InputStream& stream) {
    ExplosionParams result;
    result.radius = stream.readDouble();
    result.damage = stream.readInt();
    return result;
}
void ExplosionParams::writeTo(OutputStream& stream) const {
    stream.write(radius);
    stream.write(damage);
}
static std::string kv(const std::string&k,const std::string&v){return "\""+k+"\":"+v;}
std::string ExplosionParams::toString() const {
  #define F(NAME)kv(#NAME,std::to_string(NAME))
  #define G(NAME)kv(#NAME,NAME.toString())
  return "{" +
    F(radius) + "," +
    F(damage) +
  "}";
}
