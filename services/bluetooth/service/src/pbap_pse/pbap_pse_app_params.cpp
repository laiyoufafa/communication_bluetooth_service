/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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
 */

#include "pbap_pse_app_params.h"
#include <cstring>
#include "pbap_pse_def.h"

namespace OHOS {
namespace bluetooth {
const std::map<uint8_t, int> PbapPseAppParams::LENS_MAP = {
    {ORDER, 1},
    {SEARCH_VALUE, -1},
    {SEARCH_PROPERTY, 1},
    {MAX_LIST_COUNT, 2},
    {LIST_START_OFFSET, 2},
    {PROPERTY_SELECTOR, 8},
    {FORMAT, 1},
    {PHONEBOOK_SIZE, 2},
    {NEW_MISSED_CALLS, 1},
    {PRIMARY_FOLDER_VERSION, 16},
    {SECONDARY_FOLDER_VERSION, 16},
    {VCARD_SELECTOR, 8},
    {DATABASE_IDENTIFIER, 16},
    {VCARD_SELECTOR_OPERATOR, 1},
    {RESET_NEW_MISSED_CALLS, 1},
    {PBAP_SUPPORTED_FEATURES, 4}
};

bool PbapPseAppParams::CheckParams(const ObexTlvParamters &obexTlvParamters)
{
    for (auto &tlv : obexTlvParamters.GetTlvTriplets()) {
        if (LENS_MAP.find(tlv->GetTagId()) == LENS_MAP.end()) {
            PBAP_PSE_LOG_ERROR("unknow Application Parameters header : %x", tlv->GetTagId());
            return false;
        }
        int expectLen = LENS_MAP.at(tlv->GetTagId());
        if (expectLen != -1 && expectLen != tlv->GetLen()) {
            PBAP_PSE_LOG_ERROR("Wrong Application Parameters header Length for TagId[%{public}x]:expect "
                "is [%{public}d], actual is [%{public}u].", tlv->GetTagId(), expectLen, tlv->GetLen());
            return false;
        }
    }
    return true;
}

bool PbapPseAppParams::Init(const ObexTlvParamters &obexTlvParamters)
{
    if (!CheckParams(obexTlvParamters)) {
        return false;
    }
    SetOrderTlv(obexTlvParamters);
    SetSearchValueUtf8Tlv(obexTlvParamters);
    SetSearchPropertyTlv(obexTlvParamters);
    SetMaxListCountTlv(obexTlvParamters);
    SetListStartOffsetTlv(obexTlvParamters);
    SetPropertySelectorTlv(obexTlvParamters);
    SetFormatTlv(obexTlvParamters);
    SetPhonebookSizeTlv(obexTlvParamters);
    SetNewMissedCallsTlv(obexTlvParamters);
    SetPrimaryFolderVersionTlv(obexTlvParamters);
    SetSecondaryFolderVersionTlv(obexTlvParamters);
    SetVcardSelectorTlv(obexTlvParamters);
    SetDatabaseIdentifierTlv(obexTlvParamters);
    SetVcardSelectorOperatorTlv(obexTlvParamters);
    SetResetNewMissedCallsTlv(obexTlvParamters);
    SetPbapSupportedFeaturesTlv(obexTlvParamters);
    return true;
}

void PbapPseAppParams::AddToObexHeader(ObexHeader &hdr) const
{
    ObexTlvParamters obexTlvParamters;
    AddTlvOrder(obexTlvParamters);
    AddTlvSearchValueUtf8(obexTlvParamters);
    AddTlvSearchProperty(obexTlvParamters);
    AddTlvMaxListCount(obexTlvParamters);
    AddTlvListStartOffAddTlv(obexTlvParamters);
    AddTlvPropertySelector(obexTlvParamters);
    AddTlvFormat(obexTlvParamters);
    AddTlvPhonebookSize(obexTlvParamters);
    AddTlvNewMissedCalls(obexTlvParamters);
    AddTlvPrimaryFolderVersion(obexTlvParamters);
    AddTlvSecondaryFolderVersion(obexTlvParamters);
    AddTlvVcardSelector(obexTlvParamters);
    AddTlvDatabaseIdentifier(obexTlvParamters);
    AddTlvVcardSelectorOperator(obexTlvParamters);
    AddTlvReAddTlvNewMissedCalls(obexTlvParamters);
    AddTlvPbapSupportedFeatures(obexTlvParamters);
    if (obexTlvParamters.GetTlvTriplets().size() > 0) {
        hdr.AppendItemAppParams(obexTlvParamters);
    }
}

const uint8_t *PbapPseAppParams::GetOrder() const
{
    if (!order_) {
        return nullptr;
    }
    return order_.get();
}

const std::vector<uint8_t> &PbapPseAppParams::GetSearchValueUtf8() const
{
    return searchValueUtf8_;
}

const uint8_t *PbapPseAppParams::GetSearchProperty() const
{
    if (!searchProperty_) {
        return nullptr;
    }
    return searchProperty_.get();
}

const uint16_t *PbapPseAppParams::GetMaxListCount() const
{
    if (!maxListCount_) {
        return nullptr;
    }
    return maxListCount_.get();
}

const uint16_t *PbapPseAppParams::GetListStartOffset() const
{
    if (!listStartOffset_) {
        return nullptr;
    }
    return listStartOffset_.get();
}

const uint64_t *PbapPseAppParams::GetPropertySelector() const
{
    if (!propertySelector_) {
        return nullptr;
    }
    return propertySelector_.get();
}

const uint8_t *PbapPseAppParams::GetFormat() const
{
    if (!format_) {
        return nullptr;
    }
    return format_.get();
}

const uint16_t *PbapPseAppParams::GetPhonebookSize() const
{
    if (!phonebookSize_) {
        return nullptr;
    }
    return phonebookSize_.get();
}

const uint8_t *PbapPseAppParams::GetNewMissedCalls() const
{
    if (!newMissedCalls_) {
        return nullptr;
    }
    return newMissedCalls_.get();
}

const std::vector<uint8_t> &PbapPseAppParams::GetPrimaryFolderVersion() const
{
    return primaryFolderVer_;
}

const std::vector<uint8_t> &PbapPseAppParams::GetSecondaryFolderVersion() const
{
    return secondaryFolderVer_;
}

const uint64_t *PbapPseAppParams::GetVcardSelector() const
{
    if (!vcardSelector_) {
        return nullptr;
    }
    return vcardSelector_.get();
}

const std::vector<uint8_t> &PbapPseAppParams::GetDatabaseIdentifier() const
{
    return databaseIdentifier_;
}

const uint8_t *PbapPseAppParams::GetVcardSelectorOperator() const
{
    if (!vcardSelectorOp_) {
        return nullptr;
    }
    return vcardSelectorOp_.get();
}

const uint8_t *PbapPseAppParams::GetResetNewMissedCalls() const
{
    if (!resetNewMissedCalls_) {
        return nullptr;
    }
    return resetNewMissedCalls_.get();
}

const uint32_t *PbapPseAppParams::GetPbapSupportedFeatures() const
{
    if (!pbapSupportedFeatures_) {
        return nullptr;
    }
    return pbapSupportedFeatures_.get();
}

void PbapPseAppParams::SetOrder(uint8_t val)
{
    if (!order_) {
        order_ = std::make_unique<uint8_t>();
    }
    *order_ = val;
}

void PbapPseAppParams::SetSearchValueUtf8(const std::vector<uint8_t> &val)
{
    searchValueUtf8_ = val;
}

void PbapPseAppParams::SetSearchProperty(uint8_t val)
{
    if (!searchProperty_) {
        searchProperty_ = std::make_unique<uint8_t>();
    }
    *searchProperty_ = val;
}

void PbapPseAppParams::SetMaxListCount(uint16_t val)
{
    if (!maxListCount_) {
        maxListCount_ = std::make_unique<uint16_t>();
    }
    *maxListCount_ = val;
}

void PbapPseAppParams::SetListStartOffset(uint16_t val)
{
    if (!listStartOffset_) {
        listStartOffset_ = std::make_unique<uint16_t>();
    }
    *listStartOffset_ = val;
}

void PbapPseAppParams::SetPropertySelector(uint64_t val)
{
    if (!propertySelector_) {
        propertySelector_ = std::make_unique<uint64_t>();
    }
    *propertySelector_ = val;
}

void PbapPseAppParams::SetFormat(uint8_t val)
{
    if (!format_) {
        format_ = std::make_unique<uint8_t>();
    }
    *format_ = val;
}

void PbapPseAppParams::SetPhonebookSize(uint16_t val)
{
    if (!phonebookSize_) {
        phonebookSize_ = std::make_unique<uint16_t>();
    }
    *phonebookSize_ = val;
}

void PbapPseAppParams::SetNewMissedCalls(uint8_t val)
{
    if (!newMissedCalls_) {
        newMissedCalls_ = std::make_unique<uint8_t>();
    }
    *newMissedCalls_ = val;
}

void PbapPseAppParams::SetPrimaryFolderVersion(const std::vector<uint8_t> &val)
{
    primaryFolderVer_ = val;
}

void PbapPseAppParams::SetSecondaryFolderVersion(const std::vector<uint8_t> &val)
{
    secondaryFolderVer_ = val;
}

void PbapPseAppParams::SetVcardSelector(uint64_t val)
{
    if (!vcardSelector_) {
        vcardSelector_ = std::make_unique<uint64_t>();
    }
    *vcardSelector_ = val;
}

void PbapPseAppParams::SetDatabaseIdentifier(const std::vector<uint8_t> &val)
{
    databaseIdentifier_ = val;
}

void PbapPseAppParams::SetVcardSelectorOperator(uint8_t val)
{
    if (!vcardSelectorOp_) {
        vcardSelectorOp_ = std::make_unique<uint8_t>();
    }
    *vcardSelectorOp_ = val;
}

void PbapPseAppParams::SetResetNewMissedCalls(uint8_t val)
{
    if (!resetNewMissedCalls_) {
        resetNewMissedCalls_ = std::make_unique<uint8_t>();
    }
    *resetNewMissedCalls_ = val;
}

void PbapPseAppParams::SetPbapSupportedFeatures(uint32_t val)
{
    if (!pbapSupportedFeatures_) {
        pbapSupportedFeatures_ = std::make_unique<uint32_t>();
    }
    *pbapSupportedFeatures_ = val;
}

void PbapPseAppParams::SetOrderTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(ORDER);
    if (tlv != nullptr) {
        SetOrder(*tlv->GetVal());
    }
}

void PbapPseAppParams::SetSearchValueUtf8Tlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(SEARCH_VALUE);
    if (tlv != nullptr) {
        std::vector<uint8_t> datas(tlv->GetVal(), tlv->GetVal() + tlv->GetLen());
        SetSearchValueUtf8(datas);
    }
}

