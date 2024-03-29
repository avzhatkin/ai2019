#include "PlayerMessageGame.hpp"


PlayerMessageGame::CustomDataMessage::CustomDataMessage() { }
PlayerMessageGame::CustomDataMessage::CustomDataMessage(std::shared_ptr<CustomData> data) : data(data) { }
PlayerMessageGame::CustomDataMessage PlayerMessageGame::CustomDataMessage::readFrom(InputStream& stream) {
    PlayerMessageGame::CustomDataMessage result;
    result.data = CustomData::readFrom(stream);
    return result;
}
void PlayerMessageGame::CustomDataMessage::writeTo(OutputStream& stream) const {
    stream.write(TAG);
    data->writeTo(stream);
}
std::string PlayerMessageGame::CustomDataMessage::toString() const {
    return std::string("PlayerMessageGame::CustomDataMessage") + "(" +
        data->toString() +
        ")";
}

PlayerMessageGame::ActionMessage::ActionMessage() { }
PlayerMessageGame::ActionMessage::ActionMessage(std::unordered_map<int, UnitAction> action) : action(action) { }
PlayerMessageGame::ActionMessage PlayerMessageGame::ActionMessage::readFrom(InputStream& stream) {
    PlayerMessageGame::ActionMessage result;
    size_t actionSize = stream.readInt();
    result.action = std::unordered_map<int, UnitAction>();
    result.action.reserve(actionSize);
    for (size_t i = 0; i < actionSize; i++) {
        int actionKey;
        actionKey = stream.readInt();
        UnitAction actionValue;
        actionValue = UnitAction::readFrom(stream);
        result.action.emplace(std::make_pair(actionKey, actionValue));
    }
    return result;
}
void PlayerMessageGame::ActionMessage::writeTo(OutputStream& stream) const {
    stream.write(TAG);
    stream.write((int)(action.size()));
    for (const auto& actionEntry : action) {
        stream.write(actionEntry.first);
        actionEntry.second.writeTo(stream);
    }
}
std::string PlayerMessageGame::ActionMessage::toString() const {
    return std::string("PlayerMessageGame::ActionMessage") + "(" +
        "TODO" + 
        ")";
}
std::shared_ptr<PlayerMessageGame> PlayerMessageGame::readFrom(InputStream& stream) {
    switch (stream.readInt()) {
    case 0:
        return std::shared_ptr<PlayerMessageGame::CustomDataMessage>(new PlayerMessageGame::CustomDataMessage(PlayerMessageGame::CustomDataMessage::readFrom(stream)));
    case 1:
        return std::shared_ptr<PlayerMessageGame::ActionMessage>(new PlayerMessageGame::ActionMessage(PlayerMessageGame::ActionMessage::readFrom(stream)));
    default:
        throw std::runtime_error("Unexpected discriminant value");
    }
};
