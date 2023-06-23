#include "adapterreader.h"
using vk::AdapterData;
using vk::AdapterReader;

AdapterData::AdapterData(VkPhysicalDevice adapter)
    :
      _adapter(adapter),
      _properties(),
      _features()
{
    if(_adapter != VK_NULL_HANDLE) {
        vkGetPhysicalDeviceProperties(_adapter, &_properties);
        vkGetPhysicalDeviceFeatures(_adapter, &_features);
    }
}

AdapterData::AdapterData(const AdapterData& data)
    :
      _adapter(data._adapter),
      _properties(data._properties),
      _features(data._features)
{}

AdapterData::AdapterData(AdapterData&& data) {
    std::swap(_adapter, data._adapter);
    std::swap(_properties, data._properties);
    std::swap(_features, data._features);
}

AdapterData& AdapterData::operator=(const AdapterData& data) {
    if(this != &data) {
        _adapter = data._adapter;
        _properties = data._properties;
        _features = data._features;
    }
    return *this;
}

AdapterData& AdapterData::operator=(AdapterData&& data) {
    if(this != &data) {
        std::swap(_adapter, data._adapter);
        std::swap(_properties, data._properties);
        std::swap(_features, data._features);
    }
    return *this;
}

const VkPhysicalDevice AdapterData::adapter() const {
    return _adapter;
}

const VkPhysicalDeviceProperties& AdapterData::properties() const {
    return _properties;
}

const VkPhysicalDeviceFeatures& AdapterData::features() const {
    return _features;
}

void AdapterReader::read(const IVulkanInstance& vk_inst, QVector<AdapterData>* data) {
    if(data == nullptr)
        return;

    if(!data->empty())
        data->clear();

    uint32_t deviceCount = 0;
    if(vkEnumeratePhysicalDevices((VkInstance)vk_inst, &deviceCount, nullptr) != VK_SUCCESS) return;

    data->reserve(deviceCount);

    QVector<VkPhysicalDevice> devices(deviceCount);
    if(vkEnumeratePhysicalDevices((VkInstance)vk_inst, &deviceCount, devices.data()) != VK_SUCCESS) return;

    for (int index = 0; index < deviceCount; ++index) {
        data->emplace_back((AdapterData)(devices[index]));
    }
}
