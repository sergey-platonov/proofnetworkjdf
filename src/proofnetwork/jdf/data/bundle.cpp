#include "bundle.h"

#include "proofnetwork/networkdataentity_p.h"

namespace Proof {
namespace Jdf {

class BundlePrivate : NetworkDataEntityPrivate
{
    Q_DECLARE_PUBLIC(Bundle)

    ApiHelper::BundleType bundleType = ApiHelper::Box;
    int totalAmount = 0;
};

ApiHelper::BundleType Bundle::bundleType() const
{
    Q_D(const Bundle);
    return d->bundleType;
}

int Bundle::totalAmount() const
{
    Q_D(const Bundle);
    return d->totalAmount;
}

void Bundle::setBundleType(ApiHelper::BundleType arg)
{
    Q_D(Bundle);
    if (d->bundleType != arg) {
        d->bundleType = arg;
        emit bundleTypeChanged(arg);
    }
}

void Bundle::setTotalAmount(int arg)
{
    Q_D(Bundle);
    if (d->totalAmount != arg) {
        d->totalAmount = arg;
        emit totalAmountChanged(arg);
    }
}

void Bundle::updateFrom(const NetworkDataEntitySP &other)
{
    BundleSP castedOther = qSharedPointerCast<Bundle>(other);
    setBundleType(castedOther->bundleType());
    setTotalAmount(castedOther->totalAmount());

    NetworkDataEntity::updateFrom(other);
}

BundleQmlWrapper *Bundle::toQmlWrapper(QObject *parent) const
{
    Q_D(const Bundle);
    BundleSP castedSelf = qSharedPointerCast<Bundle>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new BundleQmlWrapper(castedSelf, parent);
}

BundleSP Bundle::create()
{
    BundleSP result(new Bundle());
    result->d_func()->weakSelf = result.toWeakRef();
    return result;
}

BundleSP Bundle::fromJdf(QXmlStreamReader &xmlReader)
{
    BundleSP bundle = create();

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        if (xmlReader.name() == "Bundle" && xmlReader.isStartElement() && ! bundle->isFetched()) {
            bundle->setFetched(true);
            QXmlStreamAttributes attributes = xmlReader.attributes();
            bundle->setBundleType(ApiHelper::bundleTypeFromString(attributes.value("BundleType").toString()));
            bundle->setTotalAmount(attributes.value("TotalAmount").toInt());
        } else if (xmlReader.isStartElement()) {
            uint count = 1;
            while (count && !xmlReader.atEnd() && !xmlReader.hasError()) {
               xmlReader.readNext();
               if (xmlReader.isStartElement())
                   ++count;
               else if (xmlReader.isEndElement())
                   --count;
            }
        } else if (xmlReader.isEndElement()) {
            break;
        }
        xmlReader.readNext();
    }

    return bundle;
}

void Bundle::toJdf(QXmlStreamWriter &jdfWriter)
{
    Q_D(Bundle);
    jdfWriter.writeStartElement("Bundle");
    jdfWriter.writeAttribute("BundleType", ApiHelper::bundleTypeToString(d->bundleType));
    jdfWriter.writeAttribute("TotalAmount", QString::number(d->totalAmount));
    jdfWriter.writeEndElement();
}

BundleSP Bundle::defaultObject()
{
    static BundleSP entity = create();
    return entity;
}

Bundle::Bundle()
    : NetworkDataEntity(*new BundlePrivate)
{
}

} // namespace Jdf
} // namespace Proof