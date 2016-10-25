#include "devicefilter.h"

#include "proofnetwork/networkdataentity_p.h"
#include "proofnetwork/jdf/apihelper.h"

namespace Proof {
namespace Jdf {

class DeviceFilterPrivate : public NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(DeviceFilter)

    void updateFrom(const Proof::NetworkDataEntitySP &other) override;

    ApiHelper::DeviceFilterDetails details = ApiHelper::DeviceFilterDetails::NoneDeviceFilterDetails;
};

ApiHelper::DeviceFilterDetails DeviceFilter::details() const
{
    Q_D(const DeviceFilter);
    return d->details;
}

void DeviceFilter::setDetails(ApiHelper::DeviceFilterDetails arg)
{
    Q_D(DeviceFilter);
    if (d->details != arg) {
        d->details = arg;
        emit detailsChanged(d->details);
    }
}

NetworkDataEntityQmlWrapper *DeviceFilter::toQmlWrapper(QObject *) const
{
    Q_ASSERT(false);
    return nullptr;
}

DeviceFilterSP DeviceFilter::create()
{
    DeviceFilterSP result(new DeviceFilter());
    initSelfWeakPtr(result);
    return result;
}

void DeviceFilter::toJmf(QXmlStreamWriter &xmlWriter)
{
    xmlWriter.writeStartElement("DeviceFilter");
    xmlWriter.writeAttribute("DeviceDetails", ApiHelper::deviceFilterDetailsToString(details()));
    xmlWriter.writeEndElement();
}

DeviceFilterSP DeviceFilter::fromJmf(QXmlStreamReader &xmlReader)
{
    DeviceFilterSP result;
    if (xmlReader.isStartElement() && xmlReader.name() == "DeviceFilter") {
        result = create();
        result->setFetched(true);
        auto attributes = xmlReader.attributes();
        result->setDetails(ApiHelper::deviceFilterDetailsFromString(attributes.value("DeviceDetails").toString()));
        xmlReader.skipCurrentElement();
    }
    return result;
}

DeviceFilter::DeviceFilter()
    : NetworkDataEntity(*new DeviceFilterPrivate)
{
}

void DeviceFilterPrivate::updateFrom(const NetworkDataEntitySP &other)
{
    Q_Q(DeviceFilter);
    DeviceFilterSP castedOther = qSharedPointerCast<DeviceFilter>(other);
    q->setDetails(castedOther->details());
    NetworkDataEntityPrivate::updateFrom(other);
}

} // namespace Jdf
} // namespace Proof
