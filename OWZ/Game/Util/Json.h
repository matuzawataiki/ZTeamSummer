#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>

namespace nsk2Engine
{
    inline nlohmann::json LoadScene(const std::string& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return nlohmann::json();
        }

        nlohmann::json jsonRoot;
        file >> jsonRoot;

        return jsonRoot;
    }

}