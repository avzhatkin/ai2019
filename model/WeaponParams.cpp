#include "WeaponParams.hpp"

WeaponParams::WeaponParams() { }
WeaponParams::WeaponParams(int magazineSize, double fireRate, double reloadTime, double minSpread, double maxSpread, double recoil, double aimSpeed, BulletParams bullet, std::shared_ptr<ExplosionParams> explosion) : magazineSize(magazineSize), fireRate(fireRate), reloadTime(reloadTime), minSpread(minSpread), maxSpread(maxSpread), recoil(recoil), aimSpeed(aimSpeed), bullet(bullet), explosion(explosion) { }
WeaponParams WeaponParams::readFrom(InputStream& stream) {
    WeaponParams result;
    result.magazineSize = stream.readInt();
    result.fireRate = stream.readDouble();
    result.reloadTime = stream.readDouble();
    result.minSpread = stream.readDouble();
    result.maxSpread = stream.readDouble();
    result.recoil = stream.readDouble();
    result.aimSpeed = stream.readDouble();
    result.bullet = BulletParams::readFrom(stream);
    if (stream.readBool()) {
        result.explosion = std::shared_ptr<ExplosionParams>(new ExplosionParams());
        *result.explosion = ExplosionParams::readFrom(stream);
    } else {
        result.explosion = std::shared_ptr<ExplosionParams>();
    }
    return result;
}
void WeaponParams::writeTo(OutputStream& stream) const {
    stream.write(magazineSize);
    stream.write(fireRate);
    stream.write(reloadTime);
    stream.write(minSpread);
    stream.write(maxSpread);
    stream.write(recoil);
    stream.write(aimSpeed);
    bullet.writeTo(stream);
    if (explosion) {
        stream.write(false);
    } else {
        stream.write(true);
        (*explosion).writeTo(stream);
    }

}
static std::string kv(const std::string&k,const std::string&v){return "\""+k+"\":"+v;}
std::string WeaponParams::toString() const {
  #define F(NAME)kv(#NAME,std::to_string(NAME))
  #define G(NAME)kv(#NAME,NAME.toString())
  return "{"+
    F(magazineSize) + "," +
    F(fireRate) + "," +
    F(reloadTime) + "," +
    F(minSpread) + "," +
    F(maxSpread) + "," +
    F(recoil) + "," +
    F(aimSpeed) + "," +
    G(bullet) + "," +
    kv("explosion",explosion?explosion->toString():"null") +
  "}";
}
