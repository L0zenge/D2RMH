/*
 * Copyright (c) 2021 Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "jsonlng.h"

#include "json/json.hpp"

#include <fstream>

bool JsonLng::load(const std::string &filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) { return false; }
    nlohmann::json j;
    ifs >> j;
    ifs.close();
    for (auto j2: j) {
        auto &arr = strings_[j2["Key"].get<std::string>()];
        arr[LNG_enUS] = j2["enUS"].get<std::string>();
        arr[LNG_zhTW] = j2["zhTW"].get<std::string>();
        arr[LNG_deDE] = j2["deDE"].get<std::string>();
        arr[LNG_esES] = j2["esES"].get<std::string>();
        arr[LNG_frFR] = j2["frFR"].get<std::string>();
        arr[LNG_itIT] = j2["itIT"].get<std::string>();
        arr[LNG_koKR] = j2["koKR"].get<std::string>();
        arr[LNG_plPL] = j2["plPL"].get<std::string>();
        arr[LNG_esMX] = j2["esMX"].get<std::string>();
        arr[LNG_jaJP] = j2["jaJP"].get<std::string>();
        arr[LNG_ptBR] = j2["ptBR"].get<std::string>();
        arr[LNG_ruRU] = j2["ruRU"].get<std::string>();
        arr[LNG_zhCN] = j2["zhCN"].get<std::string>();
    }
    return true;
}

const std::string &JsonLng::get(const std::string &key, JsonLng::LNG lang, JsonLng::LNG fallback) {
    auto ite = strings_.find(key);
    if (ite == strings_.end()) {
        static std::string empty; return empty;
    }
    const auto &result = ite->second[lang];
    if (!result.empty()) { return result; }
    return ite->second[fallback];
}

const std::array<std::string, JsonLng::LNG_MAX> *JsonLng::get(const std::string &key) {
    auto ite = strings_.find(key);
    if (ite == strings_.end()) { return nullptr; }
    return &ite->second;
}