void PbapPseAppParams::SetSearchPropertyTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(SEARCH_PROPERTY);
    if (tlv != nullptr) {
        SetSearchProperty(*tlv->GetVal());
    }
}

void PbapPseAppParams::SetMaxListCountTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(MAX_LIST_COUNT);
    if (tlv != nullptr) {
        SetMaxListCount(tlv->GetUint16());
    }
}

void PbapPseAppParams::SetListStartOffsetTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(LIST_START_OFFSET);
    if (tlv != nullptr) {
        SetListStartOffset(tlv->GetUint16());
    }
}

void PbapPseAppParams::SetPropertySelectorTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(PROPERTY_SELECTOR);
    if (tlv != nullptr) {
        SetPropertySelector(tlv->GetUint64());
    }
}

void PbapPseAppParams::SetFormatTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(FORMAT);
    if (tlv != nullptr) {
        SetFormat(*tlv->GetVal());
    }
}

void PbapPseAppParams::SetPhonebookSizeTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(PHONEBOOK_SIZE);
    if (tlv != nullptr) {
        SetPhonebookSize(tlv->GetUint16());
    }
}

void PbapPseAppParams::SetNewMissedCallsTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(NEW_MISSED_CALLS);
    if (tlv != nullptr) {
        SetNewMissedCalls(*tlv->GetVal());
    }
}

