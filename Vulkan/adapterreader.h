#ifndef ADAPTERREADER_H
#define ADAPTERREADER_H

#include "ivulkaninstance.h"

namespace vk {
    class AdapterData {
    public:
        explicit AdapterData(VkPhysicalDevice adapter);
        AdapterData(const AdapterData& data);
        AdapterData(AdapterData&& data);
        virtual ~AdapterData() {}

        AdapterData& operator=(const AdapterData& data);
        AdapterData& operator=(AdapterData&& data);

        const VkPhysicalDevice adapter() const;
        const VkPhysicalDeviceProperties& properties() const;
        const VkPhysicalDeviceFeatures& features() const;
    protected:
    private:
        VkPhysicalDevice _adapter;
        VkPhysicalDeviceProperties _properties;
        VkPhysicalDeviceFeatures _features;
    };

    class AdapterReader {
    public:
        static void read(const IVulkanInstance& vk_inst, QVector<AdapterData>* data);
    protected:
    private:
    };
}

#endif // ADAPTERREADER_H
