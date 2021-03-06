/*
 * This source file is part of ARK
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2019 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFApp.hpp"
#include "base/AFBus.hpp"
#include "base/AFEnum.hpp"
#include "interface/AFIModule.hpp"

namespace ark {

class AFIBusModule : public AFIModule
{
public:
    // get the app whole name, like app-bus_id
    virtual const std::string GetAppWholeName(const int bus_id) = 0;
    // just get the app name
    virtual const std::string& GetAppName(const ARK_APP_TYPE& app_type) = 0;
    // get app type
    virtual ARK_APP_TYPE GetAppType(const std::string& name) = 0;

    //// get a process info which act a server
    virtual const AFProcConfig& GetSelfProc() = 0;

    virtual ARK_APP_TYPE GetSelfAppType() = 0;
    virtual int GetSelfBusID() = 0;
    virtual const std::string GetSelfBusName() = 0;

    virtual int CombineBusID(const ARK_APP_TYPE app_type, const uint8_t inst_id) = 0;
    virtual const AFRegCenter& GetRegCenter() = 0;

    //virtual uint16_t CalcProcPort(const int bus_id) = 0;

    virtual bool GetTargetBusRelations(std::vector<ARK_APP_TYPE>& target_list) = 0;
};

} // namespace ark
