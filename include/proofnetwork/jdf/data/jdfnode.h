#ifndef JDFJDFNODE_H
#define JDFJDFNODE_H

#include "proofnetwork/networkdataentity.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/data/qmlwrappers/jdfnodeqmlwrapper.h"

#include <QXmlStreamReader>
#include <QList>

namespace Proof {
namespace Jdf {

class JdfNodePrivate;
class PROOF_NETWORK_JDF_EXPORT JdfNode : public NetworkDataEntity // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(JdfNode)
public:
    QString id() const;
    QString jobId() const;
    QString jobPartId() const;
    AuditPoolSP auditPool() const;
    ResourcePoolSP resourcePool() const;
    ResourceLinkPoolSP resourceLinkPool() const;
    QList<JdfNodeSP> jdfNodes() const;
    QString type() const;
    QStringList types() const;

    void setId(const QString &arg);
    void setJobId(const QString &arg);
    void setJobPartId(const QString &arg);
    void setAuditPool(const AuditPoolSP &arg);
    void setResourcePool(const ResourcePoolSP &arg);
    void setResourceLinkPool(const ResourceLinkPoolSP &arg);
    void setJdfNodes(const QList<JdfNodeSP> &arg);
    void addJdfNode(const JdfNodeSP &arg);
    void setType(const QString &arg);
    void setTypes(const QStringList &arg);

    JdfNodeSP findNode(const std::function<bool (const JdfNodeSP &)> &predicate) const;
    ComponentSP findComponent(const std::function<bool (const Proof::Jdf::ComponentSP &)> &predicate) const;
    ComponentLinkSP findComponentLink(const std::function<bool (const Proof::Jdf::ComponentLinkSP &)> &predicate) const;
    MediaSP findMedia(const std::function<bool (const MediaSP &)> &predicate) const;
    LayoutSP findLayout(const std::function<bool (const LayoutSP &)> &predicate) const;

    QList<JdfNodeSP> findAllNodes(const std::function<bool (const JdfNodeSP &)> &predicate) const;
    QList<ComponentSP> findAllComponents(const std::function<bool (const Proof::Jdf::ComponentSP &)> &predicate) const;
    QList<ComponentLinkSP> findAllComponentLinks(const std::function<bool (const Proof::Jdf::ComponentLinkSP &)> &predicate) const;
    QList<MediaSP> findAllMedia(const std::function<bool (const MediaSP &)> &predicate) const;
    QList<LayoutSP> findAllLayouts(const std::function<bool (const LayoutSP &)> &predicate) const;

    JdfNodeQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static JdfNodeSP create();

    static JdfNodeSP fromJdf(QXmlStreamReader &xmlReader, const QStringList &alternativeIdAttributes = QStringList(), bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter, bool rootNode = false);

signals:
    void idChanged(const QString &arg);
    void jobIdChanged(const QString &arg);
    void jobPartIdChanged(const QString &arg);
    void auditPoolChanged(const Proof::Jdf::AuditPoolSP &arg);
    void resourcePoolChanged(const Proof::Jdf::ResourcePoolSP &arg);
    void resourceLinkPoolChanged(const Proof::Jdf::ResourceLinkPoolSP &resourceLinkPool);
    void jdfNodesChanged();
    void typeChanged(const QString &type);
    void typesChanged(const QStringList &types);

protected:
    JdfNode();
    JdfNode(JdfNodePrivate &dd, QObject *parent = nullptr);
    void update(const JdfNodeSP &other);

};

}
}

#endif // JDFJDFNODE_H