void PbapPseAppParams::SetPrimaryFolderVersionTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(PRIMARY_FOLDER_VERSION);
    if (tlv != nullptr) {
        std::vector<uint8_t> datas(tlv->GetVal(), tlv->GetVal() + tlv->GetLen());
        SetPrimaryFolderVersion(datas);
    }
}

void PbapPseAppParams::SetSecondaryFolderVersionTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(SECONDARY_FOLDER_VERSION);
    if (tlv != nullptr) {
        std::vector<uint8_t> datas(tlv->GetVal(), tlv->GetVal() + tlv->GetLen());
        SetSecondaryFolderVersion(datas);
    }
}

void PbapPseAppParams::SetVcardSelectorTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(VCARD_SELECTOR);
    if (tlv != nullptr) {
        SetVcardSelector(tlv->GetUint64());
    }
}

void PbapPseAppParams::SetDatabaseIdentifierTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(DATABASE_IDENTIFIER);
    if (tlv != nullptr) {
        std::vector<uint8_t> datas(tlv->GetVal(), tlv->GetVal() + tlv->GetLen());
        SetDatabaseIdentifier(datas);
    }
}

void PbapPseAppParams::SetVcardSelectorOperatorTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(VCARD_SELECTOR_OPERATOR);
    if (tlv != nullptr) {
        SetVcardSelectorOperator(*tlv->GetVal());
    }
}

