#include "jdfdocument.h"
#include "proofnetwork/jdf/data/jdfnode_p.h"

namespace Proof {
namespace Jdf {

class JdfDocumentPrivate : public JdfNodePrivate
{
    Q_DECLARE_PUBLIC(JdfDocument)
};

}
}

using namespace Proof::Jdf;

JdfDocument::JdfDocument()
    : JdfNode(*new JdfDocumentPrivate)
{
}

JdfDocumentQmlWrapper *JdfDocument::toQmlWrapper(QObject *parent) const
{
    Q_D(const JdfDocument);
    JdfDocumentSP castedSelf = qSharedPointerCast<JdfDocument>(d->weakSelf);
    Q_ASSERT(castedSelf);
    return new JdfDocumentQmlWrapper(castedSelf, parent);
}

JdfDocumentSP JdfDocument::create()
{
    JdfDocumentSP result(new JdfDocument());
    initSelfWeakPtr(result);
    return result;
}

JdfDocumentSP JdfDocument::fromJdf(QXmlStreamReader &xmlReader)
{
    JdfDocumentSP document = create();
    JdfNodeSP node = JdfNode::fromJdf(xmlReader);
    document->updateFrom(node);
    return document;
}

QString JdfDocument::toJdf()
{
    QString jdf;
    QXmlStreamWriter jdfWriter(&jdf);

    jdfWriter.setAutoFormatting(true);
    jdfWriter.writeStartDocument();
    jdfWriter.writeDefaultNamespace("http://www.CIP4.org/JDFSchema_1_1");
    JdfNode::toJdf(jdfWriter);
    jdfWriter.writeEndDocument();
    return jdf;
}

