#ifndef VULKANINSTANCE_H
#define VULKANINSTANCE_H

#include <QApplication>
#include <QList>
#include <QVector>
#include <vulkan/vulkan.h>
#include <QVulkanInstance>

namespace vk {
    class VulkanInstance {
    public:
        VulkanInstance();
        VulkanInstance(const VulkanInstance&) = delete;
        virtual ~VulkanInstance();

        QVector<VkExtensionProperties> supportedExtensions() const;
        QVector<VkLayerProperties> supportedLayers() const;

        bool CheckInstanceExtensionsSupported(const QVector<const QByteArray>& extensionNames) const;
        bool CheckInstanceLayersSupported(const QVector<const QByteArray>& layerNames) const;

        bool Create(
                const QString& engineName,
                const QVector<const QByteArray>& extensionRequired,
                const QVector<const QByteArray>& validationLayersRequired);
        void Destroy();

        VulkanInstance& operator=(const VulkanInstance&) = delete;
    protected:
    private:
        VkInstance vk_instance;
    };
}

#endif // VULKANINSTANCE_H
