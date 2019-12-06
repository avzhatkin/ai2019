#include "Properties.hpp"

Properties::Properties() { }
Properties::Properties(int maxTickCount, int teamSize, double ticksPerSecond, int updatesPerTick, Vec2Double lootBoxSize, Vec2Double unitSize, double unitMaxHorizontalSpeed, double unitFallSpeed, double unitJumpTime, double unitJumpSpeed, double jumpPadJumpTime, double jumpPadJumpSpeed, int unitMaxHealth, int healthPackHealth, std::unordered_map<WeaponType, WeaponParams> weaponParams, Vec2Double mineSize, ExplosionParams mineExplosionParams, double minePrepareTime, double mineTriggerTime, double mineTriggerRadius, int killScore) : maxTickCount(maxTickCount), teamSize(teamSize), ticksPerSecond(ticksPerSecond), updatesPerTick(updatesPerTick), lootBoxSize(lootBoxSize), unitSize(unitSize), unitMaxHorizontalSpeed(unitMaxHorizontalSpeed), unitFallSpeed(unitFallSpeed), unitJumpTime(unitJumpTime), unitJumpSpeed(unitJumpSpeed), jumpPadJumpTime(jumpPadJumpTime), jumpPadJumpSpeed(jumpPadJumpSpeed), unitMaxHealth(unitMaxHealth), healthPackHealth(healthPackHealth), weaponParams(weaponParams), mineSize(mineSize), mineExplosionParams(mineExplosionParams), minePrepareTime(minePrepareTime), mineTriggerTime(mineTriggerTime), mineTriggerRadius(mineTriggerRadius), killScore(killScore) { }
Properties Properties::readFrom(InputStream& stream) {
    Properties result;
    result.maxTickCount = stream.readInt();
    result.teamSize = stream.readInt();
    result.ticksPerSecond = stream.readDouble();
    result.updatesPerTick = stream.readInt();
    result.lootBoxSize = Vec2Double::readFrom(stream);
    result.unitSize = Vec2Double::readFrom(stream);
    result.unitMaxHorizontalSpeed = stream.readDouble();
    result.unitFallSpeed = stream.readDouble();
    result.unitJumpTime = stream.readDouble();
    result.unitJumpSpeed = stream.readDouble();
    result.jumpPadJumpTime = stream.readDouble();
    result.jumpPadJumpSpeed = stream.readDouble();
    result.unitMaxHealth = stream.readInt();
    result.healthPackHealth = stream.readInt();
    size_t weaponParamsSize = stream.readInt();
    result.weaponParams = std::unordered_map<WeaponType, WeaponParams>();
    result.weaponParams.reserve(weaponParamsSize);
    for (size_t i = 0; i < weaponParamsSize; i++) {
        WeaponType weaponParamsKey;
        switch (stream.readInt()) {
        case 0:
            weaponParamsKey = WeaponType::PISTOL;
            break;
        case 1:
            weaponParamsKey = WeaponType::ASSAULT_RIFLE;
            break;
        case 2:
            weaponParamsKey = WeaponType::ROCKET_LAUNCHER;
            break;
        default:
            throw std::runtime_error("Unexpected discriminant value");
        }
        WeaponParams weaponParamsValue;
        weaponParamsValue = WeaponParams::readFrom(stream);
        result.weaponParams.emplace(std::make_pair(weaponParamsKey, weaponParamsValue));
    }
    result.mineSize = Vec2Double::readFrom(stream);
    result.mineExplosionParams = ExplosionParams::readFrom(stream);
    result.minePrepareTime = stream.readDouble();
    result.mineTriggerTime = stream.readDouble();
    result.mineTriggerRadius = stream.readDouble();
    result.killScore = stream.readInt();
    return result;
}
void Properties::writeTo(OutputStream& stream) const {
    stream.write(maxTickCount);
    stream.write(teamSize);
    stream.write(ticksPerSecond);
    stream.write(updatesPerTick);
    lootBoxSize.writeTo(stream);
    unitSize.writeTo(stream);
    stream.write(unitMaxHorizontalSpeed);
    stream.write(unitFallSpeed);
    stream.write(unitJumpTime);
    stream.write(unitJumpSpeed);
    stream.write(jumpPadJumpTime);
    stream.write(jumpPadJumpSpeed);
    stream.write(unitMaxHealth);
    stream.write(healthPackHealth);
    stream.write((int)(weaponParams.size()));
    for (const auto& weaponParamsEntry : weaponParams) {
        stream.write((int)(weaponParamsEntry.first));
        weaponParamsEntry.second.writeTo(stream);
    }
    mineSize.writeTo(stream);
    mineExplosionParams.writeTo(stream);
    stream.write(minePrepareTime);
    stream.write(mineTriggerTime);
    stream.write(mineTriggerRadius);
    stream.write(killScore);
}
static std::string kv(const std::string&k,const std::string&v){return "\""+k+"\":"+v;}
std::string Properties::toString() const {
  std::string wp;
  std::string t2s[]={"Pistol","AssaultRifle","RocketLauncher"};
  for(const auto&ex:weaponParams){
    wp+=kv(t2s[ex.first],ex.second.toString())+",";
  }
  wp.pop_back();
  return "{" +
    #define F(NAME)kv(#NAME,std::to_string(NAME))
    #define G(NAME)kv(#NAME,NAME.toString())
    F(maxTickCount) + "," +
    F(teamSize) + "," +
    F(ticksPerSecond) + "," +
    F(updatesPerTick) + "," +
    G(lootBoxSize) + "," +
    G(unitSize) + "," +
    F(unitMaxHorizontalSpeed) + "," +
    F(unitFallSpeed) + "," +
    F(unitJumpTime) + "," +
    F(unitJumpSpeed) + "," +
    F(jumpPadJumpTime) + "," +
    F(jumpPadJumpSpeed) + "," +
    F(unitMaxHealth) + "," +
    F(healthPackHealth) + "," +
    kv("weapon_params","{"+wp+"}") + "," +
    G(mineSize) + "," +
    G(mineExplosionParams) + "," +
    F(minePrepareTime) + "," +
    F(mineTriggerTime) + "," +
    F(mineTriggerRadius) + "," +
    F(killScore) +
  "}";
}