void PbapPseAppParams::SetResetNewMissedCallsTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(RESET_NEW_MISSED_CALLS);
    if (tlv != nullptr) {
        SetResetNewMissedCalls(*tlv->GetVal());
    }
}

void PbapPseAppParams::SetPbapSupportedFeaturesTlv(const ObexTlvParamters &obexTlvParamters)
{
    auto tlv = obexTlvParamters.GetTlvtriplet(PBAP_SUPPORTED_FEATURES);
    if (tlv != nullptr) {
        SetPbapSupportedFeatures(tlv->GetUint32());
    }
}

void PbapPseAppParams::AddTlvOrder(ObexTlvParamters &obexTlvParamters) const
{
    if (order_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(ORDER, *order_));
    }
}

void PbapPseAppParams::AddTlvSearchValueUtf8(ObexTlvParamters &obexTlvParamters) const
{
    if (searchValueUtf8_.size() > 0) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(SEARCH_VALUE, searchValueUtf8_.size(), searchValueUtf8_.data()));
    }
}

void PbapPseAppParams::AddTlvSearchProperty(ObexTlvParamters &obexTlvParamters) const
{
    if (searchProperty_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(SEARCH_PROPERTY, *searchProperty_));
    }
}

void PbapPseAppParams::AddTlvMaxListCount(ObexTlvParamters &obexTlvParamters) const
{
    if (maxListCount_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(MAX_LIST_COUNT, *maxListCount_));
    }
}

void PbapPseAppParams::AddTlvListStartOffAddTlv(ObexTlvParamters &obexTlvParamters) const
{
    if (listStartOffset_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(LIST_START_OFFSET, *listStartOffset_));
    }
}

void PbapPseAppParams::AddTlvPropertySelector(ObexTlvParamters &obexTlvParamters) const
{
    if (propertySelector_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(PROPERTY_SELECTOR, *propertySelector_));
    }
}

void PbapPseAppParams::AddTlvFormat(ObexTlvParamters &obexTlvParamters) const
{
    if (format_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(FORMAT, *format_));
    }
}

