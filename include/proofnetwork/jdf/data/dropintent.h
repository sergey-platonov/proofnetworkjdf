/* Copyright 2018, OpenSoft Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of OpenSoft Inc. nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef JDFDROPINTENT_H
#define JDFDROPINTENT_H

#include "proofnetwork/jdf/apihelper.h"
#include "proofnetwork/jdf/data/abstractresource.h"
#include "proofnetwork/jdf/data/qmlwrappers/dropintentqmlwrapper.h"
#include "proofnetwork/jdf/data/span.h"
#include "proofnetwork/jdf/proofnetworkjdf_global.h"
#include "proofnetwork/jdf/proofnetworkjdf_types.h"

#include <QDateTime>
#include <QXmlStreamReader>

namespace Proof {
namespace Jdf {

class DropIntentPrivate;
class PROOF_NETWORK_JDF_EXPORT DropIntent : public NetworkDataEntity
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DropIntent)
public:
    DropIntent(const DropIntent &) = delete;
    DropIntent &operator=(const DropIntent &) = delete;
    DropIntent(DropIntent &&) = delete;
    DropIntent &operator=(DropIntent &&) = delete;
    ~DropIntent() = default;

    TimeSpan earliest() const;
    DurationSpan earliestDuration() const;
    TimeSpan required() const;
    DurationSpan requiredDuration() const;
    NameSpan returnMethod() const;
    StringSpan serviceLevel() const;
    EnumerationSpan surplusHandling() const;
    EnumerationSpan transfer() const;

    QVector<DropItemIntentSP> dropItemIntents() const;

    void setEarliest(const TimeSpan &arg);
    void setEarliestDuration(const DurationSpan &arg);
    void setRequired(const TimeSpan &arg);
    void setRequiredDuration(const DurationSpan &arg);
    void setReturnMethod(const NameSpan &arg);
    void setServiceLevel(const StringSpan &arg);
    void setSurplusHandling(const EnumerationSpan &arg);
    void setTransfer(const EnumerationSpan &arg);

    void setDropItemIntents(const QVector<DropItemIntentSP> &arg);
    void addDropItemIntent(const DropItemIntentSP &arg);

    DropIntentQmlWrapper *toQmlWrapper(QObject *parent = nullptr) const override;

    static DropIntentSP create();

    static DropIntentSP fromJdf(QXmlStreamReader &xmlReader, const QString &jobId, bool sanitize = false);
    void toJdf(QXmlStreamWriter &jdfWriter);

signals:
    void earliestChanged(const Proof::Jdf::TimeSpan &arg);
    void earliestDurationChanged(const Proof::Jdf::DurationSpan &arg);
    void requiredChanged(const Proof::Jdf::TimeSpan &arg);
    void requiredDurationChanged(const Proof::Jdf::DurationSpan &arg);
    void returnMethodChanged(const Proof::Jdf::NameSpan &arg);
    void serviceLevelChanged(const Proof::Jdf::StringSpan &arg);
    void surplusHandlingChanged(const Proof::Jdf::EnumerationSpan &arg);
    void transferChanged(const Proof::Jdf::EnumerationSpan &arg);
    void dropItemIntentsChanged();

protected:
    explicit DropIntent();
    void updateSelf(const Proof::NetworkDataEntitySP &other) override;
};

} // namespace Jdf
} // namespace Proof

#endif // JDFDROPINTENT_H
