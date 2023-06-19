#ifndef IVULKANINSTANCE_H
#define IVULKANINSTANCE_H

#include <QList>
#include <QVector>
#include <vulkan/vulkan.h>

namespace vk {
    class IVulkanInstance {
    public:
        virtual explicit operator const VkInstance() const = 0;
    };
}

#endif // IVULKANINSTANCE_H
