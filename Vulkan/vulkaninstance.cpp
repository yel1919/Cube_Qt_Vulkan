#include "vulkaninstance.h"
using vk::VulkanInstance;

VulkanInstance::VulkanInstance()
    :
      vk_instance(VK_NULL_HANDLE)
{}

VulkanInstance::VulkanInstance(VulkanInstance&& instance) {
    vk_instance = instance.vk_instance;
    instance.vk_instance = VK_NULL_HANDLE;
}

VulkanInstance::~VulkanInstance() {
    Destroy();
}

VulkanInstance& VulkanInstance::operator=(VulkanInstance&& instance) {
    if (this != &instance) {
        std::swap(vk_instance, instance.vk_instance);
    }
    return *this;
}

/**Get supported extension properties
*@params
*@return vector supported extension properties
*/
QVector<VkExtensionProperties> VulkanInstance::supportedExtensions() const {
    QVector<VkExtensionProperties> availableExtensions{};
    uint instanceExtensionsCount = 0;

    vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionsCount, nullptr);

    if(instanceExtensionsCount == 0) return availableExtensions;

    availableExtensions.resize(instanceExtensionsCount);
    vkEnumerateInstanceExtensionProperties(
                nullptr,
                &instanceExtensionsCount,
                availableExtensions.data()
    );

    return availableExtensions;
}

/**Get supported layer properties
*@params
*@return vector supported layer properties
*/
QVector<VkLayerProperties> VulkanInstance::supportedLayers() const {
    QVector<VkLayerProperties> availableLayers{};
    uint instanceLayersCount = 0;

    vkEnumerateInstanceLayerProperties(&instanceLayersCount, nullptr);

    if(instanceLayersCount == 0) return availableLayers;

    availableLayers.resize(instanceLayersCount);
    vkEnumerateInstanceLayerProperties(
                &instanceLayersCount,
                availableLayers.data()
    );

    return availableLayers;
}

/**Check the requested extensions are supported
*@params extensionNames - vector of requested extension names
*@return true or false
*/
bool VulkanInstance::CheckInstanceExtensionsSupported(const QVector<const QByteArray>& extensionNames) const {
    QVector<VkExtensionProperties> availableExtensions = supportedExtensions();

    if(availableExtensions.empty()) return false;

    for(const QByteArray& reqieredExtName : extensionNames) {
        if(
                std::find_if(
                    availableExtensions.begin(),
                    availableExtensions.end(),
                    [reqieredExtName](const VkExtensionProperties& extProperties) {
                        return reqieredExtName == QString::fromLocal8Bit(extProperties.extensionName);
                    }
                ) == availableExtensions.end()
        ) {
            return false;
        }
    }

    return true;
}

/**Check the requested layers are supported
*@params layerNames - vector of requested layer names
*@return true or false
*/
bool VulkanInstance::CheckInstanceLayersSupported(const QVector<const QByteArray>& layerNames) const {
    QVector<VkLayerProperties> validationLayerProperties = supportedLayers();

    if(validationLayerProperties.empty()) return false;

    for(const QByteArray& layerName : layerNames) {
        if(
                std::find_if(
                    validationLayerProperties.begin(),
                    validationLayerProperties.end(),
                    [layerName](const VkLayerProperties& layerInfo) {
                        return layerName == QString::fromLocal8Bit(layerInfo.layerName);
                    }
                ) == validationLayerProperties.end()
        ) {
            return false;
        }
    }

    return true;
}

/**Create vulkan instance
*@params:
*engineName
*extensionRequired - vector of requested extension names
*validationLayersRequired - vector of requested validation layer names
*@return true or false
*/
bool VulkanInstance::Create(
        const QString& engineName,
        const QVector<const QByteArray>& extensionRequired,
        const QVector<const QByteArray>& validationLayersRequired
) {
    VkApplicationInfo appInfo {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = QApplication::applicationName().toLocal8Bit().data(),
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = engineName.toLocal8Bit().data(),
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0
    };

    VkInstanceCreateInfo createInfo {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo
    };

    if(!extensionRequired.empty()) {
        if(CheckInstanceExtensionsSupported(extensionRequired)) {
            createInfo.enabledExtensionCount = (uint32_t)extensionRequired.size();
            createInfo.ppEnabledExtensionNames = (char**)extensionRequired.data();
        }
    }

    if(!validationLayersRequired.empty()) {
        if(CheckInstanceLayersSupported(validationLayersRequired)) {
            createInfo.enabledLayerCount = (uint32_t)validationLayersRequired.size();
            createInfo.ppEnabledLayerNames = (char**)validationLayersRequired.data();
        }
    }

    if(vkCreateInstance(&createInfo, nullptr, &vk_instance) != VK_SUCCESS) return false;

    return true;
}

/**Destroy vulkan instance
*@params
*@return
*/
void VulkanInstance::Destroy() {
    vkDestroyInstance(vk_instance, nullptr);
}