void PbapPseAppParams::AddTlvPhonebookSize(ObexTlvParamters &obexTlvParamters) const
{
    if (phonebookSize_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(PHONEBOOK_SIZE, *phonebookSize_));
    }
}

void PbapPseAppParams::AddTlvNewMissedCalls(ObexTlvParamters &obexTlvParamters) const
{
    if (newMissedCalls_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(NEW_MISSED_CALLS, *newMissedCalls_));
    }
}

void PbapPseAppParams::AddTlvPrimaryFolderVersion(ObexTlvParamters &obexTlvParamters) const
{
    if (primaryFolderVer_.size() > 0) {
        obexTlvParamters.AppendTlvtriplet(
            TlvTriplet(PRIMARY_FOLDER_VERSION, primaryFolderVer_.size(), primaryFolderVer_.data()));
    }
}

void PbapPseAppParams::AddTlvSecondaryFolderVersion(ObexTlvParamters &obexTlvParamters) const
{
    if (secondaryFolderVer_.size() > 0) {
        obexTlvParamters.AppendTlvtriplet(
            TlvTriplet(SECONDARY_FOLDER_VERSION, secondaryFolderVer_.size(), secondaryFolderVer_.data()));
    }
}

void PbapPseAppParams::AddTlvVcardSelector(ObexTlvParamters &obexTlvParamters) const
{
    if (vcardSelector_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(VCARD_SELECTOR, *vcardSelector_));
    }
}

void PbapPseAppParams::AddTlvDatabaseIdentifier(ObexTlvParamters &obexTlvParamters) const
{
    if (databaseIdentifier_.size() > 0) {
        obexTlvParamters.AppendTlvtriplet(
            TlvTriplet(DATABASE_IDENTIFIER, databaseIdentifier_.size(), databaseIdentifier_.data()));
    }
}

void PbapPseAppParams::AddTlvVcardSelectorOperator(ObexTlvParamters &obexTlvParamters) const
{
    if (vcardSelectorOp_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(VCARD_SELECTOR_OPERATOR, *vcardSelectorOp_));
    }
}

void PbapPseAppParams::AddTlvReAddTlvNewMissedCalls(ObexTlvParamters &obexTlvParamters) const
{
    if (resetNewMissedCalls_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(RESET_NEW_MISSED_CALLS, *resetNewMissedCalls_));
    }
}

void PbapPseAppParams::AddTlvPbapSupportedFeatures(ObexTlvParamters &obexTlvParamters) const
{
    if (pbapSupportedFeatures_ != nullptr) {
        obexTlvParamters.AppendTlvtriplet(TlvTriplet(PBAP_SUPPORTED_FEATURES, *pbapSupportedFeatures_));
    }
}

const uint8_t PbapPseAppParams::ORDER;
const uint8_t PbapPseAppParams::SEARCH_VALUE;
const uint8_t PbapPseAppParams::SEARCH_PROPERTY;
const uint8_t PbapPseAppParams::MAX_LIST_COUNT;
const uint8_t PbapPseAppParams::LIST_START_OFFSET;
const uint8_t PbapPseAppParams::PROPERTY_SELECTOR;
const uint8_t PbapPseAppParams::FORMAT;
const uint8_t PbapPseAppParams::PHONEBOOK_SIZE;
const uint8_t PbapPseAppParams::NEW_MISSED_CALLS;
const uint8_t PbapPseAppParams::PRIMARY_FOLDER_VERSION;
const uint8_t PbapPseAppParams::SECONDARY_FOLDER_VERSION;
const uint8_t PbapPseAppParams::VCARD_SELECTOR;
const uint8_t PbapPseAppParams::DATABASE_IDENTIFIER;
const uint8_t PbapPseAppParams::VCARD_SELECTOR_OPERATOR;
const uint8_t PbapPseAppParams::RESET_NEW_MISSED_CALLS;
const uint8_t PbapPseAppParams::PBAP_SUPPORTED_FEATURES;
}  // namespace bluetooth
}  // namespace OHOS
