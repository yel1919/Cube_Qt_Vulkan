#ifndef VULKANINSTANCE_H
#define VULKANINSTANCE_H

#include <QApplication>
#include "adapterreader.h"

namespace vk {
    class VulkanInstance : public IVulkanInstance {
    public:
        VulkanInstance();
        VulkanInstance(const VulkanInstance&) = delete;
        VulkanInstance(VulkanInstance&& instance);
        virtual ~VulkanInstance();

        explicit operator const VkInstance() const override;

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
        VulkanInstance& operator=(VulkanInstance&& instance);
    protected:
    private:
        VkInstance vk_instance;
    };
}

#endif // VULKANINSTANCE_H
